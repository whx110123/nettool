#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QByteArray>
#include "globaldefine.h"


class DataConfig
{
public:
	DataConfig();
};


class IECDataConfig :public DataConfig
{
public:
	IECDataConfig();

	QByteArray data;		//报文
	int state;				//状态
	bool isMaster;			//是否为主站
	uchar controltype;		//帧类型
	uchar asdutype;			//asdu类型
	bool sqflag;			//是否需要信息体地址
	bool isfirst;			//是否是第一个
};


#endif // DATACONFIG_H
