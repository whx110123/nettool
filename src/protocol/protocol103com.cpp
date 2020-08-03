#include "protocol103com.h"

protocol103::protocol103com::protocol103com()
{
    m_apdu = new APDU103COM;
    m_asdu = &m_apdu->asdu;
}

protocol103::protocol103com::~protocol103com()
{
    if(m_apdu)
    {
        delete m_apdu;
        m_apdu = NULL;
    }
}

QString protocol103::protocol103com::dealAPDU()
{
    QString text;
    QString tmp;
    text.append(dealAPCI());
    if(m_apdu->apci.flag1 == 0x68)
    {
        text.append(dealASDU());
        text.append("\r\n\t ASDU"+QString::number(m_asdu->type)+"解析结束\r\n");
        text.append("-----------------------------------------------------------------------------------------------\r\n");
    } 
    tmp = CharToHexStr(m_apdu->crc);
    text.append(tmp + "\t" + dealCRC());
    tmp = CharToHexStr(m_apdu->last);
    text.append(tmp + "\t结束字符0x16\r\n");

    text.append("\r\n\t 解析完成\r\n");
    text.append("****************************************************************************************************\r\n");
    return text;
}

int protocol103::protocol103com::CharT0APDU(char *data, int len)
{
    if(len < 5)
    {
        return 1;
    }
    int i= 0;
    m_apdu->apci.flag1 = data[i++];

    if(m_apdu->apci.flag1 == 0x10)
    {
        m_apdu->apci.len1 = 3;
        m_apdu->apci.len2 = m_apdu->apci.len1;
        m_apdu->apci.flag2 = m_apdu->apci.flag1;
        m_apdu->apci.ctrl = data[i++];
        m_apdu->apci.addr = data[i++];
        m_apdu->crc = data[i++];
        m_apdu->last = data[i++];
        m_apdu->length =5;
        memset(&m_apdu->asdu,0,sizeof(m_apdu->asdu));
        return 0;
    }
    else if(m_apdu->apci.flag1 == 0x68)
    {

        m_apdu->apci.len1 = data[i++];
        m_apdu->length = m_apdu->apci.len1+6;
        if(m_apdu->length >len)
        {
            return 2;
        }
        m_apdu->apci.len2 =data[i++];
        m_apdu->apci.flag2 = data[i++];
        m_apdu->apci.ctrl = data[i++];
        m_apdu->apci.addr = data[i++];

        m_apdu->asdu.type = data[i++];
        m_apdu->asdu.vsq = data[i++];
        m_apdu->asdu.cot = data[i++];
        m_apdu->asdu.commonaddr = data[i++];


        int k = i;
        for(int j = 0;j <m_apdu->length-2-k ;j++)
        {
            m_apdu->asdu.data[j] =  data[i++];
        }
        m_apdu->crc = data[i++];
        m_apdu->last = data[i++];
        m_apdu->asdu.length = m_apdu->length-8;
        return 0;

    }
    return 3;
}

QString protocol103::protocol103com::dealERR(int err)
{
    QString text;
    switch (err)
    {
    case 1:
        text.append("出错！报文总长不满5个字节，条件不满足，因此报文有问题\r\n");
        break;
    case 2:
        text.append("出错！根据长度域计算出的长度比实际报文长度要长，因此报文有问题\r\n");
        break;
    case 3:
        text.append("出错！串口103报文必须是0x68或0x10开头，条件不满足，因此报文有问题\r\n");
        break;
    }
    return text;
}

QString protocol103::protocol103com::dealAPCI()
{
    QString text;
    QString tmp = CharToHexStr(m_apdu->apci.flag1);
    if(m_apdu->apci.flag1 == 0x68)
    {
        text.append("****************************************************************************************************\r\n");
        text.append(tmp + "\t报文头0x68，可变帧长报文\r\n");
        tmp = CharToHexStr(m_apdu->apci.len1);
        text.append(tmp + "\t报文长度:"+QString::number(m_apdu->apci.len1)+" 控制域、地址域、用户数据的总长度\r\n");
        tmp = CharToHexStr(m_apdu->apci.len2);
        text.append(tmp + "\t同报文长度\r\n");
        tmp = CharToHexStr(m_apdu->apci.flag2);
        text.append(tmp + "\t同报文头0x68\r\n");
    }
    else if(m_apdu->apci.flag1 == 0x10)
    {
        text.append("****************************************************************************************************\r\n");
        text.append(tmp + "\t报文头0x10，固定帧长报文\r\n");
    }

    tmp = CharToHexStr(m_apdu->apci.ctrl);
    text.append(tmp + "\t");
    text.append(dealCTRL());

    tmp = CharToHexStr(m_apdu->apci.addr);
    text.append(tmp + "\t地址域:" + QString::number(m_apdu->apci.addr) + "\r\n");

    return text;
}

QString protocol103::protocol103com::dealCTRL()
{
    QString text = "控制域:";
    prm = m_apdu->apci.ctrl & 0x40;
    text.append(dealPRM() +"\r\n\t");
    if(prm)
    {
        fcb = m_apdu->apci.ctrl & 0x20;
        fcv = m_apdu->apci.ctrl & 0x10;
        cw1 = m_apdu->apci.ctrl & 0x0f;
        text.append(dealFCB()+"\r\n\t"+ dealFCV() +"\r\n\t"+ dealCW1()+"\r\n");
    }
    else
    {
        acd = m_apdu->apci.ctrl & 0x20;
        dfc = m_apdu->apci.ctrl & 0x10;
        cw2 = m_apdu->apci.ctrl & 0x0f;
        text.append(dealACD()+"\r\n\t" + dealDFC()+"\r\n\t" + dealCW2()+"\r\n");
    }

    return text;

}

QString protocol103::protocol103com::dealPRM()
{
    QString text = "PRM(bit7):" ;
    if(prm)
    {
        text.append("1 启动站向从动站传输的报文");
    }
    else
    {
        text.append("0 从动(响应)站向启动站传输的报文");
    }
    text.append("   ");
    return text;
}

QString protocol103::protocol103com::dealFCB()
{
    QString text = "FCB(bit6):" ;
    if(fcb)
    {
        text.append("1 帧计数位");
    }
    else
    {
        text.append("0 帧计数位");
    }
    text.append("   ");
    return text;
}

QString protocol103::protocol103com::dealFCV()
{
    QString text = "FCV(bit5):" ;
    if(fcv)
    {
        text.append("1 表示帧计数位FCB的变化有效");
    }
    else
    {
        text.append("0 表示帧计数位FCB的变化无效");
    }
    text.append("   ");
    return text;
}

QString protocol103::protocol103com::dealACD()
{
    QString text = "ACD(bit6):" ;
    if(acd)
    {
        text.append("1 从动站有1级用户数据要求访问");
    }
    else
    {
        text.append("0 从动站无1级用户数据要求访问");
    }
    text.append("   ");
    return text;
}

QString protocol103::protocol103com::dealDFC()
{
    QString text = "DFC(bit5):" ;
    if(dfc)
    {
        text.append("1 表示从动站接收后续报文将引起数据溢出");
    }
    else
    {
        text.append("0 表示从动站可以接收后续报文");
    }
    text.append("   ");
    return text;
}

QString protocol103::protocol103com::dealCW1()
{
    QString text = "功能码(bit1-4):" + QString::number(cw1) + " ";
    switch (cw1)
    {
    case 0:
        text.append("帧类型:发送/确认帧  功能描述:复位通信单元  帧计数有效位FCV:0");
        break;
    case 1:
        text.append("帧类型:发送/确认帧  功能描述:用户进程复位  帧计数有效位FCV:0");
        break;
    case 2:
        text.append("保留");
        break;
    case 3:
        text.append("帧类型:发送/确认帧  功能描述:传送数据  帧计数有效位FCV:1");
        break;
    case 4:
        text.append("帧类型:发送/无回答帧  功能描述:传送数据  帧计数有效位FCV:0");
        break;
    case 5:
        text.append("保留");
        break;
    case 6:
        text.append("保留");
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
    text.append("   ");
    return text;
}

QString protocol103::protocol103com::dealCW2()
{
    QString text = "功能码(bit1-4):" + QString::number(cw2) + " ";
    switch (cw2)
    {
    case 0:
        text.append("帧类型:确认帧  功能描述:认可，肯定认可");
        break;
    case 1:
        text.append("帧类型:确认帧  功能描述:否定认可，未收到报文，链路忙");
        break;
    case 2:
        text.append("保留");
        break;
    case 3:
        text.append("保留");
        break;
    case 4:
        text.append("保留");
        break;
    case 5:
        text.append("保留");
        break;
    case 6:
        text.append("保留");
        break;
    case 7:
        text.append("保留");
        break;
    case 8:
        text.append("帧类型:响应帧  功能描述:以数据包响应请求帧");
        break;
    case 9:
        text.append("帧类型:响应帧  功能描述:从站没有所召唤的数据");
        break;
    case 10:
        text.append("保留");
        break;
    case 11:
        text.append("帧类型:响应帧  功能描述:响应链路状态或要求访问");
        break;
    default:
        text.append("保留");
        break;
    }
    text.append("   ");
    return text;
}

QString protocol103::protocol103com::dealCRC()
{
    QString text = "校验CRC:" ;
    uchar tmp = m_apdu->apci.ctrl +m_apdu->apci.addr + m_asdu->type + m_asdu->vsq ;

        tmp += m_asdu->cot + m_asdu->commonaddr;


    for(int i=0;i<m_asdu->length-4;i++)
    {
        tmp += m_asdu->data[i];
    }
    if(m_apdu->crc == tmp)
    {
        text.append("正确，与计算出来的CRC一致");
    }
    else
    {
        text.append("出错！与计算出来的CRC不一致");
    }
    text.append("\r\n");
    return text;
}
