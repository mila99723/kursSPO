#include <iostream>
#include <stdio.h>
#include "CPU.h"
#include "Memory.h"
#include "Devices.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	//ofstream myfile;
	//myfile.open("log.csv", ios::out | ios::app);
	//myfile.close();

	CPU cpu;
	Memory mem;
	Devices dev;

	int menu;
	do {
		cout << " ################################################# " << endl
			 << "#  MENU:                                          #" << endl
			 << "# 1.�������� �������� ����������                  #" << endl
			 << "# 2.�������� ��������� ������                     #" << endl
			 << "# 3.�������� ������ ���������                     #" << endl
			 << "# 0.�����                                         #" << endl
			 << " ################################################# " << endl;
		do { cin >> menu; } while (menu < 0 || menu > 3);
		switch (menu) {
		case 1: cpu.showInf();
				break;
		case 2: mem.showInf();
				break;
		case 3: //dev.getDevsList();
				dev.getDevsListEx();
				break;
		case 0: break;
		default: break;
		}
	} while (menu != 0);
	
	system("pause");
	return 0; 
}


