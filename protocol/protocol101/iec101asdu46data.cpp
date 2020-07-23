#include "iec101asdu46data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu46data::IEC101asdu46data()
{
	dco = 0;
}

IEC101asdu46data::~IEC101asdu46data()
{

}

bool IEC101asdu46data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	dco = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + dcsToText(dco) + "   " + seToText(dco) + "   " + quToText(dco) + "\r\n");
	return true;
}

bool IEC101asdu46data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	dco = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + dcsToText(dco) + "   " + seToText(dco) + "   " + quToText(dco) + "\r\n");
	return true;
}

QString IEC101asdu46data::showToText()
{
	return mText;
}

bool IEC101asdu46data::createData(IECDataConfig &config)
{
	config.data += uintToBa(config.infaddr,3);
	config.data += config.infdata;
	return true;
}
