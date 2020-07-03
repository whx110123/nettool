#ifndef IEC104_H
#define IEC104_H

#include <QByteArray>
#include <QString>
/*******************************************************************************/

enum
{
	ITYPE = 1,
	UTYPE,
	STYPE
};


class IEC104Control
{
public:
	IEC104Control();
	virtual ~IEC104Control();
	virtual bool init(QByteArray buff)=0;				//初始化
	virtual QString showToText()=0;					//显示到文本

public:
	QByteArray mBAdata;
	QString mText;
	int error;
	int type;
};

class IEC104IControl : public IEC104Control			//I帧
{
public:
	IEC104IControl();
	~IEC104IControl();
	virtual bool init(QByteArray buff);				//初始化
	virtual QString showToText();					//显示到文本

public:
//	void handleNo();
public:
	ushort sendNo;
	ushort recvNo;

};
class IEC104UControl : public IEC104Control			//U帧
{
public:
	IEC104UControl();
	virtual bool init(QByteArray buff);				//初始化
	virtual QString showToText();					//显示到文本

public:

public:
	uchar code;
	uchar reserve[3];
};
class IEC104SControl : public IEC104Control			//S帧
{
public:
	IEC104SControl();
	virtual bool init(QByteArray buff);				//初始化
	virtual QString showToText();					//显示到文本

public:

public:
	uchar reserve[2];
	ushort recvNo;
};
/************************************************************************************/
class IEC104apci
{
public:
	IEC104apci();
	~IEC104apci();
	bool init(QByteArray buff);				//初始化
	QString showToText();					//显示到文本

public:
	QByteArray mBAdata;
	QString mText;
	int error;
	uchar first;
	uchar length;
	IEC104Control *control;

};

class IEC104
{
public:
	IEC104();
	~IEC104();
	bool init(QByteArray buff);
	QString showToText();

public:
	QByteArray mBAdata;
	QString mText;
	int error;
	IEC104apci *apci;

};

#endif // IEC104_H
