/*
 * log.h
 *
 *  Created on: 2013-5-31
 *      Author: YangQi
 */

#ifndef LOG_H_
#define LOG_H_

#include "Common.h"

#define LOGFILENAME "log"

extern Log sLog;

class Log
{
public:
	Log();
	~Log();

	void OutError(const char* err,...);
private:
	FILE *m_logFile;
};
#endif /* LOG_H_ */
