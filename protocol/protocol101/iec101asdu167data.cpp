#include "iec101asdu167data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu167data::IEC101asdu167data()
{
	ctrl = 0;
	devaddr = 0;
	iec103len = 0;
}

IEC101asdu167data::~IEC101asdu167data()
{

}

bool IEC101asdu167data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();

	ctrl = *buff.data();
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data()) + "\t" + ctrlToText() + "\r\n");

	devaddr = charTouint(buff.data() + 1, 2);
	mText.append(CharToHexStr(buff.data() + 1, 2) + "\t保护装置地址:" + QString::number(devaddr) + "\r\n");

	iec103len = *(buff.data()+2);
	mText.append(CharToHexStr(buff.data() + 2) + "\tIEC103数据长度:" + QString::number(iec103len) + "\r\n");

	return true;
}

bool IEC101asdu167data::init(QByteArray buff, uint addr)
{
// 	mRecvData = buff;
// 	mText.clear();
// 	infaddr = addr;
// 	mText.append("-----------------------------------------------------------------------------------------------\r\n");
// 	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");
// 
// 	shortdata = charToint(buff.data(), 2);
// 	mText.append(CharToHexStr(buff.data(), 2) + "\t规一化值:" + QString::number(shortdata) + "\r\n");

	return false;
}

QString IEC101asdu167data::showToText()
{
	return mText;
}

bool IEC101asdu167data::createData(IECDataConfig &config)
{
	return true;
}

QString IEC101asdu167data::ctrlToText()
{
	QString text = "保护信息传输控制字节，A/S(bit8):" + QString::number(ctrl & 0x80, 16).toUpper() + " ";
	uchar datanum = ctrl & 0x7f;
	if (ctrl & 0x80)
	{
		text.append("有后续帧");
	}
	else
	{
		text.append("无后续帧");
	}
	text.append("当前帧号(bit1-7):" + QString::number(datanum));
	return text;
}
