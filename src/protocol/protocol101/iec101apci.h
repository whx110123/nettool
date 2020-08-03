#ifndef IEC101APCI_H
#define IEC101APCI_H

#include <dataconfig.h>
#include <mybase.h>

class IEC101Code : public MyBase
{
public:
	IEC101Code();
	~IEC101Code();
	virtual bool init(QByteArray buff);
	virtual bool createData(IECDataConfig &config);

public:
	uchar mcode;		//功能码
};

class IEC101Apci : public MyBase
{
public:
	IEC101Apci();
	~IEC101Apci();
	virtual bool init(QByteArray buff);
	virtual bool createData(IECDataConfig &config);

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
