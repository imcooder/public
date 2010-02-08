

#include "stdafx.h"
#include "Shell.h"

#ifndef WINCE

HIMAGELIST WINAPI GetSystemImageList(UINT uFlags)
{
	SHFILEINFO sfi;

	for (TCHAR cDrive = _T('C'); cDrive <= _T('Z'); cDrive++)
	{
		if (GetDriveType(CString(cDrive) + _T(":")) == DRIVE_FIXED)
		{
			return (HIMAGELIST)::SHGetFileInfo(CString(cDrive) + _T(":\\"), 0, &sfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | uFlags);
		}
	}

	return NULL;
}

#endif