#include "iec101asdu32data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu32Data::IEC101Asdu32Data()
{
	vti = 0;
	qds = 0;
}

IEC101Asdu32Data::~IEC101Asdu32Data()
{

}

bool IEC101Asdu32Data::handle(const QByteArray &buff)
{
	mText.append( "\r\n");
	vti = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + vtiToText(vti)  + "\r\n");
	len++;

	qds = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t品质位:" + ivToText(qds) + "   " + ntToText(qds) + "   " + sbToText(qds) + "   " + blToText(qds) + "   " + ovToText(qds) + "\r\n");
	len++;

	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC101Asdu32Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
