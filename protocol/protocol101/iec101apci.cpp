#include "iec101apci.h"
#include "functotext.h"

IEC101Code::IEC101Code()
{
	mcode = 0;
}

IEC101Code::~IEC101Code()
{

}

bool IEC101Code::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	mcode = *buff.data();

	mText.append(CharToHexStr(buff.data())+"\t" +prmToText(mcode) +"\r\n");
	if(mcode & 0x40)
	{
		mText.append(fcbToText(mcode)+"\r\n\t"+ fcvToText(mcode) +"\r\n\t"+ cw1ToText(mcode)+"\r\n");
	}
	else
	{
		mText.append(acdToText(mcode)+"\r\n\t" + dfcToText(mcode)+"\r\n\t" + cw2ToText(mcode)+"\r\n");
	}
	return true;
}

QString IEC101Code::showToText()
{
	return mText;
}

bool IEC101Code::createData(IECDataConfig &config)
{

	return false;
}
IEC101apci::IEC101apci()
{
	error = 0;
	mstate = STATE_INIT;
	len = 0;
	flag1 = 0;
	length1 = 0;
	length2 = 0;
	flag2 = 0;
	addr = 0;
}

IEC101apci::~IEC101apci()
{

}

bool IEC101apci::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	len = 0;
	if(mRecvData.count() < 5)
	{
		error = 1;
		return false;
	}
	flag1 = *buff.data();

	if(flag1 == 0x68)
	{
		mText.append(CharToHexStr(buff.data()+len)+"\t启动字符:0x68\r\n");
		len++;

		length1 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data()+len)+"\t长度域1:"+QString::number(length1) +"\r\n");
		len++;

		length2 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data()+len)+"\t长度域2:"+QString::number(length2) +"\r\n");
		len++;

		if(length1 != length2)
		{
			return false;
		}

		flag2 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data()+len)+"\t启动字符:0x68\r\n");
		len++;
		if(flag2 != 0x68)
		{
			return false;
		}
		length = length1 + 6;
	}
	else if (flag1 == 0x10)
	{
		mText.append(CharToHexStr(buff.data()+len)+"\t启动字符:0x10\r\n");
		len++;
		length = 5;
	}
	else
	{
		error = 2;
		mText.append(CharToHexStr(buff.data())+"\t启动字符不是0x68\r\n");
		return false;
	}

	if(!code.init(buff.mid(len,1)))
	{
		return false;
	}
	mstate = code.mstate;
	mText.append(code.showToText());
	len++;

	addr = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data()+len)+"\t地址域:"+QString::number(addr) +"\r\n");
	len++;

	return true;

}

QString IEC101apci::showToText()
{
	QString text;
	text.append(mText);
	return text;
}

bool IEC101apci::createData(IECDataConfig &config)
{
//	config.data += 0x68;
//	config.data += '\0';
//	if(!code.createData(config))
//	{
//		return false;
//	}
	return false;
}
