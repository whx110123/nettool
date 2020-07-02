#include "iec104.h"
#include "globaldefine.h"


IEC104Control::IEC104Control()
{

}

IEC104Control::~IEC104Control()
{

}



IEC104IControl::IEC104IControl()
{
	sendNo = 0;
	recvNo = 0;
}

IEC104IControl::~IEC104IControl()
{

}

bool IEC104IControl::init(QByteArray buff)
{
	mBAdata = buff;
	if(mBAdata.count() < 4)
	{
		error = 1;
		return false;
	}
	sendNo = (ushort )charTouint((uchar *)buff.data(),2);
	sendNo /= 2;
	recvNo = (ushort )charTouint((uchar *)(buff.data()+2),2);
	if(recvNo % 2)
	{
		error = 2;
		return false;
	}
	recvNo /= 2;
	return true;
}

QString IEC104IControl::showToText()
{

}

IEC104UControl::IEC104UControl()
{

}

bool IEC104UControl::init(QByteArray buff)
{
	mBAdata = buff;
	if(mBAdata.count() < 4)
	{
		error = 1;
		return false;
	}
}

QString IEC104UControl::showToText()
{

}

IEC104SControl::IEC104SControl()
{

}

bool IEC104SControl::init(QByteArray buff)
{
	mBAdata = buff;
	if(mBAdata.count() < 4)
	{
		error = 1;
		return false;
	}
}

QString IEC104SControl::showToText()
{

}

IEC104apci::IEC104apci()
{
	error = 0;
	first = 0;
	length = 0;
	control = NULL;
}

IEC104apci::~IEC104apci()
{
	if(control)
	{
		delete control;
		control = NULL;
	}
}

bool IEC104apci::init(QByteArray buff)
{
	mBAdata = buff;
	if(mBAdata.count() < 6)
	{
		error = 1;
		return false;
	}
	first = mBAdata.at(0);
	if(first != 0x68)
	{
		error = 2;
		return false;
	}
	length = mBAdata.at(1);
	uchar tmp = mBAdata.at(2);
	if(tmp & 0x01)
	{
		if(tmp & 0x02)
		{
			IEC104UControl *uc = new IEC104UControl;
			if(uc->init(mBAdata.mid(2,4)))
			{
				control = uc;
				control->type = UTYPE;
			}
			else
			{
				if(uc)
				{
					delete uc;
					uc = NULL;
				}
				error = 3;
				return false;
			}

		}
		else
		{
			IEC104SControl *sc = new IEC104SControl;
			if(sc->init(mBAdata.mid(2,4)))
			{
				control = sc;
				control->type = STYPE;
			}
			else
			{
				if(sc)
				{
					delete sc;
					sc = NULL;
				}
				error = 4;
				return false;
			}
		}
	}
	else
	{
		IEC104IControl *ic = new IEC104IControl;
		if(ic->init(mBAdata.mid(2,4)))
		{
			control = ic;
			control->type = ITYPE;
		}
		else
		{
			if(ic)
			{
				delete ic;
				ic = NULL;
			}
			error = 5;
			return false;
		}
	}
	return true;

}

QString IEC104apci::showToText()
{

}

IEC104::IEC104()
{
	apci = NULL;
	error = 0;
}

IEC104::~IEC104()
{
	if(apci)
	{
		delete apci;
		apci = NULL;
	}
}

bool IEC104::init(QByteArray buff)
{
	mBAdata = buff;
	apci = new IEC104apci();
	apci->init(buff.left(6));
}

QString IEC104::showToText()
{

}
