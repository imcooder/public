/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	StrSafeEx.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/06/21
*********************************************************************/

#include "stdafx.h"
#include "StrSafeEx.h"
#include <wchar.h>


CHAR*		WINAPI StringTokenA( CHAR* pszToken, const CHAR* pszDelimit, CHAR ** pszContext)
{
	CHAR* pszSubStr = NULL;
	if ((!pszToken && pszContext && !*pszContext) || (!pszDelimit) || (!pszContext))
	{
		return pszSubStr;
	}

	CHAR* pszBegin = NULL;
	CHAR* pszEnd = NULL;
	CHAR* pszHeader = NULL;
	CHAR* pszTail = NULL;
	if (pszToken)
	{
		pszBegin = pszToken;
	}
	else
	{
		pszBegin = *pszContext;
	}
	UINT nLen = strlen(pszBegin);
	pszEnd = pszBegin + nLen + 1;
	UINT nHeader = strspn(pszBegin, pszDelimit);
	assert(nHeader <= nLen);
	pszHeader = pszBegin + nHeader;	
	UINT nMiddle = strcspn(pszHeader, pszDelimit);
	pszTail = pszHeader + nMiddle;
	assert(pszHeader <= pszTail);
	if (pszHeader < pszTail)
	{
		pszSubStr = pszHeader;
		if (pszTail < pszEnd)
		{
			*pszTail = 0;
			pszTail ++;			
		}		
		*pszContext = pszTail;	
	}
	else if (pszHeader == pszTail)
	{
		pszSubStr = NULL;
		*pszContext = NULL;
	}
	return pszSubStr;
}

WCHAR*	WINAPI StringTokenW( WCHAR* pszToken, const WCHAR* pszDelimit, WCHAR ** pszContext)
{
	WCHAR* pszSubStr = NULL;
	if ((!pszToken && pszContext && !*pszContext) || (!pszDelimit) || (!pszContext))
	{
		return pszSubStr;
	}

	WCHAR* pszBegin = NULL;
	WCHAR* pszEnd = NULL;
	WCHAR* pszHeader = NULL;
	WCHAR* pszTail = NULL;
	if (pszToken)
	{
		pszBegin = pszToken;
	}
	else
	{
		pszBegin = *pszContext;
	}
	UINT nLen = wcslen(pszBegin);
	pszEnd = pszBegin + nLen + 1;
	UINT nHeader = wcsspn(pszBegin, pszDelimit);
	assert(nHeader <= nLen);
	pszHeader = pszBegin + nHeader;	
	UINT nMiddle = wcscspn(pszHeader, pszDelimit);
	pszTail = pszHeader + nMiddle;
	assert(pszHeader <= pszTail);
	if (pszHeader < pszTail)
	{
		pszSubStr = pszHeader;
		if (pszTail < pszEnd)
		{
			*pszTail = 0;
			pszTail ++;			
		}		
		*pszContext = pszTail;		
	}
	else if (pszHeader == pszTail)
	{
		pszSubStr = NULL;
		*pszContext = NULL;
	}
	return pszSubStr;	
}