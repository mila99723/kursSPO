#include "CPU.h"

UINT CPU::getNumberOfCernels() 
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	return sysInfo.dwNumberOfProcessors;
}

void  CPU::getProcessList() 
{
	HANDLE hSnap;
	//int number = 1;

	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == NULL)
	{
		return;
	}
	PROCESSENTRY32 proc;

	int process = 0, thread = 0;
	if (Process32First(hSnap, &proc))
	{
		do {
			//cout << number << ". " << proc.szExeFile << endl;
			process++;
			thread += proc.cntThreads;
			//number++;
		} while (Process32Next(hSnap, &proc));
	}
	numberOfProc = process;
	numberOfThreads = thread;
}

void  CPU::showInf() 
{
	system("cls");
	cout << "Чтобы выйти нажмите ESC" << endl;
	cout << endl;

	cout << "Количество ядер: " << getNumberOfCernels() << endl;  //логических процессоров
	//cout << "Скорость процессора: " << GetCPUFreq() << " ГГц" << endl;
	getCPUSpeed();														  
	cout << "Скорость процессора: " << speed << " ГГц" << endl;
	//cout << "Список запущенных процессов: " << endl;
	getProcessList();
	cout << "Количество запущенных процессов: " << numberOfProc << endl;
	cout << "Количество запущенных потоков: " << numberOfThreads << endl;

	while (GetKeyState(VK_ESCAPE) >= 0)
	{
		cout << "\rЗагрузка процессора: " << getCPULoad() * 100 << "%         ";
		Sleep(700);    
		fflush(stdin);
	}
	cout << endl;
}

float   CPU::calculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	static unsigned long long prevTotalTicks = 0;
	static unsigned long long prevIdleTicks = 0;

	unsigned long long totalTicksSinceLastTime = totalTicks - prevTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks - prevIdleTicks;
	prevTotalTicks = totalTicks;
	prevIdleTicks = idleTicks;

	if (totalTicksSinceLastTime > 0) return 1 - ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime;
	else return 1;  
}

unsigned long long   CPU::fileTimeToInt64(const FILETIME & ft)
{
	return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
}

float CPU::getCPULoad()  //kernel includes idle time
{
	FILETIME idleTime, kernelTime, userTime;

	if (GetSystemTimes(&idleTime, &kernelTime, &userTime)) 
		return calculateCPULoad(fileTimeToInt64(idleTime), fileTimeToInt64(kernelTime) + fileTimeToInt64(userTime));
	else return -1;
}

void CPU::getCPUSpeed()
{
	int DelayTime = 500;
	DWORD TimerHigh, TimerLow;
	int PriorityClass, Priority;

	PriorityClass = GetPriorityClass(GetCurrentProcess);
	Priority = GetThreadPriority(GetCurrentThread);

	SetPriorityClass(GetCurrentProcess, REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread, THREAD_PRIORITY_TIME_CRITICAL);

	Sleep(10);

	_asm
	{
		//dw 310Fh   //команда считывания счетчика TSC возвращает кол-во тактов с последнего сброса процессора !исп для точного замера времени
		jmp short $ + 3
		mov eax, 9090310Fh
		mov TimerLow, eax
		mov TimerHigh, edx
	}

	Sleep(DelayTime);

	_asm
	{
		//dw 310Fh
		jmp short $ + 3
		mov eax, 9090310Fh
		sub eax, TimerLow
		sbb edx, TimerHigh
		mov TimerLow, eax
		mov TimerHigh, edx
	}

	SetThreadPriority(GetCurrentThread, Priority);
	SetPriorityClass(GetCurrentProcess, PriorityClass);

	speed = TimerLow / (1000000.0 * DelayTime); 
}

/*float CPU::GetCPUFreq() 
{   
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	float speed = (float)freq.QuadPart / 1000000;
	return speed;
}*/