#include "iec101asdu103data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu103data::IEC101asdu103data()
{

}

IEC101asdu103data::~IEC101asdu103data()
{

}

bool IEC101asdu103data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	datetime = charToDateTime(buff.data() + infaddrlen , 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + infaddrlen , 7));
	return true;
}

bool IEC101asdu103data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	datetime = charToDateTime(buff.data() , 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() , 7));
	return true;
}

QString IEC101asdu103data::showToText()
{
	return mText;
}

bool IEC101asdu103data::createData(IECDataConfig &config)
{
	return true;
}
