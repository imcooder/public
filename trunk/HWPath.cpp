#include "stdafx.h"
#include "HWPath.h"
#include "XStrhelper.h"


DLLXEXPORT BOOL WINAPI HWPathAppend( LPWSTR pszPath, LPCWSTR pszFile)
{
	TCHAR szPath[MAX_PATH] = {0};
	if (!pszPath)
	{
		return FALSE;
	}
	StringCchCopy(szPath, _countof(szPath), pszPath);
	if (HWPathAppend_s(szPath, _countof(szPath), pszFile))
	{
		wcscpy(pszPath, szPath);
		return TRUE;
	}	
	return FALSE;
}

DLLXEXPORT BOOL WINAPI HWPathAppend_s( LPWSTR pszPath,DWORD dwLen, LPCWSTR pszFile)
{
	if (!pszPath || !pszFile)
	{
		return FALSE;
	}
	WCHAR szPath[MAX_PATH] = {0};
	WCHAR szFile[MAX_PATH] = {0};
	StringCchCopy(szPath, _countof(szPath), pszPath);
	StrTrimRight(szPath, L" \t\\/");
	StringCchCopy(szFile, _countof(szFile), pszFile);
	StrTrimLeft(szFile, L" \t\\/");
	//HWTRACE(TEXT("%s\n"), szFile);
	StringCchCat(szPath, _countof(szPath), L"\\");
	StringCchCat(szPath, _countof(szPath), szFile);
	StringCchCopy(pszPath, dwLen, szPath);
	return TRUE;
}
