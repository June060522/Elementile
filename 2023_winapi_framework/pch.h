#pragma once
//#include<iostream>
#include <Windows.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include <mmsystem.h>
#include <mutex>
#include <future>
#include "Vec2.h"
#include "enums.h"
#include "define.h"
//using namespace std; 사용 지양
using std::vector;
using std::map;
using std::wstring;
using std::ifstream;
using std::ofstream;
using std::string;
using std::endl;
using std::to_string;
using std::to_wstring;
#include "mysql_driver.h"
#include "mysql_connection.h"
using namespace sql;
// transparent 등 blt 쓸 때 필요
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "mysqlcppconn.lib")
#pragma comment(lib, "ws2_32.lib")