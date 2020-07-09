#ifndef IEC101ASDU137DATA_H
#define IEC101ASDU137DATA_H

#include "iec101asdu.h"


class IEC101asdu137data : public IEC101asdudata
{
public:
	IEC101asdu137data();
	~IEC101asdu137data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	short shortdata;
};

#endif // IEC101ASDU137DATA_H
