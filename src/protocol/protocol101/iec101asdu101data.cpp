#include "iec101asdu101data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu101Data::IEC101Asdu101Data()
{
	qcc = 0;
}

IEC101Asdu101Data::~IEC101Asdu101Data()
{

}

bool IEC101Asdu101Data::init(QByteArray buff)
{
	setDefault(buff);

	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	qcc = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + rqtToText(qcc) + "   " + frzToText(qcc)  + "\r\n");
	return true;
}

bool IEC101Asdu101Data::init(QByteArray buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	qcc = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + rqtToText(qcc) + "   " + frzToText(qcc) + "\r\n");
	return true;
}


bool IEC101Asdu101Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行] %4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
