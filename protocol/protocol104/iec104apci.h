#ifndef IEC104APCI_H
#define IEC104APCI_H

//#include "iec104control.h"

#include <QByteArray>
#include <QString>
#include <dataconfig.h>

class IEC104Control
{
public:
	IEC104Control();
	~IEC104Control();
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
	uchar type;		//帧类型

	uchar code;		//功能码
	ushort remoteSendNo;	//对端接收序号
	ushort remoteRecvNo;	//对端发送序号
	ushort localSendNo;		//本地接收序号
	ushort localRecvNo;		//本地发送序号
};

class IEC104apci
{
public:
	IEC104apci();
	~IEC104apci();
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
	uchar first;
	uchar length;
	IEC104Control control;


};

#endif // IEC104APCI_H
