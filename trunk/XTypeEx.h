#ifndef HWX_XTYPEEX_H
#define HWX_XTYPEEX_H

#include "Ext_Type.h"


#ifdef _X86_
   #define DebugBreak() _asm { int 3 }
#endif


#define SelectFont(hDC, hFont) \
   ((HFONT) ::SelectObject((hDC), (HGDIOBJ) (HFONT) (hFont)))


#define HANDLE_MSG(m_hWnd, message, fn) \
   case (message): \
      return HANDLE_##message((m_hWnd), (wParam), (lParam), (fn))


#define HANDLE_WM_COMMAND(m_hWnd, wParam, lParam, fn) \
   ( (fn) ((m_hWnd), (int) (LOWORD(wParam)), (HWND)(lParam), (UINT) HIWORD(wParam)), 0L)


#ifndef FORCEASSERT
#define FORCEASSERT(expr) \
if (!(expr))  \
{      \
	XForceTraceW(L"%s In Files %s Line:%d", _CRT_WIDE(#expr), _CRT_WIDE(__FILE__), __LINE__);  \
	DebugBreak();   \
}
#endif

#endif//HWXUE_EXT_TYPE_H_INC

