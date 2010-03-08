/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	HWStrSafe.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/06/21
*********************************************************************/

#include "stdafx.h"
#include "HWStrSafe.h"
#include <String.h>
#include <wchar.h>

#ifndef _countof
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

CHAR*		WINAPI XUE_StringTokenA( CHAR* pszToken, const CHAR* pszDelimit, CHAR ** pszContext)
{
	CHAR* pszSubStr = NULL;
	if ((!pszToken && pszContext && !*pszContext) || (!pszDelimit) || (!pszContext))
	{
		return pszSubStr;
	}

	CHAR* pszBegin = NULL;
	CHAR* pszEnd = NULL;
	CHAR* pszHeader = NULL;
	CHAR* pszTail = NULL;
	if (pszToken)
	{
		pszBegin = pszToken;
	}
	else
	{
		pszBegin = *pszContext;
	}
	UINT nLen = strlen(pszBegin);
	pszEnd = pszBegin + nLen + 1;
	UINT nHeader = strspn(pszBegin, pszDelimit);
	assert(nHeader <= nLen);
	pszHeader = pszBegin + nHeader;	
	UINT nMiddle = strcspn(pszHeader, pszDelimit);
	pszTail = pszHeader + nMiddle;
	assert(pszHeader <= pszTail);
	if (pszHeader < pszTail)
	{
		pszSubStr = pszHeader;
		if (pszTail < pszEnd)
		{
			*pszTail = 0;
			pszTail ++;			
		}		
		*pszContext = pszTail;	
	}
	else if (pszHeader == pszTail)
	{
		pszSubStr = NULL;
		*pszContext = NULL;
	}
	return pszSubStr;
}

WCHAR*	WINAPI XUE_StringTokenW( WCHAR* pszToken, const WCHAR* pszDelimit, WCHAR ** pszContext)
{
	WCHAR* pszSubStr = NULL;
	if ((!pszToken && pszContext && !*pszContext) || (!pszDelimit) || (!pszContext))
	{
		return pszSubStr;
	}

	WCHAR* pszBegin = NULL;
	WCHAR* pszEnd = NULL;
	WCHAR* pszHeader = NULL;
	WCHAR* pszTail = NULL;
	if (pszToken)
	{
		pszBegin = pszToken;
	}
	else
	{
		pszBegin = *pszContext;
	}
	UINT nLen = wcslen(pszBegin);
	pszEnd = pszBegin + nLen + 1;
	UINT nHeader = wcsspn(pszBegin, pszDelimit);
	assert(nHeader <= nLen);
	pszHeader = pszBegin + nHeader;	
	UINT nMiddle = wcscspn(pszHeader, pszDelimit);
	pszTail = pszHeader + nMiddle;
	assert(pszHeader <= pszTail);
	if (pszHeader < pszTail)
	{
		pszSubStr = pszHeader;
		if (pszTail < pszEnd)
		{
			*pszTail = 0;
			pszTail ++;			
		}		
		*pszContext = pszTail;		
	}
	else if (pszHeader == pszTail)
	{
		pszSubStr = NULL;
		*pszContext = NULL;
	}
	return pszSubStr;	
}



LONG WINAPI XUE_StringMidA(LPSTR pszString, LONG nIndex, UINT nCount)
{	 
	LONG nRet = -1;
	if (!pszString)
	{
		return nRet;
	}	
	LONG nLength = (LONG)strlen(pszString);
	assert(nIndex >= 0 && nIndex + (LONG)nCount <= nLength);	
	if (0 != nIndex && nCount >= 0)
	{
		if (nCount > 0)
		{
			memmove(pszString, pszString + nIndex, nCount * sizeof(*pszString));
			pszString[nCount] = 0;  
#if defined(_DEBUG) || defined(DEBUG)
			{
				if (nIndex + nCount < (LONG)nLength)
				{
					ZeroMemory(pszString + nCount, (nLength - nCount) * sizeof(*pszString));
				}
			}  
#endif
			nRet = (LONG)strlen(pszString);
		}
		else
		{
			pszString[0] = 0;
		}
		
	}  
	return nRet;
}
LONG WINAPI XUE_StringRightA(LPSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	return XUE_StringMidA(pszString, (LONG)strlen(pszString) - nCount, nCount);
}
LONG WINAPI XUE_StringLeftA(LPSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	LONG nLength = (LONG)strlen(pszString);
	if (nLength >= (LONG)nCount)
	{
		pszString[nCount] = 0;
		return (LONG)strlen(pszString);
	}
	return -1;
}
void WINAPI XUE_StringTrimLeftA(LPSTR pszString, LPCSTR pszTag)
{	
	if (!pszTag || !pszString)
	{
		return;
	}   
	if (!pszString[0])
	{
		return;
	}	
	LONG nLength = (LONG)strlen(pszString);
	LONG nAmount = (LONG)strspn(pszString, pszTag);
	if (nAmount <= nLength)
	{
		XUE_StringRightA(pszString, nLength - nAmount);
	}	
}

void WINAPI XUE_StringTrimRightA(LPSTR pszString, LPCSTR pszTag)
{
	if (!pszTag || !pszString)
	{
		return;
	}   
	LONG nAmount = 0;
	BOOL blContinue = TRUE;	
	LONG nLength = (LONG)strlen(pszString);
	for (LONG i = 0; i < nLength && blContinue; i++)
	{    
		if (NULL != strchr(pszTag, pszString[nLength - i - 1]))
		{
			nAmount ++;
		}
		else
		{
			blContinue = FALSE;
		}
	}  
	if (!blContinue || nAmount > 0)
	{
		XUE_StringLeftA(pszString, nLength - nAmount);
	}
}
void WINAPI XUE_StringTrimA(LPSTR pszString, LPCSTR pszTag)
{
	XUE_StringTrimLeftA(pszString, pszTag);
	XUE_StringTrimRightA(pszString, pszTag);
}

LONG WINAPI XUE_StringMidW(LPWSTR pszString, LONG nIndex, UINT nCount)
{	 
	LONG nRet = -1;
	if (!pszString)
	{
		return nRet;
	}	
	LONG nLength = (LONG)wcslen(pszString);
	assert(nIndex >= 0 && nIndex + (LONG)nCount <= nLength);	
	if (0 != nIndex && nCount >= 0)
	{
		if (nCount > 0)
		{
			memmove(pszString, pszString + nIndex, nCount * sizeof(*pszString));
			pszString[nCount] = 0;  
#if defined(_DEBUG) || defined(DEBUG)
			{
				if (nIndex + (LONG)nCount < nLength)
				{
					ZeroMemory(pszString + nCount, (nLength - nCount) * sizeof(*pszString));
				}
			}  
#endif
			nRet = (LONG)wcslen(pszString);
		}
		else
		{
			pszString[0] = 0;
		}		
	}  
	return nRet;
}
LONG WINAPI XUE_StringRightW(LPWSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	return XUE_StringMidW(pszString, (LONG)_tcslen(pszString) - nCount, nCount);
}
LONG WINAPI XUE_StringLeftW(LPWSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	LONG nLength = (LONG)wcslen(pszString);
	if (nLength >= (LONG)nCount)
	{
		pszString[nCount] = 0;
		return (LONG)wcslen(pszString);
	}
	return -1;
}
void WINAPI XUE_StringTrimLeftW(LPWSTR pszString, LPCWSTR pwhTag)
{	
	if (!pwhTag || !pszString)
	{
		return;
	}   
	if (!pszString[0])
	{
		return;
	}	
	LONG nLength = (LONG)wcslen(pszString);
	LONG nAmount = (LONG)wcsspn(pszString, pwhTag);
	if (nAmount <= nLength)
	{
		XUE_StringRightW(pszString, nLength - nAmount);
	}	
}
void WINAPI XUE_StringTrimRightW(LPWSTR pszString, LPCWSTR pszTag)
{
	if (!pszTag || !pszString)
	{
		return;
	}   
	LONG nAmount = 0;
	BOOL blContinue = TRUE;	
	LONG nLength = (LONG)wcslen(pszString);
	for (LONG i = 0; i < nLength && blContinue; i++)
	{    
		if (NULL != wcschr(pszTag, pszString[nLength - i - 1]))
		{
			nAmount ++;
		}
		else
		{
			blContinue = FALSE;
		}
	}  
	if (!blContinue || nAmount > 0)
	{
		XUE_StringLeftW(pszString, nLength - nAmount);
	}
}
void WINAPI XUE_StringTrimW(LPWSTR pszString, LPCWSTR pszTag)
{
	XUE_StringTrimLeftW(pszString, pszTag);
	XUE_StringTrimRightW(pszString, pszTag);
}


WCHAR* WINAPI XUE_StringUpperW(LPWSTR pszString)
{
	assert(pszString);
	if (!pszString)
	{
		return NULL;
	}
	if (!pszString[0])
	{
		return NULL;
	}
	return wcsupr(pszString);
}

CHAR* WINAPI XUE_StringUpperA(LPSTR pszString)
{
	assert(pszString);
	if (!pszString)
	{
		return NULL;
	}
	if (!pszString[0])
	{
		return NULL;
	}
	return _strupr(pszString);
}

WCHAR* WINAPI XUE_StringLowerW(LPWSTR pszString)
{
	assert(pszString);
	if (!pszString)
	{
		return NULL;
	}
	if (!pszString[0])
	{
		return NULL;
	}
	return wcslwr(pszString);
}

CHAR* WINAPI XUE_StringLowerA(LPSTR pszString)
{
	assert(pszString);
	if (!pszString)
	{
		return NULL;
	}
	if (!pszString[0])
	{
		return NULL;
	}
	return _strlwr(pszString);
}
WCHAR* WINAPI XUE_StringReverseW(LPWSTR pszString)
{  
	assert(pszString);
	if (!pszString)
	{
		return NULL;
	}
	if (!pszString[0])
	{
		return NULL;
	}
	return _wcsrev(pszString);
}
CHAR* WINAPI XUE_StringReverseA(LPSTR pszString)
{  
	assert(pszString);
	if (!pszString)
	{
		return NULL;
	}
	if (!pszString[0])
	{
		return NULL;
	}
	return _strrev(pszString);
}


LONG WINAPI XUE_StringWCharToChar(LPCWSTR pszStr, LONG nLen, LPSTR pszString, LONG nMaxLen)
{	
	return WideCharToMultiByte(CP_ACP, 0, pszStr, nLen,  pszString, nMaxLen, 0, 0);		
}

LONG WINAPI XUE_StringCharToWChar(LPCSTR pszStr, LONG nLen, LPWSTR pszString, LONG nMaxLen)
{ 
	return 	MultiByteToWideChar(CP_ACP, 0, pszStr, nLen,  pszString, nMaxLen);		
}
LONG WINAPI XUE_StringToLongW(LPCWSTR pszNum)
{
	LONG nValue = 0;
	if(!pszNum)
	{
		return nValue;
	}
	
	LPCWSTR pwhIndex = wcspbrk(pszNum, L"0123456789.-+");
	if (pwhIndex) 
	{
		swscanf(pwhIndex, L"%ld", &nValue);
	}
	return nValue;
}
LONG WINAPI XUE_StringToLongA(LPCSTR pszNum)
{
	LONG nValue = 0;
	if(!pszNum)
	{
		return nValue;
	}

	LPCSTR pwhIndex = strpbrk(pszNum, "0123456789.-+");
	if (pwhIndex) 
	{
		sscanf(pwhIndex, "%ld", &nValue);
	}
	return nValue;
}
float WINAPI XUE_StringToFloatW(LPCWSTR pszNum)
{
	float flValue = 0.0;
	if(!pszNum)
	{
		return flValue;
	}	
	LPCWSTR pszIndex = wcspbrk(pszNum, L"0123456789.-+");
	if (pszIndex) 
	{
		swscanf(pszIndex, L"%f", &flValue); 
	}
	return flValue;
}

float WINAPI XUE_StringToFloatA(LPCSTR pszNum)
{
	float flValue = 0.0;
	if(!pszNum)
	{
		return flValue;
	}	
	LPCSTR pszIndex = strpbrk(pszNum, "0123456789.-+");
	if (pszIndex) 
	{
		sscanf(pszIndex, "%f", &flValue); 
	}
	return flValue;
}

DWORD WINAPI XUE_StringToDwordW(LPCWSTR pszNum)
{
	DWORD dwValue = 0;
	if(!pszNum)
	{
		return dwValue;
	}	
	LPCWSTR pwhIndex = wcspbrk(pszNum, L"0123456789ABCDEFabcdef");
	if (pwhIndex) 
	{
		swscanf(pwhIndex, L"%x", &dwValue); 
	}
	return dwValue;
}

DWORD WINAPI XUE_StringToDwordA(LPCSTR pszNum)
{
	DWORD dwValue = 0;
	if(!pszNum)
	{
		return dwValue;
	}	
	LPCSTR pwhIndex = strpbrk(pszNum, "0123456789ABCDEFabcdef");
	if (pwhIndex) 
	{
		sscanf(pwhIndex, "%x", &dwValue); 
	}
	return dwValue;
}



LONG WINAPI XUE_tringCchToGuidW(LPCWSTR pszString, LONG nCount, GUID* pGUID)
{
	if (!pszString || nCount < 0 || !pGUID)
	{
		return -1;
	}
	WCHAR szGUID[64] = {0};
	StringCchCopyW(szGUID, _countof(szGUID), pszString);
	XUE_StringTrimW(szGUID, L"{}");
	swscanf(szGUID, TEXT("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X"), &pGUID->Data1, &pGUID->Data2, &pGUID->Data3, &pGUID->Data4[0], &pGUID->Data4[1], &pGUID->Data4[2], &pGUID->Data4[3], &pGUID->Data4[4], &pGUID->Data4[5], &pGUID->Data4[6], &pGUID->Data4[7]);
	return 0;	
}
LONG WINAPI XUE_StringCchToGuidA(LPCSTR pszString, LONG nCount, GUID* pGUID)
{
	WCHAR szGUID[64] = {0};
	if (!pszString || nCount < 0 || !pGUID)
	{
		return -1;
	}
	XUE_StringCharToWChar(pszString, nCount, szGUID, _countof(szGUID));	
	return XUE_tringCchToGuidW(szGUID, _countof(szGUID), pGUID);	
}

LONG WINAPI XUE_StringCchFromGuidW(const GUID* pGUID, LPWSTR pszString, LONG nCount)
{
	if (!pGUID)
	{
		return -1;
	}
	WCHAR szGUID[64] = {0};
	HRESULT  hRes = StringCchPrintfW(szGUID, _countof(szGUID), TEXT("{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}"), pGUID->Data1, pGUID->Data2, pGUID->Data3, pGUID->Data4[0], pGUID->Data4[1], pGUID->Data4[2], pGUID->Data4[3], pGUID->Data4[4], pGUID->Data4[5], pGUID->Data4[6], pGUID->Data4[7]);		
	if (hRes != S_OK)
	{	
		return -1;
	}
	if (pszString && nCount > 0)
	{
		StringCchCopyW(pszString, nCount, szGUID);
		return wcslen(pszString);
	}
	else if(!pszString && !nCount)
	{
		return wcslen(szGUID);
	}
	return -1;
}


LONG WINAPI XUE_StringCchFromGuidA(const GUID* pGUID, LPSTR pszString, LONG nCount)
{
	if (!pGUID)
	{
		return -1;
	}
	WCHAR szGUID[64] = {0};
	LONG nRet = XUE_StringCchFromGuidW(pGUID, szGUID, _countof(szGUID));
	if (!nRet && pszString && nCount > 0)
	{
		XUE_StringWCharToChar(szGUID, wcslen(szGUID), pszString, nCount);
	}
	return nRet;	
}

BOOL WINAPI XUE_StringPathAppendW( LPWSTR pszPath,DWORD dwLen, LPCWSTR pszFile)
{
	if (!pszPath || !pszFile)
	{
		return FALSE;
	}
	WCHAR szPath[MAX_PATH] = {0};
	WCHAR szFile[MAX_PATH] = {0};
	StringCchCopyW(szPath, _countof(szPath), pszPath);
	XUE_StringTrimRightW(szPath, L" \t\\/");
	StringCchCopyW(szFile, _countof(szFile), pszFile);
	XUE_StringTrimLeftW(szFile, L" \t\\/");
	//HWTRACE(TEXT("%s\n"), szFile);
	StringCchCatW(szPath, _countof(szPath), L"\\");
	StringCchCatW(szPath, _countof(szPath), szFile);
	StringCchCopyW(pszPath, dwLen, szPath);
	return TRUE;
}

BOOL WINAPI XUE_StringPathAppendA( LPSTR pszPath,DWORD dwLen, LPCSTR pszFile)
{
	if (!pszPath || !pszFile)
	{
		return FALSE;
	}
	CHAR szPath[MAX_PATH] = {0};
	CHAR szFile[MAX_PATH] = {0};
	StringCchCopyA(szPath, _countof(szPath), pszPath);
	XUE_StringTrimRightA(szPath, " \t\\/");
	StringCchCopyA(szFile, _countof(szFile), pszFile);
	XUE_StringTrimLeftA(szFile, " \t\\/");
	//HWTRACE(TEXT("%s\n"), szFile);
	StringCchCatA(szPath, _countof(szPath), "\\");
	StringCchCatA(szPath, _countof(szPath), szFile);
	StringCchCopyA(pszPath, dwLen, szPath);
	return TRUE;
}
