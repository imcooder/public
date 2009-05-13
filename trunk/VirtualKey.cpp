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


BOOL WINAPI IsVKeySys( LONG wParam)
{
	switch (LOWORD(wParam))
	{
	case VK_SELECT:
	case VK_PRINT:
	case VK_EXECUTE:
	case VK_SNAPSHOT:
	case VK_INSERT:
	case VK_HELP:
	case VK_MENU:
	case VK_PAUSE:
	case VK_NUMLOCK:
	case VK_SLEEP:
	case VK_SCROLL:
#if(_WIN32_WINNT >= 0x0500)
	case VK_BROWSER_BACK:
	case VK_BROWSER_FORWARD:
	case VK_BROWSER_REFRESH:
	case VK_BROWSER_STOP:
	case VK_BROWSER_SEARCH:
	case VK_BROWSER_FAVORITES:
	case VK_VOLUME_MUTE:
	case VK_MEDIA_NEXT_TRACK:
	case VK_MEDIA_STOP:
	case VK_MEDIA_PLAY_PAUSE:
	case VK_LAUNCH_MAIL:
	case VK_LAUNCH_MEDIA_SELECT:
#endif
		{
			return TRUE;
		}
		break;
	default:
		{			
			break;
		}
	}
	return FALSE;
}