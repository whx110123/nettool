#ifndef IEC103NETWISCOM_H
#define IEC103NETWISCOM_H

#include "iec103asdu.h"
#include "iec103netapciwiscom.h"



class IEC103NETwiscom
{
public:
	IEC103NETwiscom();
	~IEC103NETwiscom();
	bool init(QByteArray buff);
	QString showToText();
	bool createData(IECDataConfig &config);
public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;

public:
	IEC103NETapciwiscom apci;
	IEC103asdu asdu;
};

#endif // IEC103NETWISCOM_H
