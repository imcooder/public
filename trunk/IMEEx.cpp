
#include "stdafx.h"

#include "IMEEx.h"


HKL WINAPI GetHKLByIMEFileName(LPCTSTR pszFileName)
{
	DWORD dwSize;
	DWORD dwi;
	HKL hKL = 0;
	HKL *lphkl;

	dwSize = GetKeyboardLayoutList(0, NULL);

	lphkl = (HKL *)GlobalAlloc(GPTR, dwSize * sizeof(DWORD));

	if (!lphkl)
	{
		return NULL;
	}

	GetKeyboardLayoutList(dwSize, lphkl);


	for (dwi = 0; dwi < dwSize; dwi++)
	{
		TCHAR szFile[32];
		HKL hKLTemp = *(lphkl + dwi);
		ImmGetIMEFileName(hKLTemp, szFile, sizeof(szFile));

		if (!_tcsicmp(szFile, pszFileName))
		{
			hKL = hKLTemp;
			break;
		}
	}
	GlobalFree((HANDLE)lphkl);
	return hKL;
}

DWORD WINAPI FindIME(LPCTSTR pszLayoutFile) 
{   
	DWORD   dwCount = 0;   
	TCHAR		szSubkeyName[MAX_SIZE_M];   
	HKEY		hKeySub = NULL; 
	HKEY		hKey = NULL;	
	DWORD		dwDisposition = 0;
	TCHAR		szLayoutFile[MAX_NAME] = {0};
	DWORD		dwKLID = 0;
	if ( RegOpenKeyEx(HKEY_LOCAL_MACHINE,	_T("System\\CurrentControlSet\\Control\\Keyboard Layouts"), 0,	KEY_READ,	&hKey) != ERROR_SUCCESS )
	{		
		HWTRACE(TEXT("FindIME: RegOpenKeyEx System\\CurrentControlSet\\Control\\Keyboard Layouts Error\n"));
		return dwKLID;
	}
	if (!hKey)
	{
		HWTRACE(TEXT("FindIME: !hKey\n"));
		return dwKLID;
	}
	if(ERROR_SUCCESS != RegQueryInfoKey(hKey, 0, 0, 0, &dwCount, 0, 0, 0, 0, 0, 0, 0))   
	{   	
		SAFE_REG_CLOSEKEY(hKey);  
		return dwKLID;   
	}  
	for(DWORD dwIdx = 0; dwIdx < dwCount; dwIdx ++)   
	{   		 
		if(ERROR_SUCCESS == RegEnumKey(hKey, dwIdx, szSubkeyName, _countof(szSubkeyName)))   
		{   		
			if(ERROR_SUCCESS == RegOpenKey(hKey, szSubkeyName, &hKeySub))   
			{   
				DWORD dwType;
				DWORD dwSize = sizeof(szLayoutFile);
				if(ERROR_SUCCESS == RegQueryValueEx (hKeySub, TEXT("IME file"), NULL, &dwType, (BYTE *)szLayoutFile, &dwSize) && REG_SZ == dwType)
				{
					if (0 == lstrcmpi(szLayoutFile, pszLayoutFile))
					{
						_stscanf_s(szSubkeyName, TEXT("%08X"), &dwKLID);
						break;
					}
				}	
				LONG n = 0;
			}  				
		} 			 
		SAFE_REG_CLOSEKEY(hKeySub);  			
	} 			
	SAFE_REG_CLOSEKEY(hKey); 
	return dwKLID;
} 