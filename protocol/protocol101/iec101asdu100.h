#ifndef IEC101ASDU100_H
#define IEC101ASDU100_H

#include "iec101asdu.h"
#include <QList>
#include <dataconfig.h>

class IEC101asdu100data : public IEC101asdudata
{
public:
	IEC101asdu100data();
	~IEC101asdu100data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff,uint addr);
	virtual QString showToText();
	virtual bool createDate(IECDataConfig &config);

public:
	uchar qoi;

};

class IEC101asdu100 : public IEC101asdu
{
public:
	IEC101asdu100();
	~IEC101asdu100();
	virtual bool init(QByteArray buff);				//初始化
	virtual QString showToText();					//显示到文本
	virtual bool createDate(IECDataConfig &config);

public:
	QList<IEC101asdu100data *> datalist;
};

#endif // IEC101ASDU100_H
