#ifndef IEC101ASDU45DATA_H
#define IEC101ASDU45DATA_H
#include "iec101asdu.h"


class IEC101Asdu45Data : public IEC101AsduData
{
public:
	IEC101Asdu45Data();
	~IEC101Asdu45Data();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar sco;
};

#endif // IEC101ASDU45DATA_H
