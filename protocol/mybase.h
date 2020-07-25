#ifndef MYBASE_H
#define MYBASE_H

#include "dataconfig.h"

#include <QByteArray>

class MyBase
{
public:
	MyBase();
	virtual ~MyBase();
	virtual bool init(QByteArray buff) = 0;
	virtual bool init(QByteArray buff, uint addr) = 0;
	virtual bool init(QByteArray buff, uchar *ch) = 0;
	virtual QString showToText() = 0;
	virtual bool createData(IECDataConfig &config) = 0;

public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;
	int len;
};

#endif // MYBASE_H
