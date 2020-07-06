#ifndef IEC101ASDU100DATA_H
#define IEC101ASDU100DATA_H

#include "iec101asdu.h"
#include <QList>
#include <dataconfig.h>

class IEC101asdu100data : public IEC101asdudata
{
public:
	IEC101asdu100data();
	~IEC101asdu100data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar qoi;

};

#endif // IEC101ASDU100DATA_H
