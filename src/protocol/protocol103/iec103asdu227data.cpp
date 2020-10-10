﻿#include "iec103asdu227data.h"

IEC103Asdu227Data::IEC103Asdu227Data()
{
	fnam = 0;
	snam = 0;
	afq = 0;
}

IEC103Asdu227Data::~IEC103Asdu227Data()
{

}

bool IEC103Asdu227Data::handle(const QByteArray& buff)
{
	fnam = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t文件名称FNAM: " + QString::number(fnam) + "\r\n");
	len += 2;

	snam = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t节名称SNAM: " + QString::number(snam) + "\r\n");
	len++;

	afq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + afqToText(afq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

bool IEC103Asdu227Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
