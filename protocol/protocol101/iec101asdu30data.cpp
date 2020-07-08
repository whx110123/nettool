#include "iec101asdu30data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu30data::IEC101asdu30data()
{
	siq = 0;
}

IEC101asdu30data::~IEC101asdu30data()
{

}

bool IEC101asdu30data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	siq = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	datetime = charToDateTime(buff.data() + infaddrlen+1, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + infaddrlen + 1, 7));
	return true;
}

bool IEC101asdu30data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	siq = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	datetime = charToDateTime(buff.data() + 1, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + 1, 7));
	return true;
}

QString IEC101asdu30data::showToText()
{
	return mText;
}

bool IEC101asdu30data::createData(IECDataConfig &config)
{
	return true;
}
