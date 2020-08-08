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

bool IEC101Asdu103Data::init(const QByteArray &buff)
{
	setDefault(buff);

	if(infaddrlen!=3&&infaddrlen!=2&&infaddrlen!=1)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址长度错误");
		return false;
	}
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	datetime = charToDateTime(buff.data() + infaddrlen , 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + infaddrlen , 7));
	return true;
}

bool IEC101Asdu103Data::init(const QByteArray &buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	datetime = charToDateTime(buff.data() , 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() , 7));
	return true;
}


bool IEC101Asdu103Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
