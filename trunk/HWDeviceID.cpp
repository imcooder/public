
#include "stdafx.h"
#include "HWDeviceID.h"
#include <Iphlpapi.h>
#include <Ext_Type.h>
#include <StrSafe.h>

//////////////////////////////////////////////////////////////////////////
typedef DWORD (WINAPI *LPGetAdaptersInfo)(PIP_ADAPTER_INFO,PULONG);
LPGetAdaptersInfo g_pGetAdapterInfo = NULL;
HMODULE						g_hModuleIphlpapi = NULL;
//////////////////////////////////////////////////////////////////////////
static DWORD HWGetAdaptersInfo(PIP_ADAPTER_INFO pAdapterInfo,PULONG pOutBufLen);


LONG WINAPI HWGetMAC( LPWSTR pszMac , LONG nMax)
{
	BOOL blFind = FALSE;
	TCHAR szMac[256 + 10] = {0};

	ULONG nBufferLength = 0;
	BYTE* pBuffer = 0;
	g_hModuleIphlpapi = LoadLibrary(TEXT("Iphlpapi.dll"));
	if (!g_hModuleIphlpapi)
	{
		goto	__exit;
	}
	g_pGetAdapterInfo = (LPGetAdaptersInfo)GetProcAddress(g_hModuleIphlpapi, "GetAdaptersInfo");
	if (!g_pGetAdapterInfo)
	{
		goto	__exit;
	}
	if( ERROR_BUFFER_OVERFLOW == HWGetAdaptersInfo( 0, &nBufferLength ))
	{		
		pBuffer = new BYTE[ nBufferLength ];
		ZeroMemory(pBuffer, sizeof(*pBuffer) * nBufferLength);
	}
	else
	{
		
	}

	// Get the Adapter Information.
	PIP_ADAPTER_INFO pAdapterInfo =	reinterpret_cast<PIP_ADAPTER_INFO>(pBuffer);
	if (ERROR_SUCCESS == HWGetAdaptersInfo( pAdapterInfo, &nBufferLength ))
	{
		while( pAdapterInfo )
		{		
			TCHAR szElement[32] = {0};
			StringCchPrintf(szElement, _countof(szElement), _T("%02X%02X%02X%02X%02X%02X"),	
				pAdapterInfo->Address[0],	pAdapterInfo->Address[1],	pAdapterInfo->Address[2],	
				pAdapterInfo->Address[3],	pAdapterInfo->Address[4],	pAdapterInfo->Address[5]);	
			if (_tcscmp(szElement, TEXT("000000000000")))
			{
				StringCchCat(szMac, _countof(szMac), szElement);			
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
	g_pGetAdapterInfo = NULL;
	FreeLibrary(g_hModuleIphlpapi);
	g_hModuleIphlpapi = NULL;

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

DWORD HWGetAdaptersInfo(PIP_ADAPTER_INFO pAdapterInfo, PULONG pOutBufLen )
{
	if (g_pGetAdapterInfo)
	{
		return g_pGetAdapterInfo(pAdapterInfo, pOutBufLen);
	}
	return ERROR_INVALID_DATA;
}