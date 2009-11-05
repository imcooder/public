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

#define StringToken			StringTokenW	
#define StringMid				StringMidW
#define StringRight			StringRightW
#define StringLeft			StringLeftW
#define StringTrimLeft	StringTrimLeftW
#define StringTrimRight	StringTrimRightW
#define StringTrim			StringTrimW
#define StringUpper			StringUpperW
#define StringLower			StringLowerW
#define StringReverse		StringReverseW
#define StringToLong		StringToLongW
#define StringToFloat		StringToFloatW
#define StringToDword		StringToDwordW
#else

#define StringToken			StringTokenA
#define StringMid				StringMidA
#define StringRight			StringRightA
#define StringLeft			StringLeftA
#define StringTrimLeft	StringTrimLeftA
#define StringTrimRight	StringTrimRightA
#define StringTrim			StringTrimA
#define StringUpper			StringUpperA
#define StringLower			StringLowerA
#define StringReverse		StringReverseA
#define StringToLong		StringToLongA
#define StringToFloat		StringToFloatA
#define StringToDword		StringToDwordA
#endif



#ifdef __cplusplus
extern "C"{
#endif

	CHAR*		WINAPI StringTokenA(CHAR*,	const CHAR*,	CHAR **);
	WCHAR*	WINAPI StringTokenW(WCHAR*,	const WCHAR*,	WCHAR **);
	LONG		WINAPI StringMidW(LPWSTR pszString, LONG nIndex, UINT nCount);
	LONG		WINAPI StringMidA(LPSTR pszString, LONG nIndex, UINT nCount);
	LONG		WINAPI StringRightW(LPWSTR pszString, UINT nCount);
	LONG		WINAPI StringRightA(LPSTR pszString, UINT nCount);
	LONG		WINAPI StringLeftW(LPWSTR pszString, UINT nCount);
	LONG		WINAPI StringLeftA(LPSTR pszString, UINT nCount);
	void		WINAPI StringTrimLeftW(LPWSTR pszString, LPCWSTR pwhTag);
	void		WINAPI StringTrimLeftA(LPSTR pszString, LPCSTR pszTag);
	void		WINAPI StringTrimRightW(LPWSTR pszString, LPCWSTR pszTag);	
	void		WINAPI StringTrimRightA(LPSTR pszString, LPCSTR pszTag);
	void		WINAPI StringTrimW(LPWSTR pszString, LPCWSTR pszTag);
	void		WINAPI StringTrimA(LPSTR pszString, LPCSTR pszTag);
	WCHAR*	WINAPI StringUpperW(LPWSTR pszString);
	CHAR*		WINAPI StringUpperA(LPSTR pszString);
	WCHAR*	WINAPI StringLowerW(LPWSTR pszString);
	CHAR*		WINAPI StringLowerA(LPSTR pszString);
	WCHAR*	WINAPI StringReverseW(LPWSTR pszString);
	CHAR*		WINAPI StringReverseA(LPSTR pszString);
	LONG		WINAPI StringWCharToChar(LPCWSTR pszStr, LONG nLen, LPSTR pszString, LONG nMaxLen);
	LONG		WINAPI StringCharToWChar(LPCSTR pszStr, LONG nLen, LPWSTR pszString, LONG nMaxLen);
	LONG		WINAPI StringToLongW(LPCWSTR pszNum);
	LONG		WINAPI StringToLongA(LPCSTR pszNum);
	float		WINAPI StringToFloatW(LPCWSTR pszNum);
	float		WINAPI StringToFloatA(LPCSTR pszNum);
	DWORD		WINAPI StringToDwordW(LPCWSTR pszNum);
	DWORD		WINAPI StringToDwordA(LPCSTR pszNum);

#ifdef __cplusplus
}
#endif


#endif //HWX_HWSTRSAFE_H