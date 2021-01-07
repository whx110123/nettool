#ifndef PROTOCOL103WISCOMNET_H
#define PROTOCOL103WISCOMNET_H

#include "protocol103asdu.h"
#include "globaldefine.h"
namespace protocol103
{

//#define ITYPE 1             //编号的信息传输   I帧
//#define STYPE 2             //编号的监视功能   S帧
//#define UTYPE 3             //未编号的控制功能  U帧

	typedef struct
	{
		uchar flag;
		uchar length[2];
		uchar control[4];
		uchar source_factory_addr;
		uchar source_dev_addr[2];
		uchar destination_factory_addr;
		uchar destination_dev_addr[2];
		uchar reserve[2];
	} APCI103WISCOMNET;

	typedef  struct
	{
		APCI103WISCOMNET apci;
		ASDU asdu;
		int length; //报文总长度，apci+asdu的长度
	} APDU103WISCOMNET;

	class protocol103wiscomnet : public protocol103asdu
	{
	public:
		protocol103wiscomnet();
		~protocol103wiscomnet();

	public:
		QString dealAPDU();         //分析报文，返回详细说明
		int CharT0APDU(char *data, int len);
		QString dealERR(int err);
	public:
		APDU103WISCOMNET *m_apdu;
		int APCIType;

	private:
		QString dealAPCI();
		QString dealUControl();
		QString dealSControl();
		QString dealIControl();

	};
}
#endif // PROTOCOL103WISCOMNET_H
