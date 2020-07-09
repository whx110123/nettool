#ifndef IEC101ASDU46DATA_H
#define IEC101ASDU46DATA_H

#include "iec101asdu.h"


class IEC101asdu46data : public IEC101asdudata
{
public:
	IEC101asdu46data();
	~IEC101asdu46data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar dco;
};

#endif // IEC101ASDU46DATA_H
