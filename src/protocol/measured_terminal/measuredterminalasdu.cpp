#include "measuredterminalasdu.h"



MeasuredTerminalAsduData::MeasuredTerminalAsduData()
{

}

MeasuredTerminalAsduData::~MeasuredTerminalAsduData()
{

}

bool MeasuredTerminalAsduData::init(const QByteArray& buff)
{
	setDefault(buff);

	memcpy(DA, buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t" + DAToText());
	len += 2;

	memcpy(DI, buff.data() + len, 4);
	mText.append(CharToHexStr(buff.data() + len, 4) + "\t" + DIToText());
	len += 4;

	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	if(!handle(buff))
	{
		return false;
	}
	return true;
}

bool MeasuredTerminalAsduData::handle(const QByteArray& buff)
{
	return false;
}

QString MeasuredTerminalAsduData::DAToText()
{
	QString text = "信息点标识DA:";
	if(DA[0] == 0 && DA[1] == 0)
	{
		text.append("终端测量点P0");
	}
	else if(DA[0] && DA[1])
	{
		QString tmp = "对应测量点";
		int sum = 0;
		for(int i = 0; i < 8; i++)
		{
			if((DA[0] >> i) & 0x01)
			{
				tmp.append("p" + QString::number((DA[1] - 1) * 8 + i + 1) + " ");
				sum++;
			}
		}
		text.append(QString("共%1个点").arg(sum));
	}
	else
	{
		text = "错误的信息点标识";
	}

	return text;
}

QString MeasuredTerminalAsduData::DIToText()
{
	QString text = "数据标识编码DI";
	uint tmp = charTouint(DI, 4);
	switch(tmp)
	{
	case 0x00010000:
		break;
	default:
		break;
	}
	return text;
}


MeasuredTerminalAsdu::MeasuredTerminalAsdu()
{

}

MeasuredTerminalAsdu::~MeasuredTerminalAsdu()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool MeasuredTerminalAsdu::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(datalist);
	datalist.clear();

	if(buff.count() < 8)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度错误");
		return false;
	}

	afn = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + afnToText() + "\r\n");
	len++;

	seq = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + seqToText() + "\r\n");
	len++;

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	uchar pwFlag = (flag & 0x01) ? 1 : 0;
	uchar tpFlag = (flag & 0x02) ? 1 : 0;
	int index = 0;
	while(len < buff.length() - pwFlag * 16 - tpFlag * 5)
	{
		MeasuredTerminalAsduData *mdata = CreateAsduData(afn);
		if(!mdata)
		{
			error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！未识别的afn类型");
			return false;
		}
		mdata->index = index;
		if(!mdata->init(buff.mid(len)))
		{
			mText.append(mdata->showToText());
			delete mdata;
			mdata = NULL;
			return false;
		}
		datalist.append(mdata);
		mText.append(mdata->showToText());
		len += mdata->len;
		index++;
	}
	if(len != buff.length() - pwFlag * 16 - tpFlag * 5)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！用户数据报文长度错误");
		return false;
	}

	if(pwFlag)
	{
		memcpy(pw, buff.data() + len, 16);
	}
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

QString MeasuredTerminalAsdu::showToText()
{
	QString text = mText;
	return text;
}

bool MeasuredTerminalAsdu::createData(IECDataConfig& config)
{

}

QString MeasuredTerminalAsdu::afnToText()
{
	QString text = "应用层功能码AFN" + QString::number(afn) + "   ";
	switch(afn)
	{
	case 0:
		text.append("确认∕否定");
		break;
	case 2:
		text.append("链路接口检测");
		break;
	case 4:
		text.append("写参数");
		break;
	case 6:
		text.append("身份认证及密钥协商");
		break;
	case 10:
		text.append("读参数");
		break;
	case 12:
		text.append("读当前数据");
		break;
	case 13:
		text.append("读历史数据");
		break;
	case 14:
		text.append("读事件记录");
		break;
	case 15:
		text.append("文件传输");
		break;
	case 16:
		text.append("中继转发");
		break;
	case 18:
		text.append("读任务数据");
		break;
	case 19:
		text.append("读告警数据");
		break;
	case 20:
		text.append("级联命令");
		break;
	case 21:
		text.append("用户自定义数据");
		break;
	default:
		text.append("未知AFN类型");
		break;
	}
	return text;
}

QString MeasuredTerminalAsdu::seqToText()
{
	QString text = "帧序列域SEQ:";

	text.append("\r\n\t帧时间标签有效位TpV(bit8):");
	if(seq & 0x80)
	{
		text.append("80   表示带有时间标签Tp");
	}
	else
	{
		text.append("0   表示无时间标签Tp");
	}

	text.append("\r\n\t首帧标志FIR(bit7):");
	if(seq & 0x40)
	{
		text.append("40   为报文的第一帧");
	}
	else
	{
		text.append("0   非报文的第一帧");
	}

	text.append("\r\n\t末帧标志FIN(bit6):");
	if(seq & 0x20)
	{
		text.append("20   为报文的最后一帧");
	}
	else
	{
		text.append("0   非报文的最后一帧");
	}

	text.append("\r\n\t请求确认标志位CON(bit5):");
	if(seq & 0x10)
	{
		text.append("10   需要对该帧报文进行确认");
	}
	else
	{
		text.append("0   不需要对该帧报文进行确认");
	}
	text.append("\r\n\t启动帧序号PSEQ/响应帧序号RSEQ(bit1-4)" + QString::number(seq & 0x0f));


	return text;
}

MeasuredTerminalAsduData *MeasuredTerminalAsdu::CreateAsduData(uchar type)
{
	MeasuredTerminalAsduData *asdudata = NULL;
	masterState = STATE_NORMAL;
	slaveState = STATE_NORMAL;
	switch(type)
	{
	case 0:
		break;
	default:
		break;
	}
	return asdudata;
}
