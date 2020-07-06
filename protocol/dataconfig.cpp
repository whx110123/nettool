#include "dataconfig.h"

DataConfig::DataConfig()
{

}

IECDataConfig::IECDataConfig()
{
	state = 0;				//状态
	isMaster = false;			//是否为主站
	asdutype = 0;
	cot = 0;
	vsq = 1;
	isfirst = true;

}
