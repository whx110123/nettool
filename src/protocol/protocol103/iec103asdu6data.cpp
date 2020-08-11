#include "iec103asdu6data.h"
#include "functotext.h"

IEC103Asdu6Data::IEC103Asdu6Data()
{

}

IEC103Asdu6Data::~IEC103Asdu6Data()
{

}

bool IEC103Asdu6Data::handle(const QByteArray& buff)
{
	datetime = charToDateTime(buff.data() + len, 7, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 7));
	len += 7;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu6Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
