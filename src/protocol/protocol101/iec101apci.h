#ifndef IEC101APCI_H
#define IEC101APCI_H

#include <dataconfig.h>
#include <mybase.h>

class IEC101Code : public MyBase
{
public:
	IEC101Code();
	~IEC101Code();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar mcode;		//功能码
};

class IEC101Apci : public MyBase
{
public:
	IEC101Apci();
	~IEC101Apci();
	virtual bool init(const QByteArray& buff);
	virtual bool createData(IECDataConfig& config);

public:
	uchar flag1;
	uchar length1;
	uchar length2;
	uchar flag2;
	IEC101Code code;
	uchar addr;
};

#endif // IEC101APCI_H
