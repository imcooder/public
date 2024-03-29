
#include "stdafx.h"
#include "HWDeviceID.h"
#include <Iphlpapi.h>
#include <Ext_Type.h>
#include <StrSafe.h>


#define NVIDIA_GUID TEXT("{1A3E09BE-1E45-494B-9174-D7385B45BBF5}")

#ifndef OID_802_3_PERMANENT_ADDRESS
#define OID_802_3_PERMANENT_ADDRESS             0x01010101
#endif

#ifndef IOCTL_NDIS_QUERY_GLOBAL_STATS
#define IOCTL_NDIS_QUERY_GLOBAL_STATS						0x00170002
#endif



//////////////////////////////////////////////////////////////////////////
typedef DWORD (WINAPI *LPGetAdaptersInfo)(PIP_ADAPTER_INFO,PULONG);
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



LONG WINAPI HWGetMAC( LPWSTR pszMac , LONG nMax)
{
	BOOL blFind = FALSE;
	TCHAR szMac[256 + 10] = {0};
	HMODULE	hModuleIphlpapi = NULL;
	LPGetAdaptersInfo pGetAdapterInfo = NULL;

	ULONG nBufferLength = 0;
	BYTE* pBuffer = 0;
	hModuleIphlpapi = LoadLibrary(TEXT("Iphlpapi.dll"));
	if (!hModuleIphlpapi)
	{
		goto	__exit;
	}
	pGetAdapterInfo = (LPGetAdaptersInfo)GetProcAddress(hModuleIphlpapi, "GetAdaptersInfo");
	if (!pGetAdapterInfo)
	{
		goto	__exit;
	}
	if( ERROR_BUFFER_OVERFLOW == pGetAdapterInfo( 0, &nBufferLength ))
	{		
		pBuffer = new BYTE[ nBufferLength ];
		ZeroMemory(pBuffer, sizeof(*pBuffer) * nBufferLength);
	}
	else
	{

	}

	// Get the Adapter Information.
	PIP_ADAPTER_INFO pAdapterInfo =	reinterpret_cast<PIP_ADAPTER_INFO>(pBuffer);
	if (ERROR_SUCCESS == pGetAdapterInfo( pAdapterInfo, &nBufferLength ))
	{
		while( pAdapterInfo && pAdapterInfo->Description[0])
		{		
			TCHAR szPhysicalMAC[20] = {0};
			TCHAR szLogicMAC[20] = {0};
			WCHAR szAdaptrName[256] = {0};
			StringCchPrintf(szLogicMAC, _countof(szLogicMAC), _T("%02X%02X%02X%02X%02X%02X"),	pAdapterInfo->Address[0],	pAdapterInfo->Address[1],	pAdapterInfo->Address[2],	pAdapterInfo->Address[3],	pAdapterInfo->Address[4],	pAdapterInfo->Address[5]);

			MultiByteToWideChar(CP_ACP, 0, pAdapterInfo->AdapterName, strlen(pAdapterInfo->AdapterName),  szAdaptrName, _countof(szAdaptrName));
			DWORD dwError = GetNetAdapterPhysicalMAC(szAdaptrName, szPhysicalMAC, _countof(szPhysicalMAC)); 
			if (dwError)
			{
				//HWTRACE(TEXT("GetPhysicalMAC ERROR %08X %d\n"), dwError, GetLastError());
			}
			if (!szPhysicalMAC[0])
			{
				StringCchCopy(szPhysicalMAC, _countof(szPhysicalMAC), szLogicMAC);
			}
			if (_tcscmp(szPhysicalMAC, TEXT("000000000000")))
			{
				StringCchCat(szMac, _countof(szMac), szPhysicalMAC);			
			}		

			pAdapterInfo = pAdapterInfo->Next;
		}
	}	

	if (pBuffer)
	{
		delete[] pBuffer;
		pBuffer	= NULL;
	}	
__exit:
	pGetAdapterInfo = NULL;
	FreeLibrary(hModuleIphlpapi);
	hModuleIphlpapi = NULL;

	wcsupr(szMac);
	if (!pszMac && !nMax)
	{
		return _tcslen(szMac);
	}
	else if (pszMac && nMax)
	{
		StringCchCopy(pszMac, nMax, szMac);	
		return _tcslen(pszMac);
	}
	return -1;	
}


LONG WINAPI GetNetAdapterPhysicalMAC(WCHAR* strDeviceName, WCHAR* pszMac, LONG nMax)
{
	TCHAR   szDriver[256];  
	BYTE		ucData[8];
	DWORD		ByteRet;	
	WCHAR szPhysicalMAC[32] = {0};
	HANDLE hDriver = INVALID_HANDLE_VALUE;
	StringCchCopyW(szDriver, _countof(szDriver), L"\\\\.\\");
	StringCchCatW(szDriver, _countof(szDriver), strDeviceName);

	hDriver = CreateFileW(szDriver, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);  
	if(INVALID_HANDLE_VALUE == hDriver)  
	{  
		return -1;  
	}  
	ULONG dwID = OID_802_3_PERMANENT_ADDRESS;	
	ZeroMemory(ucData, sizeof(ucData));
	if(!DeviceIoControl(hDriver, IOCTL_NDIS_QUERY_GLOBAL_STATS, &dwID, sizeof(dwID), ucData, sizeof(ucData), &ByteRet, NULL))
	{
		return -2;
	}
	else
	{		
		for (DWORD dwIdx = 0; dwIdx < 6; dwIdx ++)
		{
			WCHAR szCode[8] = {0};
			StringCchPrintfW(szCode, _countof(szCode), L"%02X", ucData[dwIdx]);
			StringCchCatW(szPhysicalMAC, _countof(szPhysicalMAC), szCode);
		}		
	}
	CloseHandle(hDriver);
	hDriver = NULL;

	if (!pszMac && !nMax)
	{
		return wcslen(szPhysicalMAC);
	}
	else if (pszMac && nMax)
	{
		StringCchCopyW(pszMac, nMax, szPhysicalMAC);	
		return wcslen(pszMac);
	}
	return 0;
}

BOOL WINAPI HWIsLocalAdapter(char *pAdapterName)
{
	#define NET_CARD_KEY TEXT("System\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}")
	BOOL ret_value = FALSE;
	TCHAR szDataBuf[MAX_PATH + 1];
	DWORD dwDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	HKEY hNetKey = NULL;
	HKEY hLocalNet = NULL;

	CHAR szBuf[MAX_PATH + 1];

	if(ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, NET_CARD_KEY, 0, KEY_READ, &hNetKey))
	{
		return FALSE;
	}
	StringCchPrintfA(szBuf, _countof(szBuf), "%s\\Connection", pAdapterName);
	if(ERROR_SUCCESS != RegOpenKeyExA(hNetKey ,szBuf ,0 ,KEY_READ, &hLocalNet))
	{
		RegCloseKey(hNetKey);
		return FALSE;
	}

	if (ERROR_SUCCESS != RegQueryValueEx(hLocalNet, L"PnpInstanceID", 0, &dwType, (BYTE *)szDataBuf, &dwDataLen))
	{
		goto ret;
	}
	if (!(!_tcsnicmp(szDataBuf, L"PCI", lstrlen(L"PCI"))  || !_tcsnicmp(szDataBuf, NVIDIA_GUID, lstrlen(NVIDIA_GUID)) || !_tcsnicmp(szDataBuf, L"USB", lstrlen(L"USB"))))
	{
		goto ret;
	}

	ret_value = TRUE;

ret:
	RegCloseKey(hLocalNet);
	RegCloseKey(hNetKey);

	return ret_value;
}