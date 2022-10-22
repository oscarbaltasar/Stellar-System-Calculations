#include "CommonData.h"

GlobalData::GlobalData()
{
	realTime = new struct tm();
}

GlobalData::~GlobalData()
{
}

void GlobalData::updateTime()
{
	time(&rawTime);
	gmtime_s(realTime, &rawTime);
}
