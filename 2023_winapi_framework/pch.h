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
#include "define.h"
#include "Vec2.h"
#include "enums.h"
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

// transparent 등 blt 쓸 때 필요
#pragma comment(lib, "Msimg32.lib")