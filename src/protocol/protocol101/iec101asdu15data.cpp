#include "iec101asdu15data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu15Data::IEC101Asdu15Data()
{
	intdata = 0;
	bcr = 0;
}

IEC101Asdu15Data::~IEC101Asdu15Data()
{

}

bool IEC101Asdu15Data::handle(const QByteArray &buff)
{
	mText.append("\r\n");
	intdata = charToint(buff.data() + len,4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t整数:" + QString::number(intdata) + "\r\n");
	len += 4;

	bcr = *(buff.data() + len);
	uchar sq = bcr & 0x1f;
	mText.append(CharToHexStr(buff.data() + len) + "\t顺序号SQ(bit1-5):" + QString::number(sq) + "   品质位:" + cyToText(bcr) + "   " + caToText(bcr) + "   " + ivToText(bcr)  + "\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu15Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
