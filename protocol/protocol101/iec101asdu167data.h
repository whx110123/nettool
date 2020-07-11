#ifndef IEC101ASDU167DATA_H
#define IEC101ASDU167DATA_H
#include "iec101asdu.h"
#include "iec103asdu.h"

class IEC101asdu167data : public IEC101asdudata
{
public:
	IEC101asdu167data();
	~IEC101asdu167data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar ctrl;
	uchar devaddr[2];
	uchar iec103len;
	IEC103asdu asdu;
private:
	QString ctrlToText();
};

#endif // IEC101ASDU167DATA_H
