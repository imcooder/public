
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
DLLXEXPORT BOOL WINAPI ClientToScreen( HWND, LPRECT);
DLLXEXPORT BOOL WINAPI ScreenToClient( HWND, LPRECT);
DLLXEXPORT BOOL WINAPI ModifyStyle(HWND, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
DLLXEXPORT BOOL WINAPI ModifyStyleEx(HWND, DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
#endif
	

#endif //HWX_WINDOWEX_H