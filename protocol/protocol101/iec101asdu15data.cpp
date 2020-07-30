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
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//信息体地址长度
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
	mRecvData = buff;
	mText.clear();
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
	return false;
}
