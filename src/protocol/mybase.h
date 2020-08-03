#ifndef MYBASE_H
#define MYBASE_H

#include "dataconfig.h"

#include <QByteArray>

class MyBase
{
public:
	MyBase();
	virtual ~MyBase();
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual bool init(QByteArray buff, uchar *ch);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

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
