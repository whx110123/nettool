#ifndef IEC103ASDU10DATA_H
#define IEC103ASDU10DATA_H

#include "iec103asdu.h"
class IEC103asdudatasetgid
{
public:
	IEC103asdudatasetgid();
	~IEC103asdudatasetgid();
	bool init(QByteArray buff,uchar *gdd);				//初始化
	QString showToText();								//显示到文本
	bool createData(IECDataConfig &config);

public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;
	int len;

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

class IEC103asdudataset
{
public:
	IEC103asdudataset();
	~IEC103asdudataset();
	bool init(QByteArray buff);				//初始化
	bool init(QByteArray buff, uchar *ch);
	QString showToText();					//显示到文本
	bool createData(IECDataConfig &config);

public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;
	int len;

public:
	uchar gin[2];
	uchar kod;
	uchar gdd[3];
	int gidnum;
	QList<IEC103asdudatasetgid *> gidlist;
};

class IEC103asdu10data : public IEC103asdudata
{
public:
	IEC103asdu10data();
	~IEC103asdu10data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar rii;
	uchar ngd;
	uchar datacount;
	uchar datacont;
	int setnum;
	QList<IEC103asdudataset *> setlist;

};

#endif // IEC103ASDU10DATA_H
