#include "dataconfig.h"

DataConfig::DataConfig()
{

}

IECDataConfig::IECDataConfig()
{
	state = 0;				//状态
	isMaster = false;			//是否为主站
	asdutype = 0;
	sqflag = false;			//是否需要信息体地址
	isfirst = true;
}
