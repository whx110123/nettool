#include "iec104.h"
#include "globaldefine.h"

#include <iec101asdu1data.h>
#include <iec101asdu100data.h>
#include <iec101asdu13data.h>
#include <iec101asdu70data.h>

IEC104::IEC104()
{


	error = 0;
	mstate = STATE_INIT;
}

IEC104::~IEC104()
{

}

bool IEC104::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	if(buff.count()<6)
	{
		error =1;
		return false;
	}

	if(!apci.init(buff.left(6)))
	{
		mRecvData = buff.left(6);
		error =apci.error;
		return false;
	}
	mRecvData = buff.left(apci.length+2);
	mstate = apci.mstate;
	if(apci.length+2 > buff.count())
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
		if(apci.length!=4)
		{
			error = 4;
			return false;
		}
		else
		{
			return true;
		}
	}

	if(!asdu.init(buff.mid(6,apci.length-4)))
	{
		error =asdu.error;
		return false;
	}
	mstate = asdu.mstate;
	return true;
}

QString IEC104::showToText()
{
	QString text;

	text.append(apci.showToText());

	text.append(asdu.showToText());


	return text;
}

bool IEC104::createData(IECDataConfig &config)
{
	config.data.clear();
	if(config.isMaster)
	{
		switch (config.state)
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
			config.asdutype = 0;
			break;
		default:
			break;
		}
	}
	else
	{

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
	char len = config.data.size()-2;
	config.data.replace(1,1,&len,1);
	return true;
}


