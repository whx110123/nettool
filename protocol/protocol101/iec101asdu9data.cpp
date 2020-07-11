#include "iec101asdu9data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu9data::IEC101asdu9data()
{
	shortdata = 0;
	qds = 0;
}

IEC101asdu9data::~IEC101asdu9data()
{

}

bool IEC101asdu9data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");

	shortdata = charToint(buff.data() + infaddrlen,2);
	mText.append(CharToHexStr(buff.data() + infaddrlen, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");

	qds = *(buff.data() + infaddrlen + 2);
	mText.append(CharToHexStr(buff.data() + infaddrlen + 2) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	return true;
}

bool IEC101asdu9data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	shortdata = charToint(buff.data(),2);
	mText.append(CharToHexStr(buff.data(), 2) + "\t规一化值:" + QString::number(shortdata) + "\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");

	qds = *(buff.data() + 2);
	mText.append(CharToHexStr(buff.data() + 2) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	return true;
}

QString IEC101asdu9data::showToText()
{
	return mText;
}

bool IEC101asdu9data::createData(IECDataConfig &config)
{
	return true;
}
