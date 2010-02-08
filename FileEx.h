#ifndef HWX_FILEEX_H
#define HWX_FILEEX_H
#include "Ext_Type.h"




#ifdef _UNICODE

#define HWLoadFile			 HWLoadFileW
#define HWIsFileInUse    XIsFileInUseW
#define HWCreateDir      XCreateDirW
#define HWGenCurPath     XGenCurPathW
#define HWCreateFile     XCreateFileW
#define HWIsDirectoryExist        XIsDirectoryExistW
#define HWIsFileExist    XIsFileExistW
#define HWRemoveFile     XRemoveFileW
#define HWDeleteDirectory  XDeleteDirectoryW
#define HWIsValidDirectory		XUE_IsValidDirectoryW
#define HWIsValidFile					XUE_IsValidFileW	
#define HWCopyFolder					XUE_CopyFolderW
#else

#define HWLoadFile			 HWLoadFileA
#define HWIsFileInUse    XIsFileInUseA
#define HWCreateDir      XCreateDirA
#define HWGenCurPath     XGenCurPathA
#define HWCreateFile     XCreateFileA
#define HWIsDirectoryExist        XIsDirectoryExistA
#define HWIsFileExist    XIsFileExistA
#define HWRemoveFile     XRemoveFileA
#define HWDeleteDirectory  XDeleteDirectoryA
#define HWIsValidDirectory		XUE_IsValidDirectoryA
#define HWIsValidFile					XUE_IsValidFileA	
#define HWCopyFolder					XUE_CopyFolderA
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
	DLLXEXPORT LONG WINAPI HWLoadFileA( LPCSTR, LPBYTE *);
	DLLXEXPORT LONG WINAPI HWLoadFileW(LPCWSTR, LPBYTE *);
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

	DLLXEXPORT  BOOL    WINAPI    XIsFileInUseA(LPCSTR strFileName); 
	DLLXEXPORT  BOOL    WINAPI    XIsFileInUseW(LPCWSTR strFileName); 
	DLLXEXPORT  BOOL    WINAPI    XCreateDirW(LPCWSTR pwhDstFilePath);
	DLLXEXPORT  BOOL    WINAPI    XCreateDirA(LPCSTR pchDstFilePath);
	DLLXEXPORT  BOOL    WINAPI    XGenCurPathW(HWX_OUT LPCWSTR pwhPath);
	DLLXEXPORT  BOOL    WINAPI    XGenCurPathA(HWX_OUT LPCSTR pchPath);
	DLLXEXPORT  BOOL    WINAPI    XCreateFileW(HWX_IN LPCWSTR pwhDstFilePath, BOOL blOverwrite = TRUE);
	DLLXEXPORT  BOOL    WINAPI    XCreateFileA(HWX_IN LPCSTR pwhDstFilePath, BOOL blOverwrite = TRUE);
	DLLXEXPORT  BOOL    WINAPI    XIsDirectoryExistW(LPCWSTR pwhDir);
	DLLXEXPORT  BOOL    WINAPI    XIsDirectoryExistA(LPCSTR pchDir);
	DLLXEXPORT  BOOL    WINAPI    XIsFileExistW(LPCWSTR );
	DLLXEXPORT  BOOL    WINAPI    XIsFileExistA(LPCSTR );
	DLLXEXPORT  BOOL    WINAPI    XRemoveFileW(LPCWSTR );
	DLLXEXPORT  BOOL    WINAPI    XRemoveFileA(LPCSTR );
	DLLXEXPORT  BOOL    WINAPI    XDeleteDirectoryW(LPCWSTR , BOOL blDelAll);
	DLLXEXPORT  BOOL    WINAPI    XDeleteDirectoryA(LPCSTR , BOOL blDelAll);

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