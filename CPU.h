#pragma once
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
//#include <fstream>

using namespace std;

class CPU {
private:
	int numberOfProc;
	int numberOfThreads;
	float speed;
public:
	void showInf();
	float calculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
	unsigned long long fileTimeToInt64(const FILETIME & ft);
	float getCPULoad();
	void getCPUSpeed();
	void getProcessList();
	UINT getNumberOfCernels();
	//float GetCPUFreq();
};
