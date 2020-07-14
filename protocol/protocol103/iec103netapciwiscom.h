#ifndef IEC103NETAPCIWISCOM_H
#define IEC103NETAPCIWISCOM_H

#include <dataconfig.h>
#include <iec104apci.h>



class IEC103NETapciwiscom
{
public:
	IEC103NETapciwiscom();
	~IEC103NETapciwiscom();
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
	uchar first;					//启动字符
	ushort length;					//长度域
	IEC104Control control;			//104控制域
	uchar source_factory_addr;		//源厂站地址
	uchar source_dev_addr[2];		//源设备地址
	uchar destination_factory_addr;	//目的厂站地址
	uchar destination_dev_addr[2];	//目的设备地址
	uchar reserve[2];				//备用
};

#endif // IEC103NETAPCIWISCOM_H
