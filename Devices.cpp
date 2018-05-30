#include "Devices.h"

void Devices::getDevsList() //��������� � ����� ������ ���������
{    
	int numer = 1;
	SP_DEVINFO_DATA DeviceInfoData; //��������� ���������� �� ���������� (������, GUID �����, handle to devnode, reserved)
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	DWORD i;

	system("cls");
	cout << "������ ������������� ���������: " << endl;
	

	hDevInfo = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);  //GUID pointer, Enumerator, handle of top window for user interf, flags
	if (hDevInfo == INVALID_HANDLE_VALUE) // ���� ������ �� ������� ��������
	{
		cout << "ERORR! �� ������� �������� ������\n";
	}

	// ������������ ���� ��������� 
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)  //(������ �������� ��� �� �����������, ������, ��������� �� ����������) - true
	{
		DWORD Data;
		LPTSTR buff = NULL;
		DWORD buffSize = 0;

		while (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_DEVICEDESC,  //���� REG_SZ ������, � ������� �������� ����������
			&Data,
			(PBYTE)buff,
			buffSize,
			&buffSize))   //����������� ������ ������
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buff) LocalFree(buff);  // ��������� ������� ������
				buff = (char*)LocalAlloc(LPTR, buffSize * 2); // �������� ������� ������ � ������ �������� ��� Win2K MBCS systems per KB 888609
			}
			else
			{
				if (GetLastError() == ERROR_INVALID_DATA);  //�������� �� ��������
				else cout << "Error - " << GetLastError() << endl;
				break;
			}
		}
		if (buff != NULL)
		{
			cout << numer << "  " << buff << endl; //  ����� �������� ������ 
		}
		else
		{
			if (GetLastError() == ERROR_INVALID_DATA) numer -= 1; //���������������� ��� ����������� ����������
			else cout << "Error - " << GetLastError() << endl;
		}

		if (buff) LocalFree(buff);
		numer++;
	}

	if (GetLastError() != NO_ERROR && GetLastError() != ERROR_NO_MORE_ITEMS)
	{
		cout << "ERORR! �� ������� �������� ������\n";
	}
	SetupDiDestroyDeviceInfoList(hDevInfo); //  ������� ������ �� ������
}

void Devices::getDevsListEx() 
{
	system("cls");
	cout << "������ ������������� ���������: " << endl;

	GUID ClassGuid;
	hDevInfo = SetupDiGetClassDevs(&ClassGuid, 0, 0, DIGCF_ALLCLASSES | DIGCF_PRESENT); //GUID pointer, Enumerator, handle of top window for user interf, flags

	SP_DEVINFO_DATA DeviceInfoData;
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	BYTE Buff[MAX_DEV_LEN];
	DWORD DataType;
	DWORD RequiredSize = 0;
	DWORD i = 0;
	int numer = 1;
	
	while (SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData))  ////(������ �������� ��� �� �����������, ������, ��������� �� ����������) - true
	{
		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo, 
			&DeviceInfoData,
			SPDRP_CLASS,       //���� ����� ����������
			&DataType,        //��� ������ ����������� ��������
			Buff, 
			MAX_DEV_LEN, 
			&RequiredSize))
		{
			if (GetLastError() == ERROR_INVALID_DATA);  //�������� �� ��������
			else cout << "Error - " << GetLastError() << endl;
		}
		else
		{
			cout << numer << ". " << Buff << endl;
		}

		if(!SetupDiGetDeviceRegistryProperty(
			hDevInfo, 
			&DeviceInfoData,
			SPDRP_DEVICEDESC,  //���� REG_SZ ������, � ������� �������� ����������
			&DataType, //��� ������ ����������� ��������
			Buff, 
			MAX_DEV_LEN, 
			&RequiredSize))
		{
			if (GetLastError() == ERROR_INVALID_DATA);  //�������� �� ��������
			else cout << "Error - " << GetLastError() << endl;
		}
		else
		{
			cout << Buff << endl;
		}

		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo, 
			&DeviceInfoData,
			SPDRP_FRIENDLYNAME,           //���� ������ � ������� friendly name ����������
			&DataType,      //��� ������ ����������� ��������
			Buff, 
			MAX_DEV_LEN, 
			&RequiredSize))
		{
			if (GetLastError() == ERROR_INVALID_DATA);  //�������� �� ��������
			else cout << "Error - " << GetLastError() << endl;
		}
		else
		{
			cout << Buff << endl;
		}
		
		cout << endl;
		i++;
		numer++;
	}
	if (GetLastError() != NO_ERROR && GetLastError() != ERROR_NO_MORE_ITEMS)
	{
		cout << "ERORR! �� ������� �������� ������" << endl; 
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);   //  ������� ������ �� ������
}
