#ifndef MEASUREDTERMINALASDUDATA_H
#define MEASUREDTERMINALASDUDATA_H

#include <mybase.h>

class MTAsduData : public MyBase
{
public:
	MTAsduData();
	~MTAsduData();
	virtual bool init(const QByteArray& buff);

	void dataClear();									//清除所有数据
	bool handle(const QByteArray& buff);				//单独处理数据
	bool handleData_UINT32(const QByteArray& buff);

public:
	QString DAToText();
	QString DIToText();
	uchar flag;								//功能标志，用于记录功能码对应的报文内容
	uchar DA[2];							//信息点标识
	uchar DI[4];							//数据标识编码

	uchar dataTpye;							//数据类型
	ushort dataLength;						//数据长度
	uchar pointIndex;						//小数点位数

	QVector<uint> uintLst;

	QDateTime dt1;							//数据时间1
	QDateTime dt2;							//数据时间2
	uchar density;							//数据密度

};

#endif // MEASUREDTERMINALASDUDATA_H
