#ifndef IEC103ASDU1DATA_H
#define IEC103ASDU1DATA_H

#include "iec103asdu.h"


class IEC103asdu1data : public IEC103asdudata
{
public:
	IEC103asdu1data();
	~IEC103asdu1data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar dip;
	QDateTime datetime;
	uchar sin;
};

#endif // IEC103ASDU1DATA_H
