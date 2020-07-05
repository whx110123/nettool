#ifndef IEC101ASDU13_H
#define IEC101ASDU13_H

#include "iec101asdu.h"
#include <QList>

class IEC101asdu13data : public IEC101asdudata
{
public:
	IEC101asdu13data();
	~IEC101asdu13data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createDate(IECDataConfig &config);

public:
	float floatdata;
	uchar qds;

};

class IEC101asdu13 : public IEC101asdu
{
public:
	IEC101asdu13();
	~IEC101asdu13();
	virtual bool init(QByteArray buff);				//初始化
	virtual QString showToText();					//显示到文本
	virtual bool createDate(IECDataConfig &config);

public:
	QList<IEC101asdu13data *> datalist;
};

#endif // IEC101ASDU13_H
