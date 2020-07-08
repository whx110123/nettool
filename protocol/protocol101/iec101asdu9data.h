#ifndef IEC101ASDU9DATA_H
#define IEC101ASDU9DATA_H

#include "iec101asdu.h"

class IEC101asdu9data : public IEC101asdudata
{
public:
	IEC101asdu9data();
	~IEC101asdu9data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	float floatdata;
	uchar qds;
};

#endif // IEC101ASDU9DATA_H
