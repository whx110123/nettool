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


bool IEC101Asdu101Data::handle(const QByteArray &buff)
{
	mText.append("\r\n");
	qcc = *(buff.data()+len);
	mText.append(CharToHexStr(buff.data()+len) + "\t" + rqtToText(qcc) + "   " + frzToText(qcc) + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu101Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
