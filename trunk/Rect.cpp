
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