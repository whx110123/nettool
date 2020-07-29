#include "iec101.h"

IEC101::IEC101()
{
	error = 0;
	masterState = STATE_INIT;
	len = 0;
	crc = 0;
	end = 0;
}

IEC101::~IEC101()
{

}

bool IEC101::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	len = 0;
	if(buff.count()<5)
	{
		error =1;
		return false;
	}
	if(*buff.data() == 0x68)
	{
		len += 6;
	}
	else if(*buff.data() == 0x10)
	{
		len += 3;
	}
	else
	{
		error =2;
		return false;
	}
	if(!apci.init(buff.left(len)))
	{
		mRecvData = buff.left(len);
		error =apci.error;
		return false;
	}
	if(apci.length > buff.count())
	{
		error = 3;
		return false;
	}
	mRecvData = buff.left(apci.length);
	masterState = apci.masterState;

	if(apci.flag1 == 0x68 && buff.count()> 9)
	{
		if(!asdu.init(buff.mid(len,apci.length1-2)))
		{
			error =asdu.error;
			return false;
		}
		masterState = asdu.masterState;
		len += apci.length1-2;

	}
	else if (apci.flag1 == 0x10 )
	{
		if(apci.length!=5)
		{
			error = 4;
			return false;
		}
	}
	else
	{
		error = 3;
		return false;
	}
	uchar crctmp = 0;
	if(apci.flag1 == 0x10)
	{
		crctmp = crcsum(buff.data(),1,2);
	}
	else if(apci.flag1 == 0x68)
	{
		crctmp = crcsum(buff.data(),4,apci.length1+3);
	}



	crc = *(buff.data() + len);
	len++;
	if(crc != crctmp)
	{
		return false;
	}

	end = *(buff.data() + len);
	len++;
	if(end != 0x16)
	{
		return false;
	}

	return true;
}

bool IEC101::init(QByteArray buff, uint addr)
{
	return false;
}

bool IEC101::init(QByteArray buff, uchar *ch)
{
	return false;
}

QString IEC101::showToText()
{
	QString text;
	text.append(apci.showToText());
	text.append(asdu.showToText());
	mText.append(CharToHexStr(crc)+"\t校验和:"+QString::number(crc) +"\r\n");
	mText.append(CharToHexStr(end)+"\t结束字符:0x16"+QString::number(end) +"\r\n");
	return text;
}

bool IEC101::createData(IECDataConfig &config)
{

	return false;
}
