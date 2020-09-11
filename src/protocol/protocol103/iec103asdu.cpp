#include "iec103asdu.h"
#include "globaldefine.h"
#include "app.h"
#include "iec103asdu1data.h"
#include "iec103asdu2data.h"
#include "iec103asdu6data.h"
#include "iec103asdu7data.h"
#include "iec103asdu10data.h"
#include "iec103asdu21data.h"
#include "iec103asdu44data.h"
#include "iec103asdu50data.h"
#include "iec103asdu51data.h"
#include "iec103asdu8data.h"
#include "iec103asdu42data.h"


IEC103AsduData::IEC103AsduData()
{
	inf = 0;
	masterState = STATE_NORMAL;
}

IEC103AsduData::~IEC103AsduData()
{

}

bool IEC103AsduData::init(const QByteArray& buff)
{
	setDefault(buff);

	fun = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + funToText() + "\r\n");
	len++;

	inf = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;

	if(!handle(buff))
	{
		return false;
	}
	return true;
}

bool IEC103AsduData::init(const QByteArray& buff, uchar ch_fun)
{
	setDefault(buff);

	fun = ch_fun & 0xff;

	inf = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;

	if(!handle(buff))
	{
		return false;
	}
	return true;
}

bool IEC103AsduData::init(const QByteArray& buff, uchar ch_fun, uchar ch_inf)
{
	setDefault(buff);

	fun = ch_fun & 0xff;
	inf = ch_inf & 0xff;

	if(!handle(buff))
	{
		return false;
	}
	return true;
}

bool IEC103AsduData::handle(const QByteArray& buff)
{
	return false;
}

QString IEC103AsduData::funToText()
{
	QString text = "FUN:" + QString::number(fun) + " ";
	switch(fun)
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


QString IEC103AsduData::infToText()
{
	QString text = "INF:" + QString::number(inf) + " ";
	switch(inf)
	{
	case 240:
		text.append("读所有被定义组的标题");
		break;
	case 241:
		text.append("读一个组的全部条目的值或属性");
		break;
	case 243:
		text.append("读单个条目的目录");
		break;
	case 244:
		text.append("读单个条目的值或属性");
		break;
	case 245:
		text.append("通用分类数据的总查询(总召唤) 主站发出或子站中止");
		break;
	case 248:
		text.append("写条目");
		break;
	case 249:
		text.append("带确认的写条目");
		break;
	case 250:
		text.append("带执行的写条目");
		break;
	case 251:
		text.append("主站写条目中止或子站带中止的写条目");
		break;
	default:
		break;
	}
	return text;
}

IEC103Asdu::IEC103Asdu()
{
	type = 0;
	vsq = 0;
	cot = 0;
	commonaddr = 0;
	sqflag = 0;
	datanum = 0;
	masterState = STATE_NORMAL;
	cotlen = 1;
	comaddrlen = 1;
	endflag = 0;
	end = 0;
}

IEC103Asdu::~IEC103Asdu()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool IEC103Asdu::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(datalist);
	datalist.clear();
	if(buff.count() < 4)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度小于4");
		return false;
	}

	type = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + typeToText() + "\r\n");
	len++;

	vsq = *(buff.data() + len);
	sqflag = (vsq >> 7) & 0x01;
	datanum = vsq & 0x7f;
	mText.append(CharToHexStr(buff.data() + len) + "\t" + vsqToText() + "\r\n");
	len++;

	if(cotlen > 0)
	{
		cot = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data() + len, cotlen) + "\t" + cotToText() + "\r\n");
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！传送原因字节数错误");
		return false;
	}
	len += cotlen;

	commonaddr = charTouint(buff.data() + len, comaddrlen);
	if(comaddrlen == 1)
	{
		mText.append(CharToHexStr(buff.data() + len) + "\t公共地址:" + QString::number(commonaddr & 0xff) + "\r\n");
	}
	else if(comaddrlen == 2)
	{
		mText.append(CharToHexStr(buff.data() + len) + "\t公共地址低位:" + QString::number(commonaddr & 0xff) + "\r\n");
		mText.append(CharToHexStr(buff.data() + len + 1) + "\t公共地址高位:" + QString::number((commonaddr >> 8) & 0xff) + " 装置地址\r\n");
	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！公共地址字节数错误");
		return false;
	}
	len += comaddrlen;

	uchar fun = *(buff.data() + len);
	uchar inf = *(buff.data() + len + 1);;
	for(int index = 0; index < datanum; index++)
	{
		IEC103AsduData *mdata = CreateAsduData(type);
		if(!mdata)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的asdu类型");
			return false;
		}
		bool isOk = false;
		if(index == 0)
		{
			isOk = mdata->init(buff.mid(len));
		}
		else if(sqflag == 1)
		{
			switch(type)
			{
			case 42:
				isOk = mdata->init(buff.mid(len));
				break;
			case 50:
			case 51:
				isOk = mdata->init(buff.mid(len), fun);
			default:
				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！此asdu信息体地址未知");
				break;
			}
		}
		else
		{
			int k = 1;
			if(type == 44)
			{
				k = 16;
			}
			isOk = mdata->init(buff.mid(len), fun, (uchar)(inf + index * k));
		}
		if(!isOk)
		{
			mText.append(mdata->showToText());
			delete mdata;
			mdata = NULL;
			return false;
		}
		datalist.append(mdata);
		len += mdata->len;
	}

	if(endflag != IEC103END_NO)
	{
		end = *(buff.data() + len);
		len++;
	}
	return true;
}

QString IEC103Asdu::showToText()
{
	QString text = mText;
	for(IEC103AsduData *mdata : datalist)
	{
		text.append(mdata->showToText());
	}
	if(endflag != IEC103END_NO)
	{
		text.append(CharToHexStr(end) + "\t" + endToText() + QString::number(end) + "\r\n");
	}
	return text;
}

bool IEC103Asdu::createData(IECDataConfig& config)
{
	qDeleteAll(datalist);
	datalist.clear();

	if(config.isMaster)
	{
		config.data += config.asdutype;
		config.data += config.vsq;
		config.data += config.cot;
		config.data += (char)(config.devaddr & 0xff);
		config.data += config.fun;
		for(int i = 0; i < (config.vsq & 0x7f); i++)
		{
			IEC103AsduData *newdata = CreateAsduData(config.asdutype);
			if(!newdata)
			{
				error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！对此asdu类型未完成报文生成");
				return false;
			}
			datalist.append(newdata);
			if(!newdata->createData(config))
			{
				return false;
			}
		}

	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
		return false;
	}
	//	config.data += config.asdutype;
	//	config.data += config.vsq;
	//	config.data += config.cot;
	//	config.data += '\0';
	//	config.data += uintToBa(App::IEC_COMADDR,2);
	//	config.isfirst = true;
	//	for(int i = 0;i<(config.vsq&0x7f);i++)
	//	{
	//		IEC103asdudata *newdata = CreateAsduData(config.asdutype);
	//		newdata->createData(config);
	//		datalist.append(newdata);
	//	}

	return true;
}

QString IEC103Asdu::typeToText()
{
	QString text = "ASDU" + QString::number(type) + ":类型标识 ";
	endflag = IEC103END_NO;
	switch(type)
	{
	case 1:
		text.append("带时标的报文");
		endflag = IEC103END_SIN;
		break;
	case 2:
		text.append("具有相对时间的带时标的报文");
		endflag = IEC103END_SIN;
		break;
	case 3:
		text.append("被测值I");
		break;
	case 4:
		text.append("具有相对时间的带时标的被测值");
		break;
	case 5:
		text.append("标识");
		break;
	case 6:
		text.append("时间同步");
		break;
	case 7:
		text.append("总查询(总召唤)");
		endflag = IEC103END_SCN;
		break;
	case 8:
		text.append("总查询(总召唤)终止");
		endflag = IEC103END_SCN;
		break;
	case 9:
		text.append("被测值II");
		break;
	case 10:
		text.append("通用分类数据");
		break;
	case 11:
		text.append("通用分类标识");
		break;
	case 20:
		text.append("一般命令");
		endflag = IEC103END_RII;
		break;
	case 21:
		text.append("通用分类命令");
		break;
	case 23:
		text.append("被记录的扰动表");
		break;
	case 24:
		text.append("扰动数据传输的命令");
		break;
	case 25:
		text.append("扰动数据传输的认可");
		break;
	case 26:
		text.append("扰动数据传输准备就绪");
		break;
	case 27:
		text.append("被记录的通道传输准备就绪");
		break;
	case 28:
		text.append("带标志的状态变位传输准备就绪");
		break;
	case 29:
		text.append("传送带标志的状态变位");
		break;
	case 30:
		text.append("传送扰动值");
		break;
	case 31:
		text.append("传送结束");
		break;
	case 32:
		text.append("带时标的被测值III");
		break;
	case 33:
		text.append("带时标的被测值IV");
		break;
	case 34:
		text.append("带时标的向量被测值V");
		break;
	case 35:
		text.append("带时标的向量被测值VI");
		break;
	case 36:
		text.append("电能脉冲计数量");
		endflag = IEC103END_RII;
		break;
	case 37:
		text.append("带时标的电能脉冲计数量");
		break;
	case 38:
		text.append("步位置信息");
		break;
	case 39:
		text.append("带时标的步位置信息");
		break;
	case 40:
		text.append("单点状态信息");
		endflag = IEC103END_SIN;
		break;
	case 41:
		text.append("带时标的单点状态信息");
		endflag = IEC103END_SIN;
		break;
	case 42:
		text.append("双点状态信息");
		endflag = IEC103END_SIN;
		break;
	case 43:
		text.append("带时标的双点状态信息");
		endflag = IEC103END_SIN;
		break;
	case 44:
		text.append("单点状态和状态变位检出");
		endflag = IEC103END_SIN;
		break;
	case 45:
		text.append("带时标的单点状态和状态变位检出");
		break;
	case 46:
		text.append("双点状态和状态变位检出");
		break;
	case 47:
		text.append("带时标的双点状态和状态变位检出");
		break;
	case 48:
		text.append("水位");
		break;
	case 50:
		text.append("被测值VII");
		break;
	case 51:
		text.append("变化的被测值VII");
		break;
	case 64:
		text.append("控制断路器命令");
		endflag = IEC103END_RII;
		break;
	case 65:
		text.append("升降命令");
		break;
	case 66:
		text.append("设定命令");
		break;
	case 67:
		text.append("控制命令");
		break;
	case 88:
		text.append("电能脉冲量召唤（冻结）");
		endflag = IEC103END_RII;
		break;
	default:
		text.append("未知ASDU类型，无法继续解析");
		break;
	}
	return text;
}

QString IEC103Asdu::vsqToText()
{
	QString text;
	text.append("VSQ 可变结构限定词，信息元素数量(bit1-7):" + QString::number(datanum) + " \r\n");
	text.append("\tSQ(bit8):" + QString::number(vsq & 0x80, 16).toUpper() + " ");
	if(sqflag)
	{
		text.append("每个信息元素都有独自的地址");
	}
	else
	{
		text.append("只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1");
	}
	return text;
}

QString IEC103Asdu::cotToText()
{
	QString text = "COT:" + QString::number(cot) + " 传送原因:";
	switch(cot)
	{
	case 1:
		text.append("自发(突发)");
		break;
	case 2:
		text.append("循环");
		break;
	case 3:
		text.append("复位帧计数位(FCB)");
		break;
	case 4:
		text.append("复位通信单元(CU)");
		break;
	case 5:
		text.append("启动/重新启动");
		break;
	case 6:
		text.append("电源合上");
		break;
	case 7:
		text.append("测试模式");
		break;
	case 8:
		text.append("时间同步 主站启动或子站响应");
		break;
	case 9:
		text.append("总查询(总召唤) 主站启动或子站响应");
		break;
	case 10:
		text.append("总查询(总召唤)终止");
		break;
	case 11:
		text.append("当地操作");
		break;
	case 12:
		text.append("远方操作");
		break;
	case 20:
		text.append("一般命命令 主站发出或子站肯定认可");
		break;
	case 21:
		text.append("一般命令的否定认可");
		break;
	case 31:
		text.append("扰动数据的传送");
		break;
	case 40:
		text.append("通用分类写命令 主站发出或子站肯定认可");
		break;
	case 41:
		text.append("通用分类写命令的否定认可");
		break;
	case 42:
		text.append("对通用分类读命令 主站发出或子站有效数据响应");
		break;
	case 43:
		text.append("对通用分类读命令无效数据响应");
		break;
	case 44:
		text.append("通用分类写确认");
		break;
	default:
		text.append("未知，无法识别当前的传送原因");
		break;
	}
	return text;
}

QString IEC103Asdu::endToText()
{
	QString text;
	switch(endflag)
	{
	case IEC103END_RII:
		text.append("返回信息标识符RII:");
		break;
	case IEC103END_SCN:
		text.append("扫描序号SCN:");
		break;
	case IEC103END_SIN:
		text.append("附加信息SIN:");
		break;
	default:
		break;
	}
	return text;
}

IEC103AsduData *IEC103Asdu::CreateAsduData(uchar type)
{
	IEC103AsduData *asdudata = NULL;
	switch(type)
	{
	case 1:
		asdudata = new IEC103Asdu1Data;
		break;
	case 2:
		asdudata = new IEC103Asdu2Data;
		break;
	case 6:
		asdudata = new IEC103Asdu6Data;
		break;
	case 7:
		asdudata = new IEC103Asdu7Data;
		break;
	case 8:
		asdudata = new IEC103Asdu8Data;
		break;
	case 10:
		asdudata = new IEC103Asdu10Data;
		break;
	case 21:
		asdudata = new IEC103Asdu21Data;
		break;
	case 42:
		asdudata = new IEC103Asdu42Data;
		break;
	case 44:
		asdudata = new IEC103Asdu44Data;
		break;
	case 50:
		asdudata = new IEC103Asdu50Data;
		break;
	case 51:
		asdudata = new IEC103Asdu51Data;
		break;
	default:
		break;
	}
	return asdudata;
}





