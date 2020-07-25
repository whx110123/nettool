﻿#include "iec103asdu1data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC103Asdu1Data::IEC103Asdu1Data()
{
	dpi = 0;
	sin = 0;
}

IEC103Asdu1Data::~IEC103Asdu1Data()
{

}

bool IEC103Asdu1Data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	len = 0;

	inf = *(buff.data() + len);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;
	dpi = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(dpi) + "\r\n");
	len++;
	datetime = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 4));
	len += 4;
	sin = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data()) + "\tGID:附加信息SIN:" + QString::number(sin));
	len++;
	return true;
}

bool IEC103Asdu1Data::init(QByteArray buff, uint addr)
{
	return false;
}

QString IEC103Asdu1Data::showToText()
{
	return mText;
}

bool IEC103Asdu1Data::createData(IECDataConfig &config)
{
	return false;
}
