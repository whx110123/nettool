﻿#ifndef IEC101ASDU70DATA_H
#define IEC101ASDU70DATA_H

#include "iec101asdu.h"

class IEC101Asdu70Data : public IEC101AsduData
{
public:
	IEC101Asdu70Data();
	~IEC101Asdu70Data();
	virtual bool init(const QByteArray &buff);
	virtual bool init(const QByteArray &buff,uint addr);
	virtual bool createData(IECDataConfig &config);

public:
	uchar coi;

};

#endif // IEC101ASDU70DATA_H
