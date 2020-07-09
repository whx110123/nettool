#ifndef IEC101ASDU32DATA_H
#define IEC101ASDU32DATA_H

#include "iec101asdu.h"


class IEC101asdu32data : public IEC101asdudata
{
public:
	IEC101asdu32data();
	~IEC101asdu32data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar vti;
	uchar qds;
	QDateTime datetime;
};

#endif // IEC101ASDU32DATA_H
