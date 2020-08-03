#include "iec103netapciwiscom.h"

IEC103NetApciWiscom::IEC103NetApciWiscom()
{
	error = 0;
	masterState = STATE_INIT;
	len = 0;
	first = 0;
	length = 0;
	source_factory_addr = 0;
	memset(source_dev_addr,0,sizeof(source_dev_addr));
	destination_factory_addr = 0;
	memset(destination_dev_addr,0,sizeof (destination_dev_addr));
	memset(reserve,0,sizeof (reserve));
}

IEC103NetApciWiscom::~IEC103NetApciWiscom()
{

}

bool IEC103NetApciWiscom::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	len = 0;
	if(mRecvData.count() < 15)
	{
		error = 1;
		return false;
	}
	first = *buff.data();
	if(first != 0x68)
	{
		error = 2;
		mText.append(CharToHexStr(buff.data())+"\t启动字符不是0x68\r\n");
		return false;
	}
	mText.append(CharToHexStr(buff.data())+"\t启动字符:0x68\n");
	len++;

	length = charTouint(buff.data()+len,2);
	mText.append(CharToHexStr(buff.data()+len,2)+"\t长度域:"+QString::number(length) +"\r\n");
	len += 2;

	uchar tmp = *(buff.data()+len);
	if(tmp & 0x01)
	{
		if(tmp & 0x02)
		{
			control.type = UTYPE;
		}
		else
		{
			control.type = STYPE;
		}
	}
	else
	{
		control.type = ITYPE;

	}
	if(!control.init(mRecvData.mid(len,4)))
	{
		return false;
	}
	masterState = control.masterState;
	mText.append(control.showToText());
	len +=4;

	source_factory_addr = *(buff.data()+len);
	mText.append(CharToHexStr(buff.data()+len)+"\t源厂站地址:"+QString::number(source_factory_addr) +"\r\n");
	len++;

	memcpy(source_dev_addr,buff.data()+len,2);
	mText.append(CharToHexStr(buff.data()+len,2) + "\t源设备地址:"+QString::number(source_dev_addr[1]*0x100 + source_dev_addr[0])+"\r\n");
	len += 2;

	destination_factory_addr = *(buff.data()+len);
	mText.append(CharToHexStr(buff.data()+len) + "\t目的厂站地址:"+QString::number(destination_factory_addr)+"\r\n");
	len++;

	memcpy(destination_dev_addr,buff.data()+len,2);
	mText.append(CharToHexStr(buff.data()+len,2) + "\t目的设备地址:"+QString::number(destination_dev_addr[1]*0x100 + destination_dev_addr[0])+"\r\n");
	len += 2;

	reserve[0] = *(buff.data()+len);
	mText.append(CharToHexStr(buff.data()+len) + "\t备用\r\n");
	len++;

	reserve[1] = *(buff.data()+len);
	mText.append(CharToHexStr(buff.data()+len) + "\t备用\r\n");
	len++;

	return true;

}

QString IEC103NetApciWiscom::showToText()
{
	QString text;
	text.append(mText);

	return text;
}

bool IEC103NetApciWiscom::createData(IECDataConfig &config)
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
