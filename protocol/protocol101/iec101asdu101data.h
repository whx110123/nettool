#ifndef IEC101ASDU101DATA_H
#define IEC101ASDU101DATA_H

#include "iec101asdu.h"


class IEC101asdu101data : public IEC101asdudata
{
public:
	IEC101asdu101data();
	~IEC101asdu101data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar qcc;
};

#endif // IEC101ASDU101DATA_H
