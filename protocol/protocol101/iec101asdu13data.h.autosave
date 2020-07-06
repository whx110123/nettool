#ifndef IEC101ASDU13DATA_H
#define IEC101ASDU13DATA_H

#include "iec101asdu.h"
#include <QList>

class IEC101asdu13data : public IEC101asdudata
{
public:
	IEC101asdu13data();
	~IEC101asdu13data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	float floatdata;
	uchar qds;
};

#endif // IEC101ASDU13DATA_H
