
#include "stdafx.h"
#include "HWWinVersion.h"
#include <assert.h>


BOOL WINAPI GreaterThanEqualTo(const OSVERSIONINFO* pVersion, const DWORD maj, const DWORD min)
{
	ASSERT(pVersion);
	return (pVersion->dwMajorVersion > maj) || (pVersion->dwMajorVersion == maj && pVersion->dwMinorVersion >= min);
}

BOOL WINAPI EqualTo(const OSVERSIONINFO* pVersion, const DWORD maj, const DWORD min)
{
	return (pVersion->dwMajorVersion == maj) && (pVersion->dwMinorVersion == min);
}


BOOL WINAPI HWIsWin9x(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
}

BOOL WINAPI HWIsWin98(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && EqualTo(pVersion, 4, 10);
}

BOOL WINAPI HWIsWin98OrGreater(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && GreaterThanEqualTo(pVersion, 4, 10);
}

BOOL WINAPI HWIsWinME(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) && EqualTo(pVersion, 4, 90);
}

BOOL WINAPI HWIsWinMEOrGreater(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&	GreaterThanEqualTo(pVersion, 4, 90);
}

BOOL WINAPI HWIsWin2K(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId >= VER_PLATFORM_WIN32_NT) &&	(pVersion->dwMajorVersion == 5);
}

BOOL WINAPI HWIsWin2KOrGreater(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId >= VER_PLATFORM_WIN32_NT) &&	(pVersion->dwMajorVersion >= 5);
}



BOOL WINAPI HWIsWinXPOrGreater(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId >= VER_PLATFORM_WIN32_NT) &&	GreaterThanEqualTo(pVersion, 5, 1);
}

BOOL WINAPI HWIsWinXP(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId >= VER_PLATFORM_WIN32_NT) &&	EqualTo(pVersion, 5, 1);
}

BOOL WINAPI HWIsVistaOrGreater(const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId >= VER_PLATFORM_WIN32_NT) &&	GreaterThanEqualTo(pVersion, 6, 0);
}

BOOL WINAPI HWIsVista( const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId >= VER_PLATFORM_WIN32_NT) &&	EqualTo(pVersion, 6, 0);
}


BOOL WINAPI HWIsWin7( const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId >= VER_PLATFORM_WIN32_NT) &&	EqualTo(pVersion, 6, 1);
}

BOOL WINAPI HWIsWin7OrGreater( const OSVERSIONINFO* pVersion)
{
	if (!pVersion)
	{
		return FALSE;
	}
	return (pVersion->dwPlatformId >= VER_PLATFORM_WIN32_NT) &&	GreaterThanEqualTo(pVersion, 6, 1);
}

BOOL WINAPI HWIsX64()
{
	return 8 == sizeof(HANDLE);
}

BOOL WINAPI HWIsWow64Process(HANDLE hProecss)
{
	typedef BOOL (WINAPI *LPIsWow64Process)(HANDLE, PBOOL);
	LPIsWow64Process pIsWow64Process = NULL;
	BOOL bIsWow64 = FALSE;
	HMODULE hKernel32 = LoadLibraryW(L"kernel32");
	if (hKernel32)
	{
		pIsWow64Process = (LPIsWow64Process)GetProcAddress(hKernel32, "IsWow64Process");
		if (pIsWow64Process)
		{
			pIsWow64Process(hProecss, &bIsWow64);
		}
	}	
	if (hKernel32)
	{
		pIsWow64Process = NULL;
		FreeLibrary(hKernel32);
		hKernel32 = NULL;
	}
	return bIsWow64;	
} 

BOOL WINAPI HWIs64BitCPU()
{
	SYSTEM_INFO   si;
	BOOL       bIs64BitCpu;

	if (HWIsWow64Process(GetCurrentProcess()))
	{
		bIs64BitCpu = TRUE;
	}
	else
	{
		GetSystemInfo(&si);
		bIs64BitCpu = ((si.wProcessorArchitecture & PROCESSOR_ARCHITECTURE_IA64) || (si.wProcessorArchitecture & PROCESSOR_ARCHITECTURE_AMD64))	? TRUE : FALSE; 
	}
	return bIs64BitCpu; 
}