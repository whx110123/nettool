#ifndef IEC101ASDU36DATA_H
#define IEC101ASDU36DATA_H

#include "iec101asdu.h"



class IEC101Asdu36Data : public IEC101AsduData
{
public:
	IEC101Asdu36Data();
	~IEC101Asdu36Data();
	virtual bool handle(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	float floatdata;
	uchar qds;
	QDateTime datetime;
};

#endif // IEC101ASDU36DATA_H
