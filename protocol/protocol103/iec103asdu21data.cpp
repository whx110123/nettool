#include "iec103asdu21data.h"
#include "functotext.h"

IEC103asdu21data::IEC103asdu21data()
{
	rii = 0;
	nog = 0;
}

IEC103asdu21data::~IEC103asdu21data()
{
	qDeleteAll(setlist);
	setlist.clear();
}

bool IEC103asdu21data::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	qDeleteAll(setlist);
	setlist.clear();
	len = 0;

	inf = *(buff.data() + len);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data() + len) + "\t" + infToText() + "\r\n");
	len++;

	rii = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\tRII:" + QString::number(rii) + " 返回信息标识符\r\n");
	len++;
	if (len == buff.size())
	{
		return true;
	}

	nog = *(buff.data() + len);
//	setnum = ngd & 0x3f;
//	datacount = ngd & 0x40;
//	datacont = ngd & 0x80;
	mText.append(CharToHexStr(buff.data() + len) + "\t" + nogToText(nog) + "\r\n");
	len++;

	if (len == buff.size())
	{
		return true;
	}


	for (int index = 0; index < nog; index++)
	{
		IEC103asdudataset *mset = new IEC103asdudataset;
		bool isOk = mset->init(buff.mid(len,3));
		if (!isOk)
		{
			error = 1;
			delete mset;
			mset = NULL;
			return false;
		}
		len += mset->len;
		setlist.append(mset);
	}

	return true;
}

bool IEC103asdu21data::init(QByteArray buff, uint addr)
{
	return false;
}

QString IEC103asdu21data::showToText()
{
	QString text = mText;
	for (IEC103asdudataset *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}

bool IEC103asdu21data::createData(IECDataConfig &config)
{
	config.data += config.inf;
	config.data += config.rii;
	config.data += config.nog;
	if(config.isMaster)
	{
		for(int i = 0;i <config.nog; i++ )
		{
			config.data += config.gin[i][0];
			config.data += config.gin[i][1];
			config.data += config.kod[i];
		}
		return true;
	}

	return false;

}
