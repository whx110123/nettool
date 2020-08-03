#include "iec101asdu103data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu103Data::IEC101Asdu103Data()
{

}

IEC101Asdu103Data::~IEC101Asdu103Data()
{

}

bool IEC101Asdu103Data::init(QByteArray buff)
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

bool IEC101Asdu103Data::init(QByteArray buff, uint addr)
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


bool IEC101Asdu103Data::createData(IECDataConfig &config)
{
	return false;
}
