#ifndef PROTOCOL101ASDU_H
#define PROTOCOL101ASDU_H

#include "globaldefine.h"
//#include "protocoliec.h"
#include <QString>

namespace  protocol101
{

	typedef struct
	{
		uchar addr[3];
		uchar data[5];
		uchar time[7];
	} GROUPDATA;

	typedef struct
	{
		uchar type;
		uchar vsq;
		uchar cot[2];
		uchar commonaddr[2];
		uchar data[245];        //存放数据元素GROUPDATA以及other相关信息
		GROUPDATA *groupdata;
		uchar other[100];
		int length;
	} ASDU;


	class protocol101asdu
	{
	public:
		protocol101asdu();
		~protocol101asdu();
//    protocoltelecontrol(ASDU *asdu);

	public:

		QString dealTYPE();
		QString dealCOT();          //解析COT，返回详细说明
		QString dealVSQ();          //解析VSQ，返回详细说明
		QString dealSPI();
		QString dealDPI();
		QString dealSCS();
		QString dealDCS();
		QString dealBL();
		QString dealSB();
		QString dealNT();
		QString dealIV();
		QString dealOV();
		QString dealQOI();
		QString dealCOI();
		QString dealRQT();
		QString dealFRZ();
		QString dealSU();
		QString dealQU();
		QString dealSE();
		QString dealCA();
		QString dealCY();
		QString dealVTI();
		QString dealQOS();

		QString dealASDU();         //解析ASDU，返回详细说明
		QString dealASDU1Data(int index);        //解析单个ASDU1信息元素数据
		QString dealASDU3Data(int index);
		QString dealASDU9Data(int index);
		QString dealASDU13Data(int index);
		QString dealASDU15Data(int index);
		QString dealASDU21Data(int index);
		QString dealASDU30Data(int index);
		QString dealASDU31Data(int index);
		QString dealASDU32Data(int index);
		QString dealASDU45Data(int index);
		QString dealASDU46Data(int index);
		QString dealASDU50Data(int index);
		QString dealASDU70Data(int index);
		QString dealASDU100Data(int index);
		QString dealASDU101Data(int index);
		QString dealASDU103Data(int index);
		QString dealASDU137Data(int index);
		QString dealASDU167();

		void charToASDUDate();              //将报文写入到GROUPDATA结构体里面
		QString dealOTHER();
		QString dealDateTime(int index);    //解析时间报文

	public:
		ASDU *m_asdu;
		int sqflag;                 //SQ 0：信息元素单个排列，每个信息元素都带地址
		//   1：信息元素顺序排列，只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1
		int datanum;                //信息元素的数量
		int datalen;                //每个信息元素数据的字节数
		int timelen;                //每个信息元素时间的字节数
		int other;                  //信息元素之外的字节数
		uchar res;                    //RES 未定义的bit位  保留
		uchar iv;                     //IV bit位8  0：有效，1：无效
		uchar nt;                     //NT bit位7  0：当前值，1：非当前值
		uchar sb;                     //SB bit位6  0：未被取代，1：被取代
		uchar bl;                     //BL bit位5  0：未被闭锁，1：被闭锁
		uchar spi;                    //SPI bit位1  0：单点遥信分位，1：单点遥信合位
		uchar dpi;                  //DPI bit1-2 双点遥信
		uchar scs;
		uchar dcs;
		uchar ov;                   //OV bit位1  0：未溢出，1：溢出
		uchar qoi;                  //QOI 召唤限定词，总召唤或分组召唤
		uchar coi;                  //COI 初始化原因
		uchar su;                   //SU 0：标准时间 1：夏季时间
		uchar qu;
		uchar se;
		uchar ql;
		uchar sqindex;
		uchar cy;
		uchar ca;
		uchar rqt;
		uchar frz;
		uchar vti;
		uchar qos;

		int cotlen;                 //传送原因字节数
		int comaddrlen;             //公共地址字节数
		int dataaddrlen;            //信息体地址字节数
	};
}
#endif // PROTOCOL101ASDU_H
