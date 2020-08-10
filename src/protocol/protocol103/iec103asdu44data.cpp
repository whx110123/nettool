#include "iec103asdu44data.h"
#include "functotext.h"

IEC103Asdu44Data::IEC103Asdu44Data()
{
	yx16 = 0;
	yx16flag = 0;
	qds = 0;
}

IEC103Asdu44Data::~IEC103Asdu44Data()
{

}

bool IEC103Asdu44Data::handle(const QByteArray &buff)
{
	yx16 = charTouint(buff.data() + len,2);
	mText.append(CharToHexStr(buff.data() + len,2) + "\t" + yxToText() + "\r\n");
	len += 2;

	yx16flag = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len,2) + "\t" + yxFlagToText() + "\r\n");
	len += 2;

	qds = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data()+len) + "\t品质位:" + ivToText(qds) +"   "+ ntToText(qds)+"   "+ sbToText(qds)+"   "+ blToText(qds)+"   "+ ovToText(qds)+"\r\n");
	len++;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	return true;
}

bool IEC103Asdu44Data::createData(IECDataConfig &config)
{
	error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！生成报文失败");
	return false;
}

QString IEC103Asdu44Data::yxToText()
{
	QString text = "16个遥信状态";
	for(int i = 0;i<16;i++)
	{
		text.append("\r\n\t");
		text.append((yx16>>i)&0x01 ? "1 合位":"0 分位");
		text.append(" 对应INF:"+QString::number(inf+i));
	}
	return text;
}

QString IEC103Asdu44Data::yxFlagToText()
{
	QString text = "16个遥信与上次查询的变化状态";
	for(int i = 0;i<16;i++)
	{
		text.append("\r\n\t");
		text.append((yx16flag>>i)&0x01 ? "1  有改变":"0  无改变");
		text.append(" 对应INF:"+QString::number(inf+i));
	}
	return text;
}
