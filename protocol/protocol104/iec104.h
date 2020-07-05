#ifndef IEC104_H
#define IEC104_H

#include "iec104apci.h"
#include "iec101asdu.h"
#include <QByteArray>
#include <QString>
#include "dataconfig.h"

class IEC104
{
public:
	IEC104();
	~IEC104();
	bool init(QByteArray buff);
	QString showToText();
	bool createDate(IECDataConfig &config);
public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;

public:
	IEC104apci apci;
	IEC101asdu *asdu;

private:
	IEC101asdu *CreateAsdu(uchar type);
};

#endif // IEC104_H
