#include "iec101asdu100data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu100data::IEC101asdu100data()
{
	qoi = 0;
	infaddr = 0;
}

IEC101asdu100data::~IEC101asdu100data()
{

}

bool IEC101asdu100data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(),infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+"\r\n");
	qoi = *(buff.data()+infaddrlen);
	mText.append(CharToHexStr(buff.data()+infaddrlen) + "\t" + qoiToText(qoi) +"\r\n");
	return true;
}

bool IEC101asdu100data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) +"\r\n");
	qoi = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + qoiToText(qoi) +"\r\n");
	return true;
}

QString IEC101asdu100data::showToText()
{
	return mText;
}

bool IEC101asdu100data::createData(IECDataConfig &config)
{
	if(config.isfirst)
	{

	}
	if(config.isfirst || (config.vsq & 0x80) == 0)
	{
		infaddr = 0;
		config.data += uintToBa(infaddr,3);
	}

	if(config.isMaster)
	{
		config.data += 0x14;
	}
	else
	{

	}
	config.isfirst = false;
	return true;
}
