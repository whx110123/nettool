#ifndef IEC103ASDU41DATA_H
#define IEC103ASDU41DATA_H

#include "iec103asdu.h"

class IEC103Asdu41Data : public IEC103AsduData
{
public:
	IEC103Asdu41Data();
	~IEC103Asdu41Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar siq;
	QDateTime datetime;
};

#endif // IEC103ASDU41DATA_H
