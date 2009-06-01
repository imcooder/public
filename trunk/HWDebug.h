/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XDebug.h					
文件内容:		
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/10/06
*********************************************************************/
#ifndef HWX_DEBUG_H
#define HWX_DEBUG_H
#include <Ext_Type.h>

//#define HWFORCEFILE




#if defined(DEBUG) || defined(_DEBUG)
#define HWDEBUG
#else 
#undef HWDEBUG
#endif

#ifndef TRACE
#define TRACE		HWTRACE
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



#ifndef HWTRACE
#if defined(HWDEBUG)
#define HWTRACE		XTrace
#else 
#define HWTRACE		__noop
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
	//释放内存
	DLLXEXPORT void WINAPI		XTraceW(LPCWSTR, ...);	
	DLLXEXPORT void WINAPI		XTraceA(LPCSTR , ...);
	DLLXEXPORT void WINAPI		XTraceExW(BOOL, LPCWSTR, ...);	
	DLLXEXPORT void WINAPI		XTraceExA(BOOL, LPCSTR , ...);
	DLLXEXPORT void WINAPI	  XForceTraceW(LPCWSTR, ...);	
	DLLXEXPORT void WINAPI		XForceTraceA(LPCSTR , ...);
	DLLXEXPORT void WINAPI		DebugStringFileA(LPCSTR, LPCSTR);
	DLLXEXPORT void WINAPI		DebugStringFileW(LPCWSTR, LPCWSTR);
#ifdef __cplusplus
}
#endif

#define _CALL_INVALID_PARAMETER_FUNC(funcname, expr) funcname(NULL, NULL, NULL, 0, 0)
#define _INVALID_PARAMETER(expr) _CALL_INVALID_PARAMETER_FUNC(_invalid_parameter, expr)

#define _ASSERT_EXPR(expr, msg) \
	(void) ((!!(expr)) || \
	(1 != _CrtDbgReportW(_CRT_ASSERT, _CRT_WIDE(__FILE__), __LINE__, NULL, msg)) || \
	(_CrtDbgBreak(), 0))


#ifndef _VALIDATE_RETURN
#define _VALIDATE_RETURN( expr, errorcode, retexpr )                           \
{                                                                          \
	int _Expr_val=!!(expr);                                                \
	_ASSERT_EXPR( ( _Expr_val ), _CRT_WIDE(#expr) );                       \
	if ( !( _Expr_val ) )                                                  \
{                                                                      \
	int errno = errorcode;                                                 \
	_INVALID_PARAMETER(_CRT_WIDE(#expr) );                             \
	return ( retexpr );                                                \
}                                                                      \
}
#endif  /* _VALIDATE_RETURN */










#endif//HWX_DEBUG_H