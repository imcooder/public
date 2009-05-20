
#include "stdafx.h"
#include "XSystemHelper.h"
#include "Ext_Type.h"
#include <shlobj.h>
#include "HWDebug.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CXSystemVersion::CXSystemVersion()
{	
	::ZeroMemory((OSVERSIONINFO*)this, sizeof(OSVERSIONINFO));
	dwOSVersionInfoSize = sizeof(OSVERSIONINFO);	
	::GetVersionEx((OSVERSIONINFO*)this);
}

BOOL CXSystemVersion::IsWin31() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32s);
}

BOOL CXSystemVersion::IsWin95() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		(dwMajorVersion == 4) && (dwMinorVersion < 10);
}

BOOL CXSystemVersion::IsWin98() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		EqualTo(4, 10);
}

BOOL CXSystemVersion::IsWin9x() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
}

BOOL CXSystemVersion::IsWinME() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		EqualTo(4, 90);
}

BOOL CXSystemVersion::IsWinNT4() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT) &&
		EqualTo(4, 0);
}

BOOL CXSystemVersion::IsWin2K() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT) &&
		EqualTo(5, 0);
}

BOOL CXSystemVersion::IsWinXP() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_NT) &&
		EqualTo(5, 1);
}

BOOL CXSystemVersion::IsWin95OrGreater() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		(dwMajorVersion >= 4);
}

BOOL CXSystemVersion::IsWin98OrGreater() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		GreaterThanEqualTo(4, 10);
}

BOOL CXSystemVersion::IsWinMEOrGreater() const
{
	return (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		GreaterThanEqualTo(4, 90);
}

BOOL CXSystemVersion::IsWinNT4OrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		(dwMajorVersion >= 4);
}

BOOL CXSystemVersion::IsWin2KOrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		(dwMajorVersion >= 5);
}

BOOL CXSystemVersion::IsWinXPOrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		GreaterThanEqualTo(5, 1);
}

BOOL CXSystemVersion::IsWinVistaOrGreater() const
{
	return (dwPlatformId >= VER_PLATFORM_WIN32_NT) &&
		GreaterThanEqualTo(6, 0);
}

BOOL CXSystemVersion::GreaterThanEqualTo(const DWORD maj, const DWORD min) const
{
	return (dwMajorVersion > maj) || (dwMajorVersion == maj &&
		dwMinorVersion >= min);
}

BOOL CXSystemVersion::EqualTo(const DWORD maj, const DWORD min) const
{
	return (dwMajorVersion == maj) && (dwMinorVersion == min);
}

DWORD CXSystemVersion::GetComCtlVersion() const
{
	static DWORD dwVersion = 0;
	if (dwVersion != 0)
		return dwVersion;

	CXTPModuleHandle modComCtl32(_T("COMCTL32.DLL"));

	dwVersion = modComCtl32.GetVersion();

	if (dwVersion == NULL)
		dwVersion = MAKELONG(0, 4);   // Old ComCtl32 had version 4.0

	return dwVersion;
}

BOOL CXSystemVersion::IsLayoutRTLSupported()
{
	return IsWin2KOrGreater() || GetSystemMetrics(SM_MIDEASTENABLED);
}
BOOL CXSystemVersion::IsClearTypeTextQualitySupported()
{
	return IsWinXPOrGreater();

}


//=============================================================================
// Multi-Monitor API
//=============================================================================

CXTPMultiMonitor::CXTPMultiMonitor()
{
#ifdef UNICODE
	CXSystemVersion xSystemVersion;
	BOOL bIsPlatformNT = xSystemVersion.IsWinNT4OrGreater();
#endif

	m_modUser32.Init(TEXT("User32.dll"));
	if (!m_modUser32)
	{
		HWTRACE(_T("WARNING: Could not locate User32.dll.\n"));
	}

	if (!m_modUser32 ||
		!m_modUser32.GetProcAddress((FARPROC*)&m_pfnGetSystemMetrics, "GetSystemMetrics") ||
		!m_modUser32.GetProcAddress((FARPROC*)&m_pfnMonitorFromWindow, "MonitorFromWindow") ||
		!m_modUser32.GetProcAddress((FARPROC*)&m_pfnMonitorFromRect, "MonitorFromRect") ||
		!m_modUser32.GetProcAddress((FARPROC*)&m_pfnMonitorFromPoint, "MonitorFromPoint") ||
#ifndef UNICODE
		!m_modUser32.GetProcAddress((FARPROC*)&m_pfnGetMonitorInfo, "GetMonitorInfoA"))
#else
		!m_modUser32.GetProcAddress((FARPROC*)&m_pfnGetMonitorInfo, bIsPlatformNT ? "GetMonitorInfoW" : "GetMonitorInfoA"))
#endif
	{
		m_pfnGetSystemMetrics   = NULL;
		m_pfnMonitorFromWindow  = NULL;
		m_pfnMonitorFromRect    = NULL;
		m_pfnMonitorFromPoint   = NULL;
		m_pfnGetMonitorInfo     = NULL;
	}
}

BOOL CXTPMultiMonitor::GetMonitorInfo(XTP_HMONITOR hMonitor, XTP_MONITORINFO* lpMonitorInfo)
{
	if (hMonitor && m_pfnGetMonitorInfo)
	{
		lpMonitorInfo->cbSize = sizeof(XTP_MONITORINFO);
		ASSERT(sizeof(XTP_MONITORINFO) == 40);

		if (m_pfnGetMonitorInfo(hMonitor, lpMonitorInfo))
			return TRUE;
	}
	return FALSE;
}

RECT CXTPMultiMonitor::GetWorkArea(XTP_HMONITOR hMonitor)
{
	XTP_MONITORINFO info;

	if (GetMonitorInfo(hMonitor, &info))
	{
		return info.rcWork;
	}

	RECT rcWork;
	::SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcWork, 0);
	return rcWork;
}

RECT CXTPMultiMonitor::GetScreenArea(XTP_HMONITOR hMonitor)
{
	XTP_MONITORINFO info;
	RECT rtArea;
	ZeroMemory(&rtArea, sizeof(rtArea));
	if (GetMonitorInfo(hMonitor, &info))
	{
		return info.rcMonitor;
	}
	rtArea.right= ::GetSystemMetrics(SM_CXSCREEN);
	rtArea.bottom = ::GetSystemMetrics(SM_CYSCREEN);
	return rtArea;
}


RECT CXTPMultiMonitor::GetScreenArea(HWND hWnd)
{
	return GetScreenArea(m_pfnMonitorFromWindow ? m_pfnMonitorFromWindow(hWnd, 0) : 0);
}

RECT CXTPMultiMonitor::GetScreenArea(const POINT& ptScreenCoords)
{
	return GetScreenArea(m_pfnMonitorFromPoint ? m_pfnMonitorFromPoint(ptScreenCoords, 0) : 0);
}

RECT CXTPMultiMonitor::GetScreenArea(LPCRECT lprcScreenCoords)
{
	return GetScreenArea(m_pfnMonitorFromRect ? m_pfnMonitorFromRect(lprcScreenCoords, 0) : 0);
}

RECT CXTPMultiMonitor::GetWorkArea(HWND hWnd)
{
	return GetWorkArea(m_pfnMonitorFromWindow ? m_pfnMonitorFromWindow(hWnd, 0) : 0);
}

RECT CXTPMultiMonitor::GetWorkArea(const POINT& ptScreenCoords)
{
	return GetWorkArea(m_pfnMonitorFromPoint ? m_pfnMonitorFromPoint(ptScreenCoords, 0) : 0);
}

RECT CXTPMultiMonitor::GetWorkArea(LPCRECT lprcScreenCoords)
{
	return GetWorkArea(m_pfnMonitorFromRect ? m_pfnMonitorFromRect(lprcScreenCoords, 0) : 0);
}

RECT CXTPMultiMonitor::GetWorkArea()
{
	POINT point;
	::GetCursorPos(&point);

	return GetWorkArea(point);
}


//=============================================================================
// CXTPModuleHandle :
//=============================================================================

CXTPModuleHandle::CXTPModuleHandle()
: m_hModule(0)
, m_eModuleState(xtpModNone)
{
	::ZeroMemory(&m_dvInfo, sizeof(m_dvInfo));
}

CXTPModuleHandle::CXTPModuleHandle(LPCTSTR lpszModuleName)
: m_hModule(0)
, m_eModuleState(xtpModNone)
{
	::ZeroMemory(&m_dvInfo, sizeof(m_dvInfo));

	Init(lpszModuleName);
}

CXTPModuleHandle::~CXTPModuleHandle()
{
	VERIFY(FreeLibrary());
}

BOOL CXTPModuleHandle::Init(LPCTSTR lpszModuleName)
{
	// first, try to obtain the module that was mapped into
	// the address space of the calling process, if not found,
	// attempt to load the library.

	return (GetModuleHandle(lpszModuleName) || LoadLibrary(lpszModuleName));
}

BOOL CXTPModuleHandle::GetModuleHandle(LPCTSTR lpszModuleName)
{
	FreeLibrary();

	if ((m_hModule = ::GetModuleHandle(lpszModuleName)) != NULL)
	{
		m_eModuleState = xtpModMapped;
		_tcscpy_s(m_strModuleName , MAX_NAME, lpszModuleName);
		return TRUE;
	}

	return FALSE;
}

BOOL CXTPModuleHandle::LoadLibrary(LPCTSTR lpszModuleName)
{
	FreeLibrary();

	if ((m_hModule = ::LoadLibrary(lpszModuleName)) != NULL)
	{
		m_eModuleState = xtpModLoaded;		
		_tcscpy_s(m_strModuleName, MAX_NAME, lpszModuleName);
		return TRUE;
	}

	return FALSE;
}

BOOL CXTPModuleHandle::FreeLibrary()
{
	BOOL bRet = TRUE;

	if (m_hModule && m_eModuleState == xtpModLoaded)
	{
		bRet = ::FreeLibrary(m_hModule);
	}

	m_hModule = NULL;
	m_eModuleState = xtpModNone;	
	ZeroMemory(m_strModuleName, sizeof(m_strModuleName));
	return bRet;
}

BOOL CXTPModuleHandle::GetVersionInfo()
{
	if (!m_hModule)
		return FALSE;

	m_dvInfo.cbSize = sizeof(m_dvInfo);

	typedef HRESULT (WINAPI* PFNDLLVERSIONINFO)(XTP_DLLVERSIONINFO*);
	PFNDLLVERSIONINFO pfn = (PFNDLLVERSIONINFO)::GetProcAddress(m_hModule, "DllGetVersion");

	if (pfn != NULL)
	{
		return (pfn(&m_dvInfo) != NOERROR);
	}

	return FALSE;
}

DWORD CXTPModuleHandle::GetVersion()
{
	if (m_dvInfo.cbSize == 0)
		GetVersionInfo();

	DWORD dwModVer = MAKELONG(m_dvInfo.dwMinorVersion, m_dvInfo.dwMajorVersion);

	ASSERT(HIWORD(dwModVer) <= 0xFFFF);
	ASSERT(LOWORD(dwModVer) <= 0xFFFF);

	return dwModVer;
}

BOOL CXTPModuleHandle::GetProcAddress(FARPROC* ppFnPtr, LPCSTR lpProcName, DWORD dwMinVer /*= NULL*/)
{
	if (!m_hModule)
		return FALSE;

	if (dwMinVer != NULL)
	{
		DWORD dwModVer = GetVersion();

		if ((HIWORD(dwMinVer) >  HIWORD(dwModVer)) ||
			(HIWORD(dwMinVer) == HIWORD(dwModVer)) &&
			(LOWORD(dwMinVer) >  LOWORD(dwModVer)))
		{
			*ppFnPtr = NULL;
			return FALSE;
		}
	}

	*ppFnPtr = ::GetProcAddress(m_hModule, lpProcName);
	return (*ppFnPtr != NULL);
}
HMODULE CXTPModuleHandle::GetHandle() const
{
	return m_hModule;
}
LPCTSTR CXTPModuleHandle::GetName() const
{
	return m_strModuleName;
}
CXTPModuleHandle::operator HMODULE() const
{
	return m_hModule;
}
CXTPModuleHandle::XTPModuleState CXTPModuleHandle::GetModuleState() const
{
	return m_eModuleState;
}
//////////////////////////////////////////////////////////////////////////
CXTPCriticalSection::CXTPCriticalSection()
{
	::InitializeCriticalSection(&m_csMutex);
}

CXTPCriticalSection::~CXTPCriticalSection()
{
	::DeleteCriticalSection(&m_csMutex);
}

void CXTPCriticalSection::EnterCritical()
{
	::EnterCriticalSection(&m_csMutex);
}

void CXTPCriticalSection::LeaveCritical()
{
	::LeaveCriticalSection(&m_csMutex);
}
CXTPCriticalSection::operator CRITICAL_SECTION&()
{
	return m_csMutex;
}
//////////////////////////////////////////////////////////////////////////
//LockGuard
CXTPLockGuard::CXTPLockGuard(CRITICAL_SECTION& key)
: m_key(key)
{
	LockThread();
}

CXTPLockGuard::~CXTPLockGuard()
{
	UnLockThread();
}

void CXTPLockGuard::LockThread()
{
	::EnterCriticalSection(&m_key);
}

void CXTPLockGuard::UnLockThread()
{
	::LeaveCriticalSection(&m_key);
}

//////////////////////////////////////////////////////////////////////////
