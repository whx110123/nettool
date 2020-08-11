#ifndef PROTOCOL104APDU_H
#define PROTOCOL104APDU_H

#include "globaldefine.h"
#include "protocol101asdu.h"
#include <QString>

namespace  protocol101
{



//#define ITYPE 1             //编号的信息传输   I帧
//#define STYPE 2             //编号的监视功能   S帧
//#define UTYPE 3             //未编号的控制功能  U帧

	typedef struct
	{
		uchar flag;
		uchar length;
		uchar control[4];
	} APCI104;

	typedef  struct
	{
		APCI104 apci;
		ASDU asdu;
		int length; //报文总长度，apci+asdu的长度
	} APDU104;

	class protocol104apdu : public protocol101asdu
	{
	public:
		protocol104apdu();
		~protocol104apdu();
//    protocol104(APDU *apdu);


	public:

		QString dealAPDU();         //分析报文，返回详细说明
		int CharT0APDU(char *data, int len);
		QString dealERR(int err);

	public:
//    int APCIType;
		APDU104 *m_apdu;
//    ushort sendNum;             //发送序号
//    ushort receiveNum;          //接收序号

	private:
		QString dealAPCI();
		QString dealUControl();
		QString dealSControl();
		QString dealIControl();

	};
}

#endif // PROTOCOL104APDU_H
