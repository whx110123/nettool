#include "iec103netapcibaoxin.h"

IEC103NetApciBaoXin::IEC103NetApciBaoXin()
{
	first = 0;
	length = 0;
}

IEC103NetApciBaoXin::~IEC103NetApciBaoXin()
{

}

bool IEC103NetApciBaoXin::init(const QByteArray& buff)
{
	setDefault(buff);

	if(buff.length() < 6)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！报文长度不满6个字节，条件不满足，因此报文有问题");
		return false;
	}
	first = *(buff.data() + len);
	if(first != 0x68)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(CharToHexStr(buff.data() + len) + "\t启动字符不是0x68");
		return false;
	}

	mText.append(CharToHexStr(buff.data() + len) + "\t启动字符:0x68\r\n");
	len++;

	length = charTouint(buff.data() + len, 2);
	mText.append(CharToHexStr(buff.data() + len, 2) + "\t长度域:" + QString::number(length) + "\r\n");
	len += 2;

	if(!control.init(buff.mid(len, 4)))
	{
		return false;
	}
	len += 4;
	masterState = control.masterState;
	slaveState = control.slaveState;
	return true;
}

QString IEC103NetApciBaoXin::showToText()
{
	QString text(mText);
	text.append(control.showToText());
	return text;
}

bool IEC103NetApciBaoXin::createData(IECDataConfig& config)
{
	config.data += 0x68;
	config.data += '\0';
	config.data += '\0';
	if(!control.createData(config))
	{
		return false;
	}
	return true;
}
