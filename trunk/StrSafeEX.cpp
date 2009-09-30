/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	StrSafeEx.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/06/21
*********************************************************************/

#include "stdafx.h"
#include "StrSafeEx.h"
#include <String.h>
#include <wchar.h>


CHAR*		WINAPI StringTokenA( CHAR* pszToken, const CHAR* pszDelimit, CHAR ** pszContext)
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

WCHAR*	WINAPI StringTokenW( WCHAR* pszToken, const WCHAR* pszDelimit, WCHAR ** pszContext)
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



LONG WINAPI StringMidA(LPSTR pszString, LONG nIndex, UINT nCount)
{	 
	LONG nRet = -1;
	if (!pszString)
	{
		return nRet;
	}	
	LONG nLength = (LONG)strlen(pszString);
	assert(nIndex >= 0 && nIndex + (LONG)nCount <= nLength);	
	if (0 != nIndex && nCount > 0)
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
	return nRet;
}
LONG WINAPI StringRightA(LPSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	return StringMidA(pszString, (LONG)strlen(pszString) - nCount, nCount);
}
LONG WINAPI StringLeftA(LPSTR pszString, UINT nCount)
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
void WINAPI StringTrimLeftA(LPSTR pszString, LPCSTR pszTag)
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
	if (nAmount < nLength)
	{
		StringRightA(pszString, nLength - nAmount);
	}	
}

void WINAPI StringTrimRightA(LPSTR pszString, LPCSTR pszTag)
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
		StringLeftA(pszString, nLength - nAmount);
	}
}
void WINAPI StringTrimA(LPSTR pszString, LPCSTR pszTag)
{
	StringTrimLeftA(pszString, pszTag);
	StringTrimRightA(pszString, pszTag);
}

LONG WINAPI StringMidW(LPWSTR pszString, LONG nIndex, UINT nCount)
{	 
	LONG nRet = -1;
	if (!pszString)
	{
		return nRet;
	}	
	LONG nLength = (LONG)wcslen(pszString);
	assert(nIndex >= 0 && nIndex + (LONG)nCount <= nLength);	
	if (0 != nIndex && nCount > 0)
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
	return nRet;
}
LONG WINAPI StringRightW(LPWSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	return StringMidW(pszString, (LONG)_tcslen(pszString) - nCount, nCount);
}
LONG WINAPI StringLeftW(LPWSTR pszString, UINT nCount)
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
void WINAPI StringTrimLeftW(LPWSTR pszString, LPCWSTR pwhTag)
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
	if (nAmount < nLength)
	{
		StringRightW(pszString, nLength - nAmount);
	}	
}
void WINAPI StringTrimRightW(LPWSTR pszString, LPCWSTR pszTag)
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
		StringLeftW(pszString, nLength - nAmount);
	}
}
void WINAPI StringTrimW(LPWSTR pszString, LPCWSTR pszTag)
{
	StringTrimLeftW(pszString, pszTag);
	StringTrimRightW(pszString, pszTag);
}


WCHAR* WINAPI StringUpperW(LPWSTR pszString)
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

CHAR* WINAPI StringUpperA(LPSTR pszString)
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

WCHAR* WINAPI StringLowerW(LPWSTR pszString)
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

CHAR* WINAPI StringLowerA(LPSTR pszString)
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
WCHAR* WINAPI StringReverseW(LPWSTR pszString)
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
CHAR* WINAPI StringReverseA(LPSTR pszString)
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


LONG WINAPI StringWCharToChar(LPCWSTR pszStr, LONG nLen, LPSTR pszString, LONG nMaxLen)
{	
	return WideCharToMultiByte(CP_ACP, 0, pszStr, nLen,  pszString, nMaxLen, 0, 0);		
}

LONG WINAPI StringCharToWChar(LPCSTR pszStr, LONG nLen, LPWSTR pszString, LONG nMaxLen)
{ 
	return 	MultiByteToWideChar(CP_ACP, 0, pszStr, nLen,  pszString, nMaxLen);		
}