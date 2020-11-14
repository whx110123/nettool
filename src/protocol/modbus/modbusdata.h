#ifndef MODBUSDATA_H
#define MODBUSDATA_H

#include <mybase.h>



class ModbusData : public MyBase
{
public:
	ModbusData();
	~ModbusData();
	bool initData(const QByteArray& buff, QString type, QChar analysisCode);

public:
	QString mtype;		//类型
	QChar mcode;		//解析码

	uchar datauchar;
	short datashort;
	ushort dataushort;
	int dataint;
	uint datauint;
	float datafloat;
	QDateTime datetime;
};

#endif // MODBUSDATA_H
