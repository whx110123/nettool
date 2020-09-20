﻿#include "functotext.h"

QString prmToText(uchar ch)
{
	QString text = "PRM(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ";
	if(ch & 0x40)
	{
		text.append("启动站向从动站传输的报文");
	}
	else
	{
		text.append("从动(响应)站向启动站传输的报文");
	}
	return text;
}

QString fcbToText(uchar ch)
{
	QString text = "FCB(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " 帧计数位";
	return text;
}

QString fcvToText(uchar ch)
{
	QString text = "FCV(bit5):" + QString::number(ch & 0x10, 16).toUpper() + " ";
	if(ch & 0x10)
	{
		text.append("表示帧计数位FCB的变化有效");
	}
	else
	{
		text.append("表示帧计数位FCB的变化无效");
	}
	return text;
}

QString acdToText(uchar ch)
{
	QString text = "ACD(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " ";
	if(ch & 0x20)
	{
		text.append("从动站有1级用户数据要求访问");
	}
	else
	{
		text.append("从动站无1级用户数据要求访问");
	}
	return text;
}

QString dfcToText(uchar ch)
{
	QString text = "DFC(bit5):" + QString::number(ch & 0x10, 16).toUpper() + " ";
	if(ch & 0x10)
	{
		text.append("表示从动站接收后续报文将引起数据溢出");
	}
	else
	{
		text.append("表示从动站可以接收后续报文");
	}
	return text;
}

QString cw1ToText(uchar ch)
{
	QString text = "功能码(bit1-4):" + QString::number(ch & 0x0f) + " ";
	switch(ch & 0x0f)
	{
	case 0:
		text.append("帧类型:发送/确认帧  功能描述:复位通信单元  帧计数有效位FCV:0");
		break;
	case 1:
		text.append("帧类型:发送/确认帧  功能描述:用户进程复位  帧计数有效位FCV:0");
		break;
	case 3:
		text.append("帧类型:发送/确认帧  功能描述:传送数据  帧计数有效位FCV:1");
		break;
	case 4:
		text.append("帧类型:发送/无回答帧  功能描述:传送数据  帧计数有效位FCV:0");
		break;
	case 7:
		text.append("帧类型:复位帧计数位  功能描述:传送数据  帧计数有效位FCV:0");
		break;
	case 8:
		text.append("帧类型:要求访问的请求  功能描述:以要求访问位响应  帧计数有效位FCV:0");
		break;
	case 9:
		text.append("帧类型:请求/响应帧  功能描述:召唤链路状态  帧计数有效位FCV:0");
		break;
	case 10:
		text.append("帧类型:请求/响应帧  功能描述:召唤1级数据  帧计数有效位FCV:1");
		break;
	case 11:
		text.append("帧类型:请求/响应帧  功能描述:召唤2级数据  帧计数有效位FCV:1");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString cw2ToText(uchar ch)
{
	QString text = "功能码(bit1-4):" + QString::number(ch & 0x0f) + " ";
	switch(ch & 0x0f)
	{
	case 0:
		text.append("帧类型:确认帧  功能描述:认可，肯定认可");
		break;
	case 1:
		text.append("帧类型:确认帧  功能描述:否定认可，未收到报文，链路忙");
		break;
	case 8:
		text.append("帧类型:响应帧  功能描述:以数据包响应请求帧");
		break;
	case 9:
		text.append("帧类型:响应帧  功能描述:从站没有所召唤的数据");
		break;
	case 11:
		text.append("帧类型:响应帧  功能描述:响应链路状态或要求访问");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString spiToText(uchar ch)
{
	QString text = "单点遥信SPI(bit1):" + QString::number(ch & 0x01) + " ";
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
	switch(ch & 0x03)
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

QString dpiteToText(uchar ch)
{
	QString text = "带瞬变与差错的双点遥信DPI(bit1-2):" + QString::number(ch & 0x03) + " ";
	switch(ch & 0x03)
	{
	case 0:
		text.append("瞬变状态");
		break;
	case 1:
		text.append("分位");
		break;
	case 2:
		text.append("合位");
		break;
	case 3:
		text.append("差错状态");
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
	switch(ch & 0x03)
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
	QString text = "BL(bit5):" + QString::number(ch & 0x10, 16).toUpper() + " ";
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
	QString text = "SB(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " ";
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
	QString text = "NT(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ";
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
	QString text = "IV(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ";
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

QString erToText(uchar ch)
{
	QString text = "ER(bit2):" + QString::number(ch & 0x02, 16).toUpper() + " ";
	if(ch & 0x02)
	{
		text.append("被测值无效");
	}
	else
	{
		text.append("被测值有效");
	}
	return text;
}

QString qoiToText(uchar ch)
{
	QString text = "召唤限定词QOI:" + QString::number(ch) + " ";
	switch(ch)
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
	switch(ch & 0x7f)
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
	text.append("   BS(bit8):") + QString::number(ch & 0x80, 16).toUpper() + " ";
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
	switch(ch & 0x3f)
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
	QString text = "冻结FRZ(bit7-8):"  + QString::number(ch & 0xc0, 16).toUpper() + " ";
	switch(ch >> 6)
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
	QString text = "SU(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("夏季时间");
	}
	else
	{
		text.append("标准时间");
	}
	return text;
}

QString quToText(uchar ch)
{
	QString text = "QU(bit3-7):" + QString::number(ch & 0x7c, 16).toUpper() + " ";
	switch((ch & 0x7c) >> 2)
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
	return text;
}

QString seToText(uchar ch)
{
	QString text = "S/E(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ";
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
	QString text = "CA(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " ";
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
	QString text = "CY(bit6):" + QString::number(ch & 0x20, 16).toUpper() + " ";
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
	QString text = "步位置(bit1-7):"  + QString::number(ch & 0x7f) ;

	text.append("   瞬变状态BS1(bit8):") + QString::number(ch & 0x80, 16).toUpper() + " ";
	if(ch & 0x80)
	{
		text.append("设备处理瞬变状态");
	}
	else
	{
		text.append("设备未在瞬变状态");
	}
	return text;
}

QString qosToText(uchar ch)
{
	QString text = "设定命令限定词QOS";
	text.append("  QL(bit1-7):" + QString::number(ch & 0x7f) + "   " + seToText(ch));
	return text;
}

QString timeToText(const char *time, int timelen)
{
	uchar *mtime = (uchar *)time;
	return timeToText(mtime, timelen);
}

QString timeToText(uchar *time, int timelen)
{
	QString text;

	QDateTime datetime = charToDateTime(time, timelen, BINARYTIME2A);

	uint datauint = charTouint(time, 2);
	text.append(CharToHexStr(time, 2) + "\t" + QString::number(datauint) + "   秒:" + QString::number(datetime.time().second()) + "   毫秒:" + QString::number(datetime.time().msec()) + " \r\n");
	if(timelen == 2)
	{
		return text;
	}

	text.append(CharToHexStr(time[2]) + "\t分(bit1-6):" + QString::number(datetime.time().minute()) + "   " + ivToText(time[2]) + "\r\n");
	if(timelen == 3)
	{
		return text;
	}

	text.append(CharToHexStr(time[3]) + "\t时(bit1-5):" + QString::number(datetime.time().hour()) + "   " + suToText(time[3]) + "\r\n");
	if(timelen == 4)
	{
		return text;
	}

	text.append(CharToHexStr(time[4]) + "\t日(bit1-5):" + QString::number(datetime.date().day()) + "   周(bit6-8):" + QString::number(time[4] >> 5) + " (7表示星期天,0表示未用)\r\n");
	if(timelen == 5)
	{
		return text;
	}

	text.append(CharToHexStr(time[5]) + "\t月(bit1-4):" + QString::number(datetime.date().month()) + "\r\n");
	if(timelen == 6)
	{
		return text;
	}

	text.append(CharToHexStr(time[6]) + "\t年(bit1-7):" + QString::number(datetime.date().year()) + "\r\n");
	return text;
}

QString ngdToText(uchar ch)
{
	QString text;
	text.append("NO(bit1-6):" + QString::number(ch & 0x3f) + " 通用分类数据集数目\r\n\t");
	text.append("COUNT(bit7):" + QString::number(ch & 0x40, 16).toUpper() + " 具有相同返回信息标识符(RII)的应用服务数据单元的一位计数器位\r\n\t");
	text.append("CONT(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ");
	if(ch & 0x80)
	{
		text.append("后面跟着具有相同返回信息标识符(RII)的应用服务数据单元");
	}
	else
	{
		text.append("后面未跟着具有相同返回信息标识符(RII)的应用服务数据单元");
	}
	return text;
}

QString nogToText(uchar ch)
{
	QString text;
	text.append("NOG:" + QString::number(ch) + " 通用分类标识数目");
	return text;
}
QString kodToText(uchar ch)
{
	QString text = "KOD:" + QString::number(ch) + " ";
	switch(ch)
	{
	case 0:
		text.append("无所指定的描述类别");
		break;
	case 1:
		text.append("实际值");
		break;
	case 2:
		text.append("缺省值");
		break;
	case 3:
		text.append("量程(最小值最大值步长)");
		break;
	case 5:
		text.append("精度(n m)");
		break;
	case 6:
		text.append("因子");
		break;
	case 7:
		text.append("%参比");
		break;
	case 8:
		text.append("列表");
		break;
	case 9:
		text.append("量纲");
		break;
	case 10:
		text.append("描述");
		break;
	case 12:
		text.append("口令条目");
		break;
	case 13:
		text.append("只读");
		break;
	case 14:
		text.append("只写");
		break;
	case 19:
		text.append("相应的功能类型和信息序号");
		break;
	case 20:
		text.append("相应的事件");
		break;
	case 21:
		text.append("列表的文本阵列");
		break;
	case 22:
		text.append("列表的值阵列");
		break;
	case 23:
		text.append("相关联的条目");
		break;
	case 103:
		text.append("属性结构(保信规约专用)");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}

QString gdd1ToText(uchar ch)
{
	QString text = "GDD1:" + QString::number(ch) + " ";
	switch(ch)
	{
	case 0:
		text.append("无数据");
		break;
	case 1:
		text.append("OS8(ASCII8位码)");
		break;
	case 2:
		text.append("成组8位串");
		break;
	case 3:
		text.append("无符号整数");
		break;
	case 4:
		text.append("整数");
		break;
	case 5:
		text.append("无符号浮点数");
		break;
	case 6:
		text.append("浮点数");
		break;
	case 7:
		text.append("IEEE标准754短实数");
		break;
	case 8:
		text.append("IEEE标准754实数");
		break;
	case 9:
		text.append("双点信息");
		break;
	case 10:
		text.append("单点信息");
		break;
	case 11:
		text.append("带瞬变和差错的双点信息");
		break;
	case 12:
		text.append("带品质描述词的被测值");
		break;
	case 14:
		text.append("二进制时间");
		break;
	case 15:
		text.append("通用分类标识序号");
		break;
	case 16:
		text.append("相对时间");
		break;
	case 17:
		text.append("功能类型和信息序号");
		break;
	case 18:
		text.append("带时标的报文");
		break;
	case 19:
		text.append("带相对时间的时标报文");
		break;
	case 20:
		text.append("带相对时间的时标的被测值");
		break;
	case 21:
		text.append("外部文本序号");
		break;
	case 22:
		text.append("通用分类回答码");
		break;
	case 23:
		text.append("数据结构");
		break;
	case 24:
		text.append("索引");
		break;
	case 201:
		text.append("遥脉数据");
		break;
	case 205:
		text.append("故障测量数据");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}

QString gdd3ToText(uchar ch)
{
	QString text;
	text.append("GDD3:NUMBER(bit1-7):" + QString::number(ch & 0x7f) + " 信息数目   ");
	text.append("CONT(bit8):" + QString::number(ch & 0x80, 16).toUpper() + " ");
	if(ch & 0x80)
	{
		text.append("后面跟随的数据元素具有相同的返回信息标识符(RII)");
	}
	else
	{
		text.append("后面未跟随数据元素");
	}
	return text;
}

QString grcToText(uchar ch)
{
	QString text = "GRC:" + QString::number(ch) + "通用分类回答码:" ;
	switch(ch)
	{
	case 0:
		text.append("认可");
		break;
	case 1:
		text.append("无效的通用分类标识序号（GIN）");
		break;
	case 2:
		text.append("不存在所请求的数据");
		break;
	case 3:
		text.append("数据不能用，过后再来一次");
		break;
	case 4:
		text.append("改变设定时确认出错");
		break;
	case 5:
		text.append("改变设定时超出量程");
		break;
	case 6:
		text.append("条目的范围太大");
		break;
	case 7:
		text.append("太多的命令");
		break;
	case 8:
		text.append("条目是只读");
		break;
	case 9:
		text.append("设定受口令保护");
		break;
	case 10:
		text.append("当地设定在进行中");
		break;
	case 11:
		text.append("带有下面所描述的差错");
		break;
	default:
		text.append("保留");
		break;
	}
	return text;
}

QString sofToText(uchar ch)
{
	QString text;
	text.append("故障状态SOF:");
	text.append("\r\n\tTP(bit1):" + QString::number(ch & 0x01, 16).toUpper() + " ");
	if(ch & 0x01)
	{
		text.append("被记录的故障跳闸");
	}
	else
	{
		text.append("被记录的故障未跳闸");
	}

	text.append("\r\n\tTM(bit2):" + QString::number(ch & 0x02, 16).toUpper() + " ");
	if(ch & 0x02)
	{
		text.append("扰动数据正在传输");
	}
	else
	{
		text.append("扰动数据等待传输");
	}

	text.append("\r\n\tTEST(bit3):" + QString::number(ch & 0x04, 16).toUpper() + " ");
	if(ch & 0x04)
	{
		text.append("在测试模式下被记录的扰动数据");
	}
	else
	{
		text.append("在正常操作时被记录的扰动数据");
	}

	text.append("\r\n\tOTEV(bit4):" + QString::number(ch & 0x08, 16).toUpper() + " ");
	if(ch & 0x08)
	{
		text.append("由其他事件触发被记录的扰动数据");
	}
	else
	{
		text.append("由启动/检出故障触发被记录的扰动数据");
	}
	return text;
}

QString tooToText(uchar ch)
{
	QString text;
	text.append("命令类型TOO:" + QString::number(ch) + "   ");
	switch(ch)
	{
	case 1:
		text.append("故障的选择");
		break;
	case 2:
		text.append("请求扰动数据");
		break;
	case 3:
		text.append("中止扰动数据");
		break;
	case 8:
		text.append("通道的请求");
		break;
	case 9:
		text.append("通道的中止");
		break;
	case 16:
		text.append("请求带标志的状态变位");
		break;
	case 17:
		text.append("中止带标志的状态变位");
		break;
	case 24:
		text.append("请求被记录扰动表");
		break;
	case 32:
		text.append("不带中止的扰动数据传输的结束");
		break;
	case 33:
		text.append("由控制系统所中止的扰动数据传输的结束");
		break;
	case 34:
		text.append("由继电保护设备(或间隔单元)所中止的扰动数据传输的结束");
		break;
	case 35:
		text.append("不带中止的通道传输的结束");
		break;
	case 36:
		text.append("由控制系统所中止的通道传输的结束");
		break;
	case 37:
		text.append("由继电保护设备(或间隔单元)所中止的通道传输的结束");
		break;
	case 38:
		text.append("不带中止的带标志的状态变位的传输的结束");
		break;
	case 39:
		text.append("由控制系统所中止的带标志的状态变位的传输的结束");
		break;
	case 40:
		text.append("由继电保护设备(或间隔单元)所中止的带标志的状态变位传输的结束");
		break;
	case 64:
		text.append("成功的扰动数据传输(肯定)");
		break;
	case 65:
		text.append("不成功的扰动数据传输(否定)");
		break;
	case 66:
		text.append("成功的通道传输(肯定)");
		break;
	case 67:
		text.append("不成功的通道传输(否定)");
		break;
	case 68:
		text.append("成功的带标志的状态变位传输(肯定)");
		break;
	case 69:
		text.append("不成功的带标志的状态变位传输(否定)");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}

QString tovToText(uchar ch)
{
	QString text = "扰动值的类型TOV:" + QString::number(ch) + "   ";
	if(ch == 1)
	{
		text.append("瞬时值");
	}
	else
	{
		text.append("未定义");
	}
	return text;
}

QString accToText(uchar ch)
{
	QString text = "实际通道序号ACC:" + QString::number(ch) + "   ";
	switch(ch)
	{
	case 0:
		text.append("全局");
		break;
	case 1:
		text.append("I(L1)");
		break;
	case 2:
		text.append("I(L2)");
		break;
	case 3:
		text.append("I(L3)");
		break;
	case 4:
		text.append("I(N)");
		break;
	case 5:
		text.append("U(L1E)");
		break;
	case 6:
		text.append("U(L2E)");
		break;
	case 7:
		text.append("U(L3E)");
		break;
	case 8:
		text.append("U(EN)");
		break;
	default:
		text.append("备用");
		break;
	}
	return text;
}
