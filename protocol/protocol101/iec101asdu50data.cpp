#include "iec101asdu50data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu50data::IEC101asdu50data()
{
	floatdata = 0;
	qos = 0;
}

IEC101asdu50data::~IEC101asdu50data()
{

}

bool IEC101asdu50data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	floatdata = charTofloat(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");

	qos = *(buff.data() + infaddrlen + 4);
	mText.append(CharToHexStr(buff.data() + infaddrlen + 4) + "\t" + qosToText(qos) + "\r\n");
	return true;
}

bool IEC101asdu50data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	floatdata = charTofloat(buff.data());
	mText.append(CharToHexStr(buff.data(), 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");

	qos = *(buff.data() + 4);
	mText.append(CharToHexStr(buff.data() + 4) + "\t" + qosToText(qos) + "\r\n");
	return true;
}

QString IEC101asdu50data::showToText()
{
	return mText;
}

bool IEC101asdu50data::createData(IECDataConfig &config)
{
	return true;
}