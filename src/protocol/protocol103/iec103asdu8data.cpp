#include "iec103asdu8data.h"

IEC103Asdu8Data::IEC103Asdu8Data()
{

}
IEC103Asdu8Data::~IEC103Asdu8Data()
{

}

bool IEC103Asdu8Data::handle(const QByteArray& buff)
{
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu8Data::createData(IECDataConfig& config)
{
	return true;
}
