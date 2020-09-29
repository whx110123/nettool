﻿#include "iec103asdu40data.h"

IEC103Asdu40Data::IEC103Asdu40Data()
{
	siq = 0;
}

IEC103Asdu40Data::~IEC103Asdu40Data()
{

}

bool IEC103Asdu40Data::handle(const QByteArray& buff)
{
	siq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu40Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
