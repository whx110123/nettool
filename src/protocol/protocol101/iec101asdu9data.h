#ifndef IEC101ASDU9DATA_H
#define IEC101ASDU9DATA_H

#include "iec101asdu.h"

class IEC101Asdu9Data : public IEC101AsduData
{
public:
	IEC101Asdu9Data();
	~IEC101Asdu9Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	short shortdata;
	uchar qds;
};

#endif // IEC101ASDU9DATA_H
