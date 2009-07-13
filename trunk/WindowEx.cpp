

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
	HFONT hFont =  (HFONT)::GetStockObject(DEFAULT_GUI_FONT);		
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