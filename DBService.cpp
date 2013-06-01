/*
 * DBService.cpp
 *
 *  Created on: 2013-5-25
 *      Author: YangQi
 */

#include "DBService.h"

MySQL_Driver *drive;
Connection *conn;

int DBService::InitDataBase()
{
	char sql[100];
	try{
		drive = get_mysql_driver_instance();
		conn = drive->connect(DBHOST,USER,PASSWD);
		std::cout<<"connection mysql database seccess"<<std::endl;
		Statement *stmt;
		ResultSet *res;
		stmt = conn->createStatement();
		sprintf(sql,"SELECT schema_name FROM information_schema.schemata WHERE schema_name ='%s'",DBNAME);
		res = stmt->executeQuery(sql);
		if(res->rowsCount() == 0)
		{
			stmt->execute("CREATE DATABASE "DBNAME);
		}
		if(!IsExistTalbe("players"))
			CreatePlayerTable();
	}catch(SQLException &e)
	{
		printerr("init database failed");
		printerr(e.what());
		delete conn;
		exit(1);
	}
	return 0;
}

void DBService::DisconnectDataBase()
{
	if(conn != NULL)
	{
		delete conn;
		conn = NULL;
		drive = NULL;
	}
}

bool DBService::IsExistTalbe(const char *tableName)
{
	Statement *stmt;
	ResultSet *res;
	char sql[100];
	stmt = conn->createStatement();
	sprintf(sql,"SELECT table_name FROM information_schema.TABLES WHERE table_name = '%s' and table_schema = '%s'",tableName,DBNAME);
	try{
		res = stmt->executeQuery(sql);
	}catch(SQLException &e)
	{
		printerr("execute sql failed");
		printerr(e.what());
		exit(1);
		return false;
	}
	return res->rowsCount() > 0 ? true : false;
}

bool DBService::CreatePlayerTable()
{
	Statement *stmt;
	bool state = false;
	stmt = conn->createStatement();
	try{
		stmt->execute("USE "DBNAME);
		stmt->execute("CREATE TABLE players("
					"id INT UNSIGNED NOT NULL AUTO_INCREMENT"
					",name CHAR(32) NOT NULL"
					",level INT NOT NULL  DEFAULT 1"
					",sex INT NOT NULL DEFAULT 1"
					",PRIMARY KEY(id))"
					);
	}catch(SQLException &e)
	{
		printerr("Create Table Failed");
		printerr(e.what());
		exit(1);
	}
	return state;
}

bool DBService::SearchPlayerInfo(char *username,int sex)
{
	Statement *stmt;
	ResultSet *res;
	char sql[100];
	try{
		stmt = conn->createStatement();
		if(drive == NULL || conn == NULL)
		{
			InitDataBase();
		}
		stmt->execute("USE "DBNAME);
		sprintf(sql,"SELECT name FROM players WHERE name= '%s'",username);
		res = stmt->executeQuery(sql);
		if(res->rowsCount() == 0)
		{
			return false;
			sprintf(sql,"INSERT INTO players(name,level,sex) VALUES ('%s','%d','%d')",username,50,sex);
			stmt->execute(sql);
		}
		return true;
	}catch(SQLException &e)
	{
		printerr("Search Player Failed");
		printerr(e.what());
		exit(1);
	}
	return false;
}

