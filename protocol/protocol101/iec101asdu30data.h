#ifndef IEC101ASDU30DATA_H
#define IEC101ASDU30DATA_H

#include "iec101asdu.h"
#include <QDateTime>


class IEC101asdu30data : public IEC101asdudata
{
public:
	IEC101asdu30data();
	~IEC101asdu30data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar siq;
	QDateTime datetime;
};

#endif // IEC101ASDU30DATA_H
