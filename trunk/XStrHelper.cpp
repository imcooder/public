/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XStrHelper.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/06/21
*********************************************************************/

#include "stdafx.h"
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
		wcscat_s(szPath, MAX_PATH, szDir);
		nLen = wcslen(szPath) + 1;		
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
		strcat_s(szPath, szDir);		
		nLen = strlen(szPath) + 1;
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
	return (LPSTR)memmove_s(pszD, nLen * sizeof(*pszD), pszSrc, (strlen(pszSrc)) + 1 * sizeof(*pszD));	
}
LPWSTR WINAPI Helper_StrMoveW_S(LPWSTR pszD, LONG nLen, LPCWSTR pszSrc)
{
	if (!pszD || !pszSrc)
	{
		return FALSE;
	}
	return (LPWSTR)memmove_s(pszD, nLen * sizeof(*pszD), pszSrc, (wcslen(pszSrc)) + 1 * sizeof(*pszD));	
}