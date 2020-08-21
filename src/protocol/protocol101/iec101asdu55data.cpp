#include "iec101asdu55data.h"

IEC101Asdu55Data::IEC101Asdu55Data()
{

}

IEC101Asdu55Data::~IEC101Asdu55Data()
{

}

bool IEC101Asdu55Data::init(const QByteArray &buff)
{

}

QString IEC101Asdu55Data::showToText()
{

}

bool IEC101Asdu55Data::createData(IECDataConfig &config)
{

}

QString IEC101Asdu55Data::codeToText()
{
	QString text = "序列控制命令限定词:" + QString::number(code&0x7f) + " ";
	switch(code & 0x7f)
	{
	case 0:
		text.append("序列控制操作票调阅");
		break;
	case 1:
		text.append("序列控制操作预演");
		break;
	case 2:
		text.append("序列控制操作取消");
		break;
	case 3:
		text.append("序列控制操作执行");
		break;
	case 4:
		text.append("序列控制操作暂停");
		break;
	case 5:
		text.append("序列控制操作继续");
		break;
	case 6:
		text.append("序列控制操作终止");
		break;
	case 7:
		text.append("序列控制单步结果确认");
		break;
	case 11:
		text.append("序列控制成功");
		break;
	case 12:
		text.append("序列控制失败");
		break;
	case 13:
		text.append("预演成功");
		break;
	case 14:
		text.append("预演失败");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("   (bit8):") + QString::number(code & 0x80, 16).toUpper() + " ";
	if(code & 0x80)
	{
		text.append("有后续命令字段");
	}
	else
	{
		text.append("无后续命令字段");
	}
	return text;
}

QString IEC101Asdu55Data::stepToText()
{

}
