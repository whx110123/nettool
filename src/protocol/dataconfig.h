﻿#ifndef DATACONFIG_H
#define DATACONFIG_H

#include <QByteArray>
#include "globaldefine.h"


class DataConfig
{
public:
	DataConfig();
};


class IECDataConfig : public DataConfig
{
public:
	IECDataConfig();
	~IECDataConfig();
	QByteArray data;		//总报文
	QByteArray userdata;	//自定义asdu报文
	int masterState;		//主站状态
	int slaveState;			//子站状态
	bool isMaster;			//是否为主站
	/***数据*************************/
	bool isfirst;			//是否是第一个信息体
	uchar controltype;		//帧类型 I、U、S 帧
	uchar asdutype;			//asdu类型
	uchar cot;              //传送原因
	uint comaddr;			//公共地址
	uchar vsq;              //信息元素个数
	uint infaddr;			//信息体地址
	QByteArray infdata;		//信息体数据
	/***IEC103参数*************************/
	uchar fun;
	uchar inf;
	uchar rii;
	uchar ngd;				//通用分类数据集数目，包括GIN、KOD、GDD、GID
	uchar nog;				//通用分类标识数目，包括GIN、KOD
	uchar gin[20][2];
	uchar kod[20];
	uchar gdd[20][3];
	uchar gid[255];
	/***IEC104 167号报文************************/
	IECDataConfig *iec103config;
	ushort devaddr;
};


#endif // DATACONFIG_H
