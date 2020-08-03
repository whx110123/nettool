#include "iec101asdu45data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu45Data::IEC101Asdu45Data()
{
	sco = 0;
}

IEC101Asdu45Data::~IEC101Asdu45Data()
{

}

bool IEC101Asdu45Data::init(QByteArray buff)
{
	setDefault(buff);

	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	sco = *(buff.data() + infaddrlen);
	mText.append(CharToHexStr(buff.data() + infaddrlen) + "\t" + scsToText(sco) + "   " + seToText(sco) + "   " + quToText(sco) + "\r\n");
	return true;
}

bool IEC101Asdu45Data::init(QByteArray buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
	sco = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + scsToText(sco) + "   " + seToText(sco) + "   " + quToText(sco) + "\r\n");
	return true;
}


bool IEC101Asdu45Data::createData(IECDataConfig &config)
{
	config.data += uintToBa(config.infaddr,3);
	config.data += config.infdata;
	return true;
}
