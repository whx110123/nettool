#include "iec103asdu7data.h"

IEC103Asdu7Data::IEC103Asdu7Data()
{

}

IEC103Asdu7Data::~IEC103Asdu7Data()
{

}

bool IEC103Asdu7Data::handle(const QByteArray& buff)
{
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu7Data::createData(IECDataConfig& config)
{
	return true;
}
