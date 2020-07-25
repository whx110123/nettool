#include "iec101asdu31data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu31Data::IEC101Asdu31Data()
{
	diq = 0;
}

IEC101Asdu31Data::~IEC101Asdu31Data()
{

}

bool IEC101Asdu31Data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	diq = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
	datetime = charToDateTime(buff.data() + infaddrlen + 1, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + infaddrlen + 1, 7));
	return true;
}

bool IEC101Asdu31Data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	diq = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
	datetime = charToDateTime(buff.data() + 1, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + 1, 7));
	return true;
}

QString IEC101Asdu31Data::showToText()
{
	return mText;
}

bool IEC101Asdu31Data::createData(IECDataConfig &config)
{
	return true;
}
