#include "iec101asdu1.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu1data::IEC101asdu1data()
{
	siq = 0;
}

IEC101asdu1data::~IEC101asdu1data()
{

}

bool IEC101asdu1data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//104信息体地址长度
	infaddr = charTouint(buff.data(),infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+"\r\n");
	siq = *(buff.data()+infaddrlen);
	mText.append(CharToHexStr(buff.data()+infaddrlen) + "\t" + spiToText(siq) +"   "+ ivToText(siq) +"   "+ ntToText(siq)+"   "+ sbToText(siq)+"   "+ blToText(siq)+"\r\n");
	return true;
}

bool IEC101asdu1data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) +"\r\n");
	siq = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + spiToText(siq) +"   "+ ivToText(siq) +"   "+ ntToText(siq)+"   "+ sbToText(siq)+"   "+ blToText(siq)+"\r\n");
	return true;
}

QString IEC101asdu1data::showToText()
{
	return mText;
}

bool IEC101asdu1data::createDate(IECDataConfig &config)
{
	return true;
}

IEC101asdu1::IEC101asdu1()
{

}

IEC101asdu1::~IEC101asdu1()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool IEC101asdu1::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	qDeleteAll(datalist);
	datalist.clear();
	int cotlen = App::IEC_COTLEN;					//104cot长度
	int comaddrlen = App::IEC_COMADDRLEN;			//104公共地址长度
	int infaddrlen = App::IEC_INFADDRLEN;			//104信息体地址长度
	int i = 0;
	if(!initCommon(buff,i))
	{
		return false;
	}

	int lengthtmp = 2+cotlen+comaddrlen+infaddrlen+(1-sqflag)*(datanum-1)* infaddrlen+datanum*(datalen+timelen)+other;
	if( lengthtmp!= buff.count())
	{
		mText.append( "\r\n\t出错！通过VSQ与ASDU类型计算出ASDU长度为"+QString::number(lengthtmp)+"，而实际ASDU长度为"+QString::number(buff.count())+"。报文长度不符，因此报文有问题，下面的解析可能会出现异常\r\n");
 //       return text;
	}

	uint dataaddr = charTouint((uchar *)(buff.data()+i),infaddrlen);
	for(int index = 0;index<datanum;index++)
	{
		IEC101asdu1data *mdata = new IEC101asdu1data;
		bool isOk;
		if(index ==0 || sqflag == 0)
		{
			isOk = mdata->init(buff.mid(i,infaddrlen+datalen+timelen));
			i += infaddrlen+datalen+timelen;
		}
		else
		{
			isOk = mdata->init(buff.mid(i,datalen+timelen),dataaddr+index);
			i += datalen+timelen;
		}
		if(!isOk)
		{
			error = 1;
			delete mdata;
			mdata =NULL;
			return false;
		}
		datalist.append(mdata);
	}
	return true;
}

QString IEC101asdu1::showToText()
{
	QString text = mText;
	foreach(IEC101asdu1data *mdata,datalist)
	{
		text.append(mdata->showToText());
	}
	return text;
}

bool IEC101asdu1::createDate(IECDataConfig &config)
{
	return true;
}

