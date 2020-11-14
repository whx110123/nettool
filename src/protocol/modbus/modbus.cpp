#include "modbus.h"

Modbus::Modbus()
{
	isMaster = false;
}

Modbus::~Modbus()
{
	qDeleteAll(datalist);
	datalist.clear();

	qDeleteAll(groups);
	groups.clear();
}

bool Modbus::init(const QByteArray& buff)
{
	setDefault(buff);

	qDeleteAll(datalist);
	datalist.clear();

	if(buff.count() < 3)
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！长度不足");
		return false;
	}

	addr = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t装置地址: " + QString::number(addr) + "\r\n");
	len++;

	code = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t功能码: " + QString::number(code) + "\r\n");
	len++;

	if(isMaster == true)
	{
		startAddr = charTouint(buff.data() + len, 2, 1);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\t起始地址: " + QString::number(startAddr) + "\r\n");
		len += 2;

		num = charTouint(buff.data() + len, 2, 1);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\t数量: " + QString::number(num) + "    一般功能码1、2表示bit位数量，功能码3、4表示寄存器数量\r\n");
		len += 2;
	}
	else if(isMaster == false)
	{
		mgroup.dataLen = *(buff.data() + len);
		mgroup.type.clear();
		mgroup.analysis.clear();
		mText.append(CharToHexStr(buff.data() + len) + "\t长度: " + QString::number(mgroup.dataLen) + "\r\n");
		len++;

		for(ModbusDataGroup *g : groups)
		{
			if(g->dataLen == mgroup.dataLen)
			{
				mgroup.type = g->type;
				mgroup.analysis = g->analysis;
				break;
			}
		}
		if(mgroup.analysis.isEmpty())
		{
			mText.append(CharToHexStr(buff.data() + len, mgroup.dataLen) + "\t数据，未解析\r\n");
			len += mgroup.dataLen;
		}
		else
		{
			int index = 0;
			while(len < mgroup.dataLen + 3)
			{
				ModbusData *mdata = new ModbusData;
				QChar qch;
				if(index <  mgroup.analysis.length())
				{
					qch = mgroup.analysis.at(index);
				}
				else
				{
					qch = mgroup.analysis.back();
				}
				if(!mdata->initData(buff.mid(len), mgroup.type, qch))
				{
					return false;
				}
				mdata->index = index;
				datalist.append(mdata);
				len += mdata->len;
				index++;
			}
		}


	}
	else
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg("出错！无法确定此报文为召唤或应答报文");
		return false;
	}



	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}
