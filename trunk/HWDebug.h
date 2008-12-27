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



#ifndef TRACE
#if defined(DEBUG) || defined(_DEBUG)
#define TRACE		XTrace
#else 
#define TRACE		__noop
#endif
#endif

#ifdef UNICODE
#define XTrace		XTraceW
#else 
#define XTrace		XTraceA
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
	DLLXEXPORT void WINAPI	  	XForceTraceW(LPCWSTR, ...);	
	DLLXEXPORT void WINAPI		XForceTraceA(LPCSTR , ...);
	
#ifdef __cplusplus
}
#endif


#endif//HWX_DEBUG_H