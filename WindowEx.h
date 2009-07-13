
#ifndef HWX_WINDOWEX_H
#define HWX_WINDOWEX_H
#include "XTypeEx.h"


#ifdef __cplusplus
extern "C"{
#endif 
	DLLXEXPORT BOOL WINAPI InitDefaultFont(LOGFONT*);

#ifdef __cplusplus
}

DLLXEXPORT BOOL WINAPI ClientToScreen( HWND, LPRECT);
DLLXEXPORT BOOL WINAPI ScreenToClient( HWND, LPRECT);

#endif
	

#endif //HWX_WINDOWEX_H