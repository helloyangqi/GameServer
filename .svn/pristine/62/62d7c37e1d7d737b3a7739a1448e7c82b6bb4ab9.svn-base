/*
 * DBManager.h
 *
 *  Created on: 2013-5-25
 *      Author: YangQI
 */

#ifndef DBSERVICE_H_
#define DBSERVICE_H_
#include "Common.h"
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>

using namespace sql;
using namespace sql::mysql;

#define DBHOST "tcp://127.0.0.1:3306"
#define USER	"root"
#define PASSWD	"yangqi"
#define DBNAME	"MyGame"

typedef struct
{
	char account[50];
	char username[32];
	int sex;
	unsigned long long money;

}PlayerInfo;

class DBService
{
public:
	static int InitDataBase();
	static void DisconnectDataBase();
	static bool SearchPlayerInfo(char *name,int sex);
	static bool IsExistTalbe(const char *tableName);
	static bool CreatePlayerTable();
};


#endif /* DBSERVICE_H_ */
