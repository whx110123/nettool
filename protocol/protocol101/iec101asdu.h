#ifndef IEC101ASDU_H
#define IEC101ASDU_H

#include <QByteArray>
#include <QString>
#include <dataconfig.h>

class IEC101asdudata
{
public:
	IEC101asdudata();
	virtual ~IEC101asdudata();
	virtual bool init(QByteArray buff)= 0;
	virtual bool init(QByteArray buff,uint addr)=0;
	virtual QString showToText()=0;
	virtual bool createDate(IECDataConfig &config)=0;

public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;
public:
	uint infaddr;
};

class IEC101asdu
{
public:
	IEC101asdu();
	virtual ~IEC101asdu();
	virtual bool init(QByteArray buff)=0;				//初始化
	virtual QString showToText()=0;					//显示到文本
	virtual bool createDate(IECDataConfig &config)=0;

public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;

public:
	bool initCommon(QByteArray buff,int &i);				//初始化公共部分
	QString typeToText();
	QString vsqToText();
	QString cotToText();
	uchar type;
	uchar vsq;
	uchar cot[2];
	uint commonaddr;
	int sqflag;                 //SQ 0：信息元素单个排列，每个信息元素都带地址
								//   1：信息元素顺序排列，只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1
	int datanum;                //信息元素的数量
	int datalen;                //每个信息元素数据的字节数
	int timelen;                //每个信息元素时间的字节数
	int other;                  //信息元素之外的字节数
};

#endif // IEC101ASDU_H
