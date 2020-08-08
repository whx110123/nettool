#include "globaldefine.h"


QString CharToHexStr(uchar data)
{
    return QString("%1").arg(QString::number(data,16).toUpper(),2,QLatin1Char('0'));
}
QString CharToHexStr(const char *data, int len)
{
	uchar *mdata = (uchar *)data;
	return CharToHexStr(mdata, len);
}

QString CharToHexStr(uchar *data, int len)
{
	QString str;
	for (int i = 0; i < len; i++)
	{
		str.append(QString("%1").arg(QString::number(*(data + i), 16).toUpper(), 2, QLatin1Char('0')) + " ");
	}
	return str.trimmed();
}

uint charTouint(const char *data, int len, int model)
{
	uchar *mdata = (uchar *)data;
	return charTouint(mdata, len, model);
}
uint charTouint(uchar *data, int len,int model)
{
    uint tmp = 0;
    if(model == 0)
    {
        for(int i = 0;i<len;i++)
        {
            tmp += (uint)data[i]*(0x00000001<<(i*8));
        }
    }
    else if(model == 1)
    {
        for(int i = 0;i<len;i++)
        {
            tmp += (uint)data[i]*(0x01000000>>(i*8));
        }
    }
    return tmp;
}
int charToint(uchar *data, int len,int model)
{
    if(len == 0 || len > 4)
    {
        return 0;
    }
    uint tmp1 = charTouint(data,len,model);
    tmp1 = tmp1<<((4-len)*8);
    int tmp = *(int *)(&tmp1)>>((4-len)*8);
    return tmp;
}
int charToint(const char * data, int len, int model)
{
	uchar *mdata = (uchar *)data;
	return charToint(mdata, len, model);
}
short charToshortwithQ(uchar *data,uchar &ov,uchar &er,int model)
{
    ushort tmp1;
    if(model == 0)
    {
        tmp1 = (ushort)data[0] + (ushort)data[1]*0x100;
        ov = data[0] &0x01;
        er = (data[0]>>1) &0x01;
    }
    else if(model == 1)
    {
        tmp1 = (ushort)data[0]*0x100 + (ushort)data[1];
        ov = data[1] &0x01;
        er = (data[1]>>1) &0x01;
    }
    short tmp = *(short *)(&tmp1) /8;
    return tmp;
}

short charToshortwithQ(uchar * data, int model)
{
	ushort tmp1;
	if (model == 0)
	{
		tmp1 = (ushort)data[0] + (ushort)data[1] * 0x100;
	}
	else if (model == 1)
	{
		tmp1 = (ushort)data[0] * 0x100 + (ushort)data[1];
	}
	short tmp = *(short *)(&tmp1) / 8;
	return tmp;
}

short charToshortwithQ(const char * data, int model)
{
	uchar *mdata = (uchar *)data;
	return charToshortwithQ(mdata, model);
}

float charTofloat(const char *data, int model)
{
	uchar *mdata = (uchar *)data;
	return charTofloat(mdata,model);
}

float charTofloat(uchar *data,int model)
{
	uint aaa = charTouint(data,4,model);
	float tmp = *(float *)&aaa;
    return tmp;
}

QDateTime charToDateTime(uchar *data,int len, int model)
{
    QDateTime datetime = QDateTime::currentDateTime();
    ushort tmp = 0;
    ushort milliseconds = 0;
    uchar second = 0;
    uchar minutes = 0;
    uchar hours = 0;
    uchar dayofmonths = 0;
    uchar months = 0;
    ushort years = 0;

    switch (model)
    {
    case BINARYTIME2A:      
        tmp = data[0] +data[1]*256;
        if(len ==2)
        {
            break;
        }
        milliseconds = tmp % 1000;
        second = tmp/1000;
        minutes = data[2]&0x3f;
        if(len ==3)
        {
            break;
        }
        hours = data[3]&0x1f;
        if(len ==4)
        {
            break;
        }
        dayofmonths = data[4] &0x1f;
        if(len ==5)
        {
            break;
        }
        months = data[5]&0x0f;
        if(len ==6)
        {
            break;
        }
        years = (ushort)(data[6] & 0x7f)+((ushort)datetime.date().year()/100)*100;
        break;
    case BINARYTIME2B:
        break;
	default:
		break;
    }
    datetime.setDate(QDate(years,months,dayofmonths));
    datetime.setTime(QTime(hours,minutes,second,milliseconds));
    return datetime;
}

QDateTime charToDateTime(const char * data, int len, int model)
{
	uchar *mdata = (uchar *)data;
	return charToDateTime(mdata, len, model);
}

QByteArray uintToBa(uint data, int len)
{
	QByteArray tmp;
	for(int i = 0; i<len;i++)
	{
		tmp.append((data>>(i*8))&0xff);
	}
	return tmp;
}
QByteArray floatToBa(float data)
{
	char ch[4];
	memcpy(ch,&data,4);
	QByteArray ba(ch,4);
	return ba;
}
QByteArray dateTimeToBa(QDateTime datatime, int len, int model)
{

	QByteArray ba;
	switch (model)
	{
	case BINARYTIME2A:
	{
		ushort tmp = datatime.time().msec() + datatime.time().second() * 1000;
		char ch[2];
		memcpy(ch, &tmp, 2);
		ba.append(ch, 2);
		if (len == 2)
		{
			break;
		}
		uchar uch = datatime.time().minute();
		ba.append(uch);
		if (len == 3)
		{
			break;
		}
		uch = datatime.time().hour();
		ba.append(uch);
		if (len == 4)
		{
			break;
		}
		uch = datatime.date().dayOfWeek();
		uch = (uch << 5) + datatime.date().day();
		ba.append(uch);
		if (len == 5)
		{
			break;
		}
		uch = datatime.date().month();
		ba.append(uch);
		if (len == 6)
		{
			break;
		}
		uch = datatime.date().year() % 100;
		ba.append(uch);
		break;
	}
	case BINARYTIME2B:
		break;
	default:
		break;
	}
	return ba;
}

uchar crcsum(const char *data, int start, int end)
{
	uchar tmp = 0;
	for (int i = start;i < end+1 ;i++)
	{
		tmp += *(uchar *)(data +i);
	}
	return tmp;
}


