#pragma once
#include <iostream>
#include <windows.h>
//#include <fstream>

using namespace std;

#define MB 1048576

class Memory {
private:
	MEMORYSTATUSEX memStat;
public:
	void showInf();
};
