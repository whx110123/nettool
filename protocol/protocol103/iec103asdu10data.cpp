#include "iec103asdu10data.h"
#include "globaldefine.h"
#include "app.h"
#include "functotext.h"
#include "QTextCodec"


IEC103asdudatasetgid::IEC103asdudatasetgid()
{
}

IEC103asdudatasetgid::~IEC103asdudatasetgid()
{
}

bool IEC103asdudatasetgid::init(QByteArray buff,uchar *gdd)
{
	mRecvData = buff;
	mText.clear();
	len = 0;

	switch (gdd[0])
	{
	case 1:
	{
		QByteArray ba(buff.data(),gdd[1]);
		QTextCodec *gbk = QTextCodec::codecForName("GB18030");
		gbkstr = gbk->toUnicode(ba);
		mText.append(CharToHexStr(buff.data(),gdd[1]) + "\tOS8(ASCII8位码):" + gbkstr);
		len += gdd[1];
	}
		break;
    case 2:
	{
		bit8 = QString("%1").arg(QString::number(*(uchar *)buff.data(), 2), 8, '0');
		mText.append(CharToHexStr(buff.data()) + "\t成组8位串:" + bit8);
		len++;
	}
        break;
	case 3:
		datauint = charTouint(buff.data(), gdd[1]);
		mText.append(CharToHexStr(buff.data(), gdd[1]) + "\tGID:无符号整数:" + QString::number(datauint));
		len += gdd[1];
		break;
	case 4:
		dataint = charToint(buff.data(), gdd[1]);
		mText.append(CharToHexStr(buff.data(), gdd[1]) + "\tGID:整数:" + QString::number(dataint));
		len += gdd[1];
		break;
	case 7:
		if (gdd[1] != 4)
		{
			return false;
		}
		datafloat = charTofloat(buff.data());
		mText.append(CharToHexStr(buff.data(), gdd[1]) + "\tGID:IEEE标准754短实数:" + QString::number(datafloat));
		len += gdd[1];
		break;
	case 9:
		datauchar = *buff.data();
		mText.append(CharToHexStr(buff.data()) + "\tGID:" + dpiToText(datauchar));
		len++;
		break;
	case 10:
		datauchar = *buff.data();
		mText.append(CharToHexStr(buff.data()) + "\tGID:" + spiToText(datauchar));
		len++;
		break;
	case 11:
		datauchar = *buff.data();
		mText.append(CharToHexStr(buff.data()) + "\tGID:" + dpiteToText(datauchar));
		len++;
		break;
	case 12:
		if (gdd[1] != 2)
		{
			return false;
		}
		datashort = charToshortwithQ(buff.data());
		mText.append(CharToHexStr(buff.data(),2) + "\tGID:带品质描述词的被测值(bit4-16):" + QString::number(datashort) + ovToText(*buff.data()) +erToText(*buff.data())+"\r\n");
		len += gdd[1];
		break;
	case 18:
		if (gdd[1] != 6)
		{
			return false;
		}
		datauchar = *buff.data();
		mText.append(CharToHexStr(buff.data()) + "\tGID:" + spiToText(datauchar) + "\r\n");
		len++;
		mText.append(timeToText(buff.data() + len, 4));
		len += 4;
		datauchar1 = *(buff.data()+ len);
		mText.append(CharToHexStr(buff.data()) + "\tGID:附加信息SIN:" + QString::number(datauchar1));
		len++;
		break;
	case 19:
		datauchar = *buff.data();
		mText.append(CharToHexStr(buff.data()) + "\tGID:" + spiToText(datauchar) + "\r\n");
		len++;
		datauint = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data()+len,2) + "\tGID:相对时间RET:" + QString::number(datauint));
		mText.append("   秒:" + QString::number(datauint / 1000) + "   毫秒:" + QString::number(datauint % 1000) + " \r\n");
		len += 2;

		datauint1 = charTouint(buff.data() + len, 2);
		mText.append(CharToHexStr(buff.data() + len, 2) + "\tGID:故障序号FAN:" + QString::number(datauint1) + "\r\n");
		len += 2;

		mText.append(timeToText(buff.data() + len, 4));
		len += 4;

		datauchar1 = *(buff.data() + len);
		mText.append(CharToHexStr(buff.data()+len) + "\tGID:附加信息SIN:" + QString::number(datauchar1));
		len++;

		break;
	case 201:
		datauint = charTouint(buff.data() , 4);
		mText.append(CharToHexStr(buff.data() ,4) + "\tGID:无符号整数:" + QString::number(datauint) + "\r\n");
		len += 4;
		datauchar = *(buff.data()+len);
		mText.append(CharToHexStr(buff.data()+len) + "\tGID:预留字节,无定义");
		len++;
		break;
	default:
		return false;
		break;
	}
	mText.append("\r\n");
	return true;
}


QString IEC103asdudatasetgid::showToText()
{
	return mText;
}

bool IEC103asdudatasetgid::createData(IECDataConfig & config)
{
	return false;
}

IEC103asdudataset::IEC103asdudataset()
{
	error = 0;
	len = 0;
	mstate = STATE_NORMAL;
	gidnum = 0;
}

IEC103asdudataset::~IEC103asdudataset()
{
	qDeleteAll(gidlist);
	gidlist.clear();
}

bool IEC103asdudataset::init(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	qDeleteAll(gidlist);
	gidlist.clear();
	len = 0;

	memcpy(gin, buff.data(), 2);
	mText.append("-----------------------------------------------------------------------------------------------\r\n");
	mText.append(CharToHexStr(buff.data()+len,2) + "\tGIN:组号" + QString::number(gin[0]) + "   条目号" + QString::number(gin[1]) + "\r\n");
	len += 2;

	kod = *(buff.data() + len);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + kodToText(kod) + "\r\n");
	len++;

	memcpy(gdd, buff.data()+len, 3);
	mText.append(CharToHexStr(buff.data() + len) + "\t" + gdd1ToText(gdd[0]) + "\r\n");
	mText.append(CharToHexStr(buff.data() + len+1) + "\tGDD2:" + QString::number(gdd[1]) + " 数据宽度\r\n");
	mText.append(CharToHexStr(buff.data() + len+2) + "\t" + gdd3ToText(gdd[2]) + "\r\n");
	if (gdd[0] == 2)
	{
		gidnum = ((ushort)gdd[1] * (gdd[2]&0x7f) - 1) / 8 + 1;
	} 
	else
	{
		gidnum = gdd[2] & 0x7f;
	}
	len += 3;

	for (int i = 0;i < gidnum;i++)
	{
		IEC103asdudatasetgid *mgid = new IEC103asdudatasetgid;
		bool isOk = mgid->init(buff.mid(len),gdd);
		if (!isOk)
		{
			error = 1;
			delete mgid;
			mgid = NULL;
			return false;
		}
		len += mgid->len;
		gidlist.append(mgid);
	}
	return true;
}

bool IEC103asdudataset::init(QByteArray buff, uchar * ch)
{
	return false;
}

QString IEC103asdudataset::showToText()
{
	QString text = mText;
	for (IEC103asdudatasetgid *mgid : gidlist)
	{
		text.append(mgid->showToText());
	}
	return text;
}

bool IEC103asdudataset::createData(IECDataConfig & config)
{
	return false;
}


IEC103asdu10data::IEC103asdu10data()
{
	rii = 0;
	ngd = 0;
}

IEC103asdu10data::~IEC103asdu10data()
{
	qDeleteAll(setlist);
	setlist.clear();
}

bool IEC103asdu10data::init(QByteArray buff)
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

	ngd = *(buff.data() + len);
	setnum = ngd & 0x3f;
	datacount = ngd & 0x40;
	datacont = ngd & 0x80;
	mText.append(CharToHexStr(buff.data() + len) + "\t" + ngdToText(ngd) + "\r\n");
	len++;

	uchar *gin = (uchar *)(buff.data() + len);
	for (int index = 0; index < setnum; index++)
	{
		IEC103asdudataset *mset = new IEC103asdudataset;
		bool isOk = mset->init(buff.mid(len));
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

bool IEC103asdu10data::init(QByteArray buff, uint addr)
{
	return false;
}

QString IEC103asdu10data::showToText()
{
	QString text = mText;
	for (IEC103asdudataset *mset : setlist)
	{
		text.append(mset->showToText());
	}
	return text;
}

bool IEC103asdu10data::createData(IECDataConfig &config)
{
	return true;
}


