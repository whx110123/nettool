﻿#include "iec101asdu32data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu32Data::IEC101Asdu32Data()
{
	vti = 0;
	qds = 0;
}

IEC101Asdu32Data::~IEC101Asdu32Data()
{

}

bool IEC101Asdu32Data::init(QByteArray buff)
{
	setDefault(buff);

	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	vti = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + vtiToText(vti)  + "\r\n");
	qds = *(buff.data() + infaddrlen + 1);
	mText.append(CharToHexStr(buff.data() + infaddrlen + 1) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	datetime = charToDateTime(buff.data() + infaddrlen + 2, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + infaddrlen + 2, 7));
	return true;
}

bool IEC101Asdu32Data::init(QByteArray buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	vti = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + vtiToText(vti) + "\r\n");
	qds = *(buff.data() + 1);
	mText.append(CharToHexStr(buff.data() + 1) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	datetime = charToDateTime(buff.data() + 2, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + 2, 7));
	return true;
}

bool IEC101Asdu32Data::createData(IECDataConfig &config)
{
	return false;
}