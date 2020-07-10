#include "iec103asdu.h"
#include "globaldefine.h"
#include "app.h"
//#include "iec103asdu1data.h"
//#include "iec103asdu3data.h"
//#include "iec103asdu9data.h"
//#include "iec103asdu13data.h"
//#include "iec103asdu15data.h"
//#include "iec103asdu21data.h"
//#include "iec103asdu30data.h"
//#include "iec103asdu31data.h"
//#include "iec103asdu32data.h"
//#include "iec103asdu45data.h"
//#include "iec103asdu46data.h"
//#include "iec103asdu50data.h"
//#include "iec103asdu70data.h"
//#include "iec103asdu100data.h"
//#include "iec103asdu101data.h"
//#include "iec103asdu103data.h"
//#include "iec103asdu137data.h"

IEC103asdudata::IEC103asdudata()
{
	error = 0;
	inf = 0;
	mstate = STATE_NORMAL;
}

IEC103asdudata::~IEC103asdudata()
{

}

IEC103asdu::IEC103asdu()
{
	error = 0;
	type = 0;
	vsq = 0;
	cot = 0;
	commonaddr = 0;
	sqflag = 0;
	datanum = 0;
	asdulen = 0;
//	timelen = 0;
//	other = 0;
	mstate = STATE_NORMAL;
}

IEC103asdu::~IEC103asdu()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool IEC103asdu::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	qDeleteAll(datalist);
	datalist.clear();
	asdulen = 0;
	if(buff.count() < 4)
	{
		error = 1;
		return false;
	}

	type = *(buff.data()+asdulen);
	mText.append(CharToHexStr(buff.data()+asdulen) + "\t类型标识 " + typeToText()+"\r\n");
	asdulen++;

	vsq = *(buff.data()+asdulen);
	mText.append(CharToHexStr(buff.data()+asdulen) + "\t" + vsqToText()+"\r\n");
	asdulen++;

	cot = *(buff.data()+asdulen);
	mText.append(CharToHexStr(buff.data()+asdulen) + "\t" +cotToText()+"\r\n");
	asdulen++;

	commonaddr = *(buff.data()+asdulen);
	mText.append(CharToHexStr(buff.data()+asdulen) + "\t公共地址:" + QString::number(commonaddr) +"\r\n");
	asdulen ++;

	fun = *(buff.data()+asdulen);
	mText.append(CharToHexStr(buff.data()+asdulen) + "\t" + funToText() +"\r\n");
	asdulen ++;
//	int lengthtmp = 2+cotlen+comaddrlen+infaddrlen+(1-sqflag)*(datanum-1)* infaddrlen+datanum*(datalen+timelen)+other;
//	if( lengthtmp!= buff.count())
//	{
//		mText.append( "\r\n\t出错！通过VSQ与ASDU类型计算出ASDU长度为"+QString::number(lengthtmp)+"，而实际ASDU长度为"+QString::number(buff.count())+"。报文长度不符，因此报文有问题，下面的解析可能会出现异常\r\n");
//	}

	uchar inf = *(buff.data()+asdulen);;
	for(int index = 0;index<datanum;index++)
	{
		IEC103asdudata *mdata = CreateAsduData(type);
		bool isOk;
		if(index ==0 || sqflag == 1)
		{
			isOk = mdata->init(buff.mid(asdulen));
		}
		else
		{
			isOk = mdata->init(buff.mid(asdulen),inf+index);
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

QString IEC103asdu::showToText()
{
	QString text = mText;
	for(IEC103asdudata *mdata:datalist)
	{
		text.append(mdata->showToText());
	}
	return text;
}

bool IEC103asdu::createData(IECDataConfig &config)
{
	qDeleteAll(datalist);
	datalist.clear();

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

QString IEC103asdu::typeToText()
{
	QString text = "类型标识TYPE ASDU"+ QString::number(type) + ":";
	switch (type)
	{
	case 1:
		text.append("带时标的报文");
		break;
	case 2:
		text.append("具有相对时间的带时标的报文");
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
		break;
	case 8:
		text.append("总查询(总召唤)终止");
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
	case 36:
		text.append("电能脉冲量上送");
		break;
	case 38:
		text.append("总查询及变位上送步位置");
		break;
	case 39:
		text.append("步位置的SOE");
		break;
	case 40:
		text.append("上送变位遥信");
		break;
	case 41:
		text.append("上送SOE");
		break;
	case 42:
		text.append("总控上送变位遥信");
		break;
	case 43:
		text.append("总控上送SOE");
		break;
	case 44:
		text.append("上送全遥信");
		break;
	case 50:
		text.append("遥测上送");
		break;
	case 51:
		text.append("总控超过门限值的遥测上送");
		break;
	case 64:
		text.append("遥控选择/执行/撤消");
		break;
	case 88:
		text.append("电能脉冲量召唤（冻结）");
		break;
	default:
		text.append("未知ASDU类型，无法继续解析");
		break;
	}
	return text;
}

QString IEC103asdu::vsqToText()
{
	QString text = "可变结构限定词VSQ，";
	sqflag = (vsq>>7) & 0x01;
	datanum = vsq & 0x7f;

	text.append("信息元素数量(bit1-7):" + QString::number(datanum) + " \r\n\t");
	text.append("\tSQ(bit8):" + QString::number(vsq & 0x80,16).toUpper() + " ");
	if(sqflag)
	{
		text.append("每个信息元素都有独自的地址");
	}
	else
	{
		text.append("只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1");
	}
	text.append("\r\n");
	return text;
}

QString IEC103asdu::cotToText()
{
	QString text = "传送原因COT:"+ QString::number(cot) + " ";
	switch (cot)
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

QString IEC103asdu::funToText()
{
	QString text = "功能码fun:"+ QString::number(fun) + " ";
	switch (fun)
	{
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

IEC103asdudata *IEC103asdu::CreateAsduData(uchar type)
{
	IEC103asdudata *asdudata = NULL;
	switch (type)
	{
	case 10:
		asdudata = new IEC103asdu10data;
		break;
	case 21:
		asdudata = new IEC103asdu21data;
		break;
//	case 9:
//		asdudata = new IEC103asdu9data;
//		break;
//	case 13:
//		asdudata = new IEC103asdu13data;
//		break;
//	case 15:
//		asdudata = new IEC103asdu15data;
//		break;
//	case 21:
//		asdudata = new IEC103asdu21data;
//		break;
//	case 30:
//		asdudata = new IEC103asdu30data;
//		break;
//	case 31:
//		asdudata = new IEC103asdu31data;
//		break;
//	case 32:
//		asdudata = new IEC103asdu32data;
//		break;
//	case 45:
//		asdudata = new IEC103asdu45data;
//		break;
//	case 46:
//		asdudata = new IEC103asdu46data;
//		break;
//	case 50:
//		asdudata = new IEC103asdu50data;
//		break;
//	case 70:
//		asdudata = new IEC103asdu70data;
//		mstate = STATE_CALLALL;
//		break;
//	case 100:
//		asdudata = new IEC103asdu100data;
//		break;
//	case 101:
//		asdudata = new IEC103asdu101data;
//		break;
//	case 103:
//		asdudata = new IEC103asdu103data;
//		break;
//	case 137:
//		asdudata = new IEC103asdu137data;
//		break;
	default:
		break;
	}
	return asdudata;
}





