#include "iec101asdu1data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu1Data::IEC101Asdu1Data()
{
	siq = 0;
}

IEC101Asdu1Data::~IEC101Asdu1Data()
{

}

//bool IEC101Asdu1Data::init(const QByteArray &buff)
//{
//	setDefault(buff);

//	if(infaddrlen!=3&&infaddrlen!=2&&infaddrlen!=1)
//	{
//		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址长度错误");
//		return false;
//	}
//	infaddr = charTouint(buff.data(),infaddrlen);
//	mText.append("-----------------------------------------------------------------------------------------------\r\n");
//	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+ "\t对应点号是:"+QString::number(infaddr-1)+"\r\n");
//	siq = *(buff.data()+infaddrlen);
//	mText.append(CharToHexStr(buff.data()+infaddrlen) + "\t" + spiToText(siq) +"   "+ ivToText(siq) +"   "+ ntToText(siq)+"   "+ sbToText(siq)+"   "+ blToText(siq)+"\r\n");
//	return true;
//}

//bool IEC101Asdu1Data::init(const QByteArray &buff, uint addr)
//{
//	setDefault(buff);

//	infaddr = addr;
//	mText.append("-----------------------------------------------------------------------------------------------\r\n");
//	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\t对应点号是:" + QString::number(infaddr - 1) + "\r\n");
//	siq = *buff.data();
//	mText.append(CharToHexStr(buff.data()) + "\t" + spiToText(siq) +"   "+ ivToText(siq) +"   "+ ntToText(siq)+"   "+ sbToText(siq)+"   "+ blToText(siq)+"\r\n");
//	return true;
//}

bool IEC101Asdu1Data::handle(const QByteArray &buff)
{
	mText.append("\t对应点号是:"+QString::number(infaddr-1)+"\r\n");
	siq = *(buff.data()+len);
	mText.append(CharToHexStr(buff.data()+len) + "\t" + spiToText(siq) +"   "+ ivToText(siq) +"   "+ ntToText(siq)+"   "+ sbToText(siq)+"   "+ blToText(siq)+"\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu1Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}


