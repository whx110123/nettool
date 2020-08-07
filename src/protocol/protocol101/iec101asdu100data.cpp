#include "iec101asdu100data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu100Data::IEC101Asdu100Data()
{
	qoi = 0;
	infaddr = 0;
}

IEC101Asdu100Data::~IEC101Asdu100Data()
{

}

bool IEC101Asdu100Data::init(QByteArray buff)
{
	setDefault(buff);

	if(infaddrlen!=3&&infaddrlen!=2&&infaddrlen!=1)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址长度错误");
		return false;
	}
	infaddr = charTouint(buff.data(),infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+"\r\n");
	qoi = *(buff.data()+infaddrlen);
	mText.append(CharToHexStr(buff.data()+infaddrlen) + "\t" + qoiToText(qoi) +"\r\n");
	return true;
}

bool IEC101Asdu100Data::init(QByteArray buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) +"\r\n");
	qoi = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + qoiToText(qoi) +"\r\n");
	return true;
}

bool IEC101Asdu100Data::createData(IECDataConfig &config)
{

	if(config.isfirst || (config.vsq & 0x80) == 0)
	{
		infaddr = 0;
		config.data += uintToBa(infaddr,infaddrlen);
	}

	if(config.isMaster)
	{
		config.data += 0x14;
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
	}
	config.isfirst = false;
	return true;
}
