#include "iec101asdu46data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101Asdu46Data::IEC101Asdu46Data()
{
	dco = 0;
}

IEC101Asdu46Data::~IEC101Asdu46Data()
{

}

bool IEC101Asdu46Data::handle(const QByteArray& buff)
{
	mText.append("\r\n");
	dco = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dcsToText(dco) + "   " + seToText(dco) + "   " + quToText(dco) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC101Asdu46Data::createData(IECDataConfig& config)
{
	config.data += uintToBa(config.infaddr, infaddrlen);
	config.data += config.infdata;
	return true;
}
