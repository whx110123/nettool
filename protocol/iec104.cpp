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
	mText.clear();
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
	return mText;
}

IEC104UControl::IEC104UControl()
{
	code = 0;
	memset(reserve,0,sizeof (reserve));
}

bool IEC104UControl::init(QByteArray buff)
{
	mBAdata = buff;
	mText.clear();
	if(mBAdata.count() < 4)
	{
		error = 1;
		return false;
	}
	code = buff.at(0);

	for(int i = 0; i <3; i++)
	{
		reserve[i] = buff.at(i+1);
		if(reserve[i] != 0)
		{
			error = 1;
			return false;
		}
	}
	return true;
}

QString IEC104UControl::showToText()
{
	return mText;
}

IEC104SControl::IEC104SControl()
{
	memset(reserve,0,sizeof (reserve));
	recvNo = 0;
}

bool IEC104SControl::init(QByteArray buff)
{
	mBAdata = buff;
	mText.clear();
	if(mBAdata.count() < 4)
	{
		error = 1;
		return false;
	}
	for(int i = 0; i <2; i++)
	{
		reserve[i] = buff.at(i);
	}
	if(reserve[0] != 0x01)
	{
		error = 2;
		return false;
	}
	recvNo = (ushort )charTouint((uchar *)(buff.data()+2),2);
	if(recvNo % 2)
	{
		error = 3;
		return false;
	}
	recvNo /= 2;
	return true;
}

QString IEC104SControl::showToText()
{
	return mText;
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
	mText.clear();
	if(mBAdata.count() < 6)
	{
		error = 1;
		return false;
	}
	first = mBAdata.at(0);
	if(first != 0x68)
	{
		error = 2;
		mText.append(CharToHexStr(buff.data())+"\t启动字符不是0x68");
		return false;
	}

	mText.append(CharToHexStr(buff.data())+"\t启动字符:0x68");
	length = mBAdata.at(1);
	mText.append(CharToHexStr(buff.data()+1)+"\t长度域:"+QString::number(length));
	uchar tmp = mBAdata.at(2);
	if(tmp & 0x01)
	{
		if(tmp & 0x02)
		{
			IEC104UControl *uc = new IEC104UControl;
			if(uc->init(mBAdata.mid(2,4)))
			{
				if(control)
				{
					delete control;
				}
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
				if(control)
				{
					delete control;
				}
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
			if(control)
			{
				delete control;
			}
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
	QString text;
	text.append(mText);
	text.append(control->showToText());
	return text;
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
	mText.clear();
	if(apci)
	{
		delete apci;
	}
	if(buff.count()<6)
	{
		error =1;
		return false;
	}
	apci = new IEC104apci();
	apci->init(buff.left(6));
	return true;
}

QString IEC104::showToText()
{
	QString text;
	if(apci)
	{
		text.append(apci->showToText());
	}


	return text;
}
