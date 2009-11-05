

#ifndef HWX_HWDEVICEID_H
#define HWX_HWDEVICEID_H

#include <windows.h>
LONG WINAPI HWGetMAC(LPWSTR, LONG);
LONG WINAPI GetNetAdapterPhysicalMAC(WCHAR*, WCHAR*, LONG);
#endif