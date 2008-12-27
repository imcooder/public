

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

