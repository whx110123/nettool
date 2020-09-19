#ifndef IEC103ASDU25DATA_H
#define IEC103ASDU25DATA_H

#include "iec103asdu.h"



class IEC103Asdu25Data : public IEC103AsduData
{
public:
	IEC103Asdu25Data();
	~IEC103Asdu25Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar too;
	uchar tov;
	ushort fan;
	uchar acc;
};

#endif // IEC103ASDU25DATA_H
