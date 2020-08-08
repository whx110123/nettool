﻿#include "iec103asdu2data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC103Asdu2Data::IEC103Asdu2Data()
{
	dpi = 0;

}

IEC103Asdu2Data::~IEC103Asdu2Data()
{

}

bool IEC103Asdu2Data::init(const QByteArray &buff)
{
	setDefault(buff);

	inf = *(buff.data() + len);

	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;

	dpi = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(dpi) + "\r\n");
	len++;

	ret = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len,2) + "\t相对时间RET:" + QString::number(ret) + "\r\n");
	len += 2;

	fan = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	len += 2;

	if(buff.length() < 20)
	{
		datetime1 = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 4));
		len += 4;
	}
	else
	{
		datetime1 = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 7));
		len += 7;
		datetime2 = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
		mText.append(timeToText(buff.data() + len, 7));
		len += 7;
	}
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu2Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
