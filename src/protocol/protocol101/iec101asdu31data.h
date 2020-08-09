#ifndef IEC101ASDU31DATA_H
#define IEC101ASDU31DATA_H
#include "iec101asdu.h"


class IEC101Asdu31Data : public IEC101AsduData
{
public:
	IEC101Asdu31Data();
	~IEC101Asdu31Data();
//	virtual bool init(const QByteArray &buff);
//	virtual bool init(const QByteArray &buff, uint addr);
	virtual bool handle(const QByteArray &buff);
	virtual bool createData(IECDataConfig &config);

public:
	uchar diq;
	QDateTime datetime;
};

#endif // IEC101ASDU31DATA_H
