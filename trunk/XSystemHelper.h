
#ifndef HWX_XSYSTEMHELPER_H
#define HWX_XSYSTEMHELPER_H


#if _MSC_VER > 1000
#pragma once
#endif 
#include "Ext_Type.h"
#include <accctrl.h>
#include <winbase.h>
#include <windows.h>
#include <Sddl.h> 
#include <AclAPI.h>


class CXSystemVersion : public OSVERSIONINFO
{
public:
	CXSystemVersion();
	BOOL IsWin31() const;
	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows 95.
	// Returns:
	//     true if the OS is Windows 95, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWin95() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows 98.
	// Returns:
	//     true if the OS is Windows 98, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWin98() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows ME.
	// Returns:
	//     true if the OS is Windows ME, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWinME() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows NT 4.
	// Returns:
	//     true if the OS is Windows NT 4, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWinNT4() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows 2000.
	// Returns:
	//     true if the OS is Windows 2000, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWin2K() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is Windows XP.
	// Returns:
	//     true if the OS is Windows XP, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWinXP() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is greater than or equal to Windows 3.1.
	// Returns:
	//     true if the OS is greater than or equal to Windows 3.1,
	//     otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWin31OrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//      Call this member function to check whether or not the
	//      operating system is of the Windows 9x family, and if it is
	//      Windows 95 or a later version.
	// Returns:
	//      true if the OS is of the Windows 9x family, and is Windows 95
	///     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWin95OrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows 9x family, and if it is
	//     Windows 98 or a later version.
	// Returns:
	//     true if the OS is of the Windows 9x family, and is Windows 98
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWin98OrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows 9x family
	// Returns:
	//     true if the OS is of the Windows 9x family
	//-----------------------------------------------------------------------
	BOOL IsWin9x() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows 9x family, and if it is
	//     Windows ME or a later version.
	// Returns:
	//     true if the OS is of the Windows 9x family, and is Windows ME
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWinMEOrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows NT 4 or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows NT
	//     4 or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWinNT4OrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows 2000 or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows
	//     2000 or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWin2KOrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows XP or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows XP
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWinXPOrGreater() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this member function to check whether or not the
	//     operating system is of the Windows NT family, and if it is
	//     Windows Vista or a later version.
	// Returns:
	//     true if the OS is of the Windows NT family, and is Windows Vista
	//     or a later version, otherwise returns false.
	//-----------------------------------------------------------------------
	BOOL IsWinVistaOrGreater() const;

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Use this member function to return the version number of the
	//      comctl32.dll. The high-order word of the return
	//     value represents the major version number and the low-order
	//     word of the returned value represents the minor version number.
	// Returns:
	//     A DWORD value if successful, otherwise 0L.
	//-----------------------------------------------------------------------
	DWORD GetComCtlVersion() const;

public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Determines if right-to-left (RTL) formatting is supported by current OS
	// Returns:
	//     TRUE if right-to-left (RTL) formatting is supported.
	//-----------------------------------------------------------------------
	BOOL IsLayoutRTLSupported();

	//-----------------------------------------------------------------------
	// Summary:
	//     Determines if ClearType text is supported by current OS
	//-----------------------------------------------------------------------
	BOOL IsClearTypeTextQualitySupported();


private:

	//-----------------------------------------------------------------------
	// Summary:
	//     Checks to see if the OS is greater or equal to the specified
	//     version number
	// Returns:
	//     true if the OS is greater than or equal to the specified
	//     version.
	//-----------------------------------------------------------------------
	BOOL GreaterThanEqualTo(const DWORD maj, const DWORD min) const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Checks to see if the OS is equal to the specified version
	//     number
	// Returns:
	//     true if the OS is equal to the specified version.
	//-----------------------------------------------------------------------
	BOOL EqualTo(const DWORD maj, const DWORD min) const;

	
};


class CXTPModuleHandle
{
public:
	//-----------------------------------------------------------------------
	// Module state
	//-----------------------------------------------------------------------
	enum XTPModuleState
	{
		xtpModNone,     // Indicates no module found.
		xtpModMapped,   // Indicates the module handle was set using GetModuleHandle
		xtpModLoaded    // Indicates the module handle was set using LoadLibrary.
	};
public:
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPModuleHandle object.
	//-----------------------------------------------------------------------
	CXTPModuleHandle();

	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPModuleHandle object.
	// Parameters:
	//     lpszModuleName - Pointer to a null-terminated string that names
	//                  the .DLL file. The name specified is the
	//                  filename of the module and is not related to the
	//                  name stored in the library module itself, as
	//                  specified by the LIBRARY keyword in the module-
	//                  definition (.DEF) file.
	//                  If the string specifies a path but the file does
	//                  not exist in the specified directory, the
	//                  function fails.  When specifying a path, be sure
	//                  to use backslashes (\), not forward slashes (/).
	//-----------------------------------------------------------------------
	CXTPModuleHandle(LPCTSTR lpszModuleName);

	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTPModuleHandle object, handles cleanup and deallocation
	//-----------------------------------------------------------------------
	virtual ~CXTPModuleHandle();

	//-----------------------------------------------------------------------
	// Summary:
	//     Call this method to LoadLibrary
	//-----------------------------------------------------------------------
	BOOL Init(LPCTSTR lpszModuleName);

	//-----------------------------------------------------------------------
	// Summary:
	//     This member function is called to load the library specified
	//     by 'lpszModule'.  Once the library is loaded, you can
	//     retrieve the instance handle by using the HINSTANCE operator.
	// Parameters:
	//     lpszModuleName - Pointer to a null-terminated string that names
	//                  the .DLL file. The name specified is the
	//                  filename of the module and is not related to the
	//                  name stored in the library module itself, as
	//                  specified by the LIBRARY keyword in the module-
	//                  definition (.DEF) file.
	//                  If the string specifies a path but the file does
	//                  not exist in the specified directory, the
	//                  function fails.  When specifying a path, be sure
	//                  to use backslashes (\), not forward slashes (/).
	//-----------------------------------------------------------------------
	BOOL LoadLibrary(LPCTSTR lpszModuleName);

	//-----------------------------------------------------------------------
	// Summary:
	//     The GetModuleHandle function retrieves a module handle for the specified module
	//     if the file has been mapped into the address space of the calling process.
	// Parameters:
	//     lpModuleName - Pointer to a null-terminated string that contains the name
	//     of the module (either a .dll or .exe file).
	//-----------------------------------------------------------------------
	BOOL GetModuleHandle(LPCTSTR lpszModuleName);

	//-----------------------------------------------------------------------
	// Summary:
	//     The FreeLibrary function decrements the reference count of the loaded
	//     dynamic-link library (DLL).
	//-----------------------------------------------------------------------
	BOOL FreeLibrary();

	//-----------------------------------------------------------------------
	// Summary:
	//     The GetProcAddress function retrieves the address of the specified
	//     exported dynamic-link library (DLL) function.
	//-----------------------------------------------------------------------
	BOOL GetProcAddress(FARPROC* ppFnPtr, LPCSTR lpProcName, DWORD dwMinVer = NULL);

	//-----------------------------------------------------------------------
	// Summary:
	//     Use this member function to return the version number of the
	//     module attached to this CLoadLibrary object. The high-order
	//     word of the return value represents the major version number
	//     and the low-order word of the returned value represents the
	//     minor version number.
	// Returns:
	//     A DWORD value if successful, otherwise 0L.
	//-----------------------------------------------------------------------
	DWORD GetVersion();
	operator HMODULE () const;	
	HMODULE GetHandle() const;
	LPCTSTR GetName() const;

	//-----------------------------------------------------------------------
	// Summary:
	//     Returns module state
	//-----------------------------------------------------------------------
	XTPModuleState GetModuleState() const;

private:
	BOOL GetVersionInfo();

	struct XTP_DLLVERSIONINFO
	{
		DWORD cbSize;
		DWORD dwMajorVersion;                   // Major version
		DWORD dwMinorVersion;                   // Minor version
		DWORD dwBuildNumber;                    // Build number
		DWORD dwPlatformID;                     // DLLVER_PLATFORM_*
	};

	TCHAR		           m_strModuleName[MAX_NAME];         // Module path
	HMODULE            m_hModule;               // A handle to the module indicates success.
	XTPModuleState     m_eModuleState;          // Module state
	XTP_DLLVERSIONINFO m_dvInfo;                // Version information
};

class CXTPMultiMonitor
{
private:
	DECLARE_HANDLE(XTP_HMONITOR);

private:
	struct XTP_MONITORINFO
	{
		DWORD   cbSize;
		RECT    rcMonitor;
		RECT    rcWork;
		DWORD   dwFlags;
	};

private:
	CXTPMultiMonitor();


public:
	RECT GetWorkArea();
	RECT GetWorkArea(const POINT& point);  
	RECT GetWorkArea(LPCRECT rect); 
	RECT GetWorkArea(const HWND hWnd); 
	RECT GetScreenArea(HWND hWnd); 
	RECT GetScreenArea(const POINT& point); 
	RECT GetScreenArea(LPCRECT rect); 

private:
	BOOL GetMonitorInfo(XTP_HMONITOR hMonitor, XTP_MONITORINFO* lpMonitorInfo);
	RECT GetWorkArea(XTP_HMONITOR hMonitor);
	RECT GetScreenArea(XTP_HMONITOR hMonitor);

	int      (WINAPI* m_pfnGetSystemMetrics)(int);
	XTP_HMONITOR (WINAPI* m_pfnMonitorFromWindow)(HWND, DWORD);
	XTP_HMONITOR (WINAPI* m_pfnMonitorFromRect)(LPCRECT, DWORD);
	XTP_HMONITOR (WINAPI* m_pfnMonitorFromPoint)(POINT, DWORD);
	BOOL     (WINAPI* m_pfnGetMonitorInfo)(XTP_HMONITOR, XTP_MONITORINFO*);
	CXTPModuleHandle m_modUser32;	
};


class CXTPCriticalSection
{
public:	
	CXTPCriticalSection();
	~CXTPCriticalSection();
public:
	void EnterCritical();	
	void LeaveCritical();	
	operator CRITICAL_SECTION& ();
private:
	CRITICAL_SECTION m_csMutex;
};

class CXTPLockGuard
{
public:	
	CXTPLockGuard(CRITICAL_SECTION& key);
	~CXTPLockGuard();

public:	
	void LockThread();
	void UnLockThread();
private:
	CRITICAL_SECTION& m_key;
};



#endif