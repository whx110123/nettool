#ifndef IEC101ASDU103DATA_H
#define IEC101ASDU103DATA_H

#include "iec101asdu.h"


class IEC101asdu103data : public IEC101asdudata
{
public:
	IEC101asdu103data();
	~IEC101asdu103data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	QDateTime datetime;
};

#endif // IEC101ASDU103DATA_H
