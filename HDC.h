

#ifndef HWX_HDC_H
#define HWX_HDC_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <windef.h>

BOOL FillSolidRect(HDC hDC, const RECT* pRC, COLORREF crColor);
BOOL FillSolidRect(HDC hDC, int x, int y, int cx, int cy, COLORREF clr);
BOOL Draw3dRect(HDC hDC, LPRECT lpRect,
								COLORREF clrTopLeft, COLORREF clrBottomRight);
BOOL Draw3dRect(HDC hDC, int x, int y, int cx, int cy,
								COLORREF clrTopLeft, COLORREF clrBottomRight);
BOOL MoveTo(HDC hDC, int x, int y);
DWORD GetFontCell(HDC);
BOOL WINAPI DrawBorder( const LPRECT);

BOOL SetPoint(POINT*, LONG, LONG);
BOOL IsPointNull(const POINT*);
BOOL WINAPI HDCDarker(HDC, const LPRECT, double, COLORREF crTransparent = RGB(0, 0, 0));
BOOL WINAPI HDCGray(HDC, const LPRECT);
#endif //HWX_HDC_H
