
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

