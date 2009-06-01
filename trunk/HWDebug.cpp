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
#include <XStrHelper.h>
#include <string.h>
#include <Windows.h>

#define LOGINSTANCENAME				_T("HWX_DEBUG_MUTEX")
#define HWFILE_PATH_U					L"c:\\HWLog.log"				
#define HWFILE_PATH						"c:\\HWLog.log"	
void WINAPI		ForceMessageBoxA(LPCSTR);
void WINAPI		ForceMessageBoxW(LPCWSTR);
void WINAPI		DebugStringW(LPCWSTR);
void WINAPI		DebugStringA(LPCSTR);
void WINAPI		DebugStringFileW(LPCWSTR, LPCWSTR);
void WINAPI		DebugStringFileA(LPCSTR, LPCSTR);

//////////////////////////////////////////////////////////////////////////
#ifdef WINCE
//	#pragma comment(lib, "Msgbox.lib")	
#endif			
//////////////////////////////////////////////////////////////////////////
class CLogLock
{
public:
	CLogLock()
		: m_MutexLog(NULL)
	{ //创建Log互斥变量
		m_MutexLog = CreateMutex(NULL, FALSE, LOGINSTANCENAME);
		if (m_MutexLog)
		{
			WaitForSingleObject(m_MutexLog, INFINITE);	
		}		
	}
	~CLogLock()
	{
		if (m_MutexLog)
		{
			ReleaseMutex(m_MutexLog);
			CloseHandle(m_MutexLog);
			m_MutexLog = NULL;
		}  
	}
	CLogLock& GetInstance()
	{
		static CLogLock tLog;
		return tLog;
	}
	BOOL Lock()
	{  
		return WaitForSingleObject(m_MutexLog, INFINITE) == WAIT_OBJECT_0;
	}
	BOOL UnLock()
	{
		return ::ReleaseMutex(m_MutexLog);
	}
protected:
	HANDLE m_MutexLog;
};
///////////////////////////////////////////////////////////////////////////////







void WINAPI XTraceW(LPCWSTR pwhFormat, ...)
{ 	
	WCHAR szBuffer[MAX_SIZE_L] = {0};	
/*
	{
		WCHAR szThreadID[MAX_PATH + MAX_NAME] = {0};
		WCHAR szMuduleName[MAX_NAME] = {0};
		GetModuleFileName(NULL, szMuduleName, MAX_NAME);
		_stprintf_s(szThreadID, _countof(szThreadID), TEXT("%d\tPID:%d TID:%d Name:%s\n"), GetTickCount(), GetCurrentProcessId(), GetCurrentThreadId(), szMuduleName);
		DebugStringW(szThreadID);
	}*/
#ifdef WINCE
	{
		LONG nLen = 0;
		va_list argList;
		va_start(argList, pwhFormat);
		StringCchVPrintfW(szBuffer, _countof(szBuffer), pwhFormat, argList); 
		DebugStringW(szBuffer);
		va_end(argList);	
	}
#else
	{
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
		if (nLen < _countof(szBuffer))
		{
			pwhBuffer = szBuffer;
			StringCchVPrintfW(szBuffer, _countof(szBuffer), pwhFormat, argList); 
			DebugStringW(pwhBuffer);
		}
		else
		{
			if(pwhBuffer = (LPWSTR)_alloca((nLen + 2) * sizeof(WCHAR)))
			{
				StringCchVPrintfW(pwhBuffer, nLen + 1, pwhFormat, argList);
				DebugStringW(pwhBuffer);
			}
		}	
		va_end(argList);	
	}
#endif	
}

void WINAPI XTraceA(LPCSTR pchFormat, ...)
{ 	
	CHAR szBuffer[MAX_SIZE_L];
#ifdef WINCE
	{		
		LONG nLen = 0;
		va_list argList;
		va_start(argList, pchFormat);	

		StringCchVPrintfA(szBuffer, _countof(szBuffer) - 1, pchFormat, argList); 
		DebugStringA(szBuffer);
		va_end(argList);
	}
#else
	{
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
		if (nLen < _countof(szBuffer))
		{
			pchBuffer = szBuffer;
			StringCchVPrintfA(szBuffer, _countof(szBuffer) - 1, pchFormat, argList); 
			DebugStringA(pchBuffer);
		}
		else
		{
			if (pchBuffer = (LPSTR)_alloca((nLen + 2) * sizeof(CHAR)))
			{
				StringCchVPrintfA(pchBuffer, nLen + 1, pchFormat, argList);
				DebugStringA(pchBuffer);
			}			
		}	
		va_end(argList);
	}
#endif
		
}
DLLXEXPORT void WINAPI XTraceExW( BOOL bCondition, LPCWSTR pwhFormat, ... )
{
	if (!bCondition)
	{
		return;
	}
	WCHAR szBuffer[MAX_SIZE_L] = {0};
#ifdef WINCE
	{		
		va_list argList;
		va_start(argList, pwhFormat);
		StringCchVPrintfW(szBuffer, _countof(szBuffer) - 1, pwhFormat, argList); 
		DebugStringW(szBuffer);
		va_end(argList);
	}
#else
	{
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
		if (nLen < _countof(szBuffer))
		{
			pwhBuffer = szBuffer;
			StringCchVPrintfW(szBuffer, _countof(szBuffer) - 1, pwhFormat, argList); 
			DebugStringW(pwhBuffer);
		}
		else
		{
			if(pwhBuffer = (LPWSTR)_alloca((nLen + 2) * sizeof(WCHAR)))
			{
				StringCchVPrintfW(pwhBuffer, nLen + 1, pwhFormat, argList);
				DebugStringW(pwhBuffer);
			}
		}	
		va_end(argList);
	}
#endif
		
}

DLLXEXPORT void WINAPI XTraceExA( BOOL bCondition, LPCSTR pchFormat, ... )
{
	if (bCondition)
	{
		return;
	}	
	CHAR szBuffer[MAX_SIZE_L] = {0};
#ifdef WINCE
	{		
		va_list argList;
		va_start(argList, pchFormat);		
		StringCchVPrintfA(szBuffer, _countof(szBuffer) - 1, pchFormat, argList); 
		DebugStringA(szBuffer);		
		va_end(argList);	
	}
#else
	{
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
		if (nLen < _countof(szBuffer))
		{
			pchBuffer = szBuffer;
			StringCchVPrintfA(szBuffer, _countof(szBuffer) - 1, pchFormat, argList); 
			DebugStringA(pchBuffer);
		}
		else
		{
			if (pchBuffer = (LPSTR)_alloca((nLen + 2) * sizeof(CHAR)))
			{
				StringCchVPrintfA(pchBuffer, nLen + 1, pchFormat, argList);
				DebugStringA(pchBuffer);
			}			
		}	
		va_end(argList);	
	}
#endif			
	
}

void WINAPI XForceTraceW(LPCWSTR pwhFormat, ...)
{ 	
	WCHAR szBuffer[MAX_SIZE_L];
#ifdef WINCE
	{	
		va_list argList;
		va_start(argList, pwhFormat);		
		StringCchVPrintfW(szBuffer, _countof(szBuffer) - 1, pwhFormat, argList); 
		ForceMessageBoxW(szBuffer);		
		va_end(argList);
	}
#else
	{
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
		if (nLen < _countof(szBuffer))
		{
			pwhBuffer = szBuffer;
			StringCchVPrintfW(szBuffer, _countof(szBuffer) - 1, pwhFormat, argList); 
			ForceMessageBoxW(pwhBuffer);
		}
		else
		{
			if(pwhBuffer = (LPWSTR)_alloca((nLen + 2) * sizeof(WCHAR)))
			{
				StringCchVPrintfW(pwhBuffer, nLen + 1, pwhFormat, argList);
				ForceMessageBoxW(pwhBuffer);
			}
		}	
		va_end(argList);
	}
#endif			
		
}

void WINAPI XForceTraceA(LPCSTR pchFormat, ...)
{ 		
	CHAR szBuffer[MAX_SIZE_L];
#ifdef WINCE
	{		
		va_list argList;
		va_start(argList, pchFormat);
		StringCchVPrintfA(szBuffer, _countof(szBuffer) - 1, pchFormat, argList); 
		ForceMessageBoxA(szBuffer);
		va_end(argList);	
	}
#else
	{
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
		if (nLen < MAX_SIZE_L)
		{
			pchBuffer = szBuffer;
			StringCchVPrintfA(szBuffer, _countof(szBuffer) - 1, pchFormat, argList); 
			ForceMessageBoxA(pchBuffer);
		}
		else
		{
			if (pchBuffer = (LPSTR)_alloca((nLen + 2) * sizeof(CHAR)))
			{
				StringCchVPrintfA(pchBuffer, nLen + 1, pchFormat, argList);
				ForceMessageBoxA(pchBuffer);
			}			
		}	
		va_end(argList);	
	}
#endif			
}


void WINAPI ForceMessageBoxA(LPCSTR pszMsg) 
{
	CHAR szTitle[MAX_PATH];	
#ifndef WINCE
	{
		GetModuleFileNameA(NULL, szTitle, MAX_PATH - 1);
		MessageBoxA(GetActiveWindow(), pszMsg, szTitle, MB_OK);
	}	
#endif
}
void WINAPI ForceMessageBoxW(LPCWSTR pszMsg) 
{
	WCHAR szTitle[MAX_PATH];
	GetModuleFileNameW(NULL, szTitle, MAX_PATH - 1);
	MessageBoxW(GetActiveWindow(), pszMsg, szTitle, MB_OK);
}
	
void WINAPI DebugStringW( LPCWSTR pszDebugInfo)
{
	if (!pszDebugInfo)
	{
		return;
	}
#ifdef HWFORCEFILE
	{
		DebugStringFileW(HWFILE_PATH_U, pszDebugInfo);
	}
#else
	{
		OutputDebugStringW(pszDebugInfo);
	}
#endif	
}
void WINAPI DebugStringA( LPCSTR pszDebugInfo)
{
	if (!pszDebugInfo)
	{
		return;
	}
#ifdef HWFORCEFILE
	{
		DebugStringFileA(HWFILE_PATH, pszDebugInfo);
	}
#else
	{
#ifndef WINCE
		{
			OutputDebugStringA(pszDebugInfo);
		}		
#endif
	}
#endif	
}
void WINAPI DebugStringFileW(LPCWSTR pszFile, LPCWSTR pszDebugInfo)
{
	if (!pszDebugInfo)
	{
		return;
	}
	FILE *pFile= NULL;
	pFile = _wfopen(pszFile, L"a");
	if (pFile)
	{
		LPSTR pszContent = WCharToChar(pszDebugInfo);
		if (pszContent)
		{
			CHAR szInfo[MAX_SIZE_S] = {0};
			StringCchPrintfA(szInfo, _countof(szInfo) - 1, "%d\t PID:%d TID:%d\t", GetTickCount(), GetCurrentProcessId(), GetCurrentThreadId());
			fwrite(szInfo, sizeof(CHAR), strlen(szInfo), pFile);
			fwrite(pszContent, sizeof(CHAR), strlen(pszContent), pFile);
			fclose(pFile); 
			pFile = NULL;
			SAFE_DELETE_AR(pszContent);
		}
	}  
}
void WINAPI DebugStringFileA(LPCSTR pszFile, LPCSTR pszDebugInfo)
{
	if (!pszDebugInfo)
	{
		return;
	}
	FILE *pFile= NULL;
	pFile = fopen(pszFile, "a");
	if (pFile)
	{
		CHAR szInfo[MAX_SIZE_S] = {0};
		StringCchPrintfA(szInfo, _countof(szInfo), "%d\t PID:%d TID:%d\t",GetTickCount(), GetCurrentProcessId(), GetCurrentThreadId());
		fwrite(szInfo, sizeof(CHAR), strlen(szInfo), pFile);
		fwrite(pszDebugInfo, sizeof(char), strlen(pszDebugInfo), pFile);
		fclose(pFile); 
		pFile = NULL;
	}  
}

