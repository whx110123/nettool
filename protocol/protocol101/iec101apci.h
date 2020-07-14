#ifndef IEC101APCI_H
#define IEC101APCI_H

#include <dataconfig.h>

class IEC101Code
{
public:
	IEC101Code();
	~IEC101Code();
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
	uchar mcode;		//功能码
};

class IEC101apci
{
public:
	IEC101apci();
	~IEC101apci();
	bool init(QByteArray buff);				//初始化
	QString showToText();					//显示到文本
	bool createData(IECDataConfig &config);

public:
	QByteArray mRecvData;
	QByteArray mSendData;
	QString mText;
	int error;
	int mstate;
	int len;

public:
	uchar flag1;
	uchar length1;
	uchar length2;
	uchar flag2;
	IEC101Code code;
	uchar addr;
	uchar length;	//计算出此帧101报文的总长度
};

#endif // IEC101APCI_H
