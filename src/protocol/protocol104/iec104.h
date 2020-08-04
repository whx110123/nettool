﻿#ifndef IEC104_H
#define IEC104_H

#include "iec104apci.h"
#include "iec101asdu.h"
#include <QByteArray>
#include <QString>
#include <mybase.h>
#include "dataconfig.h"

class IEC104 : public MyBase
{
public:
	IEC104();
	~IEC104();
	virtual bool init(QByteArray buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	IEC104Apci apci;
	IEC101Asdu asdu;

};

#endif // IEC104_H