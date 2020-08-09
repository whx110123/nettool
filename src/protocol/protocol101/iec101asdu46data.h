#ifndef IEC101ASDU46DATA_H
#define IEC101ASDU46DATA_H

#include "iec101asdu.h"


class IEC101Asdu46Data : public IEC101AsduData
{
public:
	IEC101Asdu46Data();
	~IEC101Asdu46Data();
//	virtual bool init(const QByteArray &buff);
//	virtual bool init(const QByteArray &buff, uint addr);
	virtual bool handle(const QByteArray &buff);
	virtual bool createData(IECDataConfig &config);

public:
	uchar dco;
};

#endif // IEC101ASDU46DATA_H
