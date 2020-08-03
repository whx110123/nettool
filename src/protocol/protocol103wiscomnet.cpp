#include "protocol103wiscomnet.h"

protocol103::protocol103wiscomnet::protocol103wiscomnet()
{
    m_apdu = new APDU103WISCOMNET;
    m_asdu = &m_apdu->asdu;
    //    m_asdu->groupdata = NULL;
}

protocol103::protocol103wiscomnet::~protocol103wiscomnet()
{
    if(m_apdu)
    {
        delete m_apdu;
        m_apdu = NULL;
    }
}

QString protocol103::protocol103wiscomnet::dealAPDU()
{
    QString text;
    text.append(dealAPCI());

	if(text.indexOf(QString("出错")) < 0 &&  m_asdu->length>0)
    {
        text.append(dealASDU());
    }
    text.append("\r\n\t 解析完成\r\n");
    text.append("****************************************************************************************************\r\n");
    return text;
}

int protocol103::protocol103wiscomnet::CharT0APDU(char *data, int len)
{
    if(len <15)
    {
        return 1;
    }
    int i= 0;

    m_apdu->apci.flag = data[i++];
    if(m_apdu->apci.flag != 0x68)
    {
        return 3;
    }
    m_apdu->apci.length[0] = data[i++];
    m_apdu->apci.length[1] = data[i++];
    m_apdu->length = m_apdu->apci.length[0] + m_apdu->apci.length[1]*0x100 + 3;
    if(m_apdu->length >len)
    {
        return 2;
    }
    m_apdu->apci.control[0] = data[i++];
    m_apdu->apci.control[1] = data[i++];
    m_apdu->apci.control[2] = data[i++];
    m_apdu->apci.control[3] = data[i++];
    m_apdu->apci.source_factory_addr = data[i++];
    m_apdu->apci.source_dev_addr[0] = data[i++];
    m_apdu->apci.source_dev_addr[1] = data[i++];
    m_apdu->apci.destination_factory_addr = data[i++];
    m_apdu->apci.destination_dev_addr[0] = data[i++];
    m_apdu->apci.destination_dev_addr[1] = data[i++];
    m_apdu->apci.reserve[0] = data[i++];
    m_apdu->apci.reserve[1] = data[i++];
    if(len ==15)
    {
        memset(&m_apdu->asdu,0,sizeof(m_apdu->asdu));
        return 0;
    }
    m_apdu->asdu.type = data[i++];
    m_apdu->asdu.vsq = data[i++];
    m_apdu->asdu.cot = data[i++];
    m_apdu->asdu.commonaddr = data[i++];

    int k = i;
    for(int j = 0;j <m_apdu->length-k ;j++)
    {
        m_apdu->asdu.data[j] =  data[i++];
    }
    m_apdu->asdu.length = m_apdu->length -15;
    return 0;
}

QString protocol103::protocol103wiscomnet::dealERR(int err)
{
    QString text;
    switch (err)
    {
    case 1:
        text.append("出错！报文总长不满15个字节，条件不满足，因此报文有问题\r\n");
        break;
    case 2:
        text.append("出错！根据长度域计算出的长度比实际报文长度要长，因此报文有问题\r\n");
        break;
    case 3:
        text.append("出错！金智网络103报文必须是0x68开头，条件不满足，因此报文有问题\r\n");
        break;
    }
    return text;
}

QString protocol103::protocol103wiscomnet::dealAPCI()
{
    QString text;
    QString tmp = CharToHexStr(m_apdu->apci.flag);
    text.append("****************************************************************************************************\r\n");
    text.append(tmp + "\t报文头，固定为0x68\r\n");
    tmp = CharToHexStr(m_apdu->apci.length[0]) + " " +CharToHexStr(m_apdu->apci.length[1]);
    text.append(tmp + "\t报文长度:"+QString::number(m_apdu->length-3)+" 控制域加数据区域\r\n");
//	text.append("-----------------------------------------------------------------------------------------------\r\n");
    if(m_apdu->apci.control[0]&0x01)
    {
        if(m_apdu->apci.control[0]&0x02)
        {
//            APCIType = UTYPE;
            text.append(dealUControl());
        }
        else
        {
//            APCIType = STYPE;
            text.append(dealSControl());
        }
    }
    else
    {
//        APCIType = ITYPE;
        text.append(dealIControl());
    }
	if(text.contains(QString("出错")))
    {
        return text;
    }
    tmp = CharToHexStr(m_apdu->apci.source_factory_addr);
	text.append(tmp + "\t源厂站地址:"+QString::number(m_apdu->apci.source_factory_addr)+"\r\n");
    tmp = CharToHexStr(m_apdu->apci.source_dev_addr[0]);
	text.append(tmp + "\t源设备地址低位:"+QString::number(m_apdu->apci.source_dev_addr[0])+"\r\n");
    tmp = CharToHexStr(m_apdu->apci.source_dev_addr[1]);
	text.append(tmp + "\t源设备地址高位:"+QString::number(m_apdu->apci.source_dev_addr[1])+"\r\n");
    tmp = CharToHexStr(m_apdu->apci.destination_factory_addr);
	text.append(tmp + "\t目的厂站地址:"+QString::number(m_apdu->apci.destination_factory_addr)+"\r\n");
    tmp = CharToHexStr(m_apdu->apci.destination_dev_addr[0]);
	text.append(tmp + "\t目的设备地址低位:"+QString::number(m_apdu->apci.destination_dev_addr[0])+"\r\n");
    tmp = CharToHexStr(m_apdu->apci.destination_dev_addr[1]);
	text.append(tmp + "\t目的设备地址高位:"+QString::number(m_apdu->apci.destination_dev_addr[1])+"\r\n");
    tmp = CharToHexStr(m_apdu->apci.reserve[0]);
    text.append(tmp + "\t备用\r\n");
    tmp = CharToHexStr(m_apdu->apci.reserve[1]);
    text.append(tmp + "\t备用\r\n");
    text.append("\r\n\t APCI解析结束\r\n");
    text.append("****************************************************************************************************\r\n");
    return text;
}

QString protocol103::protocol103wiscomnet::dealUControl()
{
    QString text;
    QString tmp;
    tmp = CharToHexStr(m_apdu->apci.control[0]);
	text.append(tmp + "\tU帧报文(bit1与bit2都为1) 无编号，起控制链路等功能\r\n\t");
    int sum = 0;
    if(m_apdu->apci.control[0] & 0x80)
    {
        text.append("(bit8):1 子站确认TESTFR，子站响应启用测试\r\n");
        sum++;
    }
    if(m_apdu->apci.control[0] & 0x40)
    {
        text.append("(bit7):1 主站激活TESTFR，主站启用测试\r\n");
        sum++;
    }
    if(m_apdu->apci.control[0] & 0x20)
    {
        text.append("(bit6):1 子站确认STOPDT，子站响应停止链路\r\n");
        sum++;
    }
    if(m_apdu->apci.control[0] & 0x10)
    {
        text.append("(bit5):1 主站激活STOPDT，主站停止链路\r\n");
        sum++;
    }
    if(m_apdu->apci.control[0] & 0x08)
    {
        text.append("(bit4):1 子站确认STARTDT，子站响应激活链路\r\n");
        sum++;
    }
    if(m_apdu->apci.control[0] & 0x04)
    {
		text.append("(bit3):1 主站激活STARTDT，主站激活链路\r\n");
        sum++;
    }

    if(sum==0)
    {
        text.append("\t出错！此U帧报文未包含任何控制功能\r\n");
        return text;
    }
    else if(sum>1)
    {
        text.append("\t出错！此U帧报文包含2种或2种以上控制功能\r\n");
        return text;
    }
    if(m_apdu->length != 15)
    {
        text.append("\t出错！U帧长度只能为15，条件不满足，因此报文有问题\r\n");
        return text;
    }

    tmp = CharToHexStr(m_apdu->apci.control[1]);//QString("%1").arg(QString::number(m_apdu->apci.control2,16),2,QLatin1Char('0'));
    if(m_apdu->apci.control[1] == 0x00)
    {
        text.append(tmp + "\t固定为0x00\r\n");
    }
    else
    {
        text.append(tmp + "\t出错！已确定此帧报文是U帧，但U帧这个位置固定为0，条件不满足，因此报文有问题\r\n");
        return text;
    }
    tmp = CharToHexStr(m_apdu->apci.control[2]);//QString("%1").arg(QString::number(m_apdu->apci.control3,16),2,QLatin1Char('0'));
    if(m_apdu->apci.control[2] == 0x00)
    {
        text.append(tmp + "\t固定为0x00\r\n");
    }
    else
    {
        text.append(tmp + "\t出错！已确定此帧报文是U帧，但U帧这个位置固定为0，条件不满足，因此报文有问题\r\n");
        return text;
    }
    tmp = CharToHexStr(m_apdu->apci.control[3]);//QString("%1").arg(QString::number(m_apdu->apci.control4,16),2,QLatin1Char('0'));
    if(m_apdu->apci.control[3] == 0x00)
    {
        text.append(tmp + "\t固定为0x00\r\n");
    }
    else
    {
        text.append(tmp + "\t出错！已确定此帧报文是U帧，但U帧这个位置固定为0，条件不满足，因此报文有问题\r\n");
        return text;
    }

    return text;
}

QString protocol103::protocol103wiscomnet::dealSControl()
{
    QString text;
    QString tmp;
//	text.append("\tS帧报文(bit1为1，bit2为0) 带编号，用于监视报文序号\r\n");
    tmp = CharToHexStr(m_apdu->apci.control[0]);//QString("%1").arg(QString::number(m_apdu->apci.control1,16),2,QLatin1Char('0'));
    if(m_apdu->apci.control[0] == 0x01)
    {
		text.append(tmp + "\tS帧报文(bit1为1，bit2为0) 带编号，用于监视报文序号\r\n");
    }
    else
    {
        text.append(tmp + "\t出错！当此字节后2位bit是0和1，可以确定是S帧，但S帧其他bit必须为0，条件不满足，因此报文有问题\r\n");
        return text;
    }

    tmp = CharToHexStr(m_apdu->apci.control[1]);//QString("%1").arg(QString::number(m_apdu->apci.control2,16),2,QLatin1Char('0'));
    if(m_apdu->apci.control[1] == 0x00)
    {
        text.append(tmp + "\t固定为0x00\r\n");
    }
    else
    {
        text.append(tmp + "\t出错！已确定此帧报文是S帧，但S帧这个位置固定为0，条件不满足，因此报文有问题\r\n");
        return text;
    }
	tmp = CharToHexStr(m_apdu->apci.control[2])+ " " + CharToHexStr(m_apdu->apci.control[3]);//QString("%1").arg(QString::number(m_apdu->apci.control3,16),2,QLatin1Char('0'));

	if(m_apdu->apci.control[2] %2 == 1)
    {
		text.append(tmp + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题\r\n");
        return text;
    }
//    tmp = CharToHexStr(m_apdu->apci.control[3]);//QString("%1").arg(QString::number(m_apdu->apci.control4,16),2,QLatin1Char('0'));
	text.append(tmp + "\t接受序号: " + QString::number((m_apdu->apci.control[3]*256+m_apdu->apci.control[2])/2) + "\r\n");
	if(m_apdu->length != 15)
	{
		text.append("\t出错！S帧长度只能为15，条件不满足，因此报文有问题\r\n");
	}
    return text;
}

QString protocol103::protocol103wiscomnet::dealIControl()
{
    QString text;
    QString tmp;
//	text.append("\tI帧报文(bit1为0) 带编号，用于信号传输\r\n");
	tmp = CharToHexStr(m_apdu->apci.control[0]) + " " + CharToHexStr(m_apdu->apci.control[1]);//QString("%1").arg(QString::number(m_apdu->apci.control1,16),2,QLatin1Char('0'));

//	text.append(tmp + "\t发送序列号低字节(bit2-8)\r\n");

//    tmp = CharToHexStr(m_apdu->apci.control[1]);//QString("%1").arg(QString::number(m_apdu->apci.control2,16),2,QLatin1Char('0'));
	text.append(tmp + "\t发送序号: " +QString::number((m_apdu->apci.control[1]*256+m_apdu->apci.control[0])/2)  + "   I帧报文(bit1为0) 带编号，用于信号传输\r\n");

	tmp = CharToHexStr(m_apdu->apci.control[2])+ " " + CharToHexStr(m_apdu->apci.control[3]);//QString("%1").arg(QString::number(m_apdu->apci.control3,16),2,QLatin1Char('0'));

	if(m_apdu->apci.control[2] %2 == 1)
    {
        text.append(tmp + "\t出错！接受序列号低字节，最后一个bit位必须为0，所以此数字必须为偶数，条件不满足，因此报文有问题\r\n");
        return text;
    }
//    tmp = CharToHexStr(m_apdu->apci.control[3]);//QString("%1").arg(QString::number(m_apdu->apci.control4,16),2,QLatin1Char('0'));
	text.append(tmp + "\t接受序号: " + QString::number((m_apdu->apci.control[3]*256+m_apdu->apci.control[2])/2)  + "\r\n");
	if(m_apdu->length <= 15)
	{
		text.append("\t出错！I帧报文总长度必须大于15，条件不满足，因此报文有问题\r\n");
	}
    return text;
}
