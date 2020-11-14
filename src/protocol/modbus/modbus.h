#ifndef MODBUS_H
#define MODBUS_H

#include "modbusdata.h"

struct ModbusDataGroup
{
	uchar dataLen;		//应答报文数据字节数
	QString type;		//数据类型
	QString analysis;	//解析码
};

class Modbus : public MyBase
{
public:
	Modbus();
	~Modbus();
	virtual bool init(const QByteArray& buff);					//初始化

public:

	bool isMaster;			//召唤或应答
	uchar addr;			//设备地址
	uchar code;			//功能码

	ushort startAddr;	//起始地址
	ushort num;			//召唤个数,一般为寄存器数量

	QList<ModbusDataGroup *> groups;
	ModbusDataGroup mgroup;
	QList<ModbusData *> datalist;	//应答报文数据集合
};

#endif // MODBUS_H
