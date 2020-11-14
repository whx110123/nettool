#include "modbusdata.h"

ModbusData::ModbusData()
{

}

ModbusData::~ModbusData()
{

}

bool ModbusData::initData(const QByteArray& buff, QString type, QChar analysisCode)
{
	setDefault(buff);
	mtype = type;
	mcode = analysisCode;

	if(type == YC)
	{
		switch(mcode.unicode())
		{
		case '0':
			break;
		case '1':
			break;
		default:
			break;
		}
	}
	else if(type == YX)
	{

	}
	else if(type == YM)
	{

	}

	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	if(len > buff.length())
	{
		error = QString("\"%1\" %2 [%3行]\r\n%4\r\n").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__).arg(QString("出错！解析所需报文长度(%1)比实际报文长度(%2)长").arg(len).arg(buff.length()));
		return false;
	}
	return true;
}

