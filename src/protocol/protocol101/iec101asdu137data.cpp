#include "iec101asdu137data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu137Data::IEC101Asdu137Data()
{
	shortdata = 0;
}

IEC101Asdu137Data::~IEC101Asdu137Data()
{

}

bool IEC101Asdu137Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	shortdata = charToint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");
	len += 2;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu137Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
