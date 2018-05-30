#pragma once
#include <iostream>
#include <windows.h>
#include <SetupAPI.h>
//#include <fstream>
#pragma comment(lib, "SetupAPI.lib")

using namespace std;

#define MAX_DEV_LEN 128

class Devices {
private:
	HDEVINFO hDevInfo;
public:
	void getDevsList();
	void getDevsListEx();
};
