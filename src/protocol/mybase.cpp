#include "mybase.h"

MyBase::MyBase()
{
	error = 0;
	len = 0;
	masterState = STATE_NORMAL;
}

MyBase::~MyBase()
{

}

bool MyBase::init(QByteArray buff)
{
	return false;
}

bool MyBase::init(QByteArray buff, uint addr)
{
	return false;
}

bool MyBase::init(QByteArray buff, uchar *ch)
{
	return false;
}

QString MyBase::showToText()
{
	return mText;
}

bool MyBase::createData(IECDataConfig &config)
{
	return false;
}
