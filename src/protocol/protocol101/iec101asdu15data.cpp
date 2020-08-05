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

bool IEC101Asdu15Data::init(QByteArray buff)
{
	setDefault(buff);

	if(infaddrlen!=3&&infaddrlen!=2&&infaddrlen!=1)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！信息体地址长度错误");
		return false;
	}
	infaddr = charTouint(buff.data(), infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(), infaddrlen) + "\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	intdata = charToint(buff.data() + infaddrlen,4);
	mText.append(CharToHexStr(buff.data() + infaddrlen, 4) + "\t整数:" + QString::number(intdata) + "\r\n");

	bcr = *(buff.data() + infaddrlen + 4);
	uchar sq = bcr & 0x1f;
	mText.append(CharToHexStr(buff.data() + infaddrlen + 4) + "\t顺序号SQ(bit1-5):" + QString::number(sq) + "   品质位:" + cyToText(bcr) + "   " + caToText(bcr) + "   " + ivToText(bcr)  + "\r\n");
	return true;
}

bool IEC101Asdu15Data::init(QByteArray buff, uint addr)
{
	setDefault(buff);

	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) + "\r\n");

	intdata = charTofloat(buff.data());
	mText.append(CharToHexStr(buff.data(), 4) + "\t整数:" + QString::number(intdata) + "\r\n");

	bcr = *(buff.data() + 4);
	uchar sq = bcr & 0x1f;
	mText.append(CharToHexStr(buff.data() + 4) + "\t顺序号SQ(bit1-5):" + QString::number(sq) + "   品质位:" + cyToText(bcr) + "   " + caToText(bcr) + "   " + ivToText(bcr) + "\r\n");
	return true;
}


bool IEC101Asdu15Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}
