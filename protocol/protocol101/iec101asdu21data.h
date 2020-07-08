#ifndef IEC101ASDU21DATA_H
#define IEC101ASDU21DATA_H

#include "iec101asdu.h"


class IEC101asdu21data : public IEC101asdudata
{
public:
	IEC101asdu21data();
	~IEC101asdu21data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	short shortdata;
};

#endif // IEC101ASDU21DATA_H
