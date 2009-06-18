#include "stdafx.h"
#include <tchar.h>
#include <stdio.h>
#include "FileEx.h"
#include "Ext_Memory.h"
#include <tchar.h>
#include <assert.h>
#include <stdio.h>
#include "XStrhelper.h"
#include <StrSafe.h>
//#include <io.h>
#include <stdio.h>
//#include <direct.h>
//#include <sys/stat.h>


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
	if( !pnBuffer )
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
	if( !pnBuffer)
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
			//_tmkdir(szPairentPath);   
			CreateDirectory(szPairentPath, NULL);
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
	//创建文件夹 免得不能创建文件
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
	//创建文件夹 免得不能创建文件
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
	DWORD dwFileAttr = GetFileAttributesW(strFileName);
	if (dwFileAttr == (DWORD)(-1))
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
	DWORD dwFileAttr = (DWORD)(-1);
#ifndef WINCE
	{
		dwFileAttr	= GetFileAttributesA(strFileName);
	}
#endif
	if (dwFileAttr == (DWORD)(-1))
	{
		return blRet;
	}
	HANDLE Handle = NULL;
#ifndef WINCE
	{
		Handle = CreateFileA(strFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);  
	}
#endif
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
#ifndef WINCE
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
				nPairentPathLen = (LONG)strlen( pchDstFilePath ) - (LONG)strlen( pchTail )/* + 1*/;
				strncpy_s(szPairentPath, MAX_PATH, pchDstFilePath, nPairentPathLen); 
				szPairentPath[nPairentPathLen] = 0;
				if (!CreateDirectoryA (szPairentPath, NULL))
				{
					if (GetLastError() != ERROR_ALREADY_EXISTS)
					{
						blRet = FALSE;
						break;
					}				
				}            
				pchTail ++;
			}
		}
_Error:
	return blRet;
}
#endif

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
			nPairentPathLen = (LONG)wcslen( pwhDstFilePath ) - (LONG)wcslen( pwhTail );
			wcsncpy_s(szPairentPath, MAX_PATH, pwhDstFilePath, nPairentPathLen);  
			szPairentPath[nPairentPathLen] = 0;
			if (!CreateDirectoryW(szPairentPath, NULL))
			{
				if (GetLastError() != ERROR_ALREADY_EXISTS)
				{
					blRet = FALSE;
					break;
				}			
			}         
			pwhTail ++;
		}
	}
_Error:

	return blRet;
}
#ifndef WINCE
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
#endif
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

#ifndef WINCE
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
#endif
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
	DWORD dwFileAtti = GetFileAttributesW(pwhDir);
	if ((DWORD)(-1) == dwFileAtti)
	{
		blRet = FALSE;
	}
	if (dwFileAtti & FILE_ATTRIBUTE_DIRECTORY)
	{

	}
	else
	{
		blRet = FALSE;
	}
	/*
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
		}*/
	
	return blRet;
}
#ifndef WINCE
BOOL WINAPI XIsDirectoryExistA(LPCSTR pchDir)
{
	char achPath[_MAX_PATH];  
	BOOL blRet = TRUE;
	DWORD dwFileAtti = GetFileAttributesA(pchDir);
	if ((DWORD)(-1) == dwFileAtti)
	{
		blRet = FALSE;
	}
	if (dwFileAtti & FILE_ATTRIBUTE_DIRECTORY)
	{

	}
	else
	{
		blRet = FALSE;
	}
/*	
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
		}*/
	
	return blRet;
}
#endif
BOOL WINAPI XIsFileExistW(LPCWSTR pwhPath)
{
	assert(pwhPath);
	BOOL blRet = TRUE;
	DWORD dwFileAttr = GetFileAttributesW(pwhPath);
	if ((DWORD)(-1) == dwFileAttr)
	{
		blRet = FALSE;
	}
	/*
	if (0 != _waccess(pwhPath, 0))
		{ 
			blRet = FALSE;
		} */
	  
	return blRet;
}
#ifndef WINCE
BOOL WINAPI XIsFileExistA(LPCSTR pchPath)
{
	assert(pchPath);
	BOOL blRet = TRUE;
	DWORD dwFileAttr = GetFileAttributesA(pchPath);
	if ((DWORD)(-1) == dwFileAttr)
	{
		blRet = FALSE;
	}
	/*
	if (0 != _access(pchPath, 0))
		{ 
			blRet = FALSE;
		}  
		*/
	 
	return blRet;
}
#endif
BOOL WINAPI XRemoveFileW(LPCWSTR pwhPath)
{
	assert(pwhPath);
	BOOL blRet = TRUE;
	BOOL isExists = XIsFileExistW(pwhPath);
	if (isExists)
	{
		blRet = DeleteFileW(pwhPath);
	}
/*
	
		if (0 == _waccess(pwhPath, 0) && 0 != _wremove(pwhPath))
		{    
			_wchmod(pwhPath, _S_IREAD | _S_IWRITE);  
			blRet = (-1 != _wremove(pwhPath)) ? TRUE : FALSE;
		} */
	  
	return blRet;
}
#ifndef WINCE
BOOL WINAPI XRemoveFileA(LPCSTR pchPath)
{
	assert(pchPath);
	BOOL blRet = TRUE;
	BOOL bExists = XIsFileExistA(pchPath);
	if (bExists)
	{
		blRet = DeleteFileA(pchPath);
	}
	/*
	if (0 == _access(pchPath, 0) && 0 != remove(pchPath))
		{  
			_chmod(pchPath, _S_IREAD | _S_IWRITE);  
			blRet = (-1 != remove(pchPath)) ? TRUE : FALSE;
		}   */
	
	return blRet;
}
#endif
BOOL WINAPI XDeleteDirectoryW(LPCWSTR pwhDir, BOOL blDelAll)
{
	BOOL blReturn = TRUE;
	WCHAR awhDir[_MAX_PATH];
	awhDir[0] = 0;
	StringCchCopyW(awhDir, _countof(awhDir), pwhDir);
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
	StringCchPrintfW(awhFile, _countof(awhFile), L"%s\\*.*", awhDir);

	WIN32_FIND_DATAW tFileSet;
	HANDLE hFile = NULL;	
	if ((hFile = FindFirstFileW(awhFile, &tFileSet)) != INVALID_HANDLE_VALUE )
	{
		BOOL blFinded = TRUE;
		while (blFinded)
		{
			if (tFileSet.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (!(0 == wcscmp(tFileSet.cFileName,L"." )|| 0 == wcscmp(tFileSet.cFileName, L"..")))
				{////删除子目录 排除.和..目录
					StringCchPrintfW(awhFile, _countof(awhFile), L"%s\\%s", awhDir, tFileSet.cFileName);
					blReturn = XDeleteDirectoryW(awhFile, blDelAll);
				}			
			}
			else
			{	//删除文件
				StringCchPrintfW(awhFile, _countof(awhFile), L"%s\\%s", awhDir, tFileSet.cFileName);
				//判定文件是否是只读的
				if (tFileSet.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
				{
					if (blDelAll)
					{
						tFileSet.dwFileAttributes &= ~FILE_ATTRIBUTE_READONLY;
						SetFileAttributes(awhFile, tFileSet.dwFileAttributes);
						blReturn = XRemoveFileW(awhFile);
						//blReturn = (-1 != _wremove(awhFile)) ? TRUE : FALSE;
					}
					else
					{
						blReturn = FALSE;
					}
				}
				else
				{
					//blReturn = (-1 != _wremove(awhFile)) ? TRUE : FALSE;
					blReturn = XRemoveFileW(awhFile);
				}
			}
			blFinded = (0 == FindNextFileW(hFile, &tFileSet))? TRUE : FALSE;
		}
	}
	FindClose(hFile);
	
	blReturn = RemoveDirectoryW(awhDir);

	return blReturn;
}
#ifndef WINCE
BOOL WINAPI XDeleteDirectoryA(LPCSTR pchDir, BOOL blDelAll)
{
	BOOL blReturn = TRUE;
	char achDir[_MAX_PATH];
	achDir[0] = 0;
	StringCchCopyA(achDir, _countof(achDir), pchDir);
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
	StringCchPrintfA(achFile, _countof(achFile), "%s\\*.*", achDir);

	WIN32_FIND_DATAA tFileSet;
	HANDLE hFile = NULL;	
	if ((hFile = FindFirstFileA(achFile, &tFileSet)) != INVALID_HANDLE_VALUE)
	{
		BOOL blFinded = TRUE;
		while (blFinded)
		{
			if (tFileSet.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (!(0 == strcmp(tFileSet.cFileName, "." )|| 0 == strcmp(tFileSet.cFileName, "..")))
				{////删除子目录 排除.和..目录
					StringCchPrintfA(achFile, _countof(achFile), "%s\\%s", achDir, tFileSet.cFileName);
					blReturn = XDeleteDirectoryA(achFile, blDelAll);
				}			
			}
			else
			{	//删除文件
				StringCchPrintfA(achFile, _countof(achFile), "%s\\%s", achDir, tFileSet.cFileName);
				//判定文件是否是只读的
				if (tFileSet.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
				{
					if (blDelAll)
					{
						tFileSet.dwFileAttributes &= ~FILE_ATTRIBUTE_READONLY;
						SetFileAttributesA(achFile, tFileSet.dwFileAttributes);
						blReturn = XRemoveFileA(achFile);
						//blReturn = (-1 != remove(achFile)) ? TRUE : FALSE;
					}
					else
					{
						blReturn = FALSE;
					}
				}
				else
				{
					blReturn = XRemoveFileA(achFile);
					//blReturn = (-1 != remove(achFile)) ? TRUE : FALSE;
				}
			}
			blFinded = (0 == FindNextFileA(hFile, &tFileSet))? TRUE : FALSE;
			//blFinded = (0 == _findnext(hFile, &tFileSet))? TRUE : FALSE;
		}
	}
	FindClose(hFile);

	blReturn = RemoveDirectoryA(achDir);
	return blReturn;
}
#endif