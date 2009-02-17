/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XDebug.h					
�ļ�����:		
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/10/06
*********************************************************************/
#ifndef HWX_DEBUG_H
#define HWX_DEBUG_H
#include <Ext_Type.h>


#if defined(DEBUG) || defined(_DEBUG)
#define HWDEBUG
#else 
#undef HWDEBUG
#endif



#ifdef _X86_
#define DebugBreak() _asm { int 3 }
#endif

#ifndef FORCEASSERT
#define FORCEASSERT(expr) \
	if (!(expr))  \
{      \
	XForceTraceW(L"%s In Files %s Line:%d", _CRT_WIDE(#expr), _CRT_WIDE(__FILE__), __LINE__);  \
	DebugBreak();   \
}
#endif

#ifndef DEBUG_ERROR
#define DEBUG_ERROR(expr) \
	if (0)  \
{      \
	XForceTraceW(TEXT("%s In Files %s Line:%d"), expr, _CRT_WIDE(__FILE__), __LINE__);  \
	DebugBreak();   \
}
#endif

#ifndef TRACE
#if defined(HWDEBUG)
#define TRACE		XTrace
#else 
#define TRACE		__noop
#endif
#endif

#ifndef TRACEEX
#if defined(HWDEBUG)
#define TRACEEX		XTraceEx
#else 
#define TRACEEX		__noop
#endif
#endif


#ifdef UNICODE
#define XTrace		XTraceW
#else 
#define XTrace		XTraceA
#endif

#ifdef UNICODE
#define XTraceEx		XTraceExW
#else 
#define XTrace		XTraceExA
#endif

#ifdef UNICODE
#define FORCETRACE		XForceTraceW
#else 
#define FORCETRACE		XForceTraceA
#endif



#ifdef __cplusplus
extern "C"
{
#endif
	//�ͷ��ڴ�
	DLLXEXPORT void WINAPI		XTraceW(LPCWSTR, ...);	
	DLLXEXPORT void WINAPI		XTraceA(LPCSTR , ...);
	DLLXEXPORT void WINAPI		XTraceExW(BOOL, LPCWSTR, ...);	
	DLLXEXPORT void WINAPI		XTraceExA(BOOL, LPCSTR , ...);
	DLLXEXPORT void WINAPI	  XForceTraceW(LPCWSTR, ...);	
	DLLXEXPORT void WINAPI		XForceTraceA(LPCSTR , ...);
	
#ifdef __cplusplus
}
#endif


#endif//HWX_DEBUG_H