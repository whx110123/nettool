#include "globaldefine.h"


QString CharToHexStr(uchar data)
{
    return QString("%1").arg(QString::number(data,16).toUpper(),2,QLatin1Char('0'));
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

    }
    datetime.setDate(QDate(years,months,dayofmonths));
    datetime.setTime(QTime(hours,minutes,second,milliseconds));
    return datetime;
}


