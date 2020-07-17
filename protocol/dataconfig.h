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
	~IECDataConfig();
	QByteArray data;		//报文
	QByteArray userdata;	//自定义asdu报文
	int state;				//状态
	bool isMaster;			//是否为主站
	uchar controltype;		//帧类型
	uchar asdutype;			//asdu类型
	uchar cot;              //传送原因
	uchar vsq;              //信息元素个数
	uchar fun;
	uchar inf;
	uchar rii;
	uchar ngd;
	bool isfirst;			//是否是第一个
	IECDataConfig *iec103config;
	ushort devaddr;
};


#endif // DATACONFIG_H
