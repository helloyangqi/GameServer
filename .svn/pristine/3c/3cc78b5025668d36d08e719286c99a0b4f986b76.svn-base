/*
 * Log.cpp
 *
 *  Created on: 2013-5-31
 *      Author: YangQi
 */

#include "Log.h"

static  Log sLog;

Log::Log()
{
	m_errLogFile = fopen(ERRORLOGFILE,"a+");
}

Log::~Log()
{
	fclose(m_errLogFile);
}

void Log::OutError(const char *err,...)
{
	if(m_errLogFile == NULL)
		m_errLogFile = fopen(ERRORLOGFILE,"a+");
	char tmp_buff[1024],tem_buff2[1024];
	va_list args;
	time_t tval;
	time(&tval);
	struct tm *ctm = localtime(&tval);

	va_start(args,err);
	vsprintf(tem_buff,err,args);
	va_end(args);

	sprintf(tmp_buff2,"ERROR:[%d/%02d/%02d %02d:%02d:%02d] %s\t\n",
			ctm->tm_year + 1900,
			ctm->tm_mon + 1,
			ctm->tm_mday,
			ctm->tm_hour,
			ctm->tm_min,
			ctm->tm_sec,
			tmp_buff);
	fprintf(m_errLogFile,tem_buff2);
}
