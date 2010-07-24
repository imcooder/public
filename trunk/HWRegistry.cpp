#include "stdafx.h"
#include "HWRegistry.h"
#include <tchar.h>
#include <assert.h>
#include <strsafe.h>
void  WINAPI RegDeleteAllSubKey(HKEY hKey) 
{   
	DWORD   dwCount = 0;   
	TCHAR		szSubkeyName[512];   
	HKEY		hKeySub = NULL; 
	if (!hKey)
	{
		return;
	}
	if(ERROR_SUCCESS != RegQueryInfoKey(hKey, 0, 0, 0, &dwCount, 0, 0, 0, 0, 0, 0, 0))   
	{   		
		return;   
	}   
	else if(dwCount)   
	{
		for(DWORD i = 0; i < dwCount; i ++)   
		{   
			DWORD dwNameLen = _countof(szSubkeyName);
			if(ERROR_SUCCESS != RegEnumKeyEx(hKey, 0, szSubkeyName, &dwNameLen, NULL, NULL, NULL, NULL))   
			{   
				assert(0);  					
				return;   
			}   			
			if(ERROR_SUCCESS != RegOpenKeyEx(hKey, szSubkeyName, 0L, KEY_ALL_ACCESS, &hKeySub))   
			{   
				assert(0);   					
				return;   
			}   			
			RegDeleteAllSubKey(hKeySub);//调用递归
			RegCloseKey(hKeySub);   
			hKeySub = NULL;
			if(ERROR_SUCCESS != RegDeleteKey(hKey, szSubkeyName))   
			{   
				assert(0);   					  
				return;   
			}   			
		}  
	}		
} 


DWORD WINAPI XUE_RegQueryValueDWORD( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue, DWORD dwData )
{
	DWORD dwValue = dwData;
	if (!hKey)
	{
		return dwValue;
	}
	DWORD dwValueSize = 0, dwValueType = 0;
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_READ, &hSubKey))
		{
			if(ERROR_SUCCESS == RegQueryValueEx (hSubKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize) && REG_DWORD == dwValueType)
			{		
				dwValueSize = sizeof(dwValue);
				if (ERROR_SUCCESS != RegQueryValueEx (hSubKey, pszValue, NULL,	&dwValueType, (LPBYTE)&dwValue, &dwValueSize))
				{
					dwValue = dwData;
				}					
			}
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{
		if(ERROR_SUCCESS == RegQueryValueEx (hKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize) && REG_DWORD == dwValueType)
		{		
			dwValueSize = sizeof(dwValue);
			if (ERROR_SUCCESS != RegQueryValueEx (hKey, pszValue, NULL,	&dwValueType, (LPBYTE)&dwValue, &dwValueSize))
			{
				dwValue = dwData;
			}					
		}
	}	
	return dwValue;
}

BOOL WINAPI XUE_RegSetValueDWORD( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue, DWORD dwData )
{	
	BOOL blRet = FALSE;
	if (!hKey)
	{
		return blRet;
	}	
	if (pszSubKey && _tcslen(pszSubKey))
	{			
		HKEY hSubKey = NULL;
		DWORD dwTmp = 0;
		if (ERROR_SUCCESS == RegCreateKeyEx(hKey, pszSubKey, 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 	NULL, &hSubKey, &dwTmp))
		{			
			if(ERROR_SUCCESS == ::RegSetValueEx (hSubKey, pszValue, 0L, REG_DWORD, (LPBYTE) &dwData, sizeof(dwData)))
			{
				blRet = TRUE;
			}		
			RegFlushKey(hSubKey);
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{		
		if(ERROR_SUCCESS == ::RegSetValueEx (hKey, pszValue, 0L, REG_DWORD, (LPBYTE) &dwData, sizeof(dwData)))		
		{
			blRet = TRUE;
			RegFlushKey(hKey);
		}
	}		
	return blRet;
}

BOOL		WINAPI XUE_RegSetValueString( HKEY hKey , LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszData )
{
	BOOL blRet = FALSE;
	if (!hKey || !pszData)
	{
		return blRet;
	}	
	if (pszSubKey && _tcslen(pszSubKey))
	{			
		HKEY hSubKey = NULL;
		DWORD dwTmp = 0;
		if (ERROR_SUCCESS == RegCreateKeyEx(hKey, pszSubKey, 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,	NULL, &hSubKey, &dwTmp))
		{
			DWORD dwSize = (_tcslen(pszData) + 1) * sizeof(*pszData);
			if(ERROR_SUCCESS == ::RegSetValueEx (hSubKey, pszValue, 0L, REG_SZ, (LPBYTE)pszData, dwSize))
			{
				blRet = TRUE;
			}
			RegFlushKey(hSubKey);
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{
		DWORD dwSize = (_tcslen(pszData) + 1) * sizeof(*pszData);
		if(ERROR_SUCCESS == ::RegSetValueEx (hKey, pszValue, 0L, REG_SZ, (LPBYTE) pszData, dwSize))		
		{
			blRet = TRUE;
			RegFlushKey(hKey);
		}
	}	
	return blRet;
}

DWORD		WINAPI XUE_RegQueryValueString( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszDefData, LPTSTR pszData, DWORD dwCount )
{	
	//内部最多支持512个字符 否则不能读取真实的值
	TCHAR szData[512] = {0};		
	if (!hKey || !pszData || dwCount <= 0)
	{
		return 0;
	}
	if (pszDefData)
	{
		StringCchCopy(szData, _countof(szData), pszDefData);
	}
	
	DWORD dwValueSize = 0, dwValueType = 0;
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_READ, &hSubKey))
		{
			if(ERROR_SUCCESS == RegQueryValueEx (hSubKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize) && REG_SZ == dwValueType)
			{		
				if (dwValueSize <= sizeof(szData))
				{					
					dwValueSize = sizeof(szData);
					RegQueryValueEx (hSubKey, pszValue, NULL,	&dwValueType, (LPBYTE)szData, &dwValueSize);					
				}						
			}
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{
		if(ERROR_SUCCESS == RegQueryValueEx (hKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize) && REG_SZ == dwValueType)
		{		
			if (dwValueSize <= sizeof(szData))
			{					
				dwValueSize = sizeof(szData);
				RegQueryValueEx (hKey, pszValue, NULL,	&dwValueType, (LPBYTE)szData, &dwValueSize);					
			}						
		}
	}	
	StringCchCopy(pszData, dwCount, szData);
	return _tcslen(pszData);
}

BOOL		WINAPI XUE_RegSetValueBinary( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue, const BYTE* pbData, DWORD dwByte )
{
	BOOL blRet = FALSE;
	if (!hKey || !pbData || dwByte <= 0)
	{
		return blRet;
	}	
	if (pszSubKey && _tcslen(pszSubKey))
	{			
		HKEY hSubKey = NULL;
		DWORD dwTmp = 0;
		if (ERROR_SUCCESS == RegCreateKeyEx(hKey, pszSubKey, 0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,	NULL, &hSubKey, &dwTmp))
		{			
			if(ERROR_SUCCESS == ::RegSetValueEx (hSubKey, pszValue, 0L, REG_BINARY, (LPBYTE)pbData, dwByte))
			{
				blRet = TRUE;
			}
			RegFlushKey(hSubKey);
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{		
		if(ERROR_SUCCESS == ::RegSetValueEx (hKey, pszValue, 0L, REG_BINARY, (LPBYTE) pbData, dwByte))		
		{
			blRet = TRUE;
			RegFlushKey(hKey);
		}
	}	
	return blRet;
}

DWORD		WINAPI XUE_RegQueryValueBinary( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue, const BYTE* pbDefData, DWORD dwDefSize, BYTE* pbData, DWORD dwCount )
{
	//内部最多支持1024Byte 否则不能读取真实的值
	BYTE abData[1024] = {0};	
	ZeroMemory(abData, sizeof(abData));
	DWORD dwRet = 0;
	if (!hKey || !pbData || dwCount <= 0)
	{
		return dwRet;
	}
	if (pbDefData && dwDefSize > 0)
	{
		dwRet = _min(dwDefSize, sizeof(abData));
		memcpy(abData, pbDefData, dwRet);
	}

	DWORD dwValueSize = 0, dwValueType = 0;
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_READ, &hSubKey))
		{
			if(ERROR_SUCCESS == RegQueryValueEx (hSubKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize) && REG_BINARY == dwValueType)
			{		
				if (dwValueSize <= sizeof(abData))
				{					
					dwValueSize = sizeof(abData);
					RegQueryValueEx (hSubKey, pszValue, NULL,	&dwValueType, (LPBYTE)abData, &dwValueSize);		
					dwRet = dwValueSize;
				}						
			}
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{
		if(ERROR_SUCCESS == RegQueryValueEx (hKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize) && REG_BINARY == dwValueType)
		{		
			if (dwValueSize <= sizeof(abData))
			{					
				dwValueSize = sizeof(abData);
				RegQueryValueEx (hKey, pszValue, NULL,	&dwValueType, (LPBYTE)abData, &dwValueSize);		
				dwRet = dwValueSize;
			}						
		}
	}	
	dwRet = _min(dwRet, dwCount);
	memcpy(pbData, abData, dwRet);
	return dwRet;
}

BOOL		WINAPI XUE_RegDeleteValue( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue )
{	
	BOOL blRet = TRUE;
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_ALL_ACCESS, &hSubKey))
		{
			if (ERROR_SUCCESS != RegDeleteValue(hSubKey, pszValue))
			{
				blRet = FALSE;				
			}			
			RegFlushKey(hSubKey);
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{
		if (ERROR_SUCCESS != RegDeleteValue(hKey, pszValue))
		{
			blRet = FALSE;			
			RegFlushKey(hKey);
		}	
	}	
	return blRet;
}

BOOL		WINAPI XUE_RegDeleteKey( HKEY hKey, LPCTSTR pszSubKey )
{		
	BOOL blRet = FALSE;	
	if (!pszSubKey || !hKey)
	{		
		return FALSE;
	}	
	HKEY hSubKey = NULL;
	if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_ALL_ACCESS, &hSubKey))
	{
		RegDeleteAllSubKey(hSubKey);
		RegCloseKey(hSubKey);
		hSubKey = NULL;
		if (ERROR_SUCCESS == RegDeleteKey(hKey, pszSubKey))
		{
			blRet = TRUE;		
		}
	}	
	return blRet;	
}

BOOL		WINAPI XUE_RegIsKeyExists( HKEY hKey, LPCTSTR pszSubKey )
{	
	BOOL blRet = FALSE;
	if (!hKey)
	{
		return blRet;
	}	
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_READ, &hSubKey))
		{			
			RegCloseKey(hSubKey);
			hSubKey = NULL;
			blRet = TRUE;
		}			
	}
	else
	{
		blRet = TRUE;			
	}	
	return blRet;
}

BOOL		WINAPI XUE_RegIsValueExists( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue )
{
	BOOL blRet = FALSE;
	if (!hKey)
	{
		return blRet;
	}	
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_READ, &hSubKey))
		{
			DWORD dwValueType = REG_NONE, dwValueSize = 0;
			if(ERROR_SUCCESS == RegQueryValueEx (hSubKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize))
			{		
				blRet = TRUE;								
			}
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{
		DWORD dwValueType = REG_NONE, dwValueSize = 0;
		if(ERROR_SUCCESS == RegQueryValueEx (hKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize))
		{		
			blRet = TRUE;					
		}
	}	
	return blRet;
}

DWORD		WINAPI XUE_RegQueryValueType( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue )
{	
	DWORD dwValueSize = 0, dwValueType = REG_NONE;
	if (!hKey)
	{
		return dwValueType;
	}
	
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_READ, &hSubKey))
		{
			if(ERROR_SUCCESS == RegQueryValueEx (hSubKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize))
			{						
							
			}
			else
			{
				dwValueType = REG_NONE;
			}
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{
		if(ERROR_SUCCESS == RegQueryValueEx (hKey, pszValue, NULL,	&dwValueType, NULL, &dwValueSize))
		{		
					
		}
		else
		{
			dwValueType = REG_NONE;
		}
	}	
	return dwValueType;
}

BOOL		WINAPI XUE_RegIsValueDWORD( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue )
{
	return REG_DWORD == XUE_RegQueryValueType(hKey, pszSubKey, pszValue);
}

BOOL		WINAPI XUE_RegIsValueString( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue )
{
	return REG_SZ == XUE_RegQueryValueType(hKey, pszSubKey, pszValue);
}

BOOL		WINAPI XUE_RegIsValueBinary( HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValue )
{
	return REG_BINARY == XUE_RegQueryValueType(hKey, pszSubKey, pszValue);
}
BOOL		WINAPI RegDeleteAllValue( HKEY hKey)
{
	BOOL blRet = TRUE;
	DWORD   dwCount = 0;   
	TCHAR		szValueName[512]; 	
	if (!hKey)
	{
		blRet = FALSE;
		return blRet;
	}
	if(ERROR_SUCCESS != RegQueryInfoKey(hKey, 0, 0, 0, 0, 0, 0, &dwCount, 0, 0, 0, 0))   
	{   
		blRet = FALSE;
		return blRet;   
	}   
	else if(dwCount)   
	{
		for(DWORD i = 0; i < dwCount; i ++)   
		{   		
			DWORD dwValueLen = _countof(szValueName);
			if(ERROR_SUCCESS != RegEnumValue(hKey, 0, szValueName, &dwValueLen, NULL, NULL, NULL, NULL))   
			{   
				blRet = FALSE;
				assert(0);  					
				return blRet;   
			}   			
			if(ERROR_SUCCESS != RegDeleteValue(hKey, szValueName))   
			{   
				if (blRet)
				{
					blRet = FALSE;
				}
				assert(0);   					
				return blRet;   
			}  					
		}  
	}	
	return blRet;
}

BOOL		WINAPI XUE_RegDeleteAllValue( HKEY hKey, LPCTSTR pszSubKey )
{
	DWORD   dwCount = 0;  	
	if (!hKey)
	{
		return FALSE;
	}
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_READ, &hSubKey))
		{
			RegDeleteAllValue(hSubKey);
			RegCloseKey(hSubKey);
			hSubKey = NULL;
		}			
	}
	else
	{
		RegDeleteAllValue(hKey);	
	}	
	return TRUE;
}


BOOL		WINAPI XUE_RegDeleteAllSubKey( HKEY hKey, LPCTSTR pszSubKey )
{
	DWORD   dwCount = 0;  		
	if (!hKey)
	{
		return FALSE;
	}
	if (pszSubKey && _tcslen(pszSubKey))
	{				
		HKEY hSubKey = NULL;
		if (ERROR_SUCCESS == RegOpenKeyEx (hKey, pszSubKey, 0L, KEY_READ, &hSubKey))
		{
			RegDeleteAllSubKey(hSubKey);
			RegCloseKey(hSubKey);
			hSubKey = NULL;		 
		}			
	}
	else
	{
		RegDeleteAllSubKey(hKey);	
	}	
	return TRUE;
}
