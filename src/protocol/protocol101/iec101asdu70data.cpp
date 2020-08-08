#include "iec101asdu70data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu70Data::IEC101Asdu70Data()
{
	coi = 0;
	infaddr = 0;
}

IEC101Asdu70Data::~IEC101Asdu70Data()
{

}

bool IEC101Asdu70Data::init(const QByteArray &buff)
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
	coi = *(buff.data()+infaddrlen);
	mText.append(CharToHexStr(buff.data()+infaddrlen) + "\t" + coiToText(coi) +"\r\n");
	return true;
}

bool IEC101Asdu70Data::init(const QByteArray &buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) +"\r\n");
	coi = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + coiToText(coi) +"\r\n");
	return true;
}


bool IEC101Asdu70Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

