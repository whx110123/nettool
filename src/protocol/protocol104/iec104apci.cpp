#include "iec104apci.h"
#include "globaldefine.h"

IEC104Control::IEC104Control()
{
	type = 0;
	code = 0;
	remoteSendNo = 0;
	remoteRecvNo = 0;
	localSendNo = 0;
	localRecvNo = 0;
}

IEC104Control::~IEC104Control()
{

}

bool IEC104Control::init(QByteArray buff)
{
	setDefault(buff);

	masterState = STATE_NORMAL;
	slaveState = STATE_NORMAL;
	switch (type)
	{
	case UTYPE:
	{
		if(mRecvData.count() < 4)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度小于4");
			return false;
		}
		code = buff.at(0);
		mText.append(CharToHexStr(buff.data()) + "\tU帧报文(bit1与bit2都为1) 无编号，起控制链路等功能\r\n\t");
		int sum = 0;
		if(code & 0x80)
		{
			mText.append("(bit8):1 子站确认TESTFR，子站响应启用测试\r\n");
			masterState = STATE_TESTACT;
			slaveState = STATE_TESTACT;
			sum++;
		}
		if(code & 0x40)
		{
			mText.append("(bit7):1 主站激活TESTFR，主站启用测试\r\n");
			masterState = STATE_TESTCONFIRM;
			slaveState = STATE_TESTCONFIRM;
			sum++;
		}
		if(code & 0x20)
		{
			mText.append("(bit6):1 子站确认STOPDT，子站响应停止链路\r\n");
			sum++;
		}
		if(code & 0x10)
		{
			mText.append("(bit5):1 主站激活STOPDT，主站停止链路\r\n");
			sum++;
		}
		if(code & 0x08)
		{
			mText.append("(bit4):1 子站确认STARTDT，子站响应激活链路\r\n");
			masterState = STATE_CALLALL;
			sum++;
		}
		if(code & 0x04)
		{
			mText.append("(bit3):1 主站激活STARTDT，主站激活链路\r\n");
			slaveState = STATE_INIT;
			sum++;
		}

		if(sum==0)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！此U帧报文未包含任何控制功能");
			return false;
		}
		else if(sum>1)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！此U帧报文包含2种或2种以上控制功能");
			return false;
		}

		for(int i = 0; i <3; i++)
		{
			if(buff.at(i+1) != 0)
			{
				error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！出现不为0的数据");
				return false;
			}
			mText.append(CharToHexStr(buff.at(i+1)) + "\t固定为0x00\r\n");
		}
		break;
	}
	case STYPE:
		if(mRecvData.count() < 4)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}

		code = buff.at(0);

		if(code != 0x01)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.at(0)) + "\t出错！当此字节后2位bit是0和1，可以确定是S帧，但S帧其他bit必须为0，条件不满足，因此报文有问题");
			return false;
		}
		mText.append(CharToHexStr(buff.at(0)) + "\tS帧报文(bit1为1，bit2为0) 带编号，用于监视报文序号\r\n");

		if(buff.at(1) == 0x00)
		{
			mText.append(CharToHexStr(buff.at(1)) + "\t固定为0x00\r\n");
		}
		else
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.at(1)) + "\t出错！已确定此帧报文是S帧，但S帧这个位置固定为0，条件不满足，因此报文有问题");
			return false;
		}

		remoteRecvNo = (ushort )charTouint((uchar *)(buff.data()+2),2);
		if(remoteRecvNo % 2)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data()+2,2) + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题");
			return false;
		}
		remoteRecvNo /= 2;
		mText.append(CharToHexStr(buff.data()+2,2) + "\t接受序号: " + QString::number(remoteRecvNo) + "\r\n");
		masterState = STATE_TESTACT;
		slaveState = STATE_NORMAL;
		break;
	case ITYPE:
		if(mRecvData.count() < 4)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}
		remoteSendNo = (ushort )charTouint((uchar *)buff.data(),2);
		remoteSendNo /= 2;
		localRecvNo = remoteSendNo+1;	//根据对面序号修改
		mText.append(CharToHexStr(buff.data(),2) + "\t发送序号: " + QString::number(remoteSendNo) + "\r\n");

		remoteRecvNo = (ushort )charTouint((uchar *)(buff.data()+2),2);
		if(remoteRecvNo % 2)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data()+2,2) + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题");
			return false;
		}
		remoteRecvNo /= 2;
		localSendNo = remoteRecvNo;		//根据对面序号修改
		mText.append(CharToHexStr(buff.data()+2,2) + "\t接受序号: " + QString::number(remoteRecvNo) + "\r\n");
		masterState = STATE_NORMAL;
		slaveState = STATE_NORMAL;
		break;
	default:
		break;
	}
	return true;
}


bool IEC104Control::createData(IECDataConfig &config)
{
	if (config.isMaster)
	{
		switch (config.controltype)
		{
		case UTYPE:
			switch (config.masterState)
			{
			case STATE_INIT:
				config.data += 0x07;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			case STATE_NORMAL:
				break;
			case STATE_TESTACT:
				config.data += 0x43;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			case STATE_TESTCONFIRM:
				config.data += 0x83;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			default:
				error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的主站状态");
				return false;
				break;
			}
			config.asdutype = 0;
			break;
		case STYPE:

			config.data += 0x01;
			config.data += '\0';
			config.data += uintToBa(localRecvNo << 1, 2);
			config.asdutype = 0;
			break;
		case ITYPE:
			config.data += uintToBa(localSendNo << 1, 2);
			config.data += uintToBa(localRecvNo << 1, 2);
			localSendNo++;

			break;
		default:
			break;
		}
	}
	else
	{
		switch (config.controltype)
		{
		case UTYPE:
			switch (config.slaveState)
			{
			case STATE_INIT:
				config.data += 0x0b;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			case STATE_NORMAL:
				break;
			case STATE_TESTACT:
				config.data += 0x43;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			case STATE_TESTCONFIRM:
				config.data += 0x83;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
				break;
			default:
				error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的子站状态");
				return false;
				break;
			}
			config.asdutype = 0;
			break;
		case STYPE:
			config.data += 0x01;
			config.data += '\0';
			config.data += uintToBa(localRecvNo << 1, 2);
			config.asdutype = 0;
			break;
		case ITYPE:
			config.data += uintToBa(localSendNo << 1, 2);
			config.data += uintToBa(localRecvNo << 1, 2);
			localSendNo++;
			break;
		default:
			break;
		}
	}

	return true;
}
IEC104Apci::IEC104Apci()
{
	first = 0;
	length = 0;
}

IEC104Apci::~IEC104Apci()
{

}

bool IEC104Apci::init(QByteArray buff)
{
	setDefault(buff);

	if(mRecvData.count() < 6)
	{
		error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度不满6个字节，条件不满足，因此报文有问题");
		return false;
	}
	first = mRecvData.at(0);
	if(first != 0x68)
	{
		error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data())+"\t启动字符不是0x68");
		return false;
	}

	mText.append(CharToHexStr(buff.data())+"\t启动字符:0x68\r\n");
	length = mRecvData.at(1);
	mText.append(CharToHexStr(buff.data()+1)+"\t长度域:"+QString::number(length) +"\r\n");
	uchar tmp = mRecvData.at(2);

	if(tmp & 0x01)
	{
		if(tmp & 0x02)
		{
			control.type = UTYPE;
		}
		else
		{
			control.type = STYPE;
		}
	}
	else
	{
		control.type = ITYPE;

	}
	if(!control.init(mRecvData.mid(2,4)))
	{
		return false;
	}
	masterState = control.masterState;
	slaveState = control.slaveState;
	return true;

}


QString IEC104Apci::showToText()
{
	QString text(mText);
	text.append(control.showToText());
	return text;
}

bool IEC104Apci::createData(IECDataConfig &config)
{
	config.data += 0x68;
	config.data += '\0';
	if(!control.createData(config))
	{
		return false;
	}
	return true;
}


