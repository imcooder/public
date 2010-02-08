
#ifndef HWX_WINDOWEX_H
#define HWX_WINDOWEX_H
#include "XTypeEx.h"


#ifdef __cplusplus
extern "C"
{
#endif 
	DLLXEXPORT BOOL WINAPI InitDefaultFont(LOGFONT*);
	
#ifdef __cplusplus

}
DLLXEXPORT BOOL WINAPI XUE_ClientToScreen( HWND, LPRECT);
DLLXEXPORT BOOL WINAPI XUE_ScreenToClient( HWND, LPRECT);
DLLXEXPORT BOOL WINAPI XUE_ModifyStyle(HWND, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
DLLXEXPORT BOOL WINAPI XUE_ModifyStyleEx(HWND, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
DLLXEXPORT DWORD WINAPI XUE_GetWindowStyle(HWND);
DLLXEXPORT DWORD WINAPI XUE_GetWindowStyleEx(HWND);
#ifndef WINCE
DLLXEXPORT HIMAGELIST WINAPI GetSystemImageList(UINT uFlags);
#endif
#endif
	

#endif //HWX_WINDOWEX_H