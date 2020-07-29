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
	QByteArray mRecvData;	//接收报文
	QByteArray mSendData;	//发送报文
	QString mText;			//解析
	int error;				//错误标识
	int masterState;		//主站状态
	int slaveState;			//子站状态
	int len;				//报文长度
};

#endif // MYBASE_H
