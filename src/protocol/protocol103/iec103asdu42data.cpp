#include "iec103asdu42data.h"
#include "functotext.h"

IEC103Asdu42Data::IEC103Asdu42Data()
{
	diq = 0;
}

IEC103Asdu42Data::~IEC103Asdu42Data()
{

}

bool IEC103Asdu42Data::init(const QByteArray &buff)
{
	setDefault(buff);

	fun = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + funToText() + "\r\n");
	len++;

	inf = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;

	diq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + dpiToText(diq) + "   " + ivToText(diq) + "   " + ntToText(diq) + "   " + sbToText(diq) + "   " + blToText(diq) + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}


bool IEC103Asdu42Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

QString IEC103Asdu42Data::funToText()
{
	QString text = "FUN:"+ QString::number(fun) + " ";
	switch (fun)
	{
	case 251:
		text.append("二次设备运行状态（分:检修 | 合:正常）（保信规约专用），此时INF表示装置地址");
		break;
	case 252:
		text.append("装置定值变化（保信规约专用），此时INF表示装置地址");
		break;
	case 253:
		text.append("二次设备通信状态（分:断 | 合:通）（保信规约专用），此时INF表示装置地址");
		break;
	case 254:
		text.append("通用分类功能类型GEN");
		break;
	case 255:
		text.append("全局功能类型GLB");
		break;
	default:
		break;
	}
	return text;
}
