#include "iec101.h"

IEC101::IEC101()
{
	masterState = STATE_INIT;
	crc = 0;
	end = 0;
}

IEC101::~IEC101()
{

}

bool IEC101::init(QByteArray buff)
{
	setDefault(buff);

	if(buff.count()<5)
	{
		error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度小于5");
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
		error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文头错误");
		return false;
	}
	if(!apci.init(buff.left(len)))
	{
		mRecvData = buff.left(len);
		return false;
	}
	if(apci.length > buff.count())
	{
		error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}
	mRecvData = buff.left(apci.length);
	masterState = apci.masterState;

	if(apci.flag1 == 0x68 && buff.count()> 9)
	{
		if(!asdu.init(buff.mid(len,apci.length1-2)))
		{
			return false;
		}
		masterState = asdu.masterState;
		len += apci.length1-2;

	}
	else if (apci.flag1 == 0x10 )
	{
		if(apci.length!=5)
		{
			error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
			return false;
		}
	}
	else
	{
		error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
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
		error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！校验错误");
		return false;
	}

	end = *(buff.data() + len);
	len++;
	if(end != 0x16)
	{
		error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文结束位错误");
		return false;
	}

	return true;
}


QString IEC101::showToText()
{
	QString text;
	text.append(apci.showToText());
	if(apci.flag1 == 0x68)
	{
		text.append(asdu.showToText());
	}
	mText.append(CharToHexStr(crc)+"\t校验和:"+QString::number(crc) +"\r\n");
	mText.append(CharToHexStr(end)+"\t结束字符:0x16"+QString::number(end) +"\r\n");
	return text;
}

bool IEC101::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
