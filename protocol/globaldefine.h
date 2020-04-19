#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#include <QString>
#include <QDateTime>
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int  uint;

#define BCDTIME1 0          //BCD时间1
#define BINARYTIME1 1       //二进制时间1
#define BINARYTIME2A 2      //二进制时间2a
#define BINARYTIME2B 3      //二进制时间2b
#define BINARYTIME2C 4      //二进制时间2c

QString CharToHexStr(uchar data);           //将一个uchar字符转换成2个字符的16进制QString
uint charTouint(uchar *data,int len,int model = 0);      //将len个uchar合成一个uint,model 0:低字节在前
int charToint(uchar *data,int len,int model = 0);      //将4个uchar合成一个int,model 0:低字节在前 1:高字节在前
short charToshortwithQ(uchar *data,uchar &ov,uchar &er,int model = 0);
float charTofloat(uchar *data,int model = 0);
QDateTime charToDateTime(uchar *data,int len,int model);//将len个uchar合成一个日期,model时间类型



#define IEC104 "104"
#define IEC101 "101"
#define IEC103WISCOMNET "金智网络103"
#define IEC103COM "串口103"


#endif // GLOBALDEFINE_H
