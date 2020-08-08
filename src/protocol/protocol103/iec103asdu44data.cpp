#include "iec103asdu44data.h"
#include "functotext.h"

IEC103Asdu44Data::IEC103Asdu44Data()
{

}

IEC103Asdu44Data::~IEC103Asdu44Data()
{

}

bool IEC103Asdu44Data::init(const QByteArray &buff)
{
	setDefault(buff);

	inf = *(buff.data() + len);

	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;

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

bool IEC103Asdu44Data::init(const QByteArray &buff, uint addr)
{
	setDefault(buff);

	inf = addr & 0xff;

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
