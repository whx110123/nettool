#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QString>
#include <QDateTime>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int  uint;

enum
{
	ITYPE = 1,
	UTYPE,
	STYPE
};

enum
{
	STATE_NODATA,				//无数据
	STATE_INIT,					//初始化
	STATE_CALLALL,				//发送总召
	STATE_NORMAL,				//正常,状态,回复S帧
	STATE_TESTACT,				//激活测试
	STATE_TESTCONFIRM,			//确认测试
	STATE_USER,					//自定义ASDU
	STATE_HOTKEY,				//通过点击快捷键
	STATE_NUM					//所有状态的数目
};
enum
{
	BCDTIME1 = 0,		//BCD时间1
	BINARYTIME1,		//二进制时间1
	BINARYTIME2A,		//二进制时间2a
	BINARYTIME2B,		//二进制时间2b
	BINARYTIME2C		//二进制时间2c
};
    

QString CharToHexStr(uchar data);           //将一个uchar字符转换成2个字符的16进制QString
QString CharToHexStr(char *data,int len=1);
QString CharToHexStr(uchar *data, int len = 1);
uint charTouint(char *data,int len,int model = 0);
uint charTouint(uchar *data,int len,int model = 0);      //将len个uchar合成一个uint,model 0:低字节在前
int charToint(uchar *data,int len,int model = 0);      //将4个uchar合成一个int,model 0:低字节在前 1:高字节在前
int charToint(char *data, int len, int model = 0);      //将4个char合成一个int,model 0:低字节在前 1:高字节在前
short charToshortwithQ(uchar *data,uchar &ov,uchar &er,int model = 0);
short charToshortwithQ(uchar *data, int model = 0);
short charToshortwithQ(char *data, int model = 0);
float charTofloat(char *data,int model = 0);
float charTofloat(uchar *data,int model = 0);
QDateTime charToDateTime(uchar *data,int len,int model);//将len个uchar合成一个日期,model时间类型
QDateTime charToDateTime(char *data, int len, int model);//将len个char合成一个日期,model时间类型

QByteArray uintToBa(uint data,int len);
QByteArray floatToBa(float data);
QByteArray dateTimeToBa(QDateTime datatime, int len, int model);

uchar crcsum(char *data,int start,int end);



#define IEC_104 "104"
#define IEC_101 "101"
#define IEC_103WISCOMNET "金智网络103"
#define IEC_103COM "串口103"
#define IEC_103ASDU "103ASDU"

#endif // GLOBALDEFINE_H
