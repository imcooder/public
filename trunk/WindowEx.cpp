

#include "stdafx.h"
#include "WindowEx.h"
#include <stdlib.h>
#include <stdio.h>
BOOL WINAPI InitDefaultFont(LOGFONT* pLogFont)
{
	if (!pLogFont)
	{
		return FALSE;
	}
#ifdef WINCE
	HFONT hFont =  (HFONT)::GetStockObject(SYSTEM_FONT);			
#else
	HFONT hFont =  (HFONT)::GetStockObject(DEFAULT_GUI_FONT);	
#endif
	GetObject(hFont, sizeof(*pLogFont), pLogFont);
	SAFE_DELETE_OBJECT(hFont);
	return TRUE;
}

BOOL WINAPI ClientToScreen( HWND hWnd, LPRECT pRect)
{
	if (!pRect)
	{
		return FALSE;
	}
	POINT point = {0, 0};
	point.x = pRect->left;
	point.y = pRect->top;
	ClientToScreen(hWnd, &point);
	pRect->left= point.x;
	pRect->top = point.y;

	point.x = pRect->right;
	point.y = pRect->bottom;
	ClientToScreen(hWnd, &point);
	pRect->right= point.x;
	pRect->bottom = point.y;
	return TRUE;
}


BOOL WINAPI ScreenToClient( HWND hWnd, LPRECT pRect)
{
	if (!pRect)
	{
		return FALSE;
	}
	POINT point = {0, 0};
	point.x = pRect->left;
	point.y = pRect->top;
	ScreenToClient(hWnd, &point);
	pRect->left= point.x;
	pRect->top = point.y;

	point.x = pRect->right;
	point.y = pRect->bottom;
	ScreenToClient(hWnd, &point);
	pRect->right= point.x;
	pRect->bottom = point.y;
	return TRUE;
}


BOOL WINAPI HWModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{	
	if (!::IsWindow(hWnd))
	{
		return FALSE;
	}
	DWORD dwStyle = ::GetWindowLong(hWnd, GWL_STYLE);
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if (dwStyle != dwNewStyle)
	{
		::SetWindowLong(hWnd, GWL_STYLE, dwNewStyle);
		if (nFlags != 0)
		{
			::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
		}
	}	
	return TRUE;
}

BOOL WINAPI HWModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags )
{	
	if (!::IsWindow(hWnd))
	{
		return FALSE;
	}
	DWORD dwStyle = ::GetWindowLong(hWnd, GWL_EXSTYLE);
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if (dwStyle != dwNewStyle)
	{
		::SetWindowLong(hWnd, GWL_EXSTYLE, dwNewStyle);
		if (nFlags != 0)
		{
			::SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | nFlags);
		}
	}	
	return TRUE;
}