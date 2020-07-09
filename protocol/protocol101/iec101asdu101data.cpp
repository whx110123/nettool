#include "iec101asdu101data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu101data::IEC101asdu101data()
{
	qcc = 0;
}

IEC101asdu101data::~IEC101asdu101data()
{

}

bool IEC101asdu101data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	qcc = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + rqtToText(qcc) + "   " + frzToText(qcc)  + "\r\n");
	return true;
}

bool IEC101asdu101data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	qcc = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + rqtToText(qcc) + "   " + frzToText(qcc) + "\r\n");
	return true;
}

QString IEC101asdu101data::showToText()
{
	return mText;
}

bool IEC101asdu101data::createData(IECDataConfig &config)
{
	return true;
}
