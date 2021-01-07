#ifndef PROTOCOL103ASDU_H
#define PROTOCOL103ASDU_H

#include "globaldefine.h"

namespace protocol103
{

	typedef struct
	{
		uchar gin[2];
		uchar kod;
		uchar gdd[3];
		uchar number;       //数据个数，由gdd3计算所得
		uchar gid[1000];
		ushort gidlen;      //gid总字节数
	} GROUPDATA;            //通用分类数据组

	typedef struct
	{
		uchar type;
		uchar vsq;
		uchar cot;
		uchar commonaddr;
		uchar data[1004];

		int length;
	} ASDU;

	class protocol103asdu
	{
	public:
		protocol103asdu();
		~protocol103asdu();

	public:
		QString dealASDU();
		QString dealTYPE();
		QString dealCOT();          //解析COT，返回详细说明
		QString dealVSQ();          //解析VSQ，返回详细说明
		QString dealFUN();
		QString dealINFGEN();
		QString dealNGD();
		QString dealKOD(uchar kod);
		QString dealGDDandGID(GROUPDATA *gpdata);
		QString dealGDD3(GROUPDATA *gpdata);
		QString dealGID(GROUPDATA *gpdata, int index);
		QString dealOV();
		QString dealER();
		QString dealDPI();
		QString dealDPITE();
		QString dealSPI();
		QString dealIV();
		QString dealBL();
		QString dealSB();
		QString dealNT();
		QString dealSU();

		QString dealASDU1Data();
		QString dealASDU2Data();
		QString dealASDU6Data();
		QString dealASDU7Data();
		QString dealASDU10Data();
		QString dealASDU44Data();
		QString dealASDU50Data();
		QString dealASDU51Data();

		uchar charToGroupDate(uchar *data, GROUPDATA *gpdata);             //将报文写入到GROUPDATA结构体里面,返回GROUPDATA总长度
		QString dealDateTime(uchar *time, int timelen);   //解析时间报文
	public:
		ASDU *m_asdu;
		int sqflag;                 //SQ 0:信息元素单个排列，每个信息元素都带地址
		//   1:信息元素顺序排列，只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1
		int datanum;                //信息元素的数量
		uchar fun;
		uchar infgen;
		uchar inf;
		uchar rii;
		uchar ngd;
		uchar no;
		uchar count;
		uchar cont;
		GROUPDATA *gpdata;
		uchar ov;
		uchar er;
		uchar dpi;
		uchar spi;
		uchar iv;
		uchar bl;
		uchar sb;
		uchar nt;
		uchar su;
	};
}
#endif // PROTOCOL103ASDU_H
