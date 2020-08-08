#ifndef IEC103ASDU_H
#define IEC103ASDU_H


#include <QByteArray>
#include <QString>
#include <dataconfig.h>
#include <mybase.h>


class IEC103AsduData : public MyBase
{
public:
	IEC103AsduData();
	~IEC103AsduData();

public:
	uchar inf;
public:
	QString infToText();
};

class IEC103Asdu : public MyBase
{
public:
	IEC103Asdu();
	~IEC103Asdu();
	virtual bool init(const QByteArray &buff);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	QString typeToText();
	QString vsqToText();
	QString cotToText();
	QString funToText();
	QString endToText();
	uchar type;
	uchar vsq;
	uchar cot;
	ushort commonaddr;
	uchar fun;
	uchar sqflag;				//SQ 1：每个信息元素都带地址
								//   0：只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1
	int datanum;                //信息元素的数量
	int cotlen ;				//cot长度
	int comaddrlen ;			//公共地址长度
	int endflag;				//结尾标识,用来识别报文最后一个字节的类型
	uchar end;
	QList<IEC103AsduData *> datalist;
private:
	IEC103AsduData *CreateAsduData(uchar type);
};

#endif // IEC103ASDU_H
