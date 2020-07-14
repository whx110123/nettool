#ifndef IEC101_H
#define IEC101_H

#include "iec101apci.h"
#include "iec101asdu.h"

#include <dataconfig.h>



class IEC101
{
public:
	IEC101();
	~IEC101();
	bool init(QByteArray buff);
	QString showToText();
	bool createData(IECDataConfig &config);
public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;
	int len;
public:
	IEC101apci apci;
	IEC101asdu asdu;
	uchar crc;
	uchar end;
};

#endif // IEC101_H
