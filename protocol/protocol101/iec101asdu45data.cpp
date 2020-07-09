#include "iec101asdu45data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu45data::IEC101asdu45data()
{
	sco = 0;
}

IEC101asdu45data::~IEC101asdu45data()
{

}

bool IEC101asdu45data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	sco = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + scsToText(sco) + "   " + seToText(sco) + "   " + quToText(sco) + "\r\n");
	return true;
}

bool IEC101asdu45data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	sco = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + scsToText(sco) + "   " + seToText(sco) + "   " + quToText(sco) + "\r\n");
	return true;
}

QString IEC101asdu45data::showToText()
{
	return mText;
}

bool IEC101asdu45data::createData(IECDataConfig &config)
{
	return true;
}
