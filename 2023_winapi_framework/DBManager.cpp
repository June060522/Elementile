#include "pch.h"
#include "DBManager.h"

void DBManager::Init()
{
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "root", "20060522");
	con->setSchema("gamep");
}