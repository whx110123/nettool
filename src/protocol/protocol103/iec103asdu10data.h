#ifndef IEC103ASDU10DATA_H
#define IEC103ASDU10DATA_H

#include "iec103asdu.h"

class IEC103AsduDataSetGdd;
class IEC103AsduDataSetGid : public MyBase
{
public:
	IEC103AsduDataSetGid();
	~IEC103AsduDataSetGid();
	virtual bool init(const QByteArray &buff, uchar *ch);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	QString gbkstr;
	QString bit8;
	float datafloat;
	short datashort;
	uint datauint;
	uint datauint1;
	int dataint;
	uchar datauchar;
	uchar datauchar1;
	QDateTime datat;
	QList<IEC103AsduDataSetGdd *> gddlist;
};

class IEC103AsduDataSetGdd : public MyBase
{
public:
	IEC103AsduDataSetGdd();
	~IEC103AsduDataSetGdd();
	virtual bool init(const QByteArray &buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar gdd[3];
	int gidnum;
	QList<IEC103AsduDataSetGid *> gidlist;
};

class IEC103AsduDataSet : public MyBase
{
public:
	IEC103AsduDataSet();
	~IEC103AsduDataSet();
	virtual bool init(const QByteArray &buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar gin[2];
	uchar kod;
	IEC103AsduDataSetGdd mygdd;
};

class IEC103Asdu10Data : public IEC103AsduData
{
public:
	IEC103Asdu10Data();
	~IEC103Asdu10Data();
	virtual bool init(const QByteArray &buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar rii;
	uchar ngd;
	uchar datacount;
	uchar datacont;
	int setnum;
	QList<IEC103AsduDataSet *> setlist;

};

#endif // IEC103ASDU10DATA_H
