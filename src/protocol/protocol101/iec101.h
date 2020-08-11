#ifndef IEC101_H
#define IEC101_H

#include "iec101apci.h"
#include "iec101asdu.h"

#include <dataconfig.h>
#include <mybase.h>



class IEC101 : public MyBase
{
public:
	IEC101();
	~IEC101();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	IEC101Apci apci;
	IEC101Asdu asdu;
	uchar crc;
	uchar end;
};

#endif // IEC101_H
