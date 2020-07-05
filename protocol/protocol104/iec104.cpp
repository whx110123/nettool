#include "iec104.h"
#include "globaldefine.h"

#include <iec101asdu1.h>
#include <iec101asdu100.h>
#include <iec101asdu13.h>

IEC104::IEC104()
{

	asdu = NULL;
	error = 0;
	mstate = STATE_INIT;
}

IEC104::~IEC104()
{

	if(asdu)
	{
		delete asdu;
		asdu = NULL;
	}
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
		error =apci.error;
		return false;
	}
	mstate = apci.mstate;
	if(apci.length+2 < buff.count())
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
		if(buff.count()> 6||apci.length!=4)
		{
			error = 4;
			return false;
		}
		else
		{
			return true;
		}
	}
	if(asdu)
	{
		delete asdu;
		asdu = NULL;
	}
	asdu = CreateAsdu(*(buff.data()+6));
	if(!asdu)
	{
		error = 5;
		return false;
	}
	if(!asdu->init(buff.mid(6,apci.length-4)))
	{
		error =asdu->error;
		delete asdu;
		asdu = NULL;
		return false;
	}
	return true;
}

QString IEC104::showToText()
{
	QString text;

	text.append(apci.showToText());

	if(asdu)
	{
		text.append(asdu->showToText());
	}

	return text;
}

bool IEC104::createDate(IECDataConfig &config)
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
			config.asdutype = 0;
			break;
		case STATE_NORMAL:
			config.controltype = STYPE;
			config.asdutype = 0;
			break;
		case STATE_CALLALL:
			config.controltype = ITYPE;
			config.asdutype = 0x64;
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

	if(!apci.createDate(config))
	{
		return false;
	}
	if(config.asdutype >0)
	{
		if(asdu)
		{
			delete asdu;
			asdu = NULL;
		}
		asdu = CreateAsdu(config.asdutype);
		if(!asdu)
		{
			error = 5;
			return false;
		}
		if(!asdu->createDate(config))
		{
			return false;
		}
	}
	if(config.data.size()<5)
	{
		return false;
	}
	char len = config.data.size()-1;
	config.data.insert(1,len);
	return true;
}

IEC101asdu *IEC104::CreateAsdu(uchar type)
{
	IEC101asdu *asdu = NULL;
	switch (type)
	{
	case 1:
		asdu = new IEC101asdu1;
		break;
	case 13:
		asdu = new IEC101asdu13;
		break;
	case 100:
		asdu = new IEC101asdu100;
		break;
	default:
		break;

	}
	return asdu;
}
