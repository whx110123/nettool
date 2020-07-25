#ifndef IEC103ASDU1DATA_H
#define IEC103ASDU1DATA_H

#include "iec103asdu.h"


class IEC103Asdu1Data : public IEC103AsduData
{
public:
	IEC103Asdu1Data();
	~IEC103Asdu1Data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar dpi;
	QDateTime datetime;
	uchar sin;
};

#endif // IEC103ASDU1DATA_H
