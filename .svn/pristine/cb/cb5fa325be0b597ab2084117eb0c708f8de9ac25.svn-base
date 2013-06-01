/*
 * commdef.h
 *
 *  Created on: 2013-5-23
 *      Author: YangQi
 */

#ifndef COMMDEF_H_
#define COMMDEF_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <assert.h>
#include <vector>
#include <list>
#include <map>

using std::vector;
using std::list;
using std::map;

typedef char 				int8;
typedef short 				int16;
typedef long 				int32;
typedef long long 			int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned long 		uint32;
typedef unsigned long long  uint64;


#define printerr(format,...)	\
	fprintf(stderr,"ERROR:[%s-%s-%d]",__FILE__,__FUNCTION__,__LINE__);	\
	fprintf(stderr,format,##__VA_ARGS__);	\
	fprintf(stderr,"(%s)\t\n",strerror(errno))


#endif /* COMMDEF_H_ */
