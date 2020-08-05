#ifndef IEC101ASDU_H
#define IEC101ASDU_H

#include <QByteArray>
#include <QString>
#include <dataconfig.h>
#include <mybase.h>

class IEC101AsduData : public MyBase
{
public:
	IEC101AsduData();
	virtual ~IEC101AsduData();

public:
	uint infaddr;
	int infaddrlen ;			//信息体地址长度
};

class IEC101Asdu : public MyBase
{
public:
	IEC101Asdu();
	~IEC101Asdu();
	virtual bool init(QByteArray buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	QString typeToText();
	QString vsqToText();
	QString cotToText();
	uchar type;
	uchar vsq;
	uchar cot[2];
	uint commonaddr;
	int sqflag;                 //SQ 0：每个信息元素都带地址
								//   1：只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1
	int datanum;                //信息元素的数量
	int datalen;                //每个信息元素数据的字节数
	int other;                  //信息元素之外的字节数
	int cotlen ;					//cot长度
	int comaddrlen ;			//公共地址长度
	int infaddrlen ;			//信息体地址长度
	QList<IEC101AsduData *> datalist;

private:
	IEC101AsduData *CreateAsduData(uchar type);
};

#endif // IEC101ASDU_H
