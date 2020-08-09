#ifndef IEC101ASDU21DATA_H
#define IEC101ASDU21DATA_H

#include "iec101asdu.h"


class IEC101Asdu21Data : public IEC101AsduData
{
public:
	IEC101Asdu21Data();
	~IEC101Asdu21Data();
//	virtual bool init(const QByteArray &buff);
//	virtual bool init(const QByteArray &buff, uint addr);
	virtual bool handle(const QByteArray &buff);
	virtual bool createData(IECDataConfig &config);

public:
	short shortdata;
};

#endif // IEC101ASDU21DATA_H
