#ifndef MEASUREDTERMINALASDU_H
#define MEASUREDTERMINALASDU_H

#include <mybase.h>


class MeasuredTerminalAsduData : public MyBase
{
public:
	MeasuredTerminalAsduData();
	~MeasuredTerminalAsduData();
	virtual bool init(const QByteArray& buff);
	virtual bool handle(const QByteArray& buff);				//单独处理数据

public:
	QString DAToText();
	QString DIToText();
	uchar DA[2];							//信息点标识
	uchar DI[4];							//数据标识编码

	QDateTime dt1;							//数据时间1
	QDateTime dt2;							//数据时间2
	uchar density;							//数据密度

};

class MeasuredTerminalAsdu : public MyBase
{
public:
	MeasuredTerminalAsdu();
	~MeasuredTerminalAsdu();
	virtual bool init(const QByteArray& buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig& config);

public:
	QString afnToText();
	QString seqToText();
	uchar afn;								//应用层功能码
	uchar seq;								//帧序列域
	QList<MeasuredTerminalAsduData *> datalist;
	uchar pw[16];							//消息验证码
	QDateTime dt;							//启动帧发送时标
	uchar delayTime;						//允许发送传输延时时间
	uchar flag;								//功能标志，用于记录功能码对应的报文内容
private:
	MeasuredTerminalAsduData *CreateAsduData(uchar type);
};

#endif // MEASUREDTERMINALASDU_H
