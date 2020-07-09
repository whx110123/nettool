#ifndef IEC101ASDU45DATA_H
#define IEC101ASDU45DATA_H
#include "iec101asdu.h"


class IEC101asdu45data : public IEC101asdudata
{
public:
	IEC101asdu45data();
	~IEC101asdu45data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar sco;
};

#endif // IEC101ASDU45DATA_H
