#ifndef IEC103ASDU42DATA_H
#define IEC103ASDU42DATA_H

#include "iec103asdu.h"



class IEC103Asdu42Data : public IEC103AsduData
{
public:
	IEC103Asdu42Data();
	~IEC103Asdu42Data();
	virtual bool init(const QByteArray &buff);
	virtual bool createData(IECDataConfig &config);

public:
	QString funToText();
	uchar fun;
	uchar diq;
};

#endif // IEC103ASDU42DATA_H
