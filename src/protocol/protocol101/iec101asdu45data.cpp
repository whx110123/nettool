#include "iec101asdu45data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu45Data::IEC101Asdu45Data()
{
	sco = 0;
}

IEC101Asdu45Data::~IEC101Asdu45Data()
{

}

bool IEC101Asdu45Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	sco = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + scsToText(sco) + "   " + seToText(sco) + "   " + quToText(sco) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC101Asdu45Data::createData(IECDataConfig& config)
{
	config.data += uintToBa(config.infaddr, infaddrlen);
	config.data += config.infdata;
	return true;
}
