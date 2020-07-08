#include "functotext.h"



QString spiToText(uchar ch)
{
	QString text = "单点遥信(bit1):" + QString::number(ch & 0x01) + " ";
	if(ch & 0x01)
	{
		text.append("合位");
	}
	else
	{
		text.append("分位");
	}
	return text;
}

QString dpiToText(uchar ch)
{
	QString text = "双点遥信DPI(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch (ch & 0x03)
	{
	case 1:
		text.append("分位");
		break;
	case 2:
		text.append("合位");
		break;
	default:
		text.append("未知状态");
		break;
	}
	return text;
}

QString scsToText(uchar ch)
{
	QString text = "单点命令(bit1):" + QString::number(ch & 0x01) + " ";
	if(ch & 0x01)
	{
		text.append("合");
	}
	else
	{
		text.append("分");
	}
	return text;
}

QString dcsToText(uchar ch)
{
	QString text = "双点命令(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch (ch & 0x03)
	{
	case 1:
		text.append("分");
		break;
	case 2:
		text.append("合");
		break;
	default:
		text.append("不允许");
		break;
	}
	return text;
}

QString blToText(uchar ch)
{
	QString text = "BL(bit5):" + QString::number(ch & 0x10,16).toUpper() + " ";
	if(ch & 0x10)
	{
		text.append("被闭锁");
	}
	else
	{
		text.append("未被闭锁");
	}
	return text;
}

QString sbToText(uchar ch)
{
	QString text = "SB(bit6):" + QString::number(ch & 0x20,16).toUpper() + " ";
	if(ch & 0x20)
	{
		text.append("被取代");
	}
	else
	{
		text.append("未被取代");
	}
	return text;
}

QString ntToText(uchar ch)
{
	QString text = "NT(bit7):" + QString::number(ch & 0x40,16).toUpper() + " ";
	if(ch & 0x40)
	{
		text.append("非当前值");
	}
	else
	{
		text.append("当前值");
	}
	return text;
}

QString ivToText(uchar ch)
{
	QString text = "IV(bit8):" + QString::number(ch & 0x80,16).toUpper() + " ";
	if(ch & 0x80)
	{
		 text.append("无效");
	}
	else
	{
		text.append("有效");
	}
	return text;
}

QString ovToText(uchar ch)
{
	QString text = "OV(bit1):" + QString::number(ch & 0x01) + " ";
	if(ch & 0x01)
	{
		 text.append("溢出");
	}
	else
	{
		text.append("未溢出");
	}
	return text;
}

QString qoiToText(uchar ch)
{
	QString text = "召唤限定词:" + QString::number(ch) + " ";
	switch (ch)
	{
	case 20:
		text.append("站召唤");
		break;
	case 21:
		text.append("第1组召唤");
		break;
	case 22:
		text.append("第2组召唤");
		break;
	case 23:
		text.append("第3组召唤");
		break;
	case 24:
		text.append("第4组召唤");
		break;
	case 25:
		text.append("第5组召唤");
		break;
	case 26:
		text.append("第6组召唤");
		break;
	case 27:
		text.append("第7组召唤");
		break;
	case 28:
		text.append("第8组召唤");
		break;
	case 29:
		text.append("第9组召唤");
		break;
	case 30:
		text.append("第10组召唤");
		break;
	case 31:
		text.append("第11组召唤");
		break;
	case 32:
		text.append("第12组召唤");
		break;
	case 33:
		text.append("第13组召唤");
		break;
	case 34:
		text.append("第14组召唤");
		break;
	case 35:
		text.append("第15组召唤");
		break;
	case 36:
		text.append("第16组召唤");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString coiToText(uchar ch)
{
	QString text = "初始化原因(bit1-7):" + QString::number(ch & 0x7f) + " ";
	switch (ch & 0x7f)
	{
	case 0:
		text.append("当地电源合上");
		break;
	case 1:
		text.append("当地手动复位");
		break;
	case 2:
		text.append("远方复位");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("   BS(bit8):") + QString::number(ch & 0x80,16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("改变当地参数后的初始化");
	}
	else
	{
		text.append("未改变当地参数后的初始化");
	}
	return text;
}

QString rqtToText(uchar ch)
{
	QString text = "计数量召唤命令限定词(QCC):请求RQT(bit1-6):"  + QString::number(ch & 0x3f) + " ";
	switch (ch & 0x3f)
	{
	case 0:
		text.append("没请求计数量（未采用）");
		break;
	case 1:
		text.append("请求计数量第1组");
		break;
	case 2:
		text.append("请求计数量第1组");
		break;
	case 3:
		text.append("请求计数量第3组");
		break;
	case 4:
		text.append("请求计数量第4组");
		break;
	case 5:
		text.append("总的请求计数量");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString frzToText(uchar ch)
{
	QString text = "冻结FRZ(bit7-8):"  + QString::number(ch & 0xc0,16).toUpper() + " ";
	switch (ch>>6)
	{
	case 0:
		text.append("读(无冻结或复位）");
		break;
	case 1:
		text.append("计数量冻结不带复位（被冻结的值为累计量）");
		break;
	case 2:
		text.append("计数量冻结带复位（被冻结的值为增量信息）");
		break;
	case 3:
		text.append("计数量复位");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString suToText(uchar ch)
{
	QString text = "SU(bit8):" + QString::number(ch & 0x80,16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("夏季时间");
	}
	else
	{
		text.append("标准时间");
	}
	text.append("   ");
	return text;
}

QString quToText(uchar ch)
{
	QString text = "QU(bit3-7):" + QString::number(ch & 0x7c,16).toUpper() + " ";
	switch ((ch & 0x7c)>>2)
	{
	case 0:
		text.append("无另外的定义");
		break;
	case 1:
		text.append("短脉冲持续时间(断路器)，持续时间由被控站内的系统参数所确定");
		break;
	case 2:
		text.append("长脉冲持续时间，持续时间由被控站内的系统参数所确定");
		break;
	case 3:
		text.append("持续输出");
		break;
	default:
		text.append("保留");
		break;
	}
	text.append("   ");
	return text;
}

QString seToText(uchar ch)
{
	QString text = "S/E(bit8):" + QString::number(ch & 0x80,16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("命令类型:选择");
	}
	else
	{
		text.append("命令类型:执行");
	}
	return text;
}

QString caToText(uchar ch)
{
	QString text = "CA(bit7):" + QString::number(ch & 0x40,16).toUpper() + " ";
	if(ch & 0x40)
	{
		text.append("上次读数后计数器被调整");
	}
	else
	{
		text.append("上次读数后计数器未被调整");
	}
	return text;
}

QString cyToText(uchar ch)
{
	QString text = "CY(bit6):" + QString::number(ch & 0x20,16).toUpper() + " ";
	if(ch & 0x20)
	{
		text.append("在相应的累加周期内计数器溢出");
	}
	else
	{
		text.append("在相应的累加周期内计数器未溢出");
	}
	return text;
}

QString vtiToText(uchar ch)
{
	QString text = "步位置(bit1-7):"  + QString::number(ch&0x7f) ;

	text.append("   瞬变状态BS1(bit8):") + QString::number(ch & 0x80,16).toUpper() + " ";
	if(ch&0x80)
	{
		text.append("设备处理瞬变状态");
	}
	else
	{
		text.append("设备未在瞬变状态");
	}
	text.append("\r\n");
	return text;
}

QString qosToText(uchar ch)
{
	QString text = "设定命令限定词QOS";
	text.append("  QL(bit1-7):" + QString::number(ch&0x7f)+"   "+ seToText(ch) );
	return text;
}

QString timeToText(char * time, int timelen)
{
	uchar *mtime = (uchar *)time;
	return timeToText(mtime, timelen);
}

QString timeToText(uchar *time, int timelen)
{
	QString text;

	QDateTime datetime = charToDateTime(time, timelen, BINARYTIME2A);

	uint datauint = charTouint(time, 2);
	text.append(CharToHexStr(time,2) + "\t" + QString::number(datauint) + "   秒:" + QString::number(datetime.time().second()) + "   毫秒:" + QString::number(datetime.time().msec()) + " \r\n");
	if (timelen == 2)
	{
		return text;
	}

	text.append(CharToHexStr(time[2]) + "\t分(bit1-6):" + QString::number(datetime.time().minute()) + "   " + ivToText(time[2]) + "\r\n");
	if (timelen == 3)
	{
		return text;
	}

	text.append(CharToHexStr(time[3]) + "\t时(bit1-5):" + QString::number(datetime.time().hour()) + "   " + suToText(time[3]) + "\r\n");
	if (timelen == 4)
	{
		return text;
	}

	text.append(CharToHexStr(time[4]) + "\t日(bit1-5):" + QString::number(datetime.date().day()) + "   周(bit6-8):" + QString::number(time[4] >> 5) + " (7表示星期天,0表示未用)\r\n");
	if (timelen == 5)
	{
		return text;
	}

	text.append(CharToHexStr(time[5]) + "\t月(bit1-4):" + QString::number(datetime.date().month()) + "\r\n");
	if (timelen == 6)
	{
		return text;
	}

	text.append(CharToHexStr(time[6]) + "\t年(bit1-7):" + QString::number(datetime.date().year()) + "\r\n");
	return text;
}
