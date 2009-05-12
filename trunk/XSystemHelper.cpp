
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

CXModule::CXModule()
: m_hModule(NULL)
{		
	m_szModuleFilePath[0] = 0;
}
CXModule::~CXModule()
{
	FreeLibrary();
}

BOOL CXModule::LoadLibrary( LPCTSTR pszPath)
{
	BOOL blReturn = FALSE;
	FreeLibrary();
	if (m_hModule = ::LoadLibrary(pszPath))
	{		
		_tcscpy_s(m_szModuleFilePath, MAX_PATH, pszPath);
		blReturn = TRUE;
	}
	else
	{		
		HWTRACE(TEXT("LoadLibrary %s failed\n"), pszPath);
	}	
	return blReturn;
}
void CXModule::FreeLibrary()
{
	SAFE_FREE_LIBRARY(m_hModule);
	m_szModuleFilePath[0] = 0;
	m_blSucceed = FALSE;
}

BOOL CXModule::Succeed()
{
	return m_hModule != NULL;
}


//////////////////////////////////////////////////////////////////////////

LONG Helper_GetObjectIntegrityLevel(HANDLE hHandle, SE_OBJECT_TYPE  objectType)
{	
	DWORD integrityLevel = SECURITY_MANDATORY_UNTRUSTED_RID;
	PSECURITY_DESCRIPTOR pSD = NULL;  
	PACL acl = 0;
	if (ERROR_SUCCESS == ::GetSecurityInfo(hHandle,
		objectType,
		LABEL_SECURITY_INFORMATION,
		0,
		0,
		0,
		&acl,
		&pSD))
	{		
		if (0 != acl && 0 < acl->AceCount)
		{
			ASSERT(1 == acl->AceCount);
			SYSTEM_MANDATORY_LABEL_ACE* ace = 0;
			if(::GetAce(acl, 0,	reinterpret_cast<void**>(&ace)))
			{
				ASSERT(0 != ace);
				SID* sid = reinterpret_cast<SID*>(&ace->SidStart);
				integrityLevel = sid->SubAuthority[0];
			}			
		}
		if (pSD)
		{
			LocalFree ( pSD );
		}
	}		
	return integrityLevel;
}

#ifndef LABEL_SECURITY_INFORMATION
#define LABEL_SECURITY_INFORMATION       (0x00000010L)
#endif

BOOL Helper_SetObjectToLowIntegrity( HANDLE hObject, SE_OBJECT_TYPE type) 
{ 
#if (WINVER >= 0x0600)	
	BOOL  blRet = TRUE;  
	{
		CXSystemVersion xSystemVersion;		
		if (xSystemVersion.IsWinVistaOrGreater())
		{	
			blRet = FALSE;		
			PSECURITY_DESCRIPTOR pSD = NULL;      
			PACL pSacl = NULL;                  // Œ¥∑÷≈‰  
			BOOL fSaclPresent = FALSE;  
			BOOL fSaclDefaulted = FALSE;  

			if (ConvertStringSecurityDescriptorToSecurityDescriptor(TEXT("S:(ML;;NW;;;LW)"), SDDL_REVISION_1, 	&pSD, NULL))
			{	
				if (GetSecurityDescriptorSacl(pSD, &fSaclPresent, &pSacl, &fSaclDefaulted))
				{
					blRet = (ERROR_SUCCESS  == SetSecurityInfo(hObject, type,   LABEL_SECURITY_INFORMATION, NULL, NULL, NULL, pSacl));
				} 			
				LocalFree ( pSD );
			}		
		}
	}
	return blRet;
#else
	return TRUE;
#endif
}


LONG Helper_GetFileIntegrityLevel(LPTSTR pszFilePath)
{	
	DWORD integrityLevel = SECURITY_MANDATORY_UNTRUSTED_RID;
	PSECURITY_DESCRIPTOR pSD = NULL;  
	PACL acl = 0;
	if (ERROR_SUCCESS == ::GetNamedSecurityInfo(pszFilePath,
		SE_FILE_OBJECT,
		LABEL_SECURITY_INFORMATION,
		0,
		0,
		0,
		&acl,
		&pSD))
	{		
		if (0 != acl && 0 < acl->AceCount)
		{
			ASSERT(1 == acl->AceCount);
			SYSTEM_MANDATORY_LABEL_ACE* ace = 0;
			if(::GetAce(acl, 0,	reinterpret_cast<void**>(&ace)))
			{
				ASSERT(0 != ace);
				SID* sid = reinterpret_cast<SID*>(&ace->SidStart);
				integrityLevel = sid->SubAuthority[0];
			}			
		}
		if (pSD)
		{
			LocalFree ( pSD );
		}
	}		
	return integrityLevel;
}


BOOL Helper_SetFileToLowIntegrity(LPCTSTR pszFileName)
{	
#if (WINVER >= 0x0600)
	BOOL  b = TRUE; 
	{
		CXSystemVersion xSystemVersion;		
		if (xSystemVersion.IsWinVistaOrGreater())
		{	 
			b = FALSE;		
			PSECURITY_DESCRIPTOR pSD = NULL;      
			PACL pSacl = NULL;                  // Œ¥∑÷≈‰  
			BOOL fSaclPresent = FALSE;  
			BOOL fSaclDefaulted = FALSE;  

			if (ConvertStringSecurityDescriptorToSecurityDescriptor(TEXT("S:(ML;;NW;;;LW)"), SDDL_REVISION_1,	&pSD, NULL))
			{
				if (GetSecurityDescriptorSacl(pSD, &fSaclPresent,	&pSacl, &fSaclDefaulted))
				{
					b = ERROR_SUCCESS == SetNamedSecurityInfo((LPTSTR)pszFileName, SE_FILE_OBJECT,  LABEL_SECURITY_INFORMATION, NULL, NULL, NULL, pSacl);
				}
				LocalFree ( pSD );
			}	
		}
	}
	return b;
#else
	return TRUE;
#endif
}



BOOL Helper_GetProcessElevation(BOOL* pIsElevation) 
{
	BOOL bIsAdmin = FALSE;
	BOOL bIsElevation = FALSE;
#if (WINVER >= 0x0600)
	{
		HANDLE hToken = NULL;
		DWORD dwSize;
		TOKEN_ELEVATION_TYPE ElevationType;
		// Get current process token
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		{
			bIsAdmin = IsUserAnAdmin();
		}	
		else
		{
			// Retrieve elevation type information
			if (GetTokenInformation(hToken, TokenElevationType,	&ElevationType, sizeof(TOKEN_ELEVATION_TYPE), &dwSize)) 
			{
				// Create the SID corresponding to the Administrators group
				BYTE adminSID[SECURITY_MAX_SID_SIZE];
				dwSize = sizeof(adminSID);
				CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, &adminSID, &dwSize);
				if (ElevationType == TokenElevationTypeLimited) 
				{
					// Get handle to linked token (will have one if we are lua)
					HANDLE hUnfilteredToken = NULL;
					GetTokenInformation(hToken, TokenLinkedToken, (VOID*)&hUnfilteredToken, sizeof(HANDLE), &dwSize);

					// Check if this original token contains admin SID
					CheckTokenMembership(hUnfilteredToken, &adminSID, &bIsAdmin); 
					// Don't forget to close the unfiltered token
					CloseHandle(hUnfilteredToken);
				} 
				else 
				{
					bIsAdmin = IsUserAnAdmin();					
				}
			}
			else
			{
				bIsAdmin = IsUserAnAdmin();
			}		
		}		

		CloseHandle(hToken);		
		if	(TokenElevationTypeDefault == ElevationType && TokenElevationTypeLimited == ElevationType)
		{
			
		}
		else if (TokenElevationTypeFull == ElevationType)
		{
			bIsElevation = FALSE;
		}
		
		return bIsAdmin;
	}
#else
	{
		bIsAdmin = IsUserAnAdmin();
	}
#endif
	if (pIsElevation)
	{
		*pIsElevation = bIsElevation;
	}
	return bIsAdmin;
}



LONG Helper_GetProcessIntegrityLevel(DWORD dwProcessId)
{	
	OSVERSIONINFO OSVersion;
	ZeroMemory( &OSVersion, sizeof( OSVersion ));
	OSVersion.dwOSVersionInfoSize = sizeof( OSVersion );
	GetVersionEx( &OSVersion );

	DWORD dwIL = SECURITY_MANDATORY_HIGH_RID;
	if(OSVersion.dwMajorVersion >= 6)
	{//Vista
		HANDLE hToken = NULL;
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
		if(hProcess)
		{
			if(OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
			{
				PTOKEN_MANDATORY_LABEL pTIL = NULL;
				DWORD dwSize=0;
				if (!GetTokenInformation(hToken, TokenIntegrityLevel, NULL, 0, &dwSize) 
					&& ERROR_INSUFFICIENT_BUFFER==GetLastError() && dwSize)
				{
					pTIL = (PTOKEN_MANDATORY_LABEL)HeapAlloc(GetProcessHeap(), 0, dwSize);
				}

				if(pTIL && GetTokenInformation(hToken, TokenIntegrityLevel, pTIL, dwSize, &dwSize))
				{
					LPBYTE lpb = GetSidSubAuthorityCount(pTIL->Label.Sid);
					if(lpb)
					{
						dwIL = *GetSidSubAuthority(pTIL->Label.Sid, *lpb - 1);
					}						
				}
				if(pTIL)
				{
					HeapFree(GetProcessHeap(), 0, pTIL);
				}
				CloseHandle(hToken);
			}
			CloseHandle(hProcess);
		}
		else 
		{
			dwIL = SECURITY_MANDATORY_UNTRUSTED_RID;
		}
	}	
	return dwIL;
}


PSID name_to_PSID(LPCTSTR pszFileName)
{
	SID_NAME_USE snu;
	TCHAR	szDomainName[512] = {0};
	DWORD	dwSidLen, dwNameLen;
	PSID  *pSid = NULL;
	dwSidLen = 512;
	pSid = (PSID*)calloc(1, dwSidLen);
	dwNameLen = sizeof(szDomainName);
	if ( !LookupAccountName(NULL, pszFileName, pSid, &dwSidLen, szDomainName, &dwNameLen, &snu) ) 
	{
		free(pSid);
		return	NULL;
	}
	return	pSid;
}

PACL	GenerateACL()
{
	PACL	pAcl = NULL;
	DWORD	szAcl = 0;
	PSID	sids[2];
	DWORD	AceMask;

	sids[0] = name_to_PSID(TEXT("everyone"));
	sids[1] = name_to_PSID(TEXT("administrators"));
	szAcl = sizeof(ACL) + ((sizeof(ACCESS_ALLOWED_ACE)-sizeof(DWORD))*sizeof(sids)/sizeof(PSID)) + GetLengthSid(sids[0]) + GetLengthSid(sids[1]);
	pAcl = (PACL) LocalAlloc(LPTR, szAcl);
	if ( !InitializeAcl(pAcl, szAcl, ACL_REVISION) ) 
	{
		LocalFree(pAcl);
		return	NULL;
	}
	AceMask = (1<<30) | (1<<31);
	if ( !AddAccessAllowedAce(pAcl, ACL_REVISION, AceMask, sids[0]) ) 
	{
		LocalFree(pAcl);
		return	NULL;
	}
	AceMask = (1<<28);
	if ( !AddAccessAllowedAce(pAcl, ACL_REVISION, AceMask, sids[1]) ) 
	{
		LocalFree(pAcl);
		return	NULL;
	}
	return	pAcl;
};

int AddAccessUser(LPTSTR pszFileName)
{
	if (!pszFileName)
	{
		return -1;
	}
	int	retval = 1;
	PACL myacl = GenerateACL();

	if ( ERROR_SUCCESS!=SetNamedSecurityInfo(pszFileName, SE_FILE_OBJECT, 	DACL_SECURITY_INFORMATION, 	NULL, NULL, myacl, NULL) ) 
	{
		retval = 0;
	}

	if ( NULL!=myacl ) 
	{
		LocalFree(myacl);
	}
	return retval;
}