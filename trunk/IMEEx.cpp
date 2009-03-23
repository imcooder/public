
#include "stdafx.h"
#include "IMEEx.h"


HKL WINAPI GetHKLByIMEFileName(LPCTSTR pszFileName)
{
	DWORD dwSize;
	DWORD dwi;
	HKL hKL = 0;
	HKL *lphkl;

	dwSize = GetKeyboardLayoutList(0, NULL);

	lphkl = (HKL *)GlobalAlloc(GPTR, dwSize * sizeof(DWORD));

	if (!lphkl)
	{
		return NULL;
	}

	GetKeyboardLayoutList(dwSize, lphkl);


	for (dwi = 0; dwi < dwSize; dwi++)
	{
		TCHAR szFile[32];
		HKL hKLTemp = *(lphkl + dwi);
		ImmGetIMEFileName(hKLTemp, szFile, sizeof(szFile));

		if (!_tcsicmp(szFile, pszFileName))
		{
			hKL = hKLTemp;
			break;
		}
	}
	GlobalFree((HANDLE)lphkl);
	return hKL;
}

