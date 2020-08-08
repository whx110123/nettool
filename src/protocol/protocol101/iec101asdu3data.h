﻿#ifndef IEC101ASDU3DATA_H
#define IEC101ASDU3DATA_H

#include "iec101asdu.h"

class IEC101Asdu3Data : public IEC101AsduData
{
public:
	IEC101Asdu3Data();
	~IEC101Asdu3Data();
	virtual bool init(const QByteArray &buff);
	virtual bool init(const QByteArray &buff,uint addr);
	virtual bool createData(IECDataConfig &config);

public:
	uchar diq;
};

#endif // IEC101ASDU3DATA_H
