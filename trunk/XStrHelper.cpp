/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XStrHelper.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/06/21
*********************************************************************/

#include "stdafx.h"
#include <wchar.h>
#include <stdio.h>
#include "XStrHelper.h"
#include <mbstring.h>

void WINAPI Helper_StrChrChrA(LPSTR strString, const CHAR& A, const CHAR& B)
{
  if (!strString)
  {
    return;
  }	
  while (*strString)
  {
    if (A == *strString)
    {
      *strString = B;
    }    		
		strString ++;
  }
}
void WINAPI Helper_StrChrChrW(LPWSTR strString, const WCHAR& A, const WCHAR& B)
{
  if (!strString)
  {
    return;
  }
  while (*strString)
  {
    if (A == *strString)
    {
      *strString = B;
    }		
    strString ++;		
  }
}

LPSTR WINAPI Helper_WCharToChar(LPCWSTR pwszStr)
{
  CHAR *pchString = NULL;
  if (pwszStr)
  {
    LONG nLen = (LONG)wcslen(pwszStr);
    if (nLen > 0)
    {
      LONG nNeedLen = WideCharToMultiByte(CP_ACP, 0, pwszStr, -1, NULL, NULL, NULL, NULL); 
      assert(nNeedLen > 0);
      VERIFY(pchString = new CHAR[nNeedLen + 1]); 
			if (pchString)
			{
				ZeroMemory(pchString, sizeof(*pchString) * (nNeedLen + 1));
				WideCharToMultiByte(CP_ACP, 0, pwszStr, -1,  pchString, nNeedLen + 1, 0 , 0);
				pchString[nNeedLen] = 0; 
			}       
    }
  }  
  return pchString;
}

LPWSTR WINAPI Helper_CharToWChar(LPCSTR pszStr)
{ 
  WCHAR *pwhString = NULL;
  if (pszStr)
  {
    LONG nLen = (LONG)strlen(pszStr);
    if (nLen > 0)
    {
      LONG nNeedLen = MultiByteToWideChar(CP_ACP, 0, pszStr, -1, NULL, NULL); 
      assert(nLen > 0);
      VERIFY(pwhString = new WCHAR[nNeedLen + 1]); 
			if (pwhString)
			{
				ZeroMemory(pwhString, sizeof(*pwhString) * (nNeedLen + 1));
				MultiByteToWideChar(CP_ACP, 0, pszStr,  -1,  pwhString, nNeedLen + 1);
				pwhString[nNeedLen] = 0; 
			}			      
    }
  }    
  return pwhString;
}

LPWSTR WINAPI Helper_StrDupW(LPCWSTR pwStr)
{
  WCHAR *pwhString = NULL;
  if (pwStr)
  {
    LONG nLen = (LONG)wcslen(pwStr);
    if (nLen > 0)
    {
      VERIFY(pwhString = new WCHAR[nLen + 1]); 
			if (pwhString)
			{
				ZeroMemory(pwhString, sizeof(*pwhString) * (nLen + 1));
				wcscpy_s(pwhString, nLen + 1, pwStr);
				pwhString[nLen] = 0;  
			}                
    }
  }    
  return pwhString;
}
LPSTR WINAPI Helper_StrDupA( LPCSTR pszStr)
{
  CHAR *pchString = NULL;
  if (pszStr)
  {
    LONG nLen = (LONG)strlen(pszStr);
    if (nLen > 0)
    {
      VERIFY(pchString = new CHAR[nLen + 1]);
			if (pchString)
			{
				ZeroMemory(pchString, sizeof(*pchString) * (nLen + 1));
				strcpy_s(pchString, nLen + 1, pszStr);      
				pchString[nLen] = 0; 
			}      
    }
  }  
  return pchString;
}


LONG WINAPI Helper_GetPathDirectoryW(LPCWSTR pwhFilePath, LPWSTR szDirectory)
{	
	LONG nLen = 0;
	WCHAR szDir[MAX_DIR] = {0};
	WCHAR szPath[MAX_PATH] = {0};
	if(0 == _wsplitpath_s(pwhFilePath, szPath, MAX_PATH, szDir, MAX_DIR, NULL, 0, NULL, 0))
	{
		wcsncat_s(szPath, MAX_PATH, szDir, _TRUNCATE);
		nLen = (LONG)wcslen(szPath) + 1;		
	}
	if (szDirectory)
	{
		wcscpy_s(szDirectory, nLen, szPath);
	}
	return nLen;
}
LONG WINAPI Helper_GetPathDirectoryA(LPCSTR pchFilePath, LPSTR szDirectory)
{
	LONG nLen = 0;
	CHAR szDir[MAX_DIR] = {0};
	CHAR szPath[MAX_PATH] = {0};
	if(0 == _splitpath_s(pchFilePath, szPath, MAX_PATH, szDir, MAX_DIR, NULL, 0, NULL, 0))
	{
		strncat_s(szPath, MAX_PATH, szDir, _TRUNCATE);		
		nLen = (LONG)strlen(szPath) + 1;
	}
		if (szDirectory)
	{
		strcpy_s(szDirectory, nLen, szPath);
	}
	return nLen;
}
LPSTR WINAPI Helper_StrMoveA(LPSTR pszD, LPCSTR pszSrc)
{
	if (!pszD || !pszSrc)
	{
		return FALSE;
	}
	return (LPSTR)memmove(pszD, pszSrc, (strlen(pszSrc)) + 1 * sizeof(*pszD));	
}
LPWSTR WINAPI Helper_StrMoveW(LPWSTR pszD, LPCWSTR pszSrc)
{
	if (!pszD || !pszSrc)
	{
		return FALSE;
	}
	return (LPWSTR)memmove(pszD, pszSrc, (wcslen(pszSrc)) + 1 * sizeof(*pszD));	
}
LPSTR WINAPI Helper_StrMoveA_S(LPSTR pszD, LONG nLen, LPCSTR pszSrc)
{
	if (!pszD || !pszSrc)
	{
		return FALSE;
	}
	return (LPSTR)memmove(pszD, pszSrc, (strlen(pszSrc)) + 1 * sizeof(*pszD));	
}
LPWSTR WINAPI Helper_StrMoveW_S(LPWSTR pszD, LONG nLen, LPCWSTR pszSrc)
{
	if (!pszD || !pszSrc)
	{
		return FALSE;
	}
	return (LPWSTR)memmove(pszD, pszSrc, (wcslen(pszSrc)) + 1 * sizeof(*pszD));	
}

LONG WINAPI Helper_StrMidW(LPWSTR pszString, LONG nIndex, UINT nCount)
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
			if (nIndex + nCount < nLength)
			{
				ZeroMemory(pszString + nCount, (nLength - nCount) * sizeof(*pszString));
			}
		}  
#endif
		nRet = (LONG)wcslen(pszString);
	}  
	return nRet;
}
LONG WINAPI Helper_StrRightW(LPWSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	return Helper_StrMidW(pszString, (LONG)_tcslen(pszString) - nCount, nCount);
}
LONG WINAPI Helper_StrLeftW(LPWSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	LONG nLength = (LONG)wcslen(pszString);
	if (nLength >= nCount)
	{
			pszString[nCount] = 0;
			return (LONG)wcslen(pszString);
	}
	return -1;
}
void WINAPI Helper_StrTrimLeftW(LPWSTR pszString, LPCWSTR pwhTag)
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
		Helper_StrRightW(pszString, nLength - nAmount);
	}	
}
void WINAPI Helper_StrTrimRightW(LPWSTR pszString, LPCWSTR pszTag)
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
		Helper_StrLeftW(pszString, nLength - nAmount);
	}
}
void WINAPI Helper_StrTrimW(LPWSTR pszString, LPCWSTR pszTag)
{
	Helper_StrTrimLeftW(pszString, pszTag);
	Helper_StrTrimRightW(pszString, pszTag);
}
INT64 WINAPI Helper_StrGetNumberW(LPCWSTR pszString)
{
	if (!pszString)
	{
		return 0;
	}
	if (!pszString[0])
	{
		return 0;
	}

	INT64 nValue = 0;
	LPCWSTR pszIndex = wcspbrk(pszString, L"0123456789-+");
	if (pszIndex) 
	{
		nValue = _wtoi64(pszIndex);
	}
	return nValue;
}

double WINAPI Helper_StrGetFloatW(LPCWSTR pszString)
{
	if (!pszString)
	{
		return 0;
	}
	if (!pszString[0])
	{
		return 0;
	}
	double flValue = 0;
	LPCWSTR pszIndex = wcspbrk(pszString, L"0123456789.-+");
	if (pszIndex) 
	{
		//swscanf_s(pszIndex, L"%30lf", &flValue);
		flValue = _wtof(pszIndex);
	}
	return flValue;
}

LONG WINAPI Helper_StrGetHexW(LPCWSTR pszString)
{
	if (!pszString)
	{
		return 0;
	}
	if (!pszString[0])
	{
		return 0;
	}

	LONG nValue = 0;
	LPCWSTR pszIndex = wcspbrk(pszString, L"0123456789ABCDEFabcdef-+");
	if (pszIndex) 
	{
#if _MSC_VER >= 1000
		swscanf_s(pszIndex, L"%x", &nValue); 
#else
		scanf(pszIndex, L"%x", &nValue);
#endif
	}
	return nValue;
}






LONG WINAPI Helper_StrMidA(LPSTR pszString, LONG nIndex, UINT nCount)
{	 
	LONG nRet = -1;
	if (!pszString)
	{
		return nRet;
	}	
	LONG nLength = (LONG)strlen(pszString);
	assert(nIndex >= 0 && nIndex + nCount <= nLength);	
	if (0 != nIndex && nCount > 0)
	{
		memmove(pszString, pszString + nIndex, nCount * sizeof(*pszString));
		pszString[nCount] = 0;  
#if defined(_DEBUG) || defined(DEBUG)
		{
			if (nIndex + nCount < nLength)
			{
				ZeroMemory(pszString + nCount, (nLength - nCount) * sizeof(*pszString));
			}
		}  
#endif
		nRet = (LONG)strlen(pszString);
	}  
	return nRet;
}
LONG WINAPI Helper_StrRightA(LPSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	return Helper_StrMidA(pszString, (LONG)strlen(pszString) - nCount, nCount);
}
LONG WINAPI Helper_StrLeftA(LPSTR pszString, UINT nCount)
{
	if (!pszString)
	{
		return -1;
	}
	LONG nLength = (LONG)strlen(pszString);
	if (nLength >= nCount)
	{
		pszString[nCount] = 0;
		return (LONG)strlen(pszString);
	}
	return -1;
}
void WINAPI Helper_StrTrimLeftA(LPSTR pszString, LPCSTR pszTag)
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
		Helper_StrRightA(pszString, nLength - nAmount);
	}	
}

void WINAPI Helper_StrTrimRightA(LPSTR pszString, LPCSTR pszTag)
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
		Helper_StrLeftA(pszString, nLength - nAmount);
	}
}
void WINAPI Helper_StrTrimA(LPSTR pszString, LPCSTR pszTag)
{
	Helper_StrTrimLeftA(pszString, pszTag);
	Helper_StrTrimRightA(pszString, pszTag);
}
INT64 WINAPI Helper_StrGetNumberA(LPCSTR pszString)
{
	if (!pszString)
	{
		return 0;
	}
	if (!pszString[0])
	{
		return 0;
	}

	INT64 nValue = 0;
	LPCSTR pszIndex = strpbrk(pszString, "0123456789-+");
	if (pszIndex) 
	{
#if _MSC_VER >= 1000
		sscanf_s(pszIndex, "%I64d", &nValue); 
#else
		sscanf(pszIndex, "%I64d", &nValue);
#endif
	}
	return nValue;
}

double WINAPI Helper_StrGetFloatA(LPCSTR pszString)
{
	if (!pszString)
	{
		return 0;
	}
	if (!pszString[0])
	{
		return 0;
	}

	double flValue = 0.0;
	LPCSTR pszIndex = strpbrk(pszString, "0123456789.-+");
	if (pszIndex) 
	{
#if _MSC_VER >= 1000
		sscanf_s(pszIndex, "%f", &flValue); 
#else
		sscanf(pszIndex, "%f", &flValue); 
#endif
	}
	return flValue;
}

LONG WINAPI Helper_StrGetHexA(LPCSTR pszString)
{
	if (!pszString)
	{
		return 0;
	}
	if (!pszString[0])
	{
		return 0;
	}

	LONG nValue = 0;
	LPCSTR pszIndex = strpbrk(pszString, "0123456789ABCDEFabcdef-+");
	if (pszIndex) 
	{
#if _MSC_VER >= 1000
		scanf_s(pszIndex, "%x", &nValue); 
#else
		scanf(pszIndex, "%x", &nValue);
#endif
	}
	return nValue;
}

void WINAPI Helper_StrUpperW(LPWSTR pszString)
{
	assert(pszString);
	if (pszString)
	{
		return;
	}
	if (pszString[0])
	{
		return;
	}
	 
#if _MSC_VER >= 1400
	LONG nLenght = (LONG)wcslen(pszString);
	_wcsupr_s(pszString, nLenght);
#else
	wcsupr(pszString);
#endif
}

void WINAPI Helper_StrUpperA(LPSTR pszString)
{
	assert(pszString);
	if (pszString)
	{
		return;
	}
	if (pszString[0])
	{
		return;
	}

#if _MSC_VER >= 1400
	LONG nLenght = (LONG)strlen(pszString);
	_strupr_s(pszString, nLenght);
#else
	strupr(pszString);
#endif
}

void WINAPI Helper_StrReverseW(LPWSTR pszString)
{  
	assert(pszString);
	if (pszString)
	{
		return;
	}
	if (pszString[0])
	{
		return;
	}
#if _MSC_VER > 1000
	_wcsrev(pszString);
#else
	wcsrev(pszString);
#endif
}
void WINAPI Helper_StrReverseA(LPSTR pszString)
{  
	assert(pszString);
	if (pszString)
	{
		return;
	}
	if (pszString[0])
	{
		return;
	}
#if _MSC_VER > 1000
	_strrev(pszString);
#else
	strrev(pszString);
#endif
}

void WINAPI Helper_StrReplaceW( LPWSTR pszString, WCHAR A, WCHAR B)
{
	LPWSTR pszA = wcschr(pszString, A);
	while(pszA)
	{
		*pszA ++ = B;		
		pszA = wcschr(pszA, A);
	}
}

void WINAPI Helper_StrReplaceA( LPSTR pszString, CHAR A, CHAR B)
{	
	LPSTR pszA = strchr(pszString, A);
	while(pszA)
	{
		*pszA ++ = B;		
		pszA = strchr(pszA, A);
	}	
}

void WINAPI Helper_StrRemoveW( LPWSTR pszString, WCHAR A)
{
	LPWSTR pszIndexA = pszString, pszIndexB = pszString;
	if (!pszString)
	{
		return;
	}
	while (*pszIndexB)
	{
		if (*pszIndexB != A)
		{
			*pszIndexA = *pszIndexB;
			pszIndexA ++;
		}
		pszIndexB ++;
	}	
	*pszIndexA = 0;
	return;
}

void WINAPI Helper_StrRemoveA( LPSTR pszString, CHAR A)
{	
	LPSTR pszIndexA = pszString, pszIndexB = pszString;
	if (!pszString)
	{
		return;
	}
	while (*pszIndexB)
	{
		if (*pszIndexB != A)
		{
			*pszIndexA = *pszIndexB;
			pszIndexA ++;
		}
		pszIndexB ++;
	}	
	*pszIndexA = 0;
	return;
}