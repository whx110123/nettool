#ifndef IEC101ASDU31DATA_H
#define IEC101ASDU31DATA_H
#include "iec101asdu.h"


class IEC101asdu31data : public IEC101asdudata
{
public:
	IEC101asdu31data();
	~IEC101asdu31data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar diq;
	QDateTime datetime;
};

#endif // IEC101ASDU31DATA_H
