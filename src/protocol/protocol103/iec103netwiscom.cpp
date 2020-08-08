#include "iec103netwiscom.h"

IEC103NetWiscom::IEC103NetWiscom()
{
	masterState = STATE_INIT;
}

IEC103NetWiscom::~IEC103NetWiscom()
{

}

bool IEC103NetWiscom::init(const QByteArray &buff)
{
	setDefault(buff);
	const int APCI_LEN = 15;			//APCI总字节数
	const int LENGTH_LEN = 2;			//长度域字节数
	if(buff.count() < APCI_LEN)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！报文总长不满%1个字节，条件不满足，因此报文有问题\r\n").arg(APCI_LEN));
		return false;
	}

	if(!apci.init(buff.left(APCI_LEN)))
	{
		mRecvData = buff.left(APCI_LEN);
		return false;
	}
	len = apci.length+LENGTH_LEN+1;
	masterState = apci.masterState;
	slaveState = apci.slaveState;
	if(len > buff.count())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	mRecvData = buff.left(len);
	if(apci.control.type == ITYPE && buff.count()<= APCI_LEN)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	else if (apci.control.type == UTYPE||apci.control.type == STYPE )
	{
		if(len!=APCI_LEN)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}
		else
		{
			return true;
		}
	}

	if(!asdu.init(buff.mid(APCI_LEN,len-APCI_LEN)))
	{
		return false;
	}
	masterState = asdu.masterState;
	slaveState = asdu.slaveState;
	return true;

}


QString IEC103NetWiscom::showToText()
{
	QString text(mText);
	if(len >14)
	{
		text.append(apci.showToText());
	}
	if(len >15 && apci.control.type == ITYPE)
	{
		text.append(asdu.showToText());
	}
	return text;
}

bool IEC103NetWiscom::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
