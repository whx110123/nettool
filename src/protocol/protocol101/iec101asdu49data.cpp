﻿#include "iec101asdu49data.h"

IEC101Asdu49Data::IEC101Asdu49Data()
{
	shortdata = 0;
	qos = 0;
}

IEC101Asdu49Data::~IEC101Asdu49Data()
{

}

bool IEC101Asdu49Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t标度化值:" + QString::number(shortdata) + "\r\n");
	len += 2;

	qos = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + qosToText(qos) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC101Asdu49Data::createData(IECDataConfig& config)
{
	config.data += uintToBa(config.infaddr, infaddrlen);
	config.data += config.infdata;
	return true;
}
