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
	setDefault(buff);

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

bool IEC101Code::createData(IECDataConfig &config)
{

	return false;
}
IEC101Apci::IEC101Apci()
{
	error = 0;
	masterState = STATE_INIT;
	len = 0;
	flag1 = 0;
	length1 = 0;
	length2 = 0;
	flag2 = 0;
	addr = 0;
}

IEC101Apci::~IEC101Apci()
{

}

bool IEC101Apci::init(QByteArray buff)
{
	setDefault(buff);

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
	masterState = code.masterState;
	mText.append(code.showToText());
	len++;

	addr = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data()+len)+"\t地址域:"+QString::number(addr) +"\r\n");
	len++;

	return true;

}


bool IEC101Apci::createData(IECDataConfig &config)
{
//	config.data += 0x68;
//	config.data += '\0';
//	if(!code.createData(config))
//	{
//		return false;
//	}
	return false;
}
