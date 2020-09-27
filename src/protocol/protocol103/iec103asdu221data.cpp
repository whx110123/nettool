#include "iec103asdu221data.h"

IEC103Asdu221Data::IEC103Asdu221Data()
{
	fnam = 0;
	snam = 0;
	scq = 0;
}

IEC103Asdu221Data::~IEC103Asdu221Data()
{

}

bool IEC103Asdu221Data::handle(const QByteArray& buff)
{
	fnam = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t文件名称FNAM: " + QString::number(fnam) + "\r\n");
	len += 2;

	snam = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t节名称SNAM: " + QString::number(snam) + "\r\n");
	len++;

	scq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + scqToText(scq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu221Data::createData(IECDataConfig& config)
{

}
