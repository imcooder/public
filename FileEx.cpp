#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>



LONG WINAPI LoadFileA( LPCSTR pszFileName, LPBYTE *ppFileContent)
{
	DWORD dwFileLen = 0;
	FILE *pf = NULL;
	*ppFileContent = NULL;
	pf = fopen( pszFileName, "rb");
	if( NULL == pf )
	{
		return -2;
	}
	fseek( pf, 0, SEEK_END );
	dwFileLen = ftell( pf );	
	*ppFileContent = new BYTE[dwFileLen];		
	if( NULL == *ppFileContent )
	{
		fclose( pf );
		return -1;
	}
	ZeroMemory(*ppFileContent, dwFileLen * sizeof(**ppFileContent));
	fseek( pf, 0, SEEK_SET );
	fread( *ppFileContent, 1, dwFileLen, pf );
	fclose( pf );
	return dwFileLen;
}
LONG WINAPI LoadFileW(LPCWSTR pszFileName, LPBYTE *ppFileContent)
{
	DWORD dwFileLen = 0;
	FILE *pf = NULL;
	*ppFileContent = NULL;
	pf = _wfopen( pszFileName, L"rb");
	if( NULL == pf )
	{
		return -2;
	}
	fseek( pf, 0, SEEK_END );
	dwFileLen = ftell( pf );	
	*ppFileContent = new BYTE[dwFileLen];		
	if( NULL == *ppFileContent )
	{
		fclose( pf );
		return -1;
	}
	ZeroMemory(*ppFileContent, dwFileLen * sizeof(**ppFileContent));
	fseek( pf, 0, SEEK_SET );
	fread( *ppFileContent, 1, dwFileLen, pf );
	fclose( pf );
	return dwFileLen;
}


