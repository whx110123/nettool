#include "protocol103asdu.h"
protocol103::protocol103asdu::protocol103asdu()
{
	gpdata = NULL;
}

protocol103::protocol103asdu::~protocol103asdu()
{
}

QString protocol103::protocol103asdu::dealASDU()
{
	QString text;
	QString tmp = CharToHexStr(m_asdu->type);
	text.append("-----------------------------------------------------------------------------------------------\r\n");
	text.append(tmp + "\t");
	text.append(dealTYPE());

	tmp = CharToHexStr(m_asdu->vsq);
	text.append(tmp + "\t");
	text.append(dealVSQ());


	tmp = CharToHexStr(m_asdu->cot);
	text.append(tmp + "\t");
	text.append(dealCOT());

	tmp = CharToHexStr(m_asdu->commonaddr);
	text.append(tmp + "\t公共地址:" + QString::number(m_asdu->commonaddr) +"\r\n");

	text.append("-----------------------------------------------------------------------------------------------\r\n");

	switch (m_asdu->type)
	{
	case 1:
		text.append(dealASDU1Data());
		break;
	case 2:
		text.append(dealASDU2Data());
		break;
	case 6:
		text.append(dealASDU6Data());
		break;
	case 7:
	case 8:
		text.append(dealASDU7Data());
		break;
	case 10:
	case 21:
		text.append(dealASDU10Data());
		break;
	case 44:
		text.append(dealASDU44Data());
		break;
	case 50:
		text.append(dealASDU50Data());
		break;
	case 51:
		text.append(dealASDU51Data());
		break;
	default:
		break;
	}

	return text;

}

QString protocol103::protocol103asdu::dealTYPE()
{
	QString text = "类型标识TYPE ASDU"+ QString::number(m_asdu->type) + ":";
	switch (m_asdu->type)
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
	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealCOT()
{
	QString text = "传送原因COT:"+ QString::number(m_asdu->cot) + " ";
	switch (m_asdu->cot)
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
	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealVSQ()
{
	QString text = "可变结构限定词VSQ，";
	sqflag = (m_asdu->vsq>>7) & 0x01;
	datanum = m_asdu->vsq & 0x7f;

	text.append("信息元素数量(bit1-7):" + QString::number(datanum) + " \r\n\t");
	if(sqflag)
	{
		text.append("SQ(bit8):1 信息元素单个排列，每个信息元素都有独自的地址");
	}
	else
	{
		text.append("SQ(bit8):0 信息元素顺序排列，只有第一个信息元素有地址，以后信息元素的地址从这个地址起顺序加1");
	}
	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealFUN()
{
	QString text = "FUN:"+ QString::number(fun) + " ";
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
	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealINFGEN()
{
	QString text = "INF:"+ QString::number(infgen) + " ";
	switch (infgen)
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
		text.append("未知");
		break;
	}
	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealNGD()
{
	QString text ;
	no = ngd & 0x3f;
	text.append("NO(bit1-6):" + QString::number(no) + " 通用分类数据集数目\r\n\t");
	count = (ngd>>6) & 0x01;
	text.append("COUNT(bit7):"+ QString::number(count) + " 具有相同返回信息标识符(RII)的应用服务数据单元的一位计数器位\r\n\t");

	cont = (ngd>>7) & 0x01;
	text.append("CONT(bit8):"+ QString::number(cont));
	if(cont)
	{
		text.append(" 后面跟着具有相同返回信息标识符(RII)的应用服务数据单元");
	}
	else
	{
		text.append(" 后面未跟着具有相同返回信息标识符(RII)的应用服务数据单元");
	}

	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealKOD(uchar kod)
{
	QString text = "KOD:"+ QString::number(kod) + " ";
	switch (kod)
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
	default:
		text.append("备用");
		break;
	}
	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealGDD3(GROUPDATA *gpdata)
{
	QString text ;
	gpdata->number = gpdata->gdd[2] & 0x7f;
	text.append("GDD3:NUMBER(bit1-7):" + QString::number(gpdata->number) + " 信息数目   ");
	cont = (ngd>>7) & 0x01;
	text.append("CONT(bit8):"+ QString::number(cont));
	if(cont)
	{
		text.append(" 后面跟随的数据元素具有相同的返回信息标识符(RII)");
	}
	else
	{
		text.append(" 后面未跟随数据元素");
	}

	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealGID(protocol103::GROUPDATA *gpdata,int index)
{
	QString text ;
	QString tmp;
	float datafloat;
	short datashort;
	uint datauint;
	int dataint;
	QDateTime datat;
	uchar *m_gid = &gpdata->gid[index*gpdata->gdd[1]];

	switch (gpdata->gdd[0])
	{
	case 0:
		text.append("无数据");
		break;
	case 1:
		text.append("OS8(ASCII8位码)");
		break;
		//    case 2:
		//        text.append("成组8位串");
		//        break;
	case 3:
		for(int k = 0;k<gpdata->gdd[1];k++)
		{
			tmp.append(CharToHexStr(*(m_gid+k))+ " ");
		}
		datauint = charTouint(m_gid,gpdata->gdd[1]);
		text.append(tmp + "\tGID:无符号整数:"+QString::number(datauint));
		break;
	case 4:
		for(int k = 0;k<gpdata->gdd[1];k++)
		{
			tmp.append(CharToHexStr(*(m_gid+k))+ " ");
		}
		dataint = charToint(m_gid,gpdata->gdd[1]);
		text.append(tmp + "\tGID:整数:"+QString::number(dataint));
		break;
	case 5:
		text.append("无符号浮点数");
		break;
	case 6:
		text.append("浮点数");
		break;
	case 7:
		for(int k = 0;k<gpdata->gdd[1];k++)
		{
			tmp.append(CharToHexStr(*(m_gid+k))+ " ");
		}
		datafloat = charTofloat(m_gid);
		text.append(tmp + "\tGID:IEEE标准754短实数:"+QString::number(datafloat));
		break;
	case 8:
		text.append("IEEE标准754实数");
		break;
	case 9:
		tmp =CharToHexStr(*m_gid);
		dpi = *m_gid & 0x03;
		text.append(tmp +  "\tGID:" + dealDPI());
		//        text.append("双点信息");
		break;
	case 10:
		tmp =CharToHexStr(*m_gid);
		spi = *m_gid & 0x01;
		text.append(tmp +  "\tGID:" + dealSPI());
		//        text.append("单点信息");
		break;
	case 11:
		tmp =CharToHexStr(*m_gid);
		dpi = *m_gid & 0x03;
		text.append(tmp +  "\tGID:" + dealDPITE());
		//        text.append("带瞬变和差错的双点信息");
		break;
	case 12:
		for(int k = 0;k<gpdata->gdd[1];k++)
		{
			tmp.append(CharToHexStr(gpdata->gid[k + index*gpdata->gdd[1]])+ " ");
		}
		datashort = charToshortwithQ(m_gid,ov,er);
		text.append(tmp + "\tGID:带品质描述词的被测值(bit4-16):"+QString::number(datashort) + "\r\n\t");
		text.append(dealOV() + dealER() );
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
		tmp =CharToHexStr(*m_gid);
		dpi = *m_gid & 0x03;
		text.append(tmp + "\tGID:" + dealDPI()+"\r\n");

		text.append(dealDateTime(m_gid+1,4));

		tmp =CharToHexStr(*(m_gid+5));
		text.append(tmp +  "\tGID:附加信息SIN:"+QString::number(*(m_gid+5)));
		//        text.append("带时标的报文");
		break;
	case 19:
		tmp =CharToHexStr(*m_gid);
		dpi = *m_gid & 0x03;
		text.append(tmp +  "\tGID:" + dealDPI()+ "\r\n");

		tmp =CharToHexStr(*(m_gid+1))+ " "+ CharToHexStr(*(m_gid+2));
		datauint = charTouint(m_gid+1,2);
		text.append(tmp +  "\tGID:相对时间RET:"+QString::number(datauint) );
		text.append("   秒:" + QString::number(datauint/1000) +"   毫秒:" + QString::number(datauint%1000) + " \r\n");

		tmp =CharToHexStr(*(m_gid+3))+ " "+ CharToHexStr(*(m_gid+4));
		datauint = charTouint(m_gid+3,2);
		text.append(tmp +  "\tGID:故障序号FAN:"+QString::number(datauint) + "\r\n");

		text.append(dealDateTime(m_gid+5,4));

		tmp =CharToHexStr(*(m_gid+9));
		text.append(tmp +  "\tGID:附加信息SIN:"+QString::number(*(m_gid+9)));

		//        text.append("带相对时间的时标报文");
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
	default:
		text.append("备用");
		break;
	}
	text.append("\r\n");
	return text;
}

QString protocol103::protocol103asdu::dealGDDandGID(protocol103::GROUPDATA *gpdata)
{
	QString text ;
	QString tmp;
	int i;
	tmp =CharToHexStr(gpdata->gdd[0]) ;
	text.append(tmp + "\tGDD1:"+ QString::number(gpdata->gdd[0]) + " ");

	switch (gpdata->gdd[0])
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
	default:
		text.append("备用");
		break;
	}
	tmp =CharToHexStr(gpdata->gdd[1]) ;
	text.append("\r\n"+tmp + "\tGDD2:" +QString::number(gpdata->gdd[1])+" 数据宽度\r\n");
	tmp =CharToHexStr(gpdata->gdd[2]) ;
	text.append(tmp + "\t" + dealGDD3(gpdata));
	if(gpdata->gdd[0] == 2)
	{
		tmp.clear();
		for(i = 0;i<gpdata->gidlen;i++)
		{
			tmp.append(CharToHexStr(gpdata->gid[i])+ " ");
		}
		text.append(tmp + "\tGID:成组8位串，每一位bit为一个信息点,共" + QString::number((ushort)gpdata->gdd[1]*gpdata->number) + "个信息点\r\n");
	}
	else
	{
		for(i = 0;i<gpdata->number;i++)
		{
			text.append(dealGID(gpdata,i));
		}
	}

	return text;
}

QString protocol103::protocol103asdu::dealOV()
{
	QString text = "OV(bit1):" ;
	if(ov)
	{
		text.append("1 溢出");
	}
	else
	{
		text.append("0 未溢出");
	}
	text.append("   ");
	return text;
}

QString protocol103::protocol103asdu::dealER()
{
	QString text = "ER(bit2):" ;
	if(er)
	{
		text.append("1 被测值无效");
	}
	else
	{
		text.append("0 被测值有效");
	}
	text.append("   ");
	return text;
}

QString protocol103::protocol103asdu::dealDPI()
{
	QString text = "双点遥信DPI(bit1-2):" + QString::number(dpi) + " ";
	switch (dpi)
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
	text.append("   ");
	return text;
}

QString protocol103::protocol103asdu::dealDPITE()
{
	QString text = "带瞬变与差错的双点遥信DPI(bit1-2):" + QString::number(dpi) + " ";
	switch (dpi)
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
	}
	text.append("   ");
	return text;
}

QString protocol103::protocol103asdu::dealSPI()
{
	QString text = "单点遥信(bit1):" + QString::number(spi) + " ";
	if(spi)
	{
		text.append("合位");
	}
	else
	{
		text.append("分位");
	}
	text.append("   ");
	return text;
}

QString protocol103::protocol103asdu::dealIV()
{
	QString text = "IV(bit8):";
	if(iv)
	{
		text.append("1 无效");
	}
	else
	{
		text.append("0 有效");
	}
	text.append("   ");
	return text;
}
QString protocol103::protocol103asdu::dealBL()
{
	QString text = "BL(bit5):";
	if(bl)
	{
		text.append("1 被闭锁");
	}
	else
	{
		text.append("0 未被闭锁");
	}
	text.append("   ");
	return text;
}

QString protocol103::protocol103asdu::dealSB()
{
	QString text = "SB(bit6):";
	if(sb)
	{
		text.append("1 被取代");
	}
	else
	{
		text.append("0 未被取代");
	}
	text.append("   ");
	return text;
}

QString protocol103::protocol103asdu::dealNT()
{
	QString text = "NT(bit7):";
	if(nt)
	{
		text.append("1 非当前值");
	}
	else
	{
		text.append("0 当前值");
	}
	text.append("   ");
	return text;
}
QString protocol103::protocol103asdu::dealSU()
{
	QString text = "SU(bit8):";
	if(su)
	{
		text.append("1 夏季时间");
	}
	else
	{
		text.append("0 标准时间");
	}
	text.append("   ");
	return text;
}

QString protocol103::protocol103asdu::dealASDU1Data()
{
	QString text;
	QString tmp;
	int i = 0;

	tmp =CharToHexStr(m_asdu->data[i]);
	fun = m_asdu->data[i++];
	text.append(tmp + "\t" + dealFUN());

	tmp =CharToHexStr(m_asdu->data[i]);
	inf = m_asdu->data[i++];
	text.append(tmp + "\tINF:" + QString::number(inf)+"\r\n");

	tmp =CharToHexStr(m_asdu->data[i]);
	dpi = m_asdu->data[i++] & 0x03;
	text.append(tmp + "\t" + dealDPI()+"\r\n");

	text.append(dealDateTime(&m_asdu->data[i],4));
	i += 4;

	tmp =CharToHexStr(m_asdu->data[i]);
	text.append(tmp +  "\t附加信息SIN:"+QString::number(m_asdu->data[i])+"\r\n");
	i++;
	if(i+4 > m_asdu->length)
	{
		text.append("\t出错！解析的报文多于实际报文，说明报文存在问题\r\n");
	}
	else if(i+4 < m_asdu->length)
	{
		text.append("\t出错！解析的报文少于实际报文，说明报文存在问题\r\n");
	}
	return text;
}

QString protocol103::protocol103asdu::dealASDU2Data()
{
	QString text;
	QString tmp;
	int i = 0;
	uint datauint;

	tmp =CharToHexStr(m_asdu->data[i]);
	fun = m_asdu->data[i++];
	text.append(tmp + "\t" + dealFUN());

	tmp =CharToHexStr(m_asdu->data[i]);
	inf = m_asdu->data[i++];
	text.append(tmp + "\tINF:" + QString::number(inf)+"\r\n");

	tmp =CharToHexStr(m_asdu->data[i]);
	dpi = m_asdu->data[i++];
	text.append(tmp + "\t" + dealDPI()+"\r\n");

	tmp =CharToHexStr(m_asdu->data[i])+ " "+ CharToHexStr(m_asdu->data[i+1]);
	datauint = charTouint(&m_asdu->data[i],2);
	text.append(tmp +  "\t相对时间RET:"+QString::number(datauint) );
	text.append("   秒:" + QString::number(datauint/1000) +"   毫秒:" + QString::number(datauint%1000) + " \r\n");
	i += 2;

	tmp =CharToHexStr(m_asdu->data[i])+ " "+ CharToHexStr(m_asdu->data[i+1]);
	datauint = charTouint(&m_asdu->data[i],2);
	text.append(tmp +  "\t故障序号FAN:"+QString::number(datauint) + "\r\n");
	i += 2;

	text.append(dealDateTime(&m_asdu->data[i],4));
	i += 4;

	tmp =CharToHexStr(m_asdu->data[i]);
	text.append(tmp +  "\t附加信息SIN:"+QString::number(m_asdu->data[i])+"\r\n");
	i++;
	if(i+4 > m_asdu->length)
	{
		text.append("\t出错！解析的报文多于实际报文，说明报文存在问题\r\n");
	}
	else if(i+4 < m_asdu->length)
	{
		text.append("\t出错！解析的报文少于实际报文，说明报文存在问题\r\n");
	}
	return text;

}

QString protocol103::protocol103asdu::dealASDU6Data()
{
	QString text;
	QString tmp;
	int i = 0;

	tmp =CharToHexStr(m_asdu->data[i]);
	fun = m_asdu->data[i++];
	text.append(tmp + "\t" + dealFUN());

	tmp =CharToHexStr(m_asdu->data[i]);
	inf = m_asdu->data[i++];
	text.append(tmp + "\tINF:" + QString::number(inf)+"\r\n");

	text.append(dealDateTime(&m_asdu->data[i],7));
	i += 7;
	if(i+4 > m_asdu->length)
	{
		text.append("\t出错！解析的报文多于实际报文，说明报文存在问题\r\n");
	}
	else if(i+4 < m_asdu->length)
	{
		text.append("\t出错！解析的报文少于实际报文，说明报文存在问题\r\n");
	}
	return text;

}

QString protocol103::protocol103asdu::dealASDU7Data()
{
	QString text;
	QString tmp;
	int i = 0;

	tmp =CharToHexStr(m_asdu->data[i]);
	fun = m_asdu->data[i++];
	text.append(tmp + "\t" + dealFUN());

	tmp =CharToHexStr(m_asdu->data[i]);
	inf = m_asdu->data[i++];
	text.append(tmp + "\tINF:" + QString::number(inf)+"\r\n");

	tmp =CharToHexStr(m_asdu->data[i]);
	text.append(tmp +  "\t扫描序号SCN:"+QString::number(m_asdu->data[i])+" 子站的总查询应答报文中附加信息SIN需要与之一样\r\n");
	i++;
	if(i+4 > m_asdu->length)
	{
		text.append("\t出错！解析的报文多于实际报文，说明报文存在问题\r\n");
	}
	else if(i+4 < m_asdu->length)
	{
		text.append("\t出错！解析的报文少于实际报文，说明报文存在问题\r\n");
	}
	return text;
}

QString protocol103::protocol103asdu::dealASDU10Data()
{
	QString text;
	QString tmp;
	int i = 0;

	tmp =CharToHexStr(m_asdu->data[i]);
	fun = m_asdu->data[i++];
	text.append(tmp + "\t" + dealFUN());

	tmp =CharToHexStr(m_asdu->data[i]);
	infgen = m_asdu->data[i++];
	text.append(tmp + "\t" + dealINFGEN());

	tmp =CharToHexStr(m_asdu->data[i]);
	rii = m_asdu->data[i++];
	text.append(tmp+ "\tRII:" +QString::number(rii)+" 返回信息标识符\r\n");

	if(i+4 == m_asdu->length)
	{
		return text;
	}
	tmp =CharToHexStr(m_asdu->data[i]);
	ngd = m_asdu->data[i++];
	text.append(tmp+ "\t" + dealNGD());

	if(no >0)
	{
		gpdata = new GROUPDATA[no];

		for(int j = 0;j<no;j++)
		{
			i += charToGroupDate(&m_asdu->data[i],&gpdata[j]);

			text.append("-----------------------------------------------------------------------------------------------\r\n");
			tmp =CharToHexStr(gpdata[j].gin[0]) + " " + CharToHexStr(gpdata[j].gin[1]);
			text.append(tmp+ "\tGIN:组号" +QString::number(gpdata[j].gin[0])+"   条目号"+QString::number(gpdata[j].gin[1])+"\r\n");

			tmp =CharToHexStr(gpdata[j].kod);
			text.append(tmp+ "\t" + dealKOD(gpdata[j].kod));
			if(m_asdu->type == 21)
			{
				continue;
			}
			text.append(dealGDDandGID(&gpdata[j]));

		}
		if(gpdata)
		{
			delete [] gpdata;
			gpdata = NULL;
		}
	}
	if(i+4 > m_asdu->length)
	{
		text.append("\t出错！解析的报文多于实际报文，说明报文存在问题\r\n");
	}
	else if(i+4 < m_asdu->length)
	{
		text.append("\t出错！解析的报文少于实际报文，说明报文存在问题\r\n");
	}
	return text;
}


QString protocol103::protocol103asdu::dealASDU44Data()
{
	QString text;
	QString tmp;
	int i = 0;

	tmp =CharToHexStr(m_asdu->data[i]);
	fun = m_asdu->data[i++];
	text.append(tmp + "\t" + dealFUN());

	tmp =CharToHexStr(m_asdu->data[i]);
	inf = m_asdu->data[i++];
	text.append(tmp + "\tINF:" + QString::number(inf)+"\r\n");
	for(int j = 0; j<datanum;j++)
	{
		tmp =CharToHexStr(m_asdu->data[i])+ " "+ CharToHexStr(m_asdu->data[i+1]);
		text.append(tmp + "\t16个遥信状态\r\n");
		ushort dataushort = m_asdu->data[i] + m_asdu->data[i+1]*0x100;
		for(int k = 0;k<16;k++)
		{
			text.append("\t第" + QString::number(j*16 + k+1)+"个遥信:");
			if((dataushort>>k)&0x01)
			{
				text.append("1 合位");
			}
			else
			{
				text.append("0 分位");
			}
			text.append("   FUN:"+ QString::number(fun) + " INF:"+QString::number(inf+j*16 + k)+"\r\n");
		}
		i +=2;
		tmp =CharToHexStr(m_asdu->data[i])+ " "+ CharToHexStr(m_asdu->data[i+1]);
		text.append(tmp + "\t16个遥信与上次查询的变化状态\r\n");
		dataushort = m_asdu->data[i] + m_asdu->data[i+1]*0x100;
		for(int k = 0;k<16;k++)
		{
			text.append("\t第" + QString::number(j*16 + k+1)+"个遥信:");
			if((dataushort>>k)&0x01)
			{
				text.append("1  有改变");
			}
			else
			{
				text.append("0  无改变");
			}
			//            text.append(" FUN:"+ QString::number(fun) + " INF:"+QString::number(inf+j*16 + k)+"\r\n");
			text.append("\r\n");
		}
		i +=2;
		tmp =CharToHexStr(m_asdu->data[i]);
		iv = m_asdu->data[i] & 0x80;
		nt = m_asdu->data[i] & 0x40;
		sb = m_asdu->data[i] & 0x20;
		bl = m_asdu->data[i] & 0x10;
		ov = m_asdu->data[i] & 0x01;
		text.append(tmp + "\t品质位:" + dealIV() + dealNT()+ dealSB()+ dealBL()+dealOV() + "\r\n");
		i++;
	}
	tmp =CharToHexStr(m_asdu->data[i]);
	text.append(tmp +  "\t扫描序号SCN:"+QString::number(m_asdu->data[i])+" 子站的总查询应答报文中附加信息SIN需要与之一样\r\n");
	i++;
	if(i+4 > m_asdu->length)
	{
		text.append("\t出错！解析的报文多于实际报文，说明报文存在问题\r\n");
	}
	else if(i+4 < m_asdu->length)
	{
		text.append("\t出错！解析的报文少于实际报文，说明报文存在问题\r\n");
	}
	return text;
}

QString protocol103::protocol103asdu::dealASDU50Data()
{
	QString text;
	QString tmp;
	int i = 0;
	short datashort;

	tmp =CharToHexStr(m_asdu->data[i]);
	fun = m_asdu->data[i++];
	text.append(tmp + "\t" + dealFUN());

	tmp =CharToHexStr(m_asdu->data[i]);
	inf = m_asdu->data[i++];
	text.append(tmp + "\tINF:" + QString::number(inf)+"\r\n");
	for(int j = 0; j<datanum;j++)
	{
		tmp =CharToHexStr(m_asdu->data[i])+ " "+ CharToHexStr(m_asdu->data[i+1]);
		datashort = charToshortwithQ(&m_asdu->data[i],ov,er);
		text.append(tmp + "\t第" + QString::number(j+1)+"个遥测(bit4-16):"+QString::number(datashort));
		text.append("   FUN:"+ QString::number(fun) + " INF:"+QString::number(inf+j)+"  ");
		text.append(dealOV() + dealER() + "\r\n");
		i += 2;
	}
	//    tmp =CharToHexStr(m_asdu->data[i]);
	//    text.append(tmp +  "\t扫描序号SCN:"+QString::number(m_asdu->data[i])+" 子站的总查询应答报文中附加信息SIN需要与之一样\r\n");
	if(i+4 > m_asdu->length)
	{
		text.append("\t出错！解析的报文多于实际报文，说明报文存在问题\r\n");
	}
	else if(i+4 < m_asdu->length)
	{
		text.append("\t出错！解析的报文少于实际报文，说明报文存在问题\r\n");
	}
	return text;

}

QString protocol103::protocol103asdu::dealASDU51Data()
{
	QString text;
	QString tmp;
	int i = 0;
	short datashort;

	tmp =CharToHexStr(m_asdu->data[i]);
	fun = m_asdu->data[i++];
	text.append(tmp + "\t" + dealFUN());
	for(int j = 0; j<datanum;j++)
	{
		tmp =CharToHexStr(m_asdu->data[i]);
		inf = m_asdu->data[i++];
		text.append(tmp + "\tINF:" + QString::number(inf)+"\r\n");

		tmp =CharToHexStr(m_asdu->data[i])+ " "+ CharToHexStr(m_asdu->data[i+1]);
		datashort = charToshortwithQ(&m_asdu->data[i],ov,er);
		text.append(tmp + "\t第" + QString::number(j+1)+"个遥测(bit4-16):"+QString::number(datashort));
		text.append("   FUN:"+ QString::number(fun) + " INF:"+QString::number(inf)+"  ");
		text.append(dealOV() + dealER() + "\r\n");
		i += 2;
	}
	//    tmp =CharToHexStr(m_asdu->data[i]);
	//    text.append(tmp +  "\t扫描序号SCN:"+QString::number(m_asdu->data[i])+" 子站的总查询应答报文中附加信息SIN需要与之一样\r\n");
	if(i+4 > m_asdu->length)
	{
		text.append("\t出错！解析的报文多于实际报文，说明报文存在问题\r\n");
	}
	else if(i+4 < m_asdu->length)
	{
		text.append("\t出错！解析的报文少于实际报文，说明报文存在问题\r\n");
	}
	return text;
}

uchar protocol103::protocol103asdu::charToGroupDate(uchar *data,GROUPDATA *gpdata)
{
	uchar i = 0;
	memcpy(gpdata->gin,&data[i],2);
	i += 2;
	gpdata->kod = data[i++];
	if(m_asdu->type == 21)
	{
		return i;
	}
	memcpy(gpdata->gdd,&data[i],3);
	i += 3;
	gpdata->number = gpdata->gdd[2]&0x7f;
	if(gpdata->gdd[1] != 0 && gpdata->number != 0)
	{
		if(gpdata->gdd[0]==2)
		{
			gpdata->gidlen = ((ushort)gpdata->gdd[1]*gpdata->number-1)/8+1;
		}
		else
		{
			gpdata->gidlen = (ushort)gpdata->gdd[1]*gpdata->number;
		}
		memcpy(gpdata->gid,&data[i],gpdata->gidlen);
		i =i + gpdata->gidlen;
	}
	return i;
}

QString protocol103::protocol103asdu::dealDateTime(uchar *time,int timelen)
{
	QString text;
	QString tmp;
	uchar datauchar;
	QDateTime datetime = charToDateTime(time,timelen,BINARYTIME2A);

	tmp =CharToHexStr(time[0]) +" "+ CharToHexStr(time[1]);
	uint datauint = charTouint(time,2);
	text.append(tmp + "\t"+QString::number(datauint) + "   秒:" + QString::number(datetime.time().second()) +"   毫秒:" + QString::number(datetime.time().msec()) + " \r\n");
	if(timelen ==2)
	{
		return text;
	}

	tmp =CharToHexStr(time[2]);
	iv = time[2]&0x80;
	text.append(tmp + "\t分(bit1-6):" + QString::number(datetime.time().minute()) + "   "+dealIV() +"\r\n");
	if(timelen ==3)
	{
		return text;
	}

	tmp =CharToHexStr(time[3]);
	su = time[3] & 0x80;
	text.append(tmp + "\t时(bit1-5):" + QString::number(datetime.time().hour()) + "   "+dealSU()+"\r\n");
	if(timelen ==4)
	{
		return text;
	}

	tmp =CharToHexStr(time[4]);
	datauchar = time[4]>>5;
	text.append(tmp + "\t日(bit1-5):" + QString::number(datetime.date().day()) +"   周(bit6-8):"+QString::number(datauchar)+ " (7表示星期天,0表示未用)\r\n");
	//    text.append(tmp + "\t日(bit1-5):" + QString::number(datetime.date().day()) +"   周(bit6-8):"+QString::number(datetime.date().dayOfWeek())+ " (7表示星期天)\r\n");
	if(timelen ==5)
	{
		return text;
	}

	tmp =CharToHexStr(time[5]);
	text.append(tmp + "\t月(bit1-4):" + QString::number(datetime.date().month()) + "\r\n");
	if(timelen ==6)
	{
		return text;
	}

	tmp =CharToHexStr(time[6]);
	text.append(tmp + "\t年(bit1-7):" + QString::number(datetime.date().year()) + "\r\n");
	return text;
}
