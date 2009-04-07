
#include "stdafx.h"
#include "Rect.h"


BOOL WINAPI IsRectNULL( const RECT * pRect)
{
	if (!pRect)
	{
		return FALSE;
	}
	return (!pRect->left && !pRect->right && !pRect->top && !pRect->bottom);
}

BOOL WINAPI MoveRectTo( LPRECT pRect, int x, int y)
{
	if (!pRect)
	{
		return FALSE;
	}
	LONG nWidth = pRect->right - pRect->left, nHeight = pRect->bottom - pRect->top;
	return SetRect(pRect, x, y, x + nWidth, y + nHeight);
}