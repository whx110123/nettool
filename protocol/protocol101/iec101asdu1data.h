#ifndef IEC101ASDU1DATA_H
#define IEC101ASDU1DATA_H

#include "iec101asdu.h"
#include <QList>
#include <dataconfig.h>

class IEC101asdu1data : public IEC101asdudata
{
public:
	IEC101asdu1data();
	~IEC101asdu1data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar siq;

};

#endif // IEC101ASDU1DATA_H
