#include "iec101asdu3data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu3Data::IEC101Asdu3Data()
{
	diq = 0;
}

IEC101Asdu3Data::~IEC101Asdu3Data()
{

}

bool IEC101Asdu3Data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(),infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+"\r\n");
	diq = *(buff.data()+infaddrlen);
	mText.append(CharToHexStr(buff.data()+infaddrlen) + "\t" + dpiToText(diq) +"   "+ ivToText(diq) +"   "+ ntToText(diq)+"   "+ sbToText(diq)+"   "+ blToText(diq)+"\r\n");
	return true;
}

bool IEC101Asdu3Data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) +"\r\n");
	diq = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + dpiToText(diq) +"   "+ ivToText(diq) +"   "+ ntToText(diq)+"   "+ sbToText(diq)+"   "+ blToText(diq)+"\r\n");
	return true;
}

bool IEC101Asdu3Data::createData(IECDataConfig &config)
{
	return false;
}
