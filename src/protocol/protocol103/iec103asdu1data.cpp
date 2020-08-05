#include "iec103asdu1data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC103Asdu1Data::IEC103Asdu1Data()
{
	dpi = 0;
	sin = 0;
}

IEC103Asdu1Data::~IEC103Asdu1Data()
{

}

bool IEC103Asdu1Data::init(QByteArray buff)
{
	setDefault(buff);

	inf = *(buff.data() + len);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;
	dpi = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(dpi) + "\r\n");
	len++;
	datetime = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 4));
	len += 4;
	sin = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data()) + "\tGID:附加信息SIN:" + QString::number(sin));
	len++;
	return true;
}


bool IEC103Asdu1Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
