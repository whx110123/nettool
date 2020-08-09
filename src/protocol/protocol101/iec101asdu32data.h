#ifndef IEC101ASDU32DATA_H
#define IEC101ASDU32DATA_H

#include "iec101asdu.h"


class IEC101Asdu32Data : public IEC101AsduData
{
public:
	IEC101Asdu32Data();
	~IEC101Asdu32Data();
//	virtual bool init(const QByteArray &buff);
//	virtual bool init(const QByteArray &buff, uint addr);
	virtual bool handle(const QByteArray &buff);
	virtual bool createData(IECDataConfig &config);

public:
	uchar vti;
	uchar qds;
	QDateTime datetime;
};

#endif // IEC101ASDU32DATA_H
