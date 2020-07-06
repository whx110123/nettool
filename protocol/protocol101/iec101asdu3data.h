#ifndef IEC101ASDU3DATA_H
#define IEC101ASDU3DATA_H

#include "iec101asdu.h"

class IEC101asdu3data : public IEC101asdudata
{
public:
	IEC101asdu3data();
	~IEC101asdu3data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar diq;
};

#endif // IEC101ASDU3DATA_H
