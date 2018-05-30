#include "Memory.h"

void Memory::showInf() 
{
	system("cls");
	memStat.dwLength = sizeof(memStat);  //������������� ��������� ������ � ������
	if (!GlobalMemoryStatusEx(&memStat))
	{
		cout << "Error - " << GetLastError() << endl;
		return;
	}

	cout << "������� ������������ ������: " << memStat.dwMemoryLoad << "%" << endl
		<< "����� ����� ���������� ������: " << memStat.ullTotalPhys / MB << " MB" << endl
		<< "����� ��������� ���������� ������: " << memStat.ullAvailPhys / MB << " MB" << endl
		<< "������ ����� ��������: " << memStat.ullTotalPageFile / MB << " MB" << endl
		<< "��������� ����� ������ � ����� ��������: " << memStat.ullAvailPageFile / MB << " MB" << endl
		<< "����� ����� ����������� ������:" << memStat.ullTotalVirtual / MB << " MB" << endl
		<< "����� ��������� ����������� ������: " << memStat.ullAvailVirtual / MB << " MB" << endl << endl;
		//<< "����� ������������������� ������ � ����������� ����� ����������� ������: " << memStat.ullAvailExtendedVirtual / MB << " MB" << endl << endl;
}