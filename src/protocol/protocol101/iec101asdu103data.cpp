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

bool IEC101Asdu103Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu103Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
