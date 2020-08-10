#include "iec101asdu50data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu50Data::IEC101Asdu50Data()
{
	floatdata = 0;
	qos = 0;
}

IEC101Asdu50Data::~IEC101Asdu50Data()
{

}

bool IEC101Asdu50Data::handle(const QByteArray &buff)
{
	mText.append("\r\n");
	floatdata = charTofloat(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t浮点数:" + QString::number(floatdata) + "\r\n");
	len += 4;

	qos = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + qosToText(qos) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC101Asdu50Data::createData(IECDataConfig &config)
{
	config.data += uintToBa(config.infaddr,infaddrlen);
	config.data += config.infdata;
	return true;
}
