/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	StrSafeEx.h					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/06/21
*********************************************************************/
#ifndef HWX_STRSAFEEX_H
#define HWX_STRSAFEEX_H
#pragma once
#include <strsafe.h>
#include "Ext_Type.h"


#ifdef _UNICODE

#define StringToken			StringTokenW	

#else

#define StringToken			StringTokenA

#endif



#ifdef __cplusplus
extern "C"{
#endif

	CHAR*		WINAPI StringTokenA(CHAR*,	const CHAR*,	CHAR **);
	WCHAR*	WINAPI StringTokenW(WCHAR*,	const WCHAR*,	WCHAR **);

#ifdef __cplusplus
}
#endif


#endif //HWX_STRSAFEEX_H