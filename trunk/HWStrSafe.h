/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	HWStrSafe.h					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/06/21
*********************************************************************/
#ifndef HWX_HWSTRSAFE_H
#define HWX_HWSTRSAFE_H
#pragma once
#include <strsafe.h>
#include "Ext_Type.h"


#ifdef _UNICODE

#define StringToken			XUE_StringTokenW	
#define StringMid				XUE_StringMidW
#define StringRight			XUE_StringRightW
#define StringLeft			XUE_StringLeftW
#define StringTrimLeft	XUE_StringTrimLeftW
#define StringTrimRight	XUE_StringTrimRightW
#define StringTrim			XUE_StringTrimW
#define StringUpper			XUE_StringUpperW
#define StringLower			XUE_StringLowerW
#define StringReverse		XUE_StringReverseW
#define StringToLong		XUE_StringToLongW
#define StringToFloat		XUE_StringToFloatW
#define StringToDword		XUE_StringToDwordW
#define StringCchToGuid	XUE_tringCchToGuidW
#define StringCchFromGuid	XUE_StringCchFromGuidW


#else

#define StringToken			XUE_StringTokenA
#define StringMid				XUE_StringMidA
#define StringRight			XUE_StringRightA
#define StringLeft			XUE_StringLeftA
#define StringTrimLeft	XUE_StringTrimLeftA
#define StringTrimRight	XUE_StringTrimRightA
#define StringTrim			XUE_StringTrimA
#define StringUpper			XUE_StringUpperA
#define StringLower			XUE_StringLowerA
#define StringReverse		XUE_StringReverseA
#define StringToLong		XUE_StringToLongA
#define StringToFloat		XUE_StringToFloatA
#define StringToDword		XUE_StringToDwordA
#define StringCchToGuid	XUE_StringCchToGuidA
#define StringCchFromGuid	XUE_StringCchFromGuidA

#endif



#ifdef __cplusplus
extern "C"{
#endif

	CHAR*		WINAPI XUE_StringTokenA(CHAR*,	const CHAR*,	CHAR **);
	WCHAR*	WINAPI XUE_StringTokenW(WCHAR*,	const WCHAR*,	WCHAR **);
	LONG		WINAPI XUE_StringMidW(LPWSTR pszString, LONG nIndex, UINT nCount);
	LONG		WINAPI XUE_StringMidA(LPSTR pszString, LONG nIndex, UINT nCount);
	LONG		WINAPI XUE_StringRightW(LPWSTR pszString, UINT nCount);
	LONG		WINAPI XUE_StringRightA(LPSTR pszString, UINT nCount);
	LONG		WINAPI XUE_StringLeftW(LPWSTR pszString, UINT nCount);
	LONG		WINAPI XUE_StringLeftA(LPSTR pszString, UINT nCount);
	void		WINAPI XUE_StringTrimLeftW(LPWSTR pszString, LPCWSTR pwhTag);
	void		WINAPI XUE_StringTrimLeftA(LPSTR pszString, LPCSTR pszTag);
	void		WINAPI XUE_StringTrimRightW(LPWSTR pszString, LPCWSTR pszTag);	
	void		WINAPI XUE_StringTrimRightA(LPSTR pszString, LPCSTR pszTag);
	void		WINAPI XUE_StringTrimW(LPWSTR pszString, LPCWSTR pszTag);
	void		WINAPI XUE_StringTrimA(LPSTR pszString, LPCSTR pszTag);
	WCHAR*	WINAPI XUE_StringUpperW(LPWSTR pszString);
	CHAR*		WINAPI XUE_StringUpperA(LPSTR pszString);
	WCHAR*	WINAPI XUE_StringLowerW(LPWSTR pszString);
	CHAR*		WINAPI XUE_StringLowerA(LPSTR pszString);
	WCHAR*	WINAPI XUE_StringReverseW(LPWSTR pszString);
	CHAR*		WINAPI XUE_StringReverseA(LPSTR pszString);
	LONG		WINAPI XUE_StringWCharToChar(LPCWSTR pszStr, LONG nLen, LPSTR pszString, LONG nMaxLen);
	LONG		WINAPI XUE_StringCharToWChar(LPCSTR pszStr, LONG nLen, LPWSTR pszString, LONG nMaxLen);
	LONG		WINAPI XUE_StringToLongW(LPCWSTR pszNum);
	LONG		WINAPI XUE_StringToLongA(LPCSTR pszNum);
	float		WINAPI XUE_StringToFloatW(LPCWSTR pszNum);
	float		WINAPI XUE_StringToFloatA(LPCSTR pszNum);
	DWORD		WINAPI XUE_StringToDwordW(LPCWSTR pszNum);
	DWORD		WINAPI XUE_StringToDwordA(LPCSTR pszNum);
	LONG		WINAPI XUE_tringCchToGuidW(LPCWSTR pszString, LONG nCount, GUID* pGUID);
	LONG		WINAPI XUE_StringCchToGuidA(LPCSTR pszString, LONG nCount, GUID* pGUID);
	LONG		WINAPI XUE_StringCchFromGuidW(const GUID* pGUID, LPWSTR pszString, LONG nCount);
	LONG		WINAPI XUE_StringCchFromGuidA(const GUID* pGUID, LPSTR pszString, LONG nCount);
	BOOL		WINAPI XUE_StringPathAppendW( LPWSTR pszPath,DWORD dwLen, LPCWSTR pszFile);
	BOOL		WINAPI XUE_StringPathAppendA( LPSTR pszPath, DWORD dwLen, LPCSTR	pszFile);
#ifdef __cplusplus
}
#endif


#endif //HWX_HWSTRSAFE_H