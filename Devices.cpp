#include "Devices.h"

void Devices::getDevsList() //получение и вывод списка устройств
{    
	int numer = 1;
	SP_DEVINFO_DATA DeviceInfoData; //структура информации об устройстве (размер, GUID класс, handle to devnode, reserved)
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	DWORD i;

	system("cls");
	cout << "Список установленных устройств: " << endl;
	

	hDevInfo = SetupDiGetClassDevs(NULL, 0, 0, DIGCF_PRESENT | DIGCF_ALLCLASSES);  //GUID pointer, Enumerator, handle of top window for user interf, flags
	if (hDevInfo == INVALID_HANDLE_VALUE) // если список не удалось получить
	{
		cout << "ERORR! Не удалось получить список\n";
	}

	// Перечисление всех устройств 
	for (i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++)  //(список структур инф об устройствах, индекс, структура об устройстве) - true
	{
		DWORD Data;
		LPTSTR buff = NULL;
		DWORD buffSize = 0;

		while (!SetupDiGetDeviceRegistryProperty(
			hDevInfo,
			&DeviceInfoData,
			SPDRP_DEVICEDESC,  //ищем REG_SZ строку, в которой описание устройства
			&Data,
			(PBYTE)buff,
			buffSize,
			&buffSize))   //необходимый размер буфера
		{
			if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			{
				if (buff) LocalFree(buff);  // изменение размера буфера
				buff = (char*)LocalAlloc(LPTR, buffSize * 2); // удвоение размера буфера в случае нехватки для Win2K MBCS systems per KB 888609
			}
			else
			{
				if (GetLastError() == ERROR_INVALID_DATA);  //свойство не доступно
				else cout << "Error - " << GetLastError() << endl;
				break;
			}
		}
		if (buff != NULL)
		{
			cout << numer << "  " << buff << endl; //  вывод элемента списка 
		}
		else
		{
			if (GetLastError() == ERROR_INVALID_DATA) numer -= 1; //недействительная или недоступная информация
			else cout << "Error - " << GetLastError() << endl;
		}

		if (buff) LocalFree(buff);
		numer++;
	}

	if (GetLastError() != NO_ERROR && GetLastError() != ERROR_NO_MORE_ITEMS)
	{
		cout << "ERORR! Не удалось получить список\n";
	}
	SetupDiDestroyDeviceInfoList(hDevInfo); //  очистка памяти от списка
}

void Devices::getDevsListEx() 
{
	system("cls");
	cout << "Список установленных устройств: " << endl;

	GUID ClassGuid;
	hDevInfo = SetupDiGetClassDevs(&ClassGuid, 0, 0, DIGCF_ALLCLASSES | DIGCF_PRESENT); //GUID pointer, Enumerator, handle of top window for user interf, flags

	SP_DEVINFO_DATA DeviceInfoData;
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	BYTE Buff[MAX_DEV_LEN];
	DWORD DataType;
	DWORD RequiredSize = 0;
	DWORD i = 0;
	int numer = 1;
	
	while (SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData))  ////(список структур инф об устройствах, индекс, структура об устройстве) - true
	{
		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo, 
			&DeviceInfoData,
			SPDRP_CLASS,       //ищем класс устройства
			&DataType,        //тип данных полученного свойства
			Buff, 
			MAX_DEV_LEN, 
			&RequiredSize))
		{
			if (GetLastError() == ERROR_INVALID_DATA);  //свойство не доступно
			else cout << "Error - " << GetLastError() << endl;
		}
		else
		{
			cout << numer << ". " << Buff << endl;
		}

		if(!SetupDiGetDeviceRegistryProperty(
			hDevInfo, 
			&DeviceInfoData,
			SPDRP_DEVICEDESC,  //ищем REG_SZ строку, в которой описание устройства
			&DataType, //тип данных полученного свойства
			Buff, 
			MAX_DEV_LEN, 
			&RequiredSize))
		{
			if (GetLastError() == ERROR_INVALID_DATA);  //свойство не доступно
			else cout << "Error - " << GetLastError() << endl;
		}
		else
		{
			cout << Buff << endl;
		}

		if (!SetupDiGetDeviceRegistryProperty(
			hDevInfo, 
			&DeviceInfoData,
			SPDRP_FRIENDLYNAME,           //ищем строку в которой friendly name устройства
			&DataType,      //тип данных полученного свойства
			Buff, 
			MAX_DEV_LEN, 
			&RequiredSize))
		{
			if (GetLastError() == ERROR_INVALID_DATA);  //свойство не доступно
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
		cout << "ERORR! Не удалось получить список" << endl; 
	}

	SetupDiDestroyDeviceInfoList(hDevInfo);   //  очистка памяти от списка
}
