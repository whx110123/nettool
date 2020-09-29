#include "iec103asdu88data.h"

IEC103Asdu88Data::IEC103Asdu88Data()
{
	qcc = 0;
}

IEC103Asdu88Data::~IEC103Asdu88Data()
{

}

bool IEC103Asdu88Data::handle(const QByteArray& buff)
{
	qcc = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t计数量召唤命令限定词(QCC):\r\n\t" + rqtToText(qcc) + "\r\n\t" + frzToText(qcc) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu88Data::createData(IECDataConfig& config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
