#include "Memory.h"

void Memory::showInf() 
{
	system("cls");
	memStat.dwLength = sizeof(memStat);  //инициализация структуры данных о памяти
	if (!GlobalMemoryStatusEx(&memStat))
	{
		cout << "Error - " << GetLastError() << endl;
		return;
	}

	cout << "Процент используемой памяти: " << memStat.dwMemoryLoad << "%" << endl
		<< "Общий объем физической памяти: " << memStat.ullTotalPhys / MB << " MB" << endl
		<< "Объем доступной физической памяти: " << memStat.ullAvailPhys / MB << " MB" << endl
		<< "Размер файла подкачки: " << memStat.ullTotalPageFile / MB << " MB" << endl
		<< "Доступный объем байтов в файле подкачки: " << memStat.ullAvailPageFile / MB << " MB" << endl
		<< "Общий объем виртуальной памяти:" << memStat.ullTotalVirtual / MB << " MB" << endl
		<< "Объем доступной виртуальной памяти: " << memStat.ullAvailVirtual / MB << " MB" << endl << endl;
		//<< "Объем незарезервированной памяти в расширенной части виртуальной памяти: " << memStat.ullAvailExtendedVirtual / MB << " MB" << endl << endl;
}