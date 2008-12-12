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
#else

#define StrChrChr     Helper_StrChrChrA
#define TCharDup      Helper_StrDupA
#define WCharToTChar  Helper_WCharToChar
#define TCharToWChar  Helper_CharToWChar
#define TCharToChar   Helper_StrDupA
#define GetPathDirectory Helper_GetPathDirectoryA
#define StrMove			 Helper_StrMoveA
#define StrMove_S			 Helper_StrMoveA_S
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
#ifdef __cplusplus
}
#endif


#endif //HWX_XSTRHELPER_H