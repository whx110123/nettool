#include "iec103asdu2data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC103Asdu2Data::IEC103Asdu2Data()
{
	dpi = 0;
	sin = 0;
}

IEC103Asdu2Data::~IEC103Asdu2Data()
{

}

bool IEC103Asdu2Data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	len = 0;

	inf = *(buff.data() + len);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;

	dpi = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(dpi) + "\r\n");
	len++;

	ret = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len,2) + "\t相对时间RET:" + QString::number(ret) + "\r\n");
	len += 2;

	fan = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t故障序号FAN:" + QString::number(fan) + "\r\n");
	len += 2;

	datetime = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 4));
	len += 4;

	sin = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data()) + "\tGID:附加信息SIN:" + QString::number(sin));
	len++;
	return true;
}

bool IEC103Asdu2Data::init(QByteArray buff, uint addr)
{
	return false;
}

QString IEC103Asdu2Data::showToText()
{
	return mText;
}

bool IEC103Asdu2Data::createData(IECDataConfig &config)
{
	return false;
}
