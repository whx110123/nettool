#include "iec101asdu46data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu46Data::IEC101Asdu46Data()
{
	dco = 0;
}

IEC101Asdu46Data::~IEC101Asdu46Data()
{

}

//bool IEC101Asdu46Data::init(const QByteArray &buff)
//{
//	setDefault(buff);

//	if(infaddrlen!=3&&infaddrlen!=2&&infaddrlen!=1)
//	{
//		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址长度错误");
//		return false;
//	}
//	infaddr = charTouint(buff.data(), infaddrlen);
//	mText.append("-----------------------------------------------------------------------------------------------\r\n");
//	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
//	dco = *(buff.data() + infaddrlen);
//	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + dcsToText(dco) + "   " + seToText(dco) + "   " + quToText(dco) + "\r\n");
//	return true;
//}

//bool IEC101Asdu46Data::init(const QByteArray &buff, uint addr)
//{
//	setDefault(buff);

//	infaddr = addr;
//	mText.append("-----------------------------------------------------------------------------------------------\r\n");
//	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
//	dco = *buff.data();
//	mText.append(CharToHexStr(buff.data()) + "\t" + dcsToText(dco) + "   " + seToText(dco) + "   " + quToText(dco) + "\r\n");
//	return true;
//}

bool IEC101Asdu46Data::handle(const QByteArray &buff)
{
	mText.append("\r\n");
	dco = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dcsToText(dco) + "   " + seToText(dco) + "   " + quToText(dco) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC101Asdu46Data::createData(IECDataConfig &config)
{
	config.data += uintToBa(config.infaddr,infaddrlen);
	config.data += config.infdata;
	return true;
}
