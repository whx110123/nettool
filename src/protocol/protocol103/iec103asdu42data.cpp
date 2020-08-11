#include "iec103asdu42data.h"
#include "functotext.h"

IEC103Asdu42Data::IEC103Asdu42Data()
{
	diq = 0;
}

IEC103Asdu42Data::~IEC103Asdu42Data()
{

}


bool IEC103Asdu42Data::handle(const QByteArray& buff)
{
	diq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC103Asdu42Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

