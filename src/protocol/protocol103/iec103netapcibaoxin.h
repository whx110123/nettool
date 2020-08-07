#ifndef IEC103NETAPCIBAOXIN_H
#define IEC103NETAPCIBAOXIN_H

#include <iec104apci.h>

class IEC103NetApciBaoXin : public MyBase
{
public:
	IEC103NetApciBaoXin();
	~IEC103NetApciBaoXin();
	virtual bool init(QByteArray buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	uchar first;
	ushort length;
	IEC104Control control;
};

#endif // IEC103NETAPCIBAOXIN_H
