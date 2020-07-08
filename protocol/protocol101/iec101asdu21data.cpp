#include "iec101asdu21data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu21data::IEC101asdu21data()
{
	shortdata = 0;
}

IEC101asdu21data::~IEC101asdu21data()
{

}

bool IEC101asdu21data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	shortdata = charToint(buff.data() + infaddrlen,2);
	mText.append(CharToHexStr(buff.data() + infaddrlen, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");

	return true;
}

bool IEC101asdu21data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	shortdata = charToint(buff.data(),2);
	mText.append(CharToHexStr(buff.data(), 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");

	return true;
}

QString IEC101asdu21data::showToText()
{
	return mText;
}

bool IEC101asdu21data::createData(IECDataConfig &config)
{
	return true;
}
