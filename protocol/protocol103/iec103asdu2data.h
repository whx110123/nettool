#ifndef IEC103ASDU2DATA_H
#define IEC103ASDU2DATA_H

#include "iec103asdu.h"
#include "dataconfig.h"



class IEC103Asdu2Data : public IEC103AsduData
{
public:
	IEC103Asdu2Data();
	~IEC103Asdu2Data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar dpi;
	ushort ret;
	ushort fan;
	QDateTime datetime;
	uchar sin;
};

#endif // IEC103ASDU2DATA_H
