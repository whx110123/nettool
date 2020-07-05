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
	mRecvData = buff;
	mText.clear();
	switch (type)
	{
	case UTYPE:
	{
		if(mRecvData.count() < 4)
		{
			error = 1;
			return false;
		}
		code = buff.at(0);
		mText.append(CharToHexStr(buff.data()) + "\tU帧报文(bit1与bit2都为1) 无编号，起控制链路等功能\r\n\t");
		int sum = 0;
		if(code & 0x80)
		{
			mText.append("(bit8):1 子站确认TESTFR，子站响应启用测试\r\n");
			mstate = STATE_TESTACT;
			sum++;
		}
		if(code & 0x40)
		{
			mText.append("(bit7):1 主站激活TESTFR，主站启用测试\r\n");
			mstate = STATE_TESTCONFIRM;
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
			mstate = STATE_CALLALL;
			sum++;
		}
		if(code & 0x04)
		{
			mText.append("(bit3):1 主站激活STARTDT，主站激活链路\r\n");
			sum++;
		}

		if(sum==0)
		{
			mText.append("\t出错！此U帧报文未包含任何控制功能\r\n");
			error = 2;
			return false;
		}
		else if(sum>1)
		{
			mText.append("\t出错！此U帧报文包含2种或2种以上控制功能\r\n");
			error = 3;
			return false;
		}

		for(int i = 0; i <3; i++)
		{
			if(buff.at(i+1) != 0)
			{
				error = 4;
				return false;
			}
			mText.append(CharToHexStr(buff.at(i+1)) + "\t固定为0x00\r\n");
		}
		break;
	}
	case STYPE:
		if(mRecvData.count() < 4)
		{
			error = 1;
			return false;
		}

		code = buff.at(0);

		if(code != 0x01)
		{
			error = 2;
			mText.append(CharToHexStr(buff.at(0)) + "\t出错！当此字节后2位bit是0和1，可以确定是S帧，但S帧其他bit必须为0，条件不满足，因此报文有问题\r\n");
			return false;
		}
		mText.append(CharToHexStr(buff.at(0)) + "\tS帧报文(bit1为1，bit2为0) 带编号，用于监视报文序号\r\n");

		if(buff.at(1) == 0x00)
		{
			mText.append(CharToHexStr(buff.at(1)) + "\t固定为0x00\r\n");
		}
		else
		{
			mText.append(CharToHexStr(buff.at(1)) + "\t出错！已确定此帧报文是S帧，但S帧这个位置固定为0，条件不满足，因此报文有问题\r\n");
			error = 3;
			return false;
		}

		remoteRecvNo = (ushort )charTouint((uchar *)(buff.data()+2),2);
		if(remoteRecvNo % 2)
		{
			mText.append(CharToHexStr(buff.data()+2,2) + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题\r\n");
			error = 3;
			return false;
		}
		remoteRecvNo /= 2;
		mText.append(CharToHexStr(buff.data()+2,2) + "\t接受序号: " + QString::number(remoteRecvNo) + "\r\n");
		mstate = STATE_TESTACT;
		break;
	case ITYPE:
		if(mRecvData.count() < 4)
		{
			error = 1;
			return false;
		}
		remoteSendNo = (ushort )charTouint((uchar *)buff.data(),2);
		remoteSendNo /= 2;
		localRecvNo = remoteSendNo+1;	//根据对面序号修改
		mText.append(CharToHexStr(buff.data(),2) + "\t发送序号: " + QString::number(remoteSendNo) + "\r\n");

		remoteRecvNo = (ushort )charTouint((uchar *)(buff.data()+2),2);
		if(remoteRecvNo % 2)
		{
			mText.append(CharToHexStr(buff.data()+2,2) + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题\r\n");
			error = 2;
			return false;
		}
		remoteRecvNo /= 2;
		localSendNo = remoteRecvNo;		//根据对面序号修改
		mText.append(CharToHexStr(buff.data()+2,2) + "\t接受序号: " + QString::number(remoteRecvNo) + "\r\n");
		mstate = STATE_NORMAL;
		break;
	default:
		break;
	}
	return true;
}

QString IEC104Control::showToText()
{
	return mText;
}

bool IEC104Control::createDate(IECDataConfig &config)
{
	if(config.isMaster)
	{
		switch (config.controltype)
		{
		case UTYPE:
			switch (config.state)
			{
			case STATE_INIT:
				config.data += 0x07;
				config.data += '\0';
				config.data += '\0';
				config.data += '\0';
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
				return false;
				break;
			}
			break;
		case STYPE:

			config.data += 0x01;
			config.data += '\0';
			config.data += uintToBa(localRecvNo<<1,2);

			break;
		case ITYPE:
			config.data += uintToBa( localSendNo<<1,2);
			config.data += uintToBa( localRecvNo<<1,2);
			localSendNo++;

			break;
		default:
			break;
		}

	}
	else
	{

	}
	return true;
}
IEC104apci::IEC104apci()
{
	error = 0;
	first = 0;
	length = 0;
}

IEC104apci::~IEC104apci()
{

}

bool IEC104apci::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	if(mRecvData.count() < 6)
	{
		error = 1;
		return false;
	}
	first = mRecvData.at(0);
	if(first != 0x68)
	{
		error = 2;
		mText.append(CharToHexStr(buff.data())+"\t启动字符不是0x68\r\n");
		return false;
	}

	mText.append(CharToHexStr(buff.data())+"\t启动字符:0x68\n");
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
	mstate = control.mstate;
	return true;

}

QString IEC104apci::showToText()
{
	QString text;
	text.append(mText);
	text.append(control.showToText());
	return text;
}

bool IEC104apci::createDate(IECDataConfig &config)
{
	config.data += 0x68;
	if(!control.createDate(config))
	{
		return false;
	}
	return true;
}


