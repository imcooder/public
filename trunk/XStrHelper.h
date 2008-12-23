/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XStrHelper.h					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/06/21
*********************************************************************/
#ifndef HWX_XSTRHELPER_H
#define HWX_XSTRHELPER_H
#pragma once
#include "Ext_Type.h"


#ifdef _UNICODE
#define StrChrChr     Helper_StrChrChrW
#define TCharDup      Helper_StrDupW
#define WCharToTChar  Helper_StrDupW
#define TCharToWChar  Helper_StrDupW
#define TCharToChar   Helper_WCharToChar
#define GetPathDirectory Helper_GetPathDirectoryW
#define StrMove			 Helper_StrMoveW
#define StrMove_S			 Helper_StrMoveW_S
#define StrMid				Helper_StrMidW
#define StrRight			Helper_StrRightW
#define StrLeft				Helper_StrLeftW
#define StrTrimLeft		Helper_StrTrimLeftW
#define StrTrimRight	Helper_StrTrimRightW
#define StrTrim				Helper_StrTrimW
#define StrUpper			Helper_StrUpperW
#define StrGetNumber	Helper_StrGetNumberW
#define StrGetFloat		Helper_StrGetFloatW
#define StrGetHex			Helper_StrGetHexW
#define StrReverse		Helper_StrReverseW



#else

#define StrChrChr     Helper_StrChrChrA
#define TCharDup      Helper_StrDupA
#define WCharToTChar  Helper_WCharToChar
#define TCharToWChar  Helper_CharToWChar
#define TCharToChar   Helper_StrDupA
#define GetPathDirectory Helper_GetPathDirectoryA
#define StrMove			 Helper_StrMoveA
#define StrMove_S			 Helper_StrMoveA_S
#define StrMid				Helper_StrMidA
#define StrRight			Helper_StrRightA
#define StrLeft				Helper_StrLeftA
#define StrTrimLeft		Helper_StrTrimLeftA
#define StrTrimRight		Helper_StrTrimRightA
#define StrTrim				Helper_StrTrimA
#define StrUpper			Helper_StrUpperA
#define StrGetNumber	Helper_StrGetNumberA
#define StrGetFloat		Helper_StrGetFloatA
#define StrGetHex			Helper_StrGetHexA
#define StrReverse		Helper_StrReverseA




#endif


#ifndef WCharToChar
#define WCharToChar		Helper_WCharToChar
#endif

#ifndef CharToWChar		
#define CharToWChar		Helper_CharToWChar
#endif


#ifdef __cplusplus
extern "C"{
#endif

  DLLXEXPORT void WINAPI Helper_StrChrChrA(LPSTR, const CHAR&, const CHAR&);
  DLLXEXPORT void  WINAPI Helper_StrChrChrW(LPWSTR, const WCHAR&, const WCHAR&);

  DLLXEXPORT LPSTR  WINAPI Helper_WCharToChar(LPCWSTR);
  DLLXEXPORT LPWSTR WINAPI Helper_CharToWChar(LPCSTR);  

  DLLXEXPORT LPWSTR WINAPI Helper_StrDupW(LPCWSTR);
  DLLXEXPORT LPSTR  WINAPI Helper_StrDupA(LPCSTR);


	DLLXEXPORT LONG WINAPI Helper_GetPathDirectoryW(LPCWSTR, LPWSTR);
	DLLXEXPORT LONG WINAPI Helper_GetPathDirectoryA(LPCSTR, LPSTR);


	LPWSTR WINAPI Helper_StrMoveW(LPWSTR, LPCWSTR);
	LPSTR WINAPI Helper_StrMoveA(LPSTR, LPCSTR);
	LPWSTR WINAPI Helper_StrMoveW_S(LPWSTR, LONG, LPCWSTR);
	LPSTR WINAPI Helper_StrMoveA_S(LPSTR, LONG, LPCSTR);

	LONG WINAPI Helper_StrMidW(LPWSTR pszString, LONG nIndex, UINT nCount);
	LONG WINAPI Helper_StrMidA(LPSTR pszString, LONG nIndex, UINT nCount);
	LONG WINAPI Helper_StrRightW(LPWSTR pszString, UINT nCount);
	LONG WINAPI Helper_StrRightA(LPSTR pszString, UINT nCount);
	LONG WINAPI Helper_StrLeftW(LPWSTR pszString, UINT nCount);
	LONG WINAPI Helper_StrLeftA(LPSTR pszString, UINT nCount);
	void WINAPI Helper_StrTrimLeftW(LPWSTR pszString, LPCWSTR pwhTag);
	void WINAPI Helper_StrTrimLeftA(LPSTR pszString, LPCSTR pszTag);
	void WINAPI Helper_StrTrimRightW(LPWSTR pszString, LPCWSTR pszTag);	
	void WINAPI Helper_StrTrimRightA(LPSTR pszString, LPCSTR pszTag);
	void WINAPI Helper_StrTrimW(LPWSTR pszString, LPCWSTR pszTag);
	void WINAPI Helper_StrTrimA(LPSTR pszString, LPCSTR pszTag);
	void WINAPI Helper_StrUpperW(LPWSTR pszString);
	void WINAPI Helper_StrUpperA(LPSTR pszString);	
	LONG WINAPI Helper_StrGetNumberW(LPCWSTR pszString);
	LONG WINAPI Helper_StrGetNumberA(LPCSTR pszString);
	double WINAPI Helper_StrGetFloatW(LPCWSTR pszString);
	double WINAPI Helper_StrGetFloatA(LPCSTR pszString);
	LONG WINAPI Helper_StrGetHexW(LPCWSTR pszString);
	LONG WINAPI Helper_StrGetHexA(LPCSTR pszString);
	void WINAPI Helper_StrReverseW(LPWSTR pszString);
	void WINAPI Helper_StrReverseA(LPSTR pszString);
	
#ifdef __cplusplus
}
#endif


#endif //HWX_XSTRHELPER_H