#include "iec101asdu30data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu30Data::IEC101Asdu30Data()
{
	siq = 0;
}

IEC101Asdu30Data::~IEC101Asdu30Data()
{

}

bool IEC101Asdu30Data::init(QByteArray buff)
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

bool IEC101Asdu30Data::init(QByteArray buff, uint addr)
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


bool IEC101Asdu30Data::createData(IECDataConfig &config)
{
	return false;
}
