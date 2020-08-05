#include "iec101asdu31data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu31Data::IEC101Asdu31Data()
{
	diq = 0;
}

IEC101Asdu31Data::~IEC101Asdu31Data()
{

}

bool IEC101Asdu31Data::init(QByteArray buff)
{
	setDefault(buff);

	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	diq = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
	datetime = charToDateTime(buff.data() + infaddrlen + 1, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + infaddrlen + 1, 7));
	return true;
}

bool IEC101Asdu31Data::init(QByteArray buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	diq = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
	datetime = charToDateTime(buff.data() + 1, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + 1, 7));
	return true;
}


bool IEC101Asdu31Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
