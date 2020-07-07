#ifndef PROTOCOL101APDU_H
#define PROTOCOL101APDU_H
#include "protocol101asdu.h"

namespace  protocol101{

typedef struct
{
    uchar flag1;
    uchar len1;
    uchar len2;
    uchar flag2;
    uchar ctrl;
    uchar addr;
}APCI101;

typedef  struct
{
    APCI101 apci;
    ASDU asdu;
    uchar crc;
    uchar last;
    int length; //报文总长度，apci+asdu的长度
}APDU101;

class protocol101apdu : public protocol101asdu
{
public:
    protocol101apdu();
    ~protocol101apdu();
public:
    QString dealAPDU();         //分析报文，返回详细说明
    int CharT0APDU(char *data,int len);
    QString dealERR(int err);

public:
    APDU101 *m_apdu;
    uchar prm;                  //启动报文位
    uchar fcb;                  //帧计数位
    uchar fcv;                  //帧计数有效位
    uchar acd;                  //要求访问位
    uchar dfc;                  //数据流控制位
    uchar cw1;                  //非平衡传输，启动站向从动站传输的报文控制域的功能码(PRM=1)
    uchar cw2;                  //非平衡传输，从动站向启动站传输的报文控制域的功能码(PRM=0)

private:
    QString dealAPCI();
    QString dealCTRL();
    QString dealPRM();
    QString dealFCB();
    QString dealFCV();
    QString dealACD();
    QString dealDFC();
    QString dealCW1();
    QString dealCW2();
    QString dealCRC();

};




}
#endif // PROTOCOL101APDU_H
