#include "iec101asdu100.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"

IEC101asdu100data::IEC101asdu100data()
{
	qoi = 0;
	infaddr = 0;
}

IEC101asdu100data::~IEC101asdu100data()
{

}

bool IEC101asdu100data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	int infaddrlen = App::IEC_INFADDRLEN;			//104信息体地址长度
	infaddr = charTouint(buff.data(),infaddrlen);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data(),infaddrlen) + "\t信息元素地址:" + QString::number(infaddr)+"\r\n");
	qoi = *(buff.data()+infaddrlen);
	mText.append(CharToHexStr(buff.data()+infaddrlen) + "\t" + qoiToText(qoi) +"\r\n");
	return true;
}

bool IEC101asdu100data::init(QByteArray buff, uint addr)
{
	mRecvData = buff;
	mText.clear();
	infaddr = addr;
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append("\t信息元素地址:" + QString::number(infaddr) +"\r\n");
	qoi = *buff.data();
	mText.append(CharToHexStr(buff.data()) + "\t" + qoiToText(qoi) +"\r\n");
	return true;
}

QString IEC101asdu100data::showToText()
{
	return mText;
}

bool IEC101asdu100data::createDate(IECDataConfig &config)
{
	infaddr = 0;
	config.data += uintToBa(infaddr,3);
	if(config.isMaster)
	{
		config.data += 0x14;
	}
	else
	{

	}
	return true;
}


IEC101asdu100::IEC101asdu100()
{

}

IEC101asdu100::~IEC101asdu100()
{
	qDeleteAll(datalist);
	datalist.clear();
}

bool IEC101asdu100::init(QByteArray buff)
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
	}

	uint dataaddr = charTouint((uchar *)(buff.data()+i),infaddrlen);
	for(int index = 0;index<datanum;index++)
	{
		IEC101asdu100data *mdata = new IEC101asdu100data;
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

QString IEC101asdu100::showToText()
{
	QString text = mText;
	foreach(IEC101asdu100data *mdata,datalist)
	{
		text.append(mdata->showToText());
	}
	return text;
}

bool IEC101asdu100::createDate(IECDataConfig &config)
{
	qDeleteAll(datalist);
	datalist.clear();

	if(config.isMaster)
	{
		config.data += 0x64;
		config.data += 0x01;
		config.data += 0x06;
		config.data += '\0';
		config.data += uintToBa(App::IEC_COMADDR,2);
		commonaddr = App::IEC_COMADDR;
		config.sqflag = true;
		config.isfirst = true;
		IEC101asdu100data *newdata = new IEC101asdu100data;
		newdata->createDate(config);
		datalist.append(newdata);
	}
	else
	{

	}
	return true;
}
