#include "StdAfx.h"
#include "VirtualKey.h"

//ÊÇ·ñÊÇÊý×Ö

BOOL WINAPI IsVKeyChar(LONG wParam)
{
	if (VK_A <= wParam && wParam <= VK_Z)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL WINAPI IsVKeyNumPad(LONG wParam)
{
	if (VK_NUMPAD0 <= wParam && wParam <= VK_NUMPAD9)
	{
		return TRUE;
	}
	return FALSE;
}
BOOL WINAPI IsVKeyNum( LONG wParam)
{
	if (VK_0 <= wParam && wParam <=  VK_9)
	{
		return TRUE;
	}
	return FALSE;	
}
BOOL WINAPI IsVKeyF(LONG wParam)
{
	if (VK_F1 <= wParam && wParam <=  VK_F24)
	{
		return TRUE;
	}
	return FALSE;	
}