#ifndef IEC101ASDU50DATA_H
#define IEC101ASDU50DATA_H

#include "iec101asdu.h"


class IEC101asdu50data : public IEC101asdudata
{
public:
	IEC101asdu50data();
	~IEC101asdu50data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	float floatdata;
	uchar qos;
};

#endif // IEC101ASDU50DATA_H
