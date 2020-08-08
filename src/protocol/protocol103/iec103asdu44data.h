#ifndef IEC103ASDU44DATA_H
#define IEC103ASDU44DATA_H

#include "iec103asdu.h"



class IEC103Asdu44Data : public IEC103AsduData
{
public:
	IEC103Asdu44Data();
	~IEC103Asdu44Data();
	virtual bool init(const QByteArray &buff);
	virtual bool init(const QByteArray &buff, uint addr);

private:
	QString yxToText();
	QString yxFlagToText();
public:
	ushort yx16;
	ushort yx16flag;
	uchar qds;
};

#endif // IEC103ASDU44DATA_H
