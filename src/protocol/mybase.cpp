#include "mybase.h"

MyBase::MyBase()
{
	setDefault(NULL);
	masterState = STATE_NORMAL;
	slaveState = STATE_NORMAL;
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

void MyBase::setDefault(QByteArray buff)
{
	mRecvData = buff;
	mText.clear();
	error = 0;
	len = 0;
}
