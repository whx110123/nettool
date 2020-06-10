#include "protocol101asdu.h"
#include "protocol103asdu.h"

protocol101::protocol101asdu::protocol101asdu()
{
//    m_asdu = new ASDU;

}

protocol101::protocol101asdu::~protocol101asdu()
{

//    if(m_asdu)
//    {
//        delete m_asdu;
//    }

}

//protocoltelecontrol::protocoltelecontrol(ASDU *asdu)
//{
//    m_asdu = new ASDU(*asdu);
//    m_asdu->groupdata = NULL;
//}

QString protocol101::protocol101asdu::dealASDU()
{
    QString text;
    QString tmp = CharToHexStr(m_asdu->type);
    text.append(tmp + "\t类型标识TYPE ");
    text.append(dealTYPE());

    tmp = CharToHexStr(m_asdu->vsq);
    text.append(tmp + "\t");
    text.append(dealVSQ());



    tmp = CharToHexStr(m_asdu->cot[0]);
    text.append(tmp + "\t" +dealCOT());

    if(cotlen == 2)
    {
        tmp = CharToHexStr(m_asdu->cot[1]);
        text.append(tmp + "\t源发站地址号:"+QString::number(m_asdu->cot[1])+"\r\n");
    }


    if(comaddrlen == 2)
    {
        tmp = CharToHexStr(m_asdu->commonaddr[0]) + " " + CharToHexStr(m_asdu->commonaddr[1]);

    }
    else
    {
        tmp = CharToHexStr(m_asdu->commonaddr[0]);
    }
    text.append(tmp + "\t公共地址:" + QString::number(charTouint(m_asdu->commonaddr,comaddrlen)) +"\r\n");

	if(m_asdu->type == 167)
	{
		text.append(dealASDU167());
		return text;
	}
//    if(datalen ==0 && timelen ==0)
//    {
//        text.append("\r\n\t未完成此ASDU剩余报文的解析\r\n");
//        tmp = QString::number(m_asdu->type);
//        text.append("\r\n\t ASDU"+tmp+"解析结束\r\n");
//        text.append("-----------------------------------------------------------------------------------------------\r\n");
//        return text;
//    }

    int lengthtmp = 2+cotlen+comaddrlen+dataaddrlen+(1-sqflag)*(datanum-1)* dataaddrlen+datanum*(datalen+timelen)+other;
    if( lengthtmp!= m_asdu->length)
    {
        text.append( "\r\n\t出错！通过VSQ与ASDU类型计算出ASDU长度为"+QString::number(lengthtmp)+"，而实际ASDU长度为"+QString::number(m_asdu->length)+"。报文长度不符，因此报文有问题，下面的解析可能会出现异常\r\n");
 //       return text;
    }
    m_asdu->groupdata = new GROUPDATA[datanum];
    charToASDUDate();

    for(int index = 0;index<datanum;index++)
    {
        text.append("-----------------------------------------------------------------------------------------------\r\n");
        uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
        tmp.clear();
        if(index ==0 || sqflag == 0)
        {
            if(dataaddrlen == 3)
            {
                tmp = CharToHexStr(m_asdu->groupdata[index].addr[0])+ " "  +CharToHexStr(m_asdu->groupdata[index].addr[1]) + " " + CharToHexStr(m_asdu->groupdata[index].addr[2]);
            }
            else if (dataaddrlen == 2)
            {
                tmp =CharToHexStr(m_asdu->groupdata[index].addr[0]) + " " + CharToHexStr(m_asdu->groupdata[index].addr[1]);
            }
            else if (dataaddrlen == 1)
            {
                tmp =CharToHexStr(m_asdu->groupdata[index].addr[0]);
            }
        }
        text.append(tmp + "\t第"+QString::number(index+1)+"个信息元素地址:" + QString::number(dataaddr));
        switch (m_asdu->type)
        {
        case 1:
            text.append(dealASDU1Data(index));
            break;
        case 3:
            text.append(dealASDU3Data(index));
            break;
        case 9:
            text.append(dealASDU9Data(index));
            break;
        case 13:
            text.append(dealASDU13Data(index));
            break;
        case 15:
            text.append(dealASDU15Data(index));
            break;
        case 21:
            text.append(dealASDU21Data(index));
            break;
        case 30:
            text.append(dealASDU30Data(index));
            break;
        case 31:
            text.append(dealASDU31Data(index));
            break;
        case 32:
            text.append(dealASDU32Data(index));
            break;
        case 45:
            text.append(dealASDU45Data(index));
            break;
        case 46:
            text.append(dealASDU46Data(index));
            break;
        case 50:
            text.append(dealASDU50Data(index));
            break;
        case 70:
            text.append(dealASDU70Data(index));
            break;
        case 100:
            text.append(dealASDU100Data(index));
            break;
        case 101:
            text.append(dealASDU101Data(index));
            break;
        case 103:
            text.append(dealASDU103Data(index));
            break;
        case 137:
            text.append(dealASDU137Data(index));
            break;
        default:
            break;
        }

    }
    if(m_asdu->groupdata)
    {
        delete [] m_asdu->groupdata;
        m_asdu->groupdata = NULL;
    }
    if(other)
    {
        text.append("-----------------------------------------------------------------------------------------------\r\n");
        text.append(dealOTHER());
    }
    text.append("\r\n\t ASDU"+QString::number(m_asdu->type)+"解析结束\r\n");
    text.append("-----------------------------------------------------------------------------------------------\r\n");
    return text;

}

QString protocol101::protocol101asdu::dealTYPE()
{
    QString text = "ASDU"+ QString::number(m_asdu->type) + ":";
    switch (m_asdu->type)
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

QString protocol101::protocol101asdu::dealCOT()
{
    QString text = "传送原因(bit1-6):"+ QString::number(m_asdu->cot[0] & 0x3f) + " ";
    switch (m_asdu->cot[0] & 0x3f)
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
    if(m_asdu->cot[0] & 0x40)
    {
        text.append("1 否定确认");
    }
    else
    {
        text.append("0 肯定确认");
    }
    text.append("   T(bit8):");
    if(m_asdu->cot[0] & 0x80)
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

QString protocol101::protocol101asdu::dealVSQ()
{
    QString text = "可变结构限定词VSQ，";
    sqflag = (m_asdu->vsq>>7) & 0x01;
    datanum = m_asdu->vsq & 0x7f;

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

QString protocol101::protocol101asdu::dealSPI()
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

QString protocol101::protocol101asdu::dealDPI()
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

QString protocol101::protocol101asdu::dealSCS()
{
    QString text = "单点命令(bit1):" + QString::number(scs) + " ";
    if(scs)
    {
        text.append("合");
    }
    else
    {
        text.append("分");
    }
    text.append("   ");
    return text;
}

QString protocol101::protocol101asdu::dealDCS()
{
    QString text = "双点命令(bit1):" + QString::number(dcs) + " ";
    switch (dcs)
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
    text.append("   ");
    return text;
}

QString protocol101::protocol101asdu::dealOV()
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

QString protocol101::protocol101asdu::dealQOI()
{
    QString text = "召唤限定词:" + QString::number(qoi) + " ";
    switch (qoi)
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
    text.append("\r\n");
    return text;

}

QString protocol101::protocol101asdu::dealCOI()
{
    QString text = "初始化原因(bit1-7):"  + QString::number(coi&0x7f) + " ";
    switch (coi&0x7f)
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
    text.append("   BS(bit8):");
    if(coi&0x80)
    {
        text.append("1 改变当地参数后的初始化");
    }
    else
    {
        text.append("0 未改变当地参数后的初始化");
    }
    text.append("\r\n");
    return text;
}

QString protocol101::protocol101asdu::dealRQT()
{
    QString text = "计数量召唤命令限定词(QCC):请求RQT(bit1-6):"  + QString::number(rqt) + " ";
    switch (rqt)
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
    text.append("   ");
    return text;
}

QString protocol101::protocol101asdu::dealFRZ()
{
    QString text = "冻结FRZ(bit7-8):"  + QString::number(frz) + " ";
    switch (frz)
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
    text.append("   ");
    return text;
}

QString protocol101::protocol101asdu::dealSU()
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

QString protocol101::protocol101asdu::dealQU()
{
    QString text = "QU(bit3-7):" + QString::number(qu) + " ";
    switch (qu)
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

QString protocol101::protocol101asdu::dealSE()
{
    QString text = "S/E(bit8):";
    if(se)
    {
        text.append("1 命令类型:选择");
    }
    else
    {
        text.append("0 命令类型:执行");
    }
    text.append("   ");
    return text;
}

QString protocol101::protocol101asdu::dealCA()
{
    QString text = "CA(bit7):";
    if(ca)
    {
        text.append("1 上次读数后计数器被调整");
    }
    else
    {
        text.append("0 上次读数后计数器未被调整");
    }
    text.append("   ");
    return text;
}

QString protocol101::protocol101asdu::dealCY()
{
    QString text = "CY(bit6):";
    if(cy)
    {
        text.append("1 在相应的累加周期内计数器溢出");
    }
    else
    {
        text.append("0 在相应的累加周期内计数器未溢出");
    }
    text.append("   ");
    return text;
}

QString protocol101::protocol101asdu::dealVTI()
{
    uchar datauchar = vti<<1;
    int dataint = charToint(&datauchar,1) / 2;
    QString text = "步位置(bit1-7):"  + QString::number(dataint) ;

    text.append("   瞬变状态BS1(bit8):");
    if(vti&0x80)
    {
        text.append("1 设备处理瞬变状态");
    }
    else
    {
        text.append("0 设备未在瞬变状态");
    }
    text.append("\r\n");
    return text;
}

QString protocol101::protocol101asdu::dealQOS()
{
    QString text = "设定命令限定词QOS";
    ql = qos&0x7f;
    se = qos&0x80;
    text.append("  QL(bit1-7):" + QString::number(ql)+"   "+ dealSE() );
    return text;
}

QString protocol101::protocol101asdu::dealBL()
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

QString protocol101::protocol101asdu::dealSB()
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

QString protocol101::protocol101asdu::dealNT()
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

QString protocol101::protocol101asdu::dealIV()
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


QString protocol101::protocol101asdu::dealASDU1Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-1)+"\r\n");

    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    iv = m_asdu->groupdata[index].data[0] & 0x80;
    nt = m_asdu->groupdata[index].data[0] & 0x40;
    sb = m_asdu->groupdata[index].data[0] & 0x20;
    bl = m_asdu->groupdata[index].data[0] & 0x10;
    spi = m_asdu->groupdata[index].data[0] & 0x01;
    text.append(tmp + "\t" + dealSPI() + dealIV() + dealNT()+ dealSB()+ dealBL()+"\r\n");
    return text;
}

QString protocol101::protocol101asdu::dealASDU3Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-1)+"\r\n");

    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    iv = m_asdu->groupdata[index].data[0] & 0x80;
    nt = m_asdu->groupdata[index].data[0] & 0x40;
    sb = m_asdu->groupdata[index].data[0] & 0x20;
    bl = m_asdu->groupdata[index].data[0] & 0x10;
    dpi = m_asdu->groupdata[index].data[0] & 0x03;
    text.append(tmp +  "\t" + dealDPI() + dealIV() + dealNT()+ dealSB()+ dealBL()+"\r\n");
    return text;
}

QString protocol101::protocol101asdu::dealASDU9Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x4001)+"\r\n");

    tmp =   CharToHexStr(m_asdu->groupdata[index].data[0])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[1]);
    int data = charToint(m_asdu->groupdata[index].data,2);
    text.append(tmp + "\t规一化值:"+QString::number(data) + "\r\n");

    tmp = CharToHexStr(m_asdu->groupdata[index].data[2]);
    iv = m_asdu->groupdata[index].data[4] & 0x80;
    nt = m_asdu->groupdata[index].data[4] & 0x40;
    sb = m_asdu->groupdata[index].data[4] & 0x20;
    bl = m_asdu->groupdata[index].data[4] & 0x10;
    ov = m_asdu->groupdata[index].data[4] & 0x01;
    text.append(tmp + "\t品质位:" + dealIV() + dealNT()+ dealSB()+ dealBL()+dealOV() + "\r\n");

    return text;
}


QString protocol101::protocol101asdu::dealASDU13Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x4001)+"\r\n");

    tmp =   CharToHexStr(m_asdu->groupdata[index].data[0])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[1])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[2])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[3]);
    float data = charTofloat(m_asdu->groupdata[index].data);
    text.append(tmp + "\t浮点数:"+QString::number(data) + "\r\n");

    tmp = CharToHexStr(m_asdu->groupdata[index].data[4]);
    iv = m_asdu->groupdata[index].data[4] & 0x80;
    nt = m_asdu->groupdata[index].data[4] & 0x40;
    sb = m_asdu->groupdata[index].data[4] & 0x20;
    bl = m_asdu->groupdata[index].data[4] & 0x10;
    ov = m_asdu->groupdata[index].data[4] & 0x01;
    text.append(tmp + "\t品质位:" + dealIV() + dealNT()+ dealSB()+ dealBL()+dealOV() + "\r\n");

    return text;
}

QString protocol101::protocol101asdu::dealASDU15Data(int index)
{
    QString text;
    QString tmp;
    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x6401)+"\r\n");

    tmp =   CharToHexStr(m_asdu->groupdata[index].data[0])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[1])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[2])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[3]);

    int data = charToint(m_asdu->groupdata[index].data,4);
    text.append(tmp + "\t整数:"+QString::number(data) + "\r\n");

    tmp = CharToHexStr(m_asdu->groupdata[index].data[4]);
    iv = m_asdu->groupdata[index].data[4] & 0x80;
    ca = m_asdu->groupdata[index].data[4] & 0x40;
    cy = m_asdu->groupdata[index].data[4] & 0x20;
    sqindex = m_asdu->groupdata[index].data[4] & 0x1f;
    text.append(tmp + "\t顺序号SQ(bit1-5):"+QString::number(sqindex) + "\r\n");
    text.append("\t品质位:" + dealCY() + dealCA()+ dealIV() + "\r\n");
    return text;
}

QString protocol101::protocol101asdu::dealASDU21Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x4001)+"\r\n");

    tmp =   CharToHexStr(m_asdu->groupdata[index].data[0])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[1]);
    int data = charToint(m_asdu->groupdata[index].data,2);
    text.append(tmp + "\t规一化值:"+QString::number(data) + "\r\n");

    return text;
}

QString protocol101::protocol101asdu::dealASDU30Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-1)+"\r\n");

    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    iv = m_asdu->groupdata[index].data[0] & 0x80;
    nt = m_asdu->groupdata[index].data[0] & 0x40;
    sb = m_asdu->groupdata[index].data[0] & 0x20;
    bl = m_asdu->groupdata[index].data[0] & 0x10;
    spi = m_asdu->groupdata[index].data[0] & 0x01;
    text.append(tmp + "\t" + dealSPI() + dealIV() + dealNT()+ dealSB()+ dealBL()+"\r\n");

    text.append(dealDateTime(index));

    return text;
}

QString protocol101::protocol101asdu::dealASDU31Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-1)+"\r\n");

    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    iv = m_asdu->groupdata[index].data[0] & 0x80;
    nt = m_asdu->groupdata[index].data[0] & 0x40;
    sb = m_asdu->groupdata[index].data[0] & 0x20;
    bl = m_asdu->groupdata[index].data[0] & 0x10;
    dpi = m_asdu->groupdata[index].data[0] & 0x03;
    text.append(tmp +  "\t" + dealDPI() + dealIV() + dealNT()+ dealSB()+ dealBL()+"\r\n");

    text.append(dealDateTime(index));
    return text;
}

QString protocol101::protocol101asdu::dealASDU32Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x6601)+"\r\n");

    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    vti = m_asdu->groupdata[index].data[0];
    text.append(tmp + "\t" + dealVTI() );

    tmp =CharToHexStr(m_asdu->groupdata[index].data[1]);
    iv = m_asdu->groupdata[index].data[1] & 0x80;
    nt = m_asdu->groupdata[index].data[1] & 0x40;
    sb = m_asdu->groupdata[index].data[1] & 0x20;
    bl = m_asdu->groupdata[index].data[1] & 0x10;
    ov = m_asdu->groupdata[index].data[1] & 0x01;
    text.append(tmp + "\t品质位:" + dealIV() + dealNT()+ dealSB()+ dealBL()+dealOV() + "\r\n");

    text.append(dealDateTime(index));
    return text;
}

QString protocol101::protocol101asdu::dealASDU45Data(int index)
{
    QString text;
    QString tmp;
    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x6001)+"\r\n");

    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    scs = m_asdu->groupdata[index].data[0]&0x01;
    qu = (m_asdu->groupdata[index].data[0]>>2)&0x1f;
    se = m_asdu->groupdata[index].data[0]&0x80;

    text.append(tmp + "\t" + dealSCS()+dealSE()+dealQU() + "\r\n");

    return text;
}

QString protocol101::protocol101asdu::dealASDU46Data(int index)
{
    QString text;
    QString tmp;
    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x6001)+"\r\n");

    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    dcs = m_asdu->groupdata[index].data[0]&0x03;
    qu = (m_asdu->groupdata[index].data[0]>>2)&0x1f;
    se = m_asdu->groupdata[index].data[0]&0x80;

    text.append(tmp +  "\t" + dealDCS()+ dealQU()+ dealSE()+"\r\n" );

    return text;
}

QString protocol101::protocol101asdu::dealASDU50Data(int index)
{
    QString text;
    QString tmp;

    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x6201)+"\r\n");

    tmp =   CharToHexStr(m_asdu->groupdata[index].data[0])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[1])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[2])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[3]);
    float data = charTofloat(m_asdu->groupdata[index].data);
    text.append(tmp + "\t浮点数:"+QString::number(data) + "\r\n");

    return text;
}

QString protocol101::protocol101asdu::dealASDU70Data(int index)
{
    QString text;
    QString tmp;
    text.append("\r\n");
    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    coi = m_asdu->groupdata[index].data[0];
    text.append(tmp + "\t" +  dealCOI() );

    return text;
}


QString protocol101::protocol101asdu::dealASDU100Data(int index)
{
    QString text;
    QString tmp;
    text.append(" 固定为0\r\n");
    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);
    qoi = m_asdu->groupdata[index].data[0];
    text.append(tmp + "\t" + dealQOI());

    return text;
}

QString protocol101::protocol101asdu::dealASDU101Data(int index)
{
    QString text;
    QString tmp;
    text.append(" 固定为0\r\n");
    tmp =CharToHexStr(m_asdu->groupdata[index].data[0]);

    rqt = m_asdu->groupdata[index].data[0]&0x3f;
    frz = (m_asdu->groupdata[index].data[0]>>6)&0x03;

    text.append(tmp + "\t" + dealRQT() + dealFRZ() + "\r\n");

    return text;
}

QString protocol101::protocol101asdu::dealASDU103Data(int index)
{
    QString text;
    QString tmp;
    text.append(" 固定为0\r\n");
    text.append(dealDateTime(index));
    return text;
}

QString protocol101::protocol101asdu::dealASDU137Data(int index)
{
    QString text;
    QString tmp;
    uint dataaddr = charTouint(m_asdu->groupdata[index].addr,dataaddrlen);
    text.append("\t对应点号是:"+QString::number(dataaddr-0x6701)+"\r\n");

    tmp =   CharToHexStr(m_asdu->groupdata[index].data[0])+ " " +
            CharToHexStr(m_asdu->groupdata[index].data[1]);

    int data = charToint(m_asdu->groupdata[index].data,2);
    text.append(tmp + "\t规一化值:"+QString::number(data) + "\r\n");
	return text;
}

QString protocol101::protocol101asdu::dealASDU167()
{
	QString text;
	text.append("-----------------------------------------------------------------------------------------------\r\n");
	QString tmp;
	uint datauint = 0;
	int i = 0;
	tmp =CharToHexStr(m_asdu->data[i]);
	text.append(tmp + "\t保护信息传输控制字节:"+QString::number(m_asdu->data[i])+"\r\n");
	i++;
	tmp =CharToHexStr(m_asdu->data[i]) + " " + CharToHexStr(m_asdu->data[i+1]);
	datauint = m_asdu->data[i] + m_asdu->data[i+1]*256;
	text.append(tmp + "\t装置地址:"+QString::number(datauint)+"\r\n");
	i += 2;
	protocol103::protocol103asdu p103 ;
	p103.m_asdu = new protocol103::ASDU;
	p103.m_asdu->length = m_asdu->data[i];
	tmp =CharToHexStr(m_asdu->data[i]);
	text.append(tmp + "\t103数据包长度:"+QString::number(m_asdu->data[i])+"\r\n");
	i++;
	p103.m_asdu->type = m_asdu->data[i++];
	p103.m_asdu->vsq = m_asdu->data[i++];
	p103.m_asdu->cot = m_asdu->data[i++];
	p103.m_asdu->commonaddr = m_asdu->data[i++];

	for(int j = 0;j<p103.m_asdu->length-4;j++)
	{
		p103.m_asdu->data[j] = m_asdu->data[i++];
	}
	text.append(p103.dealASDU());
	if(p103.m_asdu)
	{
		delete p103.m_asdu;
		p103.m_asdu = NULL;
	}
	text.append("\r\n\t ASDU"+QString::number(m_asdu->type)+"解析结束\r\n");
	text.append("-----------------------------------------------------------------------------------------------\r\n");
	return text;

}

void protocol101::protocol101asdu::charToASDUDate()
{

    int index = 0;
    uint dataaddr = 0;

    for(int i = 0;i < datanum;i++)
    {
        if(sqflag==0||i==0)
        {
            if(dataaddrlen == 3)
            {
                m_asdu->groupdata[i].addr[0] = m_asdu->data[index++];
                m_asdu->groupdata[i].addr[1] = m_asdu->data[index++];
                m_asdu->groupdata[i].addr[2] = m_asdu->data[index++];
            }
            else if (dataaddrlen == 2)
            {
                m_asdu->groupdata[i].addr[0] = m_asdu->data[index++];
                m_asdu->groupdata[i].addr[1] = m_asdu->data[index++];
                m_asdu->groupdata[i].addr[2] = 0;
            }
            else if (dataaddrlen == 1)
            {
                m_asdu->groupdata[i].addr[0] = m_asdu->data[index++];
                m_asdu->groupdata[i].addr[1] = 0;
                m_asdu->groupdata[i].addr[2] = 0;
            }
            dataaddr = charTouint(m_asdu->groupdata[i].addr,dataaddrlen);
        }
        else
        {
            dataaddr++;
            m_asdu->groupdata[i].addr[0] = dataaddr&0xff;
            m_asdu->groupdata[i].addr[1] = (dataaddr>>8)&0xff;
            m_asdu->groupdata[i].addr[2] = (dataaddr>>16)&0xff;
        }
        for(int n = 0;n<datalen;n++)
        {
            m_asdu->groupdata[i].data[n] = m_asdu->data[index++];
        }
        for(int n = 0;n<timelen;n++)
        {
            m_asdu->groupdata[i].time[n] = m_asdu->data[index++];
        }
    }
    for(int n = 0;n < other;n++)
    {
        m_asdu->other[n] = m_asdu->data[index++];
    }
}

QString protocol101::protocol101asdu::dealOTHER()
{
    QString text;
    QString tmp;
    QDateTime datetime;
    uint datauint;
    uchar datauchar;
    switch (m_asdu->type)
    {
    case 50:
        tmp =CharToHexStr(m_asdu->other[0]);
        qos = m_asdu->other[0];
        text.append(tmp +  "\t"+ dealQOS()+"\r\n" );
        break;
    case 137:
        tmp =CharToHexStr(m_asdu->other[0]);
        qos = m_asdu->other[0];
        text.append(tmp +  "\t"+ dealQOS()+"\r\n" );

        datetime = charToDateTime(&m_asdu->other[1],7,BINARYTIME2A);
        tmp =CharToHexStr(m_asdu->other[1]) +" "+ CharToHexStr(m_asdu->other[2]);
        datauint = charTouint(&m_asdu->other[1],2);
        text.append(tmp + "\t" +QString::number(datauint) +"   秒:" + QString::number(datetime.time().second()) +"   毫秒:" + QString::number(datetime.time().msec()) + " \r\n");

        tmp =CharToHexStr(m_asdu->other[3]);
        iv = m_asdu->other[3]&0x80;
        text.append(tmp + "\t分(bit1-6):" + QString::number(datetime.time().minute()) + "   "+dealIV() +"\r\n");

        tmp =CharToHexStr(m_asdu->other[4]);
        su = m_asdu->other[4] & 0x80;
        text.append(tmp + "\t时(bit1-5):" + QString::number(datetime.time().hour()) + "   "+dealSU()+"\r\n");

        tmp =CharToHexStr(m_asdu->other[5]);
        datauchar = m_asdu->other[5]>>5;
        text.append(tmp + "\t日(bit1-5):" + QString::number(datetime.date().day()) +"   周(bit6-8):"+QString::number(datauchar)+ " (7表示星期天,0表示未用)\r\n");

        tmp =CharToHexStr(m_asdu->other[6]);
        text.append(tmp + "\t月(bit1-4):" + QString::number(datetime.date().month()) + "\r\n");

        tmp =CharToHexStr(m_asdu->other[7]);
        text.append(tmp + "\t年(bit1-7):" + QString::number(datetime.date().year()) + "\r\n");

        break;
    default:
        text.append("保留");
        break;
    }
    text.append("   ");
    return text;
}

QString protocol101::protocol101asdu::dealDateTime(int index)
{
    QString text;
    QString tmp;
    uchar datauchar;
    QDateTime datetime = charToDateTime(m_asdu->groupdata[index].time,timelen,BINARYTIME2A);

    tmp =CharToHexStr(m_asdu->groupdata[index].time[0]) +" "+ CharToHexStr(m_asdu->groupdata[index].time[1]);
    uint datauint = charTouint(m_asdu->groupdata[index].time,2);
    text.append(tmp + "\t" +QString::number(datauint) +"   秒:" + QString::number(datetime.time().second()) +"   毫秒:" + QString::number(datetime.time().msec()) + " \r\n");
    if(timelen ==2)
    {
        return text;
    }

    tmp =CharToHexStr(m_asdu->groupdata[index].time[2]);
    iv = m_asdu->groupdata[index].time[2]&0x80;
    text.append(tmp + "\t分(bit1-6):" + QString::number(datetime.time().minute()) + "   "+dealIV() +"\r\n");
    if(timelen ==3)
    {
        return text;
    }

    tmp =CharToHexStr(m_asdu->groupdata[index].time[3]);
    su = m_asdu->groupdata[index].time[3] & 0x80;
    text.append(tmp + "\t时(bit1-5):" + QString::number(datetime.time().hour()) + "   "+dealSU()+"\r\n");
    if(timelen ==4)
    {
        return text;
    }

    tmp =CharToHexStr(m_asdu->groupdata[index].time[4]);
    datauchar = m_asdu->groupdata[index].time[4]>>5;
    text.append(tmp + "\t日(bit1-5):" + QString::number(datetime.date().day()) +"   周(bit6-8):"+QString::number(datauchar)+ " (7表示星期天,0表示未用)\r\n");
//    text.append(tmp + "\t日(bit1-5):" + QString::number(datetime.date().day()) +"   周(bit6-8):"+QString::number(datetime.date().dayOfWeek())+ " (7表示星期天)\r\n");
    if(timelen ==5)
    {
        return text;
    }

    tmp =CharToHexStr(m_asdu->groupdata[index].time[5]);
    text.append(tmp + "\t月(bit1-4):" + QString::number(datetime.date().month()) + "\r\n");
    if(timelen ==6)
    {
        return text;
    }

    tmp =CharToHexStr(m_asdu->groupdata[index].time[6]);
    text.append(tmp + "\t年(bit1-7):" + QString::number(datetime.date().year()) + "\r\n");
    return text;
}
