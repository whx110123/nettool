#include "iec103asdu1data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC103asdu1data::IEC103asdu1data()
{
	dip = 0;
	sin = 0;
}

IEC103asdu1data::~IEC103asdu1data()
{

}

bool IEC103asdu1data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	len = 0;

	inf = *(buff.data() + len);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;
	datetime = charToDateTime(buff.data() + len, 4, BINARYTIME2A);
	mText.append(timeToText(buff.data() + len, 4));
	len += 4;
	sin = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data()) + "\tGID:附加信息SIN:" + QString::number(sin));
	len++;
	return true;
}

bool IEC103asdu1data::init(QByteArray buff, uint addr)
{
	return false;
}

QString IEC103asdu1data::showToText()
{
	return mText;
}

bool IEC103asdu1data::createData(IECDataConfig &config)
{
	return false;
}
