﻿#include "iec101asdu21data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu21Data::IEC101Asdu21Data()
{
	shortdata = 0;
}

IEC101Asdu21Data::~IEC101Asdu21Data()
{

}

bool IEC101Asdu21Data::init(QByteArray buff)
{
	setDefault(buff);

	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");

	shortdata = charToint(buff.data() + infaddrlen,2);
	mText.append(CharToHexStr(buff.data() + infaddrlen, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");

	return true;
}

bool IEC101Asdu21Data::init(QByteArray buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");

	shortdata = charToint(buff.data(),2);
	mText.append(CharToHexStr(buff.data(), 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");

	return true;
}

bool IEC101Asdu21Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
