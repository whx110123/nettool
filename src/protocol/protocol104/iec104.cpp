#include "iec104.h"
#include "globaldefine.h"

IEC104::IEC104()
{
	error = 0;
	masterState = STATE_INIT;
}

IEC104::~IEC104()
{

}

bool IEC104::init(QByteArray buff)
{
	setDefault(buff);

	if(buff.count()<6)
	{
		error = 1;
		mText.append("出错！报文总长不满6个字节，条件不满足，因此报文有问题\r\n");
		return false;
	}

	if(!apci.init(buff.left(6)))
	{
		mRecvData = buff.left(6);
		error =apci.error;
		return false;
	}
	mRecvData = buff.left(apci.length+2);
	masterState = apci.masterState;
	slaveState = apci.slaveState;
	len = apci.length+2;
	if(len > buff.count())
	{
		error = 3;
		return false;
	}
	if(apci.control.type == ITYPE && buff.count()< 7)
	{
		error = 3;
		return false;
	}
	else if (apci.control.type == UTYPE||apci.control.type == STYPE )
	{
		if(len!=6)
		{
			error = 4;
			return false;
		}
		else
		{
			return true;
		}
	}

	if(!asdu.init(buff.mid(6,len-6)))
	{
		error =asdu.error;
		return false;
	}
	masterState = asdu.masterState;
	slaveState = asdu.slaveState;
	return true;
}


QString IEC104::showToText()
{
	QString text(mText);
	if(len >5)
	{
		text.append(apci.showToText());
	}
	if(len >6 && apci.control.type == ITYPE)
	{
		text.append(asdu.showToText());
	}
	return text;
}

bool IEC104::createData(IECDataConfig &config)
{
	config.data.clear();
	if(config.isMaster)
	{
		switch (config.masterState)
		{
		case STATE_INIT:
		case STATE_TESTACT:
		case STATE_TESTCONFIRM:
			config.controltype = UTYPE;
			break;
		case STATE_NORMAL:
			config.controltype = STYPE;
			break;
		case STATE_CALLALL:
			config.controltype = ITYPE;
			config.asdutype = 0x64;
			config.vsq = 1;
			config.cot = 0x06;
			break;
		case STATE_USER:
			config.controltype = ITYPE;	
			break;
		case STATE_HOTKEY:
			break;
		default:
			return false;
			break;
		}
	}
	else
	{
		switch (config.masterState)
		{
		case STATE_NODATA:
			return false;
			break;
		case STATE_INIT:
		case STATE_TESTACT:
		case STATE_TESTCONFIRM:
		case STATE_NORMAL:
		case STATE_CALLALL:
			config.controltype = UTYPE;
			break;
		case STATE_USER:
			config.controltype = ITYPE;
			break;
		case STATE_HOTKEY:
			break;
		default:
			return false;
			break;
		}
	}

	if(!apci.createData(config))
	{
		return false;
	}
	if(config.asdutype >0)
	{
		if(!asdu.createData(config))
		{
			return false;
		}
	}
	if(config.data.size()<5)
	{
		return false;
	}
	if(config.masterState == STATE_USER)
	{
		config.data.append(config.userdata);
	}
	char len = config.data.size()-2;
	config.data.replace(1,1,&len,1);
	return true;
}


