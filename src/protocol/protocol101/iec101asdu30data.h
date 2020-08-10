#ifndef IEC101ASDU30DATA_H
#define IEC101ASDU30DATA_H

#include "iec101asdu.h"
#include <QDateTime>


class IEC101Asdu30Data : public IEC101AsduData
{
public:
	IEC101Asdu30Data();
	~IEC101Asdu30Data();
	virtual bool handle(const QByteArray &buff);
	virtual bool createData(IECDataConfig &config);

public:
	uchar siq;
	QDateTime datetime;
};

#endif // IEC101ASDU30DATA_H
