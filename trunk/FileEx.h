#ifndef HWX_FILEEX_H
#define HWX_FILEEX_H
#include "Ext_Type.h"




#ifdef _UNICODE

#define HWLoadFile											XUE_LoadFileW
#define HWIsFileInUse										XUE_IsFileInUseW
#define HWCreateDir											XUE_CreateFolderW
#define HWGenCurPath										XUE_GenCurPathW
#define HWCreateFile										XUE_CreateFileW
#define HWCreateFolder									XUE_CreateFolderW
#define HWIsDirectoryExist							XUE_IsDirectoryExistW
#define HWIsFileExist										XUE_IsFileExistW
#define HWRemoveFile										XUE_RemoveFileW
#define HWRemoveFolder									XUE_RemoveFolderW
#define HWDeleteDirectory								XUE_RemoveFolderW
#define HWIsValidDirectory							XUE_IsValidDirectoryW
#define HWIsValidFile										XUE_IsValidFileW	
#define HWCopyFolder										XUE_CopyFolderW
#else

#define HWLoadFile											XUE_LoadFileA
#define HWIsFileInUse										XUE_IsFileInUseA
#define HWCreateDir											XUE_CreateFolderA
#define HWGenCurPath										XUE_GenCurPathA
#define HWCreateFile										XUE_CreateFileA
#define HWCreateFolder									XUE_CreateFolderA
#define HWIsDirectoryExist							XUE_IsDirectoryExistA
#define HWIsFileExist										XUE_IsFileExistA
#define HWRemoveFile										XUE_RemoveFileA
#define HWRemoveFolder									XUE_RemoveFolderA
#define HWDeleteDirectory								XUE_RemoveFolderA
#define HWIsValidDirectory							XUE_IsValidDirectoryA
#define HWIsValidFile										XUE_IsValidFileA	
#define HWCopyFolder										XUE_CopyFolderA
#endif


/*
#ifdef __cplusplus
extern "C"{
#endif*/

	//////////////////////////////////////////////////////////////////////////
	// >= 0 :file size
	// -1   :	Not enough memory
	// -2		: file not found	
	//////////////////////////////////////////////////////////////////////////
	DLLXEXPORT LONG WINAPI XUE_LoadFileA( LPCSTR, LPBYTE *);
	DLLXEXPORT LONG WINAPI XUE_LoadFileW(LPCWSTR, LPBYTE *);
	//////////////////////////////////////////////////////////////////////////
	//	>=0 if lpwstr != NULL the strlen need
	//
	//////////////////////////////////////////////////////////////////////////
	DLLXEXPORT BOOL WINAPI	File_GenTitle(HWX_IN const TCHAR *pchFileName, HWX_OUT TCHAR *ptchTitle);
	DLLXEXPORT BOOL  WINAPI File_GenName(HWX_IN const TCHAR *pchFilePath,  HWX_OUT TCHAR *pchName);
	DLLXEXPORT BOOL  WINAPI File_CreateFile(HWX_IN const TCHAR * ptchDstFilePath);
	DLLXEXPORT BOOL  WINAPI File_CreateDirs(HWX_IN const TCHAR *ptchDstFilePath );
	DLLXEXPORT BOOL  WINAPI File_GenCurPath(HWX_OUT TCHAR * ptchPath);
	DLLXEXPORT void  WINAPI File_PushBinary(HWX_IN const TCHAR *pchFileName, HWX_IN const void *pvBuffer, HWX_IN size_t stSize);
	DLLXEXPORT void  WINAPI File_WriteBinary(HWX_IN const TCHAR *pchFileName, HWX_IN const void *pvBuffer, HWX_IN size_t stSize, HWX_IN BOOL nIsAppend = TRUE);
	DLLXEXPORT void  WINAPI File_PushTextA(HWX_IN const TCHAR *pchFilePath, HWX_IN const char *pchFormat, ...);

	DLLXEXPORT  BOOL    WINAPI    XUE_IsFileInUseA(LPCSTR strFileName); 
	DLLXEXPORT  BOOL    WINAPI    XUE_IsFileInUseW(LPCWSTR strFileName); 
	DLLXEXPORT  BOOL    WINAPI    XUE_CreateFolderW(LPCWSTR pwhDstFilePath);
	DLLXEXPORT  BOOL    WINAPI    XUE_CreateFolderA(LPCSTR pchDstFilePath);
	DLLXEXPORT  BOOL    WINAPI    XUE_GenCurPathW(HWX_OUT LPCWSTR pwhPath);
	DLLXEXPORT  BOOL    WINAPI    XUE_GenCurPathA(HWX_OUT LPCSTR pchPath);
	DLLXEXPORT  BOOL    WINAPI    XUE_CreateFileW(HWX_IN LPCWSTR pwhDstFilePath, BOOL blOverwrite = TRUE);
	DLLXEXPORT  BOOL    WINAPI    XUE_CreateFileA(HWX_IN LPCSTR pwhDstFilePath, BOOL blOverwrite = TRUE);
	DLLXEXPORT  BOOL    WINAPI    XUE_IsDirectoryExistW(LPCWSTR pwhDir);
	DLLXEXPORT  BOOL    WINAPI    XUE_IsDirectoryExistA(LPCSTR pchDir);
	DLLXEXPORT  BOOL    WINAPI    XUE_IsFileExistW(LPCWSTR );
	DLLXEXPORT  BOOL    WINAPI    XUE_IsFileExistA(LPCSTR );
	DLLXEXPORT  BOOL    WINAPI    XUE_RemoveFileW(LPCWSTR );
	DLLXEXPORT  BOOL    WINAPI    XUE_RemoveFileA(LPCSTR );
	DLLXEXPORT  BOOL    WINAPI    XUE_RemoveFolderW(LPCWSTR , BOOL blDelAll);
	DLLXEXPORT  BOOL    WINAPI    XUE_RemoveFolderA(LPCSTR , BOOL blDelAll);

	DLLXEXPORT BOOL			WINAPI		XUE_IsValidFileW(LPCWSTR pszFile);
	DLLXEXPORT BOOL			WINAPI		XUE_IsValidFileA(LPCSTR pszFile);;
	DLLXEXPORT BOOL			WINAPI		XUE_IsValidDirectoryW(LPCWSTR pszDir); 
	DLLXEXPORT BOOL			WINAPI		XUE_IsValidDirectoryA(LPCSTR pszDir);  
	DLLXEXPORT BOOL			WINAPI		XUE_CopyFolderW(LPCWSTR pszSrc, LPCWSTR pszDes, BOOL bOverWrite);
	DLLXEXPORT BOOL			WINAPI		XUE_CopyFolderA(LPCSTR pszSrc, LPCSTR pszDes, BOOL bOverWrite);
	//
	LONG WINAPI HWXUE_GetFileName(const TCHAR *pszFilePath, TCHAR *pszName, LONG nMax);
/*
#ifdef __cplusplus
}
#endif*/


#endif//HWX_FILEEX_H