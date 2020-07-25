#include "iec101asdu70data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu70Data::IEC101Asdu70Data()
{
	coi = 0;
	infaddr = 0;
}

IEC101Asdu70Data::~IEC101Asdu70Data()
{

}

bool IEC101Asdu70Data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(),infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+"\r\n");
	coi = *(buff.data()+infaddrlen);
	mText.append(CharToHexStr(buff.data()+infaddrlen) + "\t" + coiToText(coi) +"\r\n");
	return true;
}

bool IEC101Asdu70Data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) +"\r\n");
	coi = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + coiToText(coi) +"\r\n");
	return true;
}

QString IEC101Asdu70Data::showToText()
{
	return mText;
}

bool IEC101Asdu70Data::createData(IECDataConfig &config)
{
	return true;
}

