#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include "FileEx.h"
#include "Ext_Memory.h"
#include <tchar.h>
#include <assert.h>
#include <stdio.h>
#include <io.h>
#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>


LONG WINAPI LoadFileA( LPCSTR pszFileName, LPBYTE *ppFileContent)
{
	DWORD dwFileLen = 0;
	FILE *pf = NULL;
	LONG *pnBuffer = NULL;
	DWORD dwSize = 0;
	*ppFileContent = NULL;
	pf = fopen( pszFileName, "rb");
	if( NULL == pf )
	{
		return -2;
	}
	fseek( pf, 0, SEEK_END );
	dwFileLen = ftell( pf );	
	dwSize = ((dwFileLen >> 2) + 1);	
	VERIFY(pnBuffer = new LONG[dwSize]);			
	if( NULL == *ppFileContent )
	{
		fclose( pf );
		return -1;
	}
	ZeroMemory(pnBuffer, sizeof(*pnBuffer) * dwSize);		
	fseek( pf, 0, SEEK_SET );
	fread( pnBuffer, 1, dwFileLen, pf );
	fclose( pf );
	*ppFileContent = (LPBYTE)pnBuffer;
	return dwFileLen;
}
LONG WINAPI LoadFileW(LPCWSTR pszFileName, LPBYTE *ppFileContent)
{
	DWORD dwFileLen = 0;
	FILE *pf = NULL;
	LONG *pnBuffer = NULL;
	DWORD dwSize = 0;
	*ppFileContent = NULL;
	pf = _wfopen( pszFileName, L"rb");
	if( NULL == pf )
	{
		return -2;
	}
	fseek( pf, 0, SEEK_END );
	dwFileLen = ftell( pf );	
	dwSize = ((dwFileLen >> 2) + 1);	
	VERIFY(pnBuffer = new LONG[dwSize]);			
	if( NULL == *ppFileContent )
	{
		fclose( pf );
		return -1;
	}
	ZeroMemory(pnBuffer, sizeof(*pnBuffer) * dwSize);		
	fseek( pf, 0, SEEK_SET );
	fread( pnBuffer, 1, dwFileLen, pf );
	fclose( pf );
	*ppFileContent = (LPBYTE)pnBuffer;
	return dwFileLen;
}



#define   BUFFER_Max    (4096)

BOOL  WINAPI File_GenTitle(HWX_IN const TCHAR *ptchFilePath, HWX_OUT TCHAR *ptchTitle)
{  
	LONG nTitleLen = 0;
	const TCHAR * ptchFllwHead = ptchFilePath;  
	const TCHAR *  ptchFllwTail = ptchFilePath;
	BOOL blRet = TRUE;
	assert(ptchFilePath && ptchTitle);

	ptchFllwHead = _tcsrchr( ptchFilePath, _T('\\'));
	ptchFllwTail = _tcsrchr( ptchFilePath, _T('.'));
	if (!(ptchFllwHead && ptchFllwTail && (nTitleLen = ptchFllwTail - ptchFllwHead -  1) > 0))
	{
		blRet = FALSE;
		goto Exit_;
	}  
	_tcsncpy_s(ptchTitle, MAX_PATH, ptchFllwHead + 1, nTitleLen);

Exit_:  
	return blRet;
}
BOOL WINAPI File_GenName(HWX_IN const TCHAR *ptchFilePath, HWX_OUT TCHAR *ptchName)
{
	LONG nNameLen = 0;
	const TCHAR * ptchFllwHead = ptchFilePath;  
	const TCHAR * ptchFllwTail = ptchFilePath;
	BOOL blRet = TRUE;
	assert(ptchFilePath && ptchName);

	ptchFllwHead = _tcsrchr(ptchFilePath, _T('\\'));  
	ptchFllwTail = ptchFilePath + _tcslen(ptchFilePath);
	if (!(ptchFllwHead && ptchFllwTail && (nNameLen = ptchFllwTail - ptchFllwHead -  1) > 0))
	{
		blRet = FALSE;
		goto Exit_;
	}  
	_tcsncpy_s(ptchName, MAX_PATH, ptchFllwHead + 1, nNameLen);

Exit_:  
	return blRet;
}
BOOL WINAPI File_GenFilePath(HWX_IN const TCHAR *ptchFullPath, HWX_OUT TCHAR *ptchPath )
{
	assert(NULL != ptchFullPath);
	assert(NULL != ptchPath);

	const TCHAR *pchHead = ptchFullPath, *pchFllwHead = NULL;
	BOOL blRet = TRUE;
	LONG nPathLen;

	if (NULL == ptchFullPath || NULL == ptchPath)
	{
		blRet = FALSE;
		goto _Exit;
	}  
	if (!(pchFllwHead = _tcsrchr(pchHead, _T('\\'))))
	{
		blRet = FALSE;
		goto _Exit;
	}
	pchHead = pchFllwHead + 1;

	nPathLen = (LONG)_tcslen( ptchFullPath ) - (LONG)_tcslen( pchHead );
	assert(nPathLen > 0);
	_tcsncpy_s( ptchPath, MAX_PATH, ptchFullPath, nPathLen );

_Exit:

	return blRet;
}


BOOL WINAPI File_GenCurPath(HWX_OUT TCHAR * ptchPath)
{
	TCHAR atchPath[MAX_PATH];
	TCHAR *ptchIndex;
	LONG nLen = GetModuleFileName(NULL, atchPath, MAX_PATH);
	assert (nLen < MAX_PATH);
	VERIFY(NULL != (ptchIndex = _tcsrchr(atchPath, _T('\\'))));
	*(ptchIndex) = 0;
	_tcscpy_s(ptchPath, MAX_PATH, atchPath);  
	return TRUE;
}

BOOL WINAPI File_CreateFile(HWX_IN const TCHAR *ptchDstFilePath)
{
	FILE *pFile = NULL;  
	BOOL blRet = TRUE;
	assert(ptchDstFilePath);
	if (!ptchDstFilePath)
	{
		blRet = FALSE;
		goto _Error;
	}
	VERIFY(FALSE != File_CreateDirs(ptchDstFilePath));

	if (NULL == (pFile = _tfopen(ptchDstFilePath, _T("a+b"))))
	{
		blRet = FALSE;
	}
	fclose(pFile);
_Error:
	return blRet;
}

BOOL WINAPI File_CreateDirs(HWX_IN const TCHAR *ptchDstFilePath )
{  
	const TCHAR *pchTail = ptchDstFilePath;  
	TCHAR szPairentPath[MAX_PATH];
	BOOL blRet = TRUE;
	int nPairentPathLen;
	if (!ptchDstFilePath)
	{
		blRet = FALSE;
		goto _Error;
	}

	while(pchTail)
	{    
		pchTail = _tcschr( pchTail, _T('\\'));
		if(pchTail)
		{
			nPairentPathLen = (LONG)_tcslen( ptchDstFilePath ) - (LONG)_tcslen( pchTail );
			_tcsncpy_s(szPairentPath, MAX_PATH, ptchDstFilePath, nPairentPathLen);      
			_tmkdir(szPairentPath);      
			pchTail ++;
		}
	}
_Error:

	return blRet;
}

void WINAPI File_WriteBinary(HWX_IN const TCHAR *pchFilePath, HWX_IN const void *pvBuffer, HWX_IN size_t stSize, HWX_IN BOOL nIsAppend)
{  
	FILE *pFile = NULL;
	assert(NULL != pchFilePath && NULL != pvBuffer);  
	//�����ļ��� ��ò��ܴ����ļ�
	if (0xFFFFFFFF == GetFileAttributes(pchFilePath))
	{
		VERIFY(FALSE != File_CreateDirs(pchFilePath));
	}
	if(NULL == (pFile = _tfopen(pchFilePath, FALSE != nIsAppend? _T("a+b") : _T("wb"))))
	{    
		return;
	}  
	fwrite(pvBuffer, 1, stSize, pFile);
	fclose(pFile);
	return;  
}

//////////////////////////////////////////////////////////////////////////
void WINAPI File_PushTextA(HWX_IN const TCHAR *pchFilePath, HWX_IN const char *pchFormat, ...)
{
	assert(NULL != pchFilePath);

	FILE *pFile = NULL;
	char achBuffer[BUFFER_Max] = {0};
	va_list arglist;  
	//�����ļ��� ��ò��ܴ����ļ�
	if (0xFFFFFFFF == GetFileAttributes(pchFilePath))
	{
		File_CreateDirs(pchFilePath);
	}  
	if(NULL == (pFile = _tfopen(pchFilePath, _T("a+t"))))
	{    
		return;
	}

	va_start(arglist, pchFormat);
	_vsnprintf(achBuffer, BUFFER_Max, pchFormat, arglist);
	va_end(arglist);

	fwrite(achBuffer, sizeof(*achBuffer), strlen(achBuffer), pFile);
	//fflush(pFile);
	fclose(pFile);  
}


BOOL WINAPI XIsFileInUseW(LPCWSTR strFileName)  
{  	
	assert(strFileName);
	BOOL   blRet = FALSE;	
	if (0 != _waccess_s(strFileName, 0))
	{
		return blRet;
	}	
	HANDLE Handle = CreateFileW(strFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
	if (INVALID_HANDLE_VALUE != Handle)  
	{		
		CloseHandle(Handle); 
	}  
	else
	{		
		blRet = TRUE;
	}
	return   blRet;  
}
BOOL WINAPI XIsFileInUseA(LPCSTR strFileName)  
{  
	assert(strFileName);
	BOOL   blRet = FALSE;
	if (0 != _access_s(strFileName, 0))
	{
		return blRet;
	}
	HANDLE Handle = CreateFileA(strFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
	if (INVALID_HANDLE_VALUE != Handle)  
	{
		CloseHandle(Handle); 
	}  
	else
	{
		blRet = TRUE;
	}
	return   blRet;  
}

BOOL WINAPI XCreateDirA(HWX_IN LPCSTR pchDstFilePath )
{   
	LPCSTR pchTail = pchDstFilePath;  
	CHAR szPairentPath[MAX_PATH] = {0};
	BOOL blRet = TRUE;
	int nPairentPathLen;
	if (!pchDstFilePath)
	{
		blRet = FALSE;
		goto _Error;
	}

	while(pchTail)
	{    
		pchTail = strchr( pchTail, '\\');
		if(pchTail)
		{
			nPairentPathLen = (LONG)strlen( pchDstFilePath ) - (LONG)strlen( pchTail ) + 1;
			strncpy_s(szPairentPath, MAX_PATH, pchDstFilePath, nPairentPathLen); 
			szPairentPath[nPairentPathLen + 1] = 0;
			if (!_mkdir(szPairentPath))
			{
				blRet = FALSE;
				break;
			}            
			pchTail ++;
		}
	}
_Error:

	return blRet;
}
BOOL WINAPI XCreateDirW(HWX_IN LPCWSTR pwhDstFilePath )
{    
	LPCWSTR pwhTail = pwhDstFilePath;  
	WCHAR szPairentPath[MAX_PATH] = {0};
	BOOL blRet = TRUE;
	int nPairentPathLen;
	if (!pwhDstFilePath)
	{
		blRet = FALSE;
		goto _Error;
	}

	while(pwhTail)
	{    
		pwhTail = wcschr( pwhTail, L'\\');
		if(pwhTail)
		{
			nPairentPathLen = (LONG)wcslen( pwhDstFilePath ) - (LONG)wcslen( pwhTail ) + 1;
			wcsncpy_s(szPairentPath, MAX_PATH, pwhDstFilePath, nPairentPathLen);  
			szPairentPath[nPairentPathLen + 1] = 0;
			if (!_wmkdir(szPairentPath))
			{
				blRet = FALSE;
				break;
			}         
			pwhTail ++;
		}
	}
_Error:

	return blRet;
}

BOOL WINAPI XGenCurPathA(HWX_OUT LPSTR pchPath)
{
	CHAR achPath[MAX_PATH];
	CHAR *pchIndex;
	LONG nLen = GetModuleFileNameA(NULL, achPath, MAX_PATH);
	assert (nLen < MAX_PATH); 
	VERIFY(NULL != (pchIndex = strrchr(achPath, '\\')));
	*(pchIndex) = 0;
	strcpy_s(pchPath, MAX_PATH, achPath);  
	return TRUE;
}
BOOL WINAPI XGenCurPathW(HWX_OUT LPWSTR pwhPath)
{
	WCHAR awhPath[MAX_PATH];
	WCHAR *pwhIndex;
	LONG nLen = GetModuleFileNameW(NULL, awhPath, MAX_PATH);
	assert (nLen < MAX_PATH);
	VERIFY(NULL != (pwhIndex = wcsrchr(awhPath, L'\\')));
	*(pwhIndex) = 0;
	wcscpy_s(pwhPath, MAX_PATH, awhPath);  
	return TRUE;
}

BOOL WINAPI XCreateFileA(HWX_IN LPCSTR pchDstFilePath, BOOL blOverwrite)
{  
	BOOL blRet = FALSE;
	assert(pchDstFilePath);
	if (!pchDstFilePath)
	{
		blRet = FALSE;
		return blRet;
	}
	VERIFY(FALSE != XCreateDirA(pchDstFilePath));


	HANDLE nFileHandle = NULL;
	if (blOverwrite)
	{
		nFileHandle = CreateFileA(pchDstFilePath, GENERIC_READ | GENERIC_WRITE, 0, 
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  
	}
	else
	{
		nFileHandle = CreateFileA(pchDstFilePath, GENERIC_READ | GENERIC_WRITE, 0, 
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
	}  
	if (INVALID_HANDLE_VALUE != nFileHandle)  
	{
		CloseHandle(nFileHandle); 
		blRet = TRUE;
	}   
	return   blRet; 
}
BOOL WINAPI XCreateFileW(HWX_IN LPCWSTR pwhDstFilePath, BOOL blOverwrite)
{  
	BOOL blRet = FALSE;
	assert(pwhDstFilePath);
	if (!pwhDstFilePath)
	{
		blRet = FALSE;
		return blRet;
	}
	VERIFY(FALSE != XCreateDirW(pwhDstFilePath));


	HANDLE nFileHandle = NULL;
	if (blOverwrite)
	{
		nFileHandle = CreateFileW(pwhDstFilePath, GENERIC_READ | GENERIC_WRITE, 0, 
			NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  
	}
	else
	{
		nFileHandle = CreateFileW(pwhDstFilePath, GENERIC_READ | GENERIC_WRITE, 0, 
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
	}  
	if (INVALID_HANDLE_VALUE != nFileHandle)  
	{
		CloseHandle(nFileHandle); 
		blRet = TRUE;
	}   
	return   blRet; 
}

BOOL WINAPI XIsDirectoryExistW(LPCWSTR pwhDir)
{  
	wchar_t wchPath[_MAX_PATH];  
	BOOL blRet = TRUE;
	if (!_wgetcwd(wchPath, _MAX_PATH))
	{
		blRet = FALSE;
	}
	else
	{
		if (_wchdir(pwhDir))
		{
			blRet = FALSE;
		}
		else
		{
			_wchdir(wchPath);
		}    
	}
	return blRet;
}
BOOL WINAPI XIsDirectoryExistA(LPCSTR pchDir)
{
	char achPath[_MAX_PATH];  
	BOOL blRet = TRUE;
	if (!_getcwd(achPath, _MAX_PATH))
	{
		blRet = FALSE;
	}
	else
	{
		if (_chdir(pchDir))
		{
			blRet = FALSE;
		}
		else
		{
			_chdir(achPath);
		}    
	}
	return blRet;
}
BOOL WINAPI XIsFileExistW(LPCWSTR pwhPath)
{
	assert(pwhPath);
	BOOL blRet = TRUE;
	if (0 != _waccess(pwhPath, 0))
	{ 
		blRet = FALSE;
	}   
	return blRet;
}
BOOL WINAPI XIsFileExistA(LPCSTR pchPath)
{
	assert(pchPath);
	BOOL blRet = TRUE;
	if (0 != _access(pchPath, 0))
	{ 
		blRet = FALSE;
	}   
	return blRet;
}
BOOL WINAPI XRemoveFileW(LPCWSTR pwhPath)
{
	assert(pwhPath);
	BOOL blRet = TRUE;
	if (0 == _waccess(pwhPath, 0) && 0 != _wremove(pwhPath))
	{    
		_wchmod(pwhPath, _S_IREAD | _S_IWRITE);  
		blRet = (-1 != _wremove(pwhPath)) ? TRUE : FALSE;
	}   
	return blRet;
}
BOOL WINAPI XRemoveFileA(LPCSTR pchPath)
{
	assert(pchPath);
	BOOL blRet = TRUE;
	if (0 == _access(pchPath, 0) && 0 != remove(pchPath))
	{  
		_chmod(pchPath, _S_IREAD | _S_IWRITE);  
		blRet = (-1 != remove(pchPath)) ? TRUE : FALSE;
	}   
	return blRet;
}
BOOL WINAPI XDeleteDirectoryW(LPCWSTR pwhDir, BOOL blDelAll)
{
	BOOL blReturn = TRUE;
	WCHAR awhDir[_MAX_PATH];
	awhDir[0] = 0;
	wcscpy_s(awhDir, _MAX_PATH, pwhDir);
	LONG nTail = (LONG)wcslen(awhDir) - 1;
	if (nTail <= 0)
	{
		return FALSE;
	}
	if (awhDir[nTail] == L'\\' || awhDir[nTail] == L'/')
	{
		awhDir[nTail] = 0;
	}

	WCHAR awhFile[MAX_PATH];
	awhFile[0] = 0;
	swprintf_s(awhFile, MAX_PATH, L"%s\\*.*", awhDir);

	struct _wfinddata_t tFileSet;
	intptr_t hFile;	
	if ((hFile = _wfindfirst(awhFile, &tFileSet)) != -1L)
	{
		BOOL blFinded = TRUE;
		while (blFinded)
		{
			if (tFileSet.attrib & _A_SUBDIR)
			{
				if (!(0 == wcscmp(tFileSet.name,L"." )|| 0 == wcscmp(tFileSet.name, L"..")))
				{////ɾ����Ŀ¼ �ų�.��..Ŀ¼
					swprintf_s(awhFile, MAX_PATH, L"%s\\%s", awhDir, tFileSet.name);
					blReturn = XDeleteDirectoryW(awhFile, blDelAll);
				}			
			}
			else
			{	//ɾ���ļ�
				swprintf_s(awhFile, MAX_PATH, L"%s\\%s", awhDir, tFileSet.name);
				//�ж��ļ��Ƿ���ֻ����
				if (tFileSet.attrib & _A_RDONLY)
				{
					if (blDelAll && (0 == _wchmod(awhFile, _S_IREAD|_S_IWRITE)))
					{
						blReturn = (-1 != _wremove(awhFile)) ? TRUE : FALSE;
					}
					else
					{
						blReturn = FALSE;
					}
				}
				else
				{
					blReturn = (-1 != _wremove(awhFile)) ? TRUE : FALSE;
				}
			}
			blFinded = (0 == _wfindnext(hFile, &tFileSet))? TRUE : FALSE;
		}
	}
	_findclose(hFile);

	if (0 == _wrmdir(awhDir))
	{
		blReturn = TRUE;
	}
	return blReturn;
}
BOOL WINAPI XDeleteDirectoryA(LPCSTR pchDir, BOOL blDelAll)
{
	BOOL blReturn = TRUE;
	char achDir[_MAX_PATH];
	achDir[0] = 0;
	strcpy_s(achDir, _MAX_PATH, pchDir);
	LONG nTail = (LONG)strlen(achDir) - 1;
	if (nTail <= 0)
	{
		return FALSE;
	}
	if (achDir[nTail] == '\\' || achDir[nTail] == '/')
	{
		achDir[nTail] = 0;
	}

	char achFile[_MAX_PATH];
	achFile[0] = 0;
	sprintf_s(achFile, _MAX_PATH, "%s\\*.*", achDir);

	struct _finddata_t tFileSet;
	intptr_t hFile;	
	if ((hFile = _findfirst(achFile, &tFileSet)) != -1L)
	{
		BOOL blFinded = TRUE;
		while (blFinded)
		{
			if (tFileSet.attrib & _A_SUBDIR)
			{
				if (!(0 == strcmp(tFileSet.name, "." )|| 0 == strcmp(tFileSet.name, "..")))
				{////ɾ����Ŀ¼ �ų�.��..Ŀ¼
					sprintf_s(achFile, _MAX_PATH, "%s\\%s", achDir, tFileSet.name);
					blReturn = XDeleteDirectoryA(achFile, blDelAll);
				}			
			}
			else
			{	//ɾ���ļ�
				sprintf_s(achFile, _MAX_PATH, "%s\\%s", achDir, tFileSet.name);
				//�ж��ļ��Ƿ���ֻ����
				if (tFileSet.attrib & _A_RDONLY)
				{
					if (blDelAll && (0 == _chmod(achFile, _S_IREAD|_S_IWRITE)))
					{
						blReturn = (-1 != remove(achFile)) ? TRUE : FALSE;
					}
					else
					{
						blReturn = FALSE;
					}
				}
				else
				{
					blReturn = (-1 != remove(achFile)) ? TRUE : FALSE;
				}
			}
			blFinded = (0 == _findnext(hFile, &tFileSet))? TRUE : FALSE;
		}
	}
	_findclose(hFile);

	if (0 == _rmdir(achDir))
	{
		blReturn = TRUE;
	}
	return blReturn;
}
