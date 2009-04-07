

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


BOOL SetPoint(POINT*, LONG, LONG);
BOOL IsPointNull(const POINT*);
#endif //HWX_HDC_H
