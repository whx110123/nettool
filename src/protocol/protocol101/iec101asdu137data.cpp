#include "iec101asdu137data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu137Data::IEC101Asdu137Data()
{
	shortdata = 0;
}

IEC101Asdu137Data::~IEC101Asdu137Data()
{

}

//bool IEC101Asdu137Data::init(const QByteArray &buff)
//{
//	setDefault(buff);

//	if(infaddrlen!=3&&infaddrlen!=2&&infaddrlen!=1)
//	{
//		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址长度错误");
//		return false;
//	}
//	infaddr = charTouint(buff.data(), infaddrlen);
//	mText.append("-----------------------------------------------------------------------------------------------\r\n");
//	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");

//	shortdata = charToint(buff.data() + infaddrlen, 2);
//	mText.append(CharToHexStr(buff.data() + infaddrlen, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");

//	return true;
//}

//bool IEC101Asdu137Data::init(const QByteArray &buff, uint addr)
//{
//	setDefault(buff);

//	infaddr = addr;
//	mText.append("-----------------------------------------------------------------------------------------------\r\n");
//	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");

//	shortdata = charToint(buff.data(), 2);
//	mText.append(CharToHexStr(buff.data(), 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");

//	return true;
//}

bool IEC101Asdu137Data::handle(const QByteArray &buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");
	len += 2;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu137Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
