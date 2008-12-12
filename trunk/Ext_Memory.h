/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����:   Ext_Memory.h          
�ļ�����:  �ڴ�����ķ�װ ������߳���ɵ�����
�汾��ʷ:  1.0
����:    xuejuntao xuejuntao@hanwang.com.cn 2008/02/26
*********************************************************************/
#ifndef HWXUE_EXT_MEMORY_H_INC
#define HWXUE_EXT_MEMORY_H_INC

#include "Ext_Type.h"
#include <malloc.h>
//���ļ��еĺ��� Ext_Mem_NewMemory Ext_Mem_ResizeMemory Ext_Mem_FreeMemory �ں����в���ʹ��

#define Mem_ResizeMemory    XMemResize
#define Mem_FreeMemory      XMemFree
#define Mem_NewMemory       XMemAlloc
#define Mem_FillMemory      XMemFill
#define Mem_ZeroMemory      XMemZero
#define Mem_EqualMemory     XMemEqual
#define Mem_CopyMemory      XMemCopy

#ifdef __cplusplus
extern "C"{
#endif
//�ͷ��ڴ�
DLLXEXPORT void WINAPI    XMemFree(void** pvMem);
/*�����µ��ڴ�*/
DLLXEXPORT BOOL WINAPI    XMemAlloc(void** ppvMem, LONG nSize);
/*�����ڴ��С*/
DLLXEXPORT BOOL WINAPI    XMemResize(void** ppvMem, LONG nSizeNew);
DLLXEXPORT BOOL WINAPI    XMemFill(void *pvMem, char bChrFill, LONG nSize);
/*�ڴ���0*/
DLLXEXPORT BOOL WINAPI    XMemZero(void *pvMem, LONG nSize);
/*�ڴ��Ƿ����*/
DLLXEXPORT BOOL  WINAPI   XMemEqual(const void *pvMemDest, const void *pvMemSrc, LONG nSize);
DLLXEXPORT  void WINAPI   XMemSet(void *p, const CHAR& b, const LONG& n );
DLLXEXPORT  LONG WINAPI   XMemCopy(void *pDest, const void *const pSource, const LONG& n );
DLLXEXPORT  LONG WINAPI   XMemMove(void *pDest, const void *const pSrc, const LONG& n );
DLLXEXPORT  LONG WINAPI   XMemCompare(void *const pDest, void *const pSrc, const LONG& n );
#ifdef __cplusplus
}
#endif

#endif//HWXUE_EXT_MEMORY_H_INC



