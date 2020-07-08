#ifndef IEC101ASDU15DATA_H
#define IEC101ASDU15DATA_H

#include "iec101asdu.h"

class IEC101asdu15data : public IEC101asdudata
{
public:
	IEC101asdu15data();
	~IEC101asdu15data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	int intdata;
	uchar bcr;
};

#endif // IEC101ASDU15DATA_H
