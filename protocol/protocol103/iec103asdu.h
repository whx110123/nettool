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
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual bool init(QByteArray buff, uchar *ch);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

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
	virtual bool init(QByteArray buff);
	virtual bool init(QByteArray buff, uint addr);
	virtual bool init(QByteArray buff, uchar *ch);
	virtual QString showToText();
	virtual bool createData(IECDataConfig &config);

public:
	QString typeToText();
	QString vsqToText();
	QString cotToText();
	QString funToText();
	uchar type;
	uchar vsq;
	uchar cot;
	uchar commonaddr;
	uchar fun;
	uchar sqflag;				//SQ 1：每个信息元素都带地址
								//   0：只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1
	int datanum;                //信息元素的数量
//	int timelen;                //每个信息元素时间的字节数
//	int other;                  //信息元素之外的字节数

	QList<IEC103AsduData *> datalist;
private:
	IEC103AsduData *CreateAsduData(uchar type);
};

#endif // IEC103ASDU_H
