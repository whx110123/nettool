﻿#include "iec103asdu51data.h"
#include "functotext.h"
IEC103Asdu51Data::IEC103Asdu51Data()
{
	shortdata = 0;
	qds = 0;
}

IEC103Asdu51Data::~IEC103Asdu51Data()
{

}

bool IEC103Asdu51Data::handle(const QByteArray &buff)
{
	shortdata = charToshortwithQ(buff.data() + len);
	qds = *(buff.data()+len);
	mText.append(CharToHexStr(buff.data() + len,2) + "\tGID:带品质描述词的被测值(bit4-16):" + QString::number(shortdata) + "\r\n\t"+ ovToText(qds) + "   "+erToText(qds)+"\r\n");
	len += 2;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu51Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
