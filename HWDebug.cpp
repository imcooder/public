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
#include <StrSafe.h>

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

static BOOL WINAPI CreateDir(HWX_IN LPCWSTR pwhDstFilePath );

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

#ifndef WINCE
void WINAPI XTraceA(LPCSTR pchFormat, ...)
{ 	
	CHAR szBuffer[MAX_SIZE_L];

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
#ifndef WINCE
DLLXEXPORT void WINAPI XTraceExA( BOOL bCondition, LPCSTR pchFormat, ... )
{
	if (bCondition)
	{
		return;
	}	
	CHAR szBuffer[MAX_SIZE_L] = {0};

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
#ifndef WINCE
void WINAPI XForceTraceA(LPCSTR pchFormat, ...)
{ 		
	CHAR szBuffer[MAX_SIZE_L];
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

#ifndef WINCE
void WINAPI ForceMessageBoxA(LPCSTR pszMsg) 
{
	CHAR szTitle[MAX_PATH];	
	GetModuleFileNameA(NULL, szTitle, MAX_PATH - 1);
	MessageBoxA(GetActiveWindow(), pszMsg, szTitle, MB_OK);
}
#endif
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
#ifndef WINCE
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
		OutputDebugStringA(pszDebugInfo);
	}
#endif	
}
#endif


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



void GetDefLogFileName(LPTSTR szFileName) 
{
	TCHAR wszExecutableFilePath[MAX_PATH];
	::GetModuleFileName(NULL, wszExecutableFilePath, MAX_PATH);
#ifdef STLOG_CREATE_FILE_IN_THE_SAME_DIRECTORY
	TCHAR *wszExecutableFileName = wszExecutableFilePath;
#else

#ifdef _WIN32_WCE
	TCHAR *wszExecutableFileName = ::_tcsrchr(wszExecutableFilePath, _T('\\'));
#else
	//For desktop systems we need to create a log on the system's windows drive
	TCHAR wszExecutableFileName[MAX_PATH+1];
	::GetWindowsDirectory(wszExecutableFileName, MAX_PATH+1); //This will create a string with start "c:\"
	TCHAR *pcFirstSlash = _tcschr(wszExecutableFileName, _T('\\'));
	TCHAR *pcLastSlash = ::_tcsrchr(wszExecutableFilePath, _T('\\'));
	//copy the name of the executable to the string containing 
	_tcscpy(pcFirstSlash, pcLastSlash); 
#endif

#endif

	TCHAR *wszLastDot = ::_tcsrchr(wszExecutableFileName, _T('.'));

#ifdef STLOG_CREATE_NEW
	BOOL bFound = FALSE;
	int nFreeNumber = 0;
	TCHAR wszTemp[MAX_PATH];

	while (!bFound) {

		_stprintf(wszTemp, _T("_log%02d.txt"), nFreeNumber);
		::_tcscpy(wszLastDot, wszTemp);
		if (0xFFFFFFFF == ::GetFileAttributes(wszExecutableFileName))
		{
			bFound = TRUE;
		} else {
			nFreeNumber++;
		}
	}

#else 
	::_tcscpy(wszLastDot, _T("_log.txt"));
#endif 

	::_tcscpy(szFileName, wszExecutableFileName);
}


HWLogFile::HWLogFile()
{
	StringCchCopy(m_szFile, _countof(m_szFile), HWTRACEFILE_PATH);
	InitializeCriticalSection(&m_CS);
	EnterCriticalSection(&m_CS);
	CreateDir(m_szFile);
#ifdef HWTRACEFILE_DELETE_OLD
	DeleteFile(m_szFile);
#endif
	m_hFile = ::CreateFile(m_szFile, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,	OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	HRESULT hr = GetLastError();
	if (m_hFile != INVALID_HANDLE_VALUE)
	{
		Log(1," =============================================");
		TCHAR szExecutable[MAX_PATH];
		GetModuleFileName(NULL, szExecutable, MAX_PATH);
		DWORD dwProcID = GetCurrentProcessId();
		SYSTEMTIME st;
		GetLocalTime(&st);
		Log(1, "Log is started on %02u.%02u.%04u, at %02u:%02u:%02u:%03u, executable: %s (ProcID: 0x%08x), compile time : %s %s", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, szExecutable, dwProcID, __DATE__ , __TIME__);
	}
	LeaveCriticalSection(&m_CS);
}

HWLogFile::~HWLogFile()
{
	SAFE_CLOSE_HANDLE(m_hFile);
	::DeleteCriticalSection(&m_CS);
}

void HWLogFile::Log( BOOL bCondition, LPCWSTR pszFormat, ... )
{
	EnterCriticalSection(&m_CS);
	if (bCondition)
	{
		WCHAR szBuffer[MAX_SIZE_LL] = {0};	
		CHAR szBufferEx[MAX_SIZE_LL] = {0};
		va_list argList;
		va_start(argList, pszFormat);
		LONG nERR = StringCchVPrintfW(szBuffer, _countof(szBuffer), pszFormat, argList); 		
		va_end(argList);	
		if (SUCCEEDED(nERR))
		{
			LONG nLen = wcstombs(NULL, szBuffer, 0);
			if (nLen + 1 < _countof(szBufferEx))
			{
				wcstombs(szBufferEx, szBuffer, _countof(szBufferEx));
				Write(szBufferEx);		
			}
			else
			{
				CHAR *pAnsiString = (CHAR*)_alloca(nLen + 1);
				if (pAnsiString)
				{
					wcstombs(pAnsiString, szBuffer, nLen + 1);
					Write(pAnsiString);	
				}		
			}				
		}		
	}
	LeaveCriticalSection(&m_CS);
}
void HWLogFile::Log( BOOL bCondition, LPCSTR pszFormat, ... )
{
	EnterCriticalSection(&m_CS);
	if (bCondition)
	{	
		CHAR szBuffer[MAX_SIZE_LL] = {0};				
		va_list argList;
		va_start(argList, pszFormat);
		StringCchVPrintfA(szBuffer, _countof(szBuffer), pszFormat, argList); 
		Write(szBuffer);
		va_end(argList);	
	}
	LeaveCriticalSection(&m_CS);
}

void HWLogFile::LogData(BOOL bCondition, LPCVOID pBytes, DWORD dwSize) 
{
	EnterCriticalSection(&m_CS);
	Log(1, "***Binary data (%d bytes)",  dwSize);
	DWORD dwWrittenBytes = 0;	
	if (pBytes && dwSize && m_hFile != INVALID_HANDLE_VALUE)
	{		
		SetFilePointer(m_hFile, 0, 0, FILE_END);
		WriteFile(m_hFile, pBytes, dwSize, &dwWrittenBytes, NULL);
		WriteFile(m_hFile, "\r\n", 2, &dwWrittenBytes, NULL);
	}
	Log(1, "***End binary data (written %d bytes)", dwWrittenBytes);
	LeaveCriticalSection(&m_CS);
}
inline void HWLogFile::Write(LPCSTR szEntry)
{
	::EnterCriticalSection(&m_CS);	
	if (m_hFile != INVALID_HANDLE_VALUE && szEntry )
	{
		CHAR szTimeString[MAX_SIZE_M] = {0};
		CHAR szBuffer[MAX_SIZE_LL] = {0};	
		GetTimeString(szTimeString, _countof(szTimeString));
		INT nBytes = _snprintf(szBuffer, _countof(szBuffer), "%s,PID:\t%08X\tTID:\t%08X: %s\r\n", szTimeString, GetCurrentProcessId(), GetCurrentThreadId(), szEntry);
		if (nBytes)
		{
			DWORD dwWrittenBytes = 0;
			::SetFilePointer(m_hFile, 0, 0, FILE_END);
			::WriteFile(m_hFile, szBuffer, nBytes, &dwWrittenBytes, NULL);
			if (dwWrittenBytes == (DWORD)nBytes) 
			{
				::FlushFileBuffers(m_hFile);	
			}	
		}	
	}
	
	::LeaveCriticalSection(&m_CS);
}

BOOL HWLogFile::GetTimeString(LPSTR szString, int nStringSize) 
{
	SYSTEMTIME st;
	GetLocalTime(&st);
#ifdef STLOG_USE_PERFORMANCE_COUNTER
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return (0 < _snprintf(szString, nStringSize, "%02u:%02u:%02u(%I64d)", st.wHour, st.wMinute, st.wSecond, counter.QuadPart));
#else
	return (0 < _snprintf(szString, nStringSize, "%02u:%02u:%02u:%03u", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds));
#endif
}
HWLogFile *HWLogFile::GetLogFile() 
{
	static HWLogFile LogFile;
	return &LogFile;
}



static BOOL WINAPI CreateDir(HWX_IN LPCWSTR pwhDstFilePath )
{    
	LPCWSTR pwhTail = pwhDstFilePath;  
	WCHAR szPairentPath[MAX_PATH] = {0};
	BOOL blRet = TRUE;
	int nPairentPathLen;
	if (!pwhDstFilePath)
	{
		blRet = FALSE;
		goto _Error;
	}

	while(pwhTail)
	{    
		pwhTail = wcschr( pwhTail, L'\\');
		if(pwhTail)
		{
			nPairentPathLen = (LONG)wcslen( pwhDstFilePath ) - (LONG)wcslen( pwhTail )/* + 1*/;
			wcsncpy_s(szPairentPath, MAX_PATH, pwhDstFilePath, nPairentPathLen);  
			szPairentPath[nPairentPathLen] = 0;
			if (!CreateDirectoryW(szPairentPath, NULL))
			{
				if (GetLastError() != ERROR_ALREADY_EXISTS)
				{
					blRet = FALSE;
					break;
				}			
			}         
			pwhTail ++;
		}
	}
_Error:

	return blRet;
}