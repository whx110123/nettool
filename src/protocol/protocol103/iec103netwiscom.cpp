#include "iec103netwiscom.h"

IEC103NetWiscom::IEC103NetWiscom()
{
	error = 0;
	masterState = STATE_INIT;
}

IEC103NetWiscom::~IEC103NetWiscom()
{

}

bool IEC103NetWiscom::init(QByteArray buff)
{
	setDefault(buff);

	if(buff.count()<15)
	{
		error =1;
		mText.append("出错！报文总长不满15个字节，条件不满足，因此报文有问题\r\n");
		return false;
	}

	if(!apci.init(buff.left(15)))
	{
		mRecvData = buff.left(15);
		error =apci.error;
		return false;
	}
	mRecvData = buff.left(apci.length+3);
	masterState = apci.masterState;
	len = apci.length+3;
	if(len > buff.count())
	{
		error = 3;
		return false;
	}
	if(apci.control.type == ITYPE && buff.count()< 16)
	{
		error = 3;
		return false;
	}
	else if (apci.control.type == UTYPE||apci.control.type == STYPE )
	{
		if(len!=15)
		{
			error = 4;
			return false;
		}
		else
		{
			return true;
		}
	}

	if(!asdu.init(buff.mid(15,len-15)))
	{
		error =asdu.error;
		return false;
	}
	masterState = asdu.masterState;
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
//	config.data.clear();
//	if(config.isMaster)
//	{
//		switch (config.state)
//		{
//		case STATE_INIT:
//		case STATE_TESTACT:
//		case STATE_TESTCONFIRM:
//			config.controltype = UTYPE;
//			break;
//		case STATE_NORMAL:
//			config.controltype = STYPE;
//			break;
//		case STATE_CALLALL:
//			config.controltype = ITYPE;
//			config.asdutype = 0x64;
//			config.vsq = 1;
//			config.cot = 0x06;
//			break;
//		case STATE_USER:
//			config.controltype = ITYPE;
//			config.asdutype = 0;
//			break;
//		default:
//			break;
//		}
//	}
//	else
//	{

//	}

//	if(!apci.createData(config))
//	{
//		return false;
//	}
//	if(config.asdutype >0)
//	{
//		if(!asdu.createData(config))
//		{
//			return false;
//		}
//	}
//	if(config.data.size()<5)
//	{
//		return false;
//	}
//	char len = config.data.size()-2;
//	config.data.replace(1,1,&len,1);
	return false;
}
