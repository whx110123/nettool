#include "iec103com.h"

IEC103COM::IEC103COM()
{
	masterState = STATE_INIT;
	crc = 0;
	end = 0;
}

IEC103COM::~IEC103COM()
{

}

bool IEC103COM::init(const QByteArray &buff)
{
	setDefault(buff);

	if(buff.count()<5)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度小于5");
		return false;
	}
	int APCI_LEN = 0;
	if(*buff.data() == 0x68)
	{
		APCI_LEN = 6;
	}
	else if(*buff.data() == 0x10)
	{
		APCI_LEN = 3;
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文头错误");
		return false;
	}
	if(!apci.init(buff.left(APCI_LEN)))
	{
		mRecvData = buff.left(APCI_LEN);
		return false;
	}
	len = APCI_LEN + apci.length1;
	masterState = apci.masterState;
	slaveState = apci.slaveState;
	if(len > buff.count())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	mRecvData = buff.left(len);

	if(apci.flag1 == 0x68 && buff.count()> APCI_LEN+3)
	{
		if(!asdu.init(buff.mid(APCI_LEN,len-APCI_LEN-2)))
		{
			return false;
		}
		masterState = asdu.masterState;
		slaveState = asdu.slaveState;
	}
	else if (apci.flag1 == 0x10 )
	{
		if(len!=APCI_LEN+2)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}

	uchar crctmp = crcsum(buff.data(),APCI_LEN-2,len-3);
	crc = *(buff.data() + len-2);
	if(crc != crctmp)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！校验错误");
		return false;
	}

	end = *(buff.data() + len-1);
	if(end != 0x16)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文结束位错误");
		return false;
	}
	return true;
}


QString IEC103COM::showToText()
{
	QString text;
	text.append(apci.showToText());
	if(apci.flag1 == 0x68)
	{
		text.append(asdu.showToText());
	}
	text.append(CharToHexStr(crc)+"\t校验和\r\n");
	text.append(CharToHexStr(end)+"\t结束字符\r\n");
	return text;
}

bool IEC103COM::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

