
#include "stdafx.h"
#include "HDC.h"

BOOL FillSolidRect(HDC hDC, const RECT* pRC, COLORREF crColor)
{
	HBRUSH hBrush = NULL, hOldBrush = NULL;
	if (!hDC || !pRC)
	{
		return FALSE;
	}	
	return FillSolidRect(hDC, pRC->left, pRC->top, pRC->right - pRC->left, pRC->bottom - pRC->top, crColor);
}
BOOL FillSolidRect(HDC hDC, int x, int y, int cx, int cy, COLORREF clr)
{	
	if (!hDC)
	{
		return FALSE;
	}
	RECT rect = {x, y, x + cx, y + cy};	
	COLORREF crOldBkColor = ::SetBkColor(hDC, clr);	
	::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
	::SetBkColor(hDC, crOldBkColor);	
	return TRUE;
}
BOOL Draw3dRect(HDC hDC, LPRECT lpRect,
								COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	if (!lpRect || !hDC)
	{
		return FALSE;
	}
	return Draw3dRect(hDC, lpRect->left, lpRect->top, lpRect->right - lpRect->left,
		lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
}

BOOL Draw3dRect(HDC hDC, int x, int y, int cx, int cy,
								COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	if (!hDC)
	{
		return FALSE;
	}
	return FillSolidRect(hDC, x, y, cx - 1, 1, clrTopLeft) 
		&& FillSolidRect(hDC, x, y, 1, cy - 1, clrTopLeft)
		&& FillSolidRect(hDC, x + cx, y, -1, cy, clrBottomRight)
		&& FillSolidRect(hDC, x, y + cy, cx, -1, clrBottomRight);
}

BOOL MoveTo(HDC hDC, int x, int y)
{
	if (!hDC)
	{
		return FALSE;
	}	
	return ::MoveToEx(hDC, x, y, NULL);
}

DWORD GetFontCell( HDC hDC)
{
	if (!hDC)
	{
		return FALSE;
	}
	TEXTMETRIC tm;	
	DWORD dwRet = 0;
	if (GetTextMetrics(hDC, &tm))
	{		
		dwRet = MAKELONG(tm.tmHeight, tm.tmHeight);
	}
	else
	{
		dwRet = MAKELONG(24, 24);
	}	
	return dwRet;
}

BOOL SetPoint( POINT* ptPoint, LONG x, LONG y)
{
	if (!ptPoint)
	{
		return FALSE;
	}
	ptPoint->x = x;
	ptPoint->y = y;
	return TRUE;
}

BOOL IsPointNull( const POINT* ptPoint)
{
	if (!ptPoint)
	{
		return FALSE;
	}
	return !ptPoint->x && !ptPoint->y;
}