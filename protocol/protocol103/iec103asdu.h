﻿#ifndef IEC103ASDU_H
#define IEC103ASDU_H


#include <QByteArray>
#include <QString>
#include <dataconfig.h>

class IEC103asdudata
{
public:
	IEC103asdudata();
	virtual ~IEC103asdudata();
	virtual bool init(QByteArray buff)= 0;
	virtual bool init(QByteArray buff,uint addr)=0;
	virtual QString showToText()=0;
	virtual bool createData(IECDataConfig &config)=0;

public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;
public:
	uchar inf;
};

class IEC103asdu
{
public:
	IEC103asdu();
	~IEC103asdu();
	bool init(QByteArray buff);				//初始化
	QString showToText();					//显示到文本
	bool createData(IECDataConfig &config);

public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;

public:
	QString typeToText();
	QString vsqToText();
	QString cotToText();
	QString funToText();
	uchar type;
	uchar vsq;
	uchar cot;
	uchar commonaddr;
	uchar fun;
	uchar sqflag;				//SQ 1：每个信息元素都带地址
								//   0：只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1
	int datanum;                //信息元素的数量
	int asdulen;                //asdu长度
//	int timelen;                //每个信息元素时间的字节数
//	int other;                  //信息元素之外的字节数

	QList<IEC103asdudata *> datalist;
private:
	IEC103asdudata *CreateAsduData(uchar type);
};

#endif // IEC103ASDU_H
