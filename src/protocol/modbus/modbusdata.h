#ifndef MODBUSDATA_H
#define MODBUSDATA_H

#include <mybase.h>

struct ModbusDataGroup
{
	uchar dataLen;		//应答报文数据字节数
	QString type;		//数据类型
	QString analysis;	//解析码
	QString sort;		//顺序
};

class ModbusData : public MyBase
{
public:
	ModbusData();
	~ModbusData();
	bool initData(const QByteArray& buff, ModbusDataGroup *group);

public:
	QString mtype;		//类型
	QChar mcode;		//解析码

	char datachar;
	uchar datauchar;
	short datashort;
	ushort dataushort;
	int dataint;
	uint datauint;
	float datafloat;
	double datadouble;
	QDateTime datetime;
};

#endif // MODBUSDATA_H
