﻿#ifndef IEC101ASDU1_H
#define IEC101ASDU1_H

#include "iec101asdu.h"
#include <QList>
#include <dataconfig.h>

class IEC101asdu1data : public IEC101asdudata
{
public:
	IEC101asdu1data();
	~IEC101asdu1data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createDate(IECDataConfig &config);

public:
	uchar siq;

};

class IEC101asdu1 : public IEC101asdu
{
public:
	IEC101asdu1();
	~IEC101asdu1();
	virtual bool init(QByteArray buff);				//初始化
	virtual QString showToText();					//显示到文本
	virtual bool createDate(IECDataConfig &config);

public:
	QList<IEC101asdu1data *> datalist;
};

#endif // IEC101ASDU1_H
