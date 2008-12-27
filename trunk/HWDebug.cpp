/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XDebug.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/10/06
*********************************************************************/
#include "stdafx.h"
#include "HWDebug.h"
#include <stdio.h>
#include <memory>

void WINAPI		ForceMessageBoxA(LPCSTR);
void WINAPI		ForceMessageBoxW(LPCWSTR);

void WINAPI XTraceW(LPCWSTR pwhFormat, ...)
{ 
	const LONG cnMaxLen = 1024;
	WCHAR athBuffer[cnMaxLen];
	LPWSTR pwhBuffer = NULL;	
	
	LONG nLen = 0;
	va_list argList;
	va_start(argList, pwhFormat);
	nLen = _vscwprintf(pwhFormat, argList);
	if (nLen	< 0)
	{
		va_end(argList);	
		return;
	}
	if (nLen < cnMaxLen)
	{
		pwhBuffer = athBuffer;
		vswprintf_s(pwhBuffer, cnMaxLen - 1, pwhFormat, argList); 
		OutputDebugStringW(pwhBuffer);
	}
	else
	{
		if(pwhBuffer = (LPWSTR)_alloca((nLen + 2) * sizeof(WCHAR)))
		{
			vswprintf_s(pwhBuffer, nLen + 1, pwhFormat, argList);
			OutputDebugStringW(pwhBuffer);
		}
	}	
	va_end(argList);	
}

void WINAPI XTraceA(LPCSTR pchFormat, ...)
{ 	
	const LONG cnMaxLen = 1024;
	CHAR athBuffer[cnMaxLen];
	LPSTR pchBuffer = NULL;	

	LONG nLen = 0;
	va_list argList;
	va_start(argList, pchFormat);
	nLen = _vscprintf(pchFormat, argList);
	if (nLen	< 0)
	{
		va_end(argList);	
		return;
	}
	if (nLen < cnMaxLen)
	{
		pchBuffer = athBuffer;
		vsprintf_s(pchBuffer, cnMaxLen - 1, pchFormat, argList); 
		OutputDebugStringA(pchBuffer);
	}
	else
	{
		if (pchBuffer = (LPSTR)_alloca((nLen + 2) * sizeof(CHAR)))
		{
			vsprintf_s(pchBuffer, nLen + 1, pchFormat, argList);
			OutputDebugStringA(pchBuffer);
		}			
	}	
	va_end(argList);	
}


void WINAPI XForceTraceW(LPCWSTR pwhFormat, ...)
{ 
	const LONG cnMaxLen = 1024;
	WCHAR athBuffer[cnMaxLen];
	LPWSTR pwhBuffer = NULL;	

	LONG nLen = 0;
	va_list argList;
	va_start(argList, pwhFormat);
	nLen = _vscwprintf(pwhFormat, argList);
	if (nLen	< 0)
	{
		va_end(argList);	
		return;
	}
	if (nLen < cnMaxLen)
	{
		pwhBuffer = athBuffer;
		vswprintf_s(pwhBuffer, cnMaxLen - 1, pwhFormat, argList); 
		ForceMessageBoxW(pwhBuffer);
	}
	else
	{
		if(pwhBuffer = (LPWSTR)_alloca((nLen + 2) * sizeof(WCHAR)))
		{
			vswprintf_s(pwhBuffer, nLen + 1, pwhFormat, argList);
			ForceMessageBoxW(pwhBuffer);
		}
	}	
	va_end(argList);	
}

void WINAPI XForceTraceA(LPCSTR pchFormat, ...)
{ 	
	const LONG cnMaxLen = 1024;
	CHAR athBuffer[cnMaxLen];
	LPSTR pchBuffer = NULL;	

	LONG nLen = 0;
	va_list argList;
	va_start(argList, pchFormat);
	nLen = _vscprintf(pchFormat, argList);
	if (nLen	< 0)
	{
		va_end(argList);	
		return;
	}
	if (nLen < cnMaxLen)
	{
		pchBuffer = athBuffer;
		vsprintf_s(pchBuffer, cnMaxLen - 1, pchFormat, argList); 
		ForceMessageBoxA(pchBuffer);
	}
	else
	{
		if (pchBuffer = (LPSTR)_alloca((nLen + 2) * sizeof(CHAR)))
		{
			vsprintf_s(pchBuffer, nLen + 1, pchFormat, argList);
			ForceMessageBoxA(pchBuffer);
		}			
	}	
	va_end(argList);	
}


void WINAPI ForceMessageBoxA(LPCSTR pszMsg) 
{
	CHAR szTitle[MAX_PATH];
	GetModuleFileNameA(NULL, szTitle, MAX_PATH - 1);
	MessageBoxA(GetActiveWindow(), pszMsg, szTitle, MB_OK);
}
void WINAPI ForceMessageBoxW(LPCWSTR pszMsg) 
{
	WCHAR szTitle[MAX_PATH];
	GetModuleFileNameW(NULL, szTitle, MAX_PATH - 1);
	MessageBoxW(GetActiveWindow(), pszMsg, szTitle, MB_OK);
}
