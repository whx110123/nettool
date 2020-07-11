#include "iec101asdu13data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu13data::IEC101asdu13data()
{
	floatdata = 0;
	qds = 0;
}

IEC101asdu13data::~IEC101asdu13data()
{

}

bool IEC101asdu13data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(),infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+ "\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");

	floatdata = charTofloat(buff.data()+infaddrlen);
	mText.append(CharToHexStr(buff.data()+infaddrlen,4) + "\t浮点数:"+QString::number(floatdata) + "\r\n");

	qds = *(buff.data()+infaddrlen+4);
	mText.append(CharToHexStr(buff.data()+infaddrlen+4) + "\t品质位:" + ivToText(qds) +"   "+ ntToText(qds)+"   "+ sbToText(qds)+"   "+ blToText(qds)+"   "+ ovToText(qds)+"\r\n");
	return true;
}

bool IEC101asdu13data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr)+ "\t对应点号是:" + QString::number(infaddr - 0x4001) + "\r\n");

	floatdata = charTofloat(buff.data());
	mText.append(CharToHexStr(buff.data(),4) + "\t浮点数:"+QString::number(floatdata) + "\r\n");

	qds = *(buff.data()+4);
	mText.append(CharToHexStr(buff.data()+4) + "\t品质位:" + ivToText(qds) +"   "+ ntToText(qds)+"   "+ sbToText(qds)+"   "+ blToText(qds)+"   "+ ovToText(qds)+"\r\n");
	return true;
}

QString IEC101asdu13data::showToText()
{
	return mText;
}

bool IEC101asdu13data::createData(IECDataConfig &config)
{
	return true;
}

