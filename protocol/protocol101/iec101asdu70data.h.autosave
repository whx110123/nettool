#ifndef IEC101ASDU70DATA_H
#define IEC101ASDU70DATA_H

#include "iec101asdu.h"
#include <QList>

class IEC101asdu70data : public IEC101asdudata
{
public:
	IEC101asdu70data();
	~IEC101asdu70data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar coi;

};

#endif // IEC101ASDU70DATA_H
