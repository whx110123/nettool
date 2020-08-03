﻿#include "iec101asdu167data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu167Data::IEC101Asdu167Data()
{
	ctrl = 0;
	memset(devaddr, 0, sizeof(devaddr));
	iec103len = 0;
}

IEC101Asdu167Data::~IEC101Asdu167Data()
{

}

bool IEC101Asdu167Data::init(QByteArray buff)
{
	setDefault(buff);

	ctrl = *buff.data();
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data()) + "\t" + ctrlToText() + "\r\n");

//	devaddr = charTouint(buff.data() + 1, 2);
	memcpy(devaddr, buff.data() + 1, 2);
	mText.append(CharToHexStr(buff.data() + 1) + "\t保护装置地址L:" + QString::number(devaddr[0]) + "\r\n");
	mText.append(CharToHexStr(buff.data() + 2) + "\t保护装置地址H:" + QString::number(devaddr[1]) + "\r\n");

	iec103len = *(buff.data()+3);
	mText.append(CharToHexStr(buff.data() + 3) + "\tIEC103数据长度:" + QString::number(iec103len) + "\r\n");

	if (!asdu.init(buff.mid(4, iec103len)))
	{
		return false;
	}
	if (asdu.len != iec103len)
	{
		return false;
	}
	return true;
}


QString IEC101Asdu167Data::showToText()
{
	QString text = mText;
	text.append(asdu.showToText());
	return text;
}

bool IEC101Asdu167Data::createData(IECDataConfig &config)
{
	config.data += '\0';
	config.data.append(uintToBa(config.iec103config->devaddr,2));
	if(config.isMaster)
	{
		config.iec103config->data.clear();
		if(!asdu.createData(*config.iec103config))
		{
			return false;
		}
		config.data += (uchar)config.iec103config->data.size();
		config.data.append(config.iec103config->data);
	}

	return true;


}

QString IEC101Asdu167Data::ctrlToText()
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
