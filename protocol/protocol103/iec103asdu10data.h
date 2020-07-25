#ifndef IEC103ASDU10DATA_H
#define IEC103ASDU10DATA_H

#include "iec103asdu.h"
class IEC103AsduDataSetGid : public MyBase
{
public:
	IEC103AsduDataSetGid();
	~IEC103AsduDataSetGid();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual bool init(QByteArray buff, uchar *ch);
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
};

class IEC103AsduDataSet : public MyBase
{
public:
	IEC103AsduDataSet();
	~IEC103AsduDataSet();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual bool init(QByteArray buff, uchar *ch);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar gin[2];
	uchar kod;
	uchar gdd[3];
	int gidnum;
	QList<IEC103AsduDataSetGid *> gidlist;
};

class IEC103Asdu10Data : public IEC103AsduData
{
public:
	IEC103Asdu10Data();
	~IEC103Asdu10Data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual bool init(QByteArray buff, uchar *ch);
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
