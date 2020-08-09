﻿#include "iec101asdu13data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu13Data::IEC101Asdu13Data()
{
	floatdata = 0;
	qds = 0;
}

IEC101Asdu13Data::~IEC101Asdu13Data()
{

}

//bool IEC101Asdu13Data::init(const QByteArray &buff)
//{
//	setDefault(buff);

//	if(infaddrlen!=3&&infaddrlen!=2&&infaddrlen!=1)
//	{
//		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址长度错误");
//		return false;
//	}
//	infaddr = charTouint(buff.data(),infaddrlen);
//	mText.append("-----------------------------------------------------------------------------------------------\r\n");
//	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+ "\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");

//	floatdata = charTofloat(buff.data()+infaddrlen);
//	mText.append(CharToHexStr(buff.data()+infaddrlen,4) + "\t浮点数:"+QString::number(floatdata) + "\r\n");

//	qds = *(buff.data()+infaddrlen+4);
//	mText.append(CharToHexStr(buff.data()+infaddrlen+4) + "\t品质位:" + ivToText(qds) +"   "+ ntToText(qds)+"   "+ sbToText(qds)+"   "+ blToText(qds)+"   "+ ovToText(qds)+"\r\n");
//	return true;
//}

//bool IEC101Asdu13Data::init(const QByteArray &buff, uint addr)
//{
//	setDefault(buff);

//	infaddr = addr;
//	mText.append("-----------------------------------------------------------------------------------------------\r\n");
//	mText.append("\t信息元素地址:" + QString::number(infaddr)+ "\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");

//	floatdata = charTofloat(buff.data());
//	mText.append(CharToHexStr(buff.data(),4) + "\t浮点数:"+QString::number(floatdata) + "\r\n");

//	qds = *(buff.data()+4);
//	mText.append(CharToHexStr(buff.data()+4) + "\t品质位:" + ivToText(qds) +"   "+ ntToText(qds)+"   "+ sbToText(qds)+"   "+ blToText(qds)+"   "+ ovToText(qds)+"\r\n");
//	return true;
//}

bool IEC101Asdu13Data::handle(const QByteArray &buff)
{
	mText.append("\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");
	floatdata = charTofloat(buff.data()+len);
	mText.append(CharToHexStr(buff.data()+len,4) + "\t浮点数:"+QString::number(floatdata) + "\r\n");
	len += 4;

	qds = *(buff.data()+len);
	mText.append(CharToHexStr(buff.data()+len) + "\t品质位:" + ivToText(qds) +"   "+ ntToText(qds)+"   "+ sbToText(qds)+"   "+ blToText(qds)+"   "+ ovToText(qds)+"\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu13Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

