#include "iec101asdu30data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu30Data::IEC101Asdu30Data()
{
	siq = 0;
}

IEC101Asdu30Data::~IEC101Asdu30Data()
{

}

bool IEC101Asdu30Data::handle(const QByteArray &buff)
{
	mText.append("\r\n");
	siq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + spiToText(siq) + "   " + ivToText(siq) + "   " + ntToText(siq) + "   " + sbToText(siq) + "   " + blToText(siq) + "\r\n");
	len++;

	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu30Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
