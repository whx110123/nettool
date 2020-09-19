#include "iec103asdu25data.h"
#include "functotext.h"

IEC103Asdu25Data::IEC103Asdu25Data()
{
	too = 0;
	tov = 0;
	fan = 0;
	acc = 0;
}

IEC103Asdu25Data::~IEC103Asdu25Data()
{

}

bool IEC103Asdu25Data::handle(const QByteArray& buff)
{
	too = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + tooToText(too) + "\r\n");
	len++;

	tov = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + tovToText(tov) + "\r\n");
	len++;

	fan = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	len += 2;

	acc = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + accToText(acc) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu25Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
