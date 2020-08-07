#include "iec101asdu50data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu50Data::IEC101Asdu50Data()
{
	floatdata = 0;
	qos = 0;
}

IEC101Asdu50Data::~IEC101Asdu50Data()
{

}

bool IEC101Asdu50Data::init(QByteArray buff)
{
	setDefault(buff);

	if(infaddrlen!=3&&infaddrlen!=2&&infaddrlen!=1)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址长度错误");
		return false;
	}
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	floatdata = charTofloat(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");

	qos = *(buff.data() + infaddrlen + 4);
	mText.append(CharToHexStr(buff.data() + infaddrlen + 4) + "\t" + qosToText(qos) + "\r\n");
	return true;
}

bool IEC101Asdu50Data::init(QByteArray buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	floatdata = charTofloat(buff.data());
	mText.append(CharToHexStr(buff.data(), 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");

	qos = *(buff.data() + 4);
	mText.append(CharToHexStr(buff.data() + 4) + "\t" + qosToText(qos) + "\r\n");
	return true;
}

bool IEC101Asdu50Data::createData(IECDataConfig &config)
{
	config.data += uintToBa(config.infaddr,infaddrlen);
	config.data += config.infdata;
	return true;
}
