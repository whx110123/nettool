#ifndef MYBASE_H
#define MYBASE_H

#include "dataconfig.h"

#include <QByteArray>

class MyBase
{
public:
	MyBase();
	virtual ~MyBase();
	virtual bool init(QByteArray buff);					//初始化
	virtual bool init(QByteArray buff, uint addr);		//初始化
	virtual bool init(QByteArray buff, uchar *ch);		//初始化
	virtual QString showToText();						//显示解析结果
	virtual bool createData(IECDataConfig &config);		//生成报文
	void setDefault(QByteArray buff);
public:
	QByteArray mSendData;	//发送报文
	QByteArray mRecvData;	//接收报文
	int len;				//接收报文长度
	QString mText;			//解析
	int error;				//错误标识
	int masterState;		//主站状态
	int slaveState;			//子站状态
};

#endif // MYBASE_H
