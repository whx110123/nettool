#include "iec101asdu.h"
#include "globaldefine.h"
#include "app.h"
#include "iec101asdu1data.h"
#include "iec101asdu3data.h"
#include "iec101asdu9data.h"
#include "iec101asdu13data.h"
#include "iec101asdu15data.h"
#include "iec101asdu21data.h"
#include "iec101asdu30data.h"
#include "iec101asdu31data.h"
#include "iec101asdu32data.h"
#include "iec101asdu45data.h"
#include "iec101asdu46data.h"
#include "iec101asdu50data.h"
#include "iec101asdu70data.h"
#include "iec101asdu100data.h"
#include "iec101asdu101data.h"
#include "iec101asdu103data.h"
#include "iec101asdu137data.h"
#include "iec101asdu167data.h"

IEC101asdudata::IEC101asdudata()
{
	error = 0;
	infaddr = 0;
	mstate = STATE_NORMAL;
}

IEC101asdudata::~IEC101asdudata()
{

}

IEC101asdu::IEC101asdu()
{
	error = 0;
	type = 0;
	vsq = 0;
	memset(cot,0,sizeof (cot));
	commonaddr = 0;
	sqflag = 0;
	datanum = 0;
	datalen = 0;
	timelen = 0;
	other = 0;
	mstate = STATE_NORMAL;
}

IEC101asdu::~IEC101asdu()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool IEC101asdu::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	qDeleteAll(datalist);
	datalist.clear();
	int cotlen = App::IEC_COTLEN;					//104cot长度
	int comaddrlen = App::IEC_COMADDRLEN;			//104公共地址长度
	int infaddrlen = App::IEC_INFADDRLEN;			//104信息体地址长度
	int i = 0;
	if(buff.count() < 2 +cotlen +comaddrlen)
	{
		error = 1;
		return false;
	}

	type = *(buff.data()+i);
	mText.append(CharToHexStr(buff.data()+i) + "\t类型标识 ");
	i++;
	mText.append(typeToText());

	vsq = *(buff.data()+i);
	mText.append(CharToHexStr(buff.data()+i) + "\t" + vsqToText());
	i++;

	cot[0] = *(buff.data()+i);
	mText.append(CharToHexStr(buff.data()+i) + "\t" +cotToText());
	i++;

	if(cotlen == 2)
	{
		cot[1] = *(buff.data()+i);
		mText.append(CharToHexStr(buff.data()+i) + "\t源发站地址号:"+QString::number(cot[1])+"\r\n");
		i++;
	}

	if(comaddrlen != 2 && comaddrlen != 1)
	{
		error = 1;
		return false;
	}
	commonaddr = charTouint(buff.data()+i,comaddrlen);
	mText.append(CharToHexStr(buff.data()+i,comaddrlen) + "\t公共地址:" + QString::number(commonaddr) +"\r\n");
	i += comaddrlen;

	if (type == 167)			//由于167号报文数据长度不固定,单独处理
	{
		IEC101asdudata *mdata = CreateAsduData(type);
		bool isOk;
		isOk = mdata->init(buff.mid(i));
		if (!isOk)
		{
			error = 1;
			delete mdata;
			mdata = NULL;
			return false;
		}
		datalist.append(mdata);
		return true;
	}
	int lengthtmp = 2+cotlen+comaddrlen+infaddrlen+(1-sqflag)*(datanum-1)* infaddrlen+datanum*(datalen+timelen)+other;
	if( lengthtmp!= buff.count())
	{
		mText.append( "\r\n\t出错！通过VSQ与ASDU类型计算出ASDU长度为"+QString::number(lengthtmp)+"，而实际ASDU长度为"+QString::number(buff.count())+"。报文长度不符，因此报文有问题，下面的解析可能会出现异常\r\n");
	}

	uint dataaddr = charTouint((uchar *)(buff.data()+i),infaddrlen);
	for(int index = 0;index<datanum;index++)
	{
		IEC101asdudata *mdata = CreateAsduData(type);
		bool isOk;
		if(index ==0 || sqflag == 0)
		{
			isOk = mdata->init(buff.mid(i,infaddrlen+datalen+timelen));
			i += infaddrlen+datalen+timelen;
		}
		else
		{
			isOk = mdata->init(buff.mid(i,datalen+timelen),dataaddr+index);
			i += datalen+timelen;
		}
		if(!isOk)
		{
			error = 1;
			delete mdata;
			mdata =NULL;
			return false;
		}
		datalist.append(mdata);
	}
	return true;
}

QString IEC101asdu::showToText()
{
	QString text = mText;
	for(IEC101asdudata *mdata:datalist)
	{
		text.append(mdata->showToText());
	}
	return text;
}

bool IEC101asdu::createData(IECDataConfig &config)
{
	qDeleteAll(datalist);
	datalist.clear();

	config.data += config.asdutype;
	config.data += config.vsq;
	config.data += config.cot;
	config.data += '\0';
	config.data += uintToBa(App::IEC_COMADDR,2);
	config.isfirst = true;
	for(int i = 0;i<(config.vsq&0x7f);i++)
	{
		IEC101asdudata *newdata = CreateAsduData(config.asdutype);
		newdata->createData(config);
		datalist.append(newdata);
	}

	return true;
}

QString IEC101asdu::typeToText()
{
	QString text = "ASDU"+ QString::number(type) + ":";
	switch (type)
	{
	case 1:
		text.append("单点信息");
		datalen = 1;
		break;
	case 2:
		text.append("带时标的单点信息");
		break;
	case 3:
		text.append("双点信息");
		datalen = 1;
		break;
	case 4:
		text.append("带时标的双点遥信");
		break;
	case 5:
		text.append("步位置(档位)信息");
		break;
	case 6:
		text.append("带时标的步位置信息");
		break;
	case 7:
		text.append("32比特串");
		break;
	case 8:
		text.append("带时标的32比特串");
		break;
	case 9:
		text.append("测量值, 规一化值");
		datalen = 3;
		break;
	case 10:
		text.append("测量值，带时标的规一化值");
		break;
	case 11:
		text.append("测量值, 标度化值");
		break;
	case 12:
		text.append("测量值, 带时标的标度化值");
		break;
	case 13:
		text.append("测量值, 短浮点数");
		datalen = 5;
		break;
	case 14:
		text.append("测量值, 带时标的短浮点数");
		break;
	case 15:
		text.append("累计量");
		datalen = 5;
		break;
	case 16:
		text.append("带时标的累计量");
		break;
	case 17:
		text.append("带时标的继电保护设备事件");
		break;
	case 18:
		text.append("带时标的继电保护设备成组启动事件");
		break;
	case 19:
		text.append("带时标的继电保护设备成组输出电路信息");
		break;
	case 20:
		text.append("带变位检出的成组单点信息");
		break;
	case 21:
		text.append("测量值, 不带品质描述词的规一化值");
		datalen = 2;
		break;
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
		text.append("未定义，保留");
		break;
	case 30:
		text.append("带CP56Time2a时标的单点信息");
		datalen = 1;
		timelen = 7;
		break;
	case 31:
		text.append("带CP56Time2a时标的双点信息");
		datalen = 1;
		timelen = 7;
		break;
	case 32:
		text.append("带CP56Time2a时标的步位置信息");
		datalen = 2;
		timelen = 7;
		break;
	case 33:
		text.append("带CP56Time2a时标的32比特串");
		break;
	case 34:
		text.append("带CP56Time2a时标的测量值, 规一化值");
		break;
	case 35:
		text.append("带CP56Time2a时标的测量值, 标度化值");
		break;
	case 36:
		text.append("带CP56Time2a时标的测量值, 短浮点数");
		break;
	case 37:
		text.append("带CP56Time2a时标的累计量");
		break;
	case 38:
		text.append("带CP56Time2a时标的继电保护设备事件");
		break;
	case 39:
		text.append("带CP56Time2a时标的继电保护设备成组启动事件");
		break;
	case 40:
		text.append("带CP56Time2a时标的继电保护设备成组输出电路信息");
		break;
	case 41:
	case 42:
	case 43:
	case 44:
		text.append("未定义，保留");
		break;
	case 45:
		text.append("单点命令");
		datalen = 1;
		break;
	case 46:
		text.append("双点命令");
		datalen = 1;
		break;
	case 47:
		text.append("步调节命令");
		break;
	case 48:
		text.append("设定值命令, 规一化值");
		break;
	case 49:
		text.append("设定值命令, 标度化值");
		break;
	case 50:
		text.append("设定值命令, 短浮点数");
		datalen = 4;
		other = 1;
		break;
	case 51:
		text.append("32比特串");
		break;
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
	case 58:
	case 59:
	case 60:
	case 61:
	case 62:
	case 63:
	case 64:
	case 65:
	case 66:
	case 67:
	case 68:
	case 69:
		text.append("未定义，保留");
		break;
	case 70:
		text.append("初始化结束");
		datalen = 1;
		break;
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 78:
	case 79:
	case 80:
	case 81:
	case 82:
	case 83:
	case 84:
	case 85:
	case 86:
	case 87:
	case 88:
	case 89:
	case 90:
	case 91:
	case 92:
	case 93:
	case 94:
	case 95:
	case 96:
	case 97:
	case 98:
	case 99:
		text.append("未定义，保留");
		break;
	case 100:
		text.append("总召唤命令");
		datalen = 1;
		break;
	case 101:
		text.append("计数量召唤命令");
		datalen = 1;
		break;
	case 102:
		text.append("读命令");
		break;
	case 103:
		text.append("时钟同步命令");
		timelen = 7;
		break;
	case 104:
		text.append("测试命今");
		break;
	case 105:
		text.append("复位进程命令");
		break;
	case 106:
		text.append("延时获得命今");
		break;
	case 107:
	case 108:
	case 109:
		text.append("未定义，保留");
		break;
	case 110:
		text.append("测量值参数, 规一化值");
		break;
	case 111:
		text.append("测量值参数, 标度化值");
		break;
	case 112:
		text.append("测量值参数, 短浮点数");
		break;
	case 113:
		text.append("参数激活");
		break;
	case 114:
	case 115:
	case 116:
	case 117:
	case 118:
	case 119:
		text.append("未定义，保留");
		break;
	case 120:
		text.append("文件淮备就绪");
		break;
	case 121:
		text.append("节淮备就绪");
		break;
	case 122:
		text.append("召唤目录, 选择文件, 召唤文件，召唤节");
		break;
	case 123:
		text.append("最后的节,最后的段");
		break;
	case 124:
		text.append("认可文件,认可节");
		break;
	case 125:
		text.append("段");
		break;
	case 126:
		text.append("目录");
		break;
	case 127:
		text.append("未定义，保留");
		break;
	case 137:
		text.append("计划曲线传送(南网扩展功能)");
		datalen = 2;
		other = 8;
		break;
	case 167:
		text.append("定值处理(扩展功能)");
		datalen = 1;
		break;
	default:
		text.append("未知ASDU类型，无法继续解析");
		datalen = 0;
		break;
	}
	text.append("\r\n");
	return text;
}

QString IEC101asdu::vsqToText()
{
	QString text = "可变结构限定词VSQ，";
	sqflag = (vsq>>7) & 0x01;
	datanum = vsq & 0x7f;

	text.append("信息元素数量(bit1-7):" + QString::number(datanum) + " \r\n\t");
	if(sqflag)
	{
		text.append("SQ(bit8):1 信息元素顺序排列，只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1");
	}
	else
	{
		text.append("SQ(bit8):0 信息元素单个排列，每个信息元素都有独自的地址");
	}
	text.append("\r\n");

	return text;
}

QString IEC101asdu::cotToText()
{
	QString text = "传送原因(bit1-6):"+ QString::number(cot[0] & 0x3f) + " ";
	switch (cot[0] & 0x3f)
	{
	case 1:
		text.append("周期、循环上送");
		break;
	case 2:
		text.append("背景扫描，基于连续传送方式，用于监视方向，将被控站的过程信息去同步控制站的数据库，优先级较低");
		break;
	case 3:
		text.append("突发、自发");
		break;
	case 4:
		text.append("初始化");
		break;
	case 5:
		text.append("请求或被请求");
		break;
	case 6:
		text.append("激活");
		break;
	case 7:
		text.append("激活确认");
		break;
	case 8:
		text.append("停止激活");
		break;
	case 9:
		text.append("停止激活确认");
		break;
	case 10:
		text.append("激活终止");
		break;
	case 11:
		text.append("远方命令引起的返送信息");
		break;
	case 12:
		text.append("当地命令引起的返送信息");
		break;
	case 13:
		text.append("文件传输");
		break;
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		text.append("保留");
		break;
	case 20:
		text.append("响应站召唤");
		break;
	case 21:
		text.append("响应第1组召唤");
		break;
	case 22:
		text.append("响应第2组召唤");
		break;
	case 23:
		text.append("响应第3组召唤");
		break;
	case 24:
		text.append("响应第4组召唤");
		break;
	case 25:
		text.append("响应第5组召唤");
		break;
	case 26:
		text.append("响应第6组召唤");
		break;
	case 27:
		text.append("响应第7组召唤");
		break;
	case 28:
		text.append("响应第8组召唤");
		break;
	case 29:
		text.append("响应第9组召唤");
		break;
	case 30:
		text.append("响应第10组召唤");
		break;
	case 31:
		text.append("响应第11组召唤");
		break;
	case 32:
		text.append("响应第12组召唤");
		break;
	case 33:
		text.append("响应第13组召唤");
		break;
	case 34:
		text.append("响应第14组召唤");
		break;
	case 35:
		text.append("响应第15组召唤");
		break;
	case 36:
		text.append("响应第16组召唤");
		break;
	case 37:
		text.append("响应计数量(累积量)站(总)召唤");
		break;
	case 38:
		text.append("响应第1组计数量(累积量)召唤");
		break;
	case 39:
		text.append("响应第2组计数量(累积量)召唤");
		break;
	case 40:
		text.append("响应第3组计数量(累积量)召唤");
		break;
	case 41:
		text.append("响应第4组计数量(累积量)召唤");
		break;
	case 42:
	case 43:
		text.append("保留");
		break;
	case 44:
		text.append("未知的类型标识，收到报文的类型标识不正确");
		break;
	case 45:
		text.append("未知的传送原因，收到报文的传送原因不正确");
		break;
	case 46:
		text.append("未知的应用服务数据单元公共地址，收到报文的公共地址不正确");
		break;
	case 47:
		text.append("未知的信息对象地址，收到报文的信息对象地址不正确");
		break;
	default:
		text.append("未知，无法识别当前的传送原因");
		break;
	}
	text.append("   P/N(bit7):");
	if(cot[0] & 0x40)
	{
		text.append("1 否定确认");
	}
	else
	{
		text.append("0 肯定确认");
	}
	text.append("   T(bit8):");
	if(cot[0] & 0x80)
	{
		text.append("1 试验状态");
	}
	else
	{
		text.append("0 未试验");
	}
	text.append("\r\n");
	return text;
}

IEC101asdudata *IEC101asdu::CreateAsduData(uchar type)
{
	IEC101asdudata *asdudata = NULL;
	switch (type)
	{
	case 1:
		asdudata = new IEC101asdu1data;
		break;
	case 3:
		asdudata = new IEC101asdu3data;
		break;
	case 9:
		asdudata = new IEC101asdu9data;
		break;
	case 13:
		asdudata = new IEC101asdu13data;
		break;
	case 15:
		asdudata = new IEC101asdu15data;
		break;
	case 21:
		asdudata = new IEC101asdu21data;
		break;
	case 30:
		asdudata = new IEC101asdu30data;
		break;
	case 31:
		asdudata = new IEC101asdu31data;
		break;
	case 32:
		asdudata = new IEC101asdu32data;
		break;
	case 45:
		asdudata = new IEC101asdu45data;
		break;
	case 46:
		asdudata = new IEC101asdu46data;
		break;
	case 50:
		asdudata = new IEC101asdu50data;
		break;
	case 70:
		asdudata = new IEC101asdu70data;
		mstate = STATE_CALLALL;
		break;
	case 100:
		asdudata = new IEC101asdu100data;
		break;
	case 101:
		asdudata = new IEC101asdu101data;
		break;
	case 103:
		asdudata = new IEC101asdu103data;
		break;
	case 137:
		asdudata = new IEC101asdu137data;
		break;
	case 167:
		asdudata = new IEC101asdu167data;
		break;
	default:
		break;
	}
	return asdudata;
}




