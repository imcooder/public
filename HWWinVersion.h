
#ifndef HWX_HWWINVERSION_H
#define HWX_HWWINVERSION_H


#if _MSC_VER > 1000
#pragma once
#endif 

BOOL WINAPI HWIsWin9x(const OSVERSIONINFO*);
BOOL WINAPI HWIsWin98(const OSVERSIONINFO*);
BOOL WINAPI HWIsWin98OrGreater(const OSVERSIONINFO*);
BOOL WINAPI HWIsWinME(const OSVERSIONINFO*);
BOOL WINAPI HWIsWinMEOrGreater(const OSVERSIONINFO*);
BOOL WINAPI HWIsWin2K(const OSVERSIONINFO*);
BOOL WINAPI HWIsWin2KOrGreater(const OSVERSIONINFO* );
BOOL WINAPI HWIsWinXPOrGreater(const OSVERSIONINFO*);
BOOL WINAPI HWIsWinXP(const OSVERSIONINFO*);

BOOL WINAPI HWIsVista(const OSVERSIONINFO*);
BOOL WINAPI HWIsVistaOrGreater(const OSVERSIONINFO*);
BOOL WINAPI HWIsWin7(const OSVERSIONINFO*);
BOOL WINAPI HWIsWin7OrGreater(const OSVERSIONINFO*);

BOOL WINAPI HWIsX64();
BOOL WINAPI HWIsWow64Process(HANDLE, PBOOL);
#endif //HWX_HWWINVERSION_H