#ifndef IEC103ASDU21DATA_H
#define IEC103ASDU21DATA_H

#include "iec103asdu.h"
#include "dataconfig.h"
#include "iec103asdu10data.h"



class IEC103asdu21data : public IEC103asdudata
{
public:
	IEC103asdu21data();
	~IEC103asdu21data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar rii;
	uchar nog;
//	uchar datacount;
//	uchar datacont;
//	int setnum;
	QList<IEC103asdudataset *> setlist;
};

#endif // IEC103ASDU21DATA_H
