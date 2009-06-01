/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	HWSearch.h					
文件内容:		
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/10/06
*********************************************************************/
#ifndef HWX_HWSEARCH_H
#define HWX_HWSEARCH_H
#include <Ext_Type.h>


#ifdef __cplusplus
extern "C"
{
#endif
	void * WINAPI HWbsearch_s(const void * _Key, const void * _Base, 	size_t _NumOfElements, size_t _SizeOfElements,	int (__cdecl * _PtFuncCompare)(void *, const void *, const void *), void * _Context);
	void * WINAPI HWbsearch(const void * _Key, const void * _Base, size_t _NumOfElements, size_t _SizeOfElements,int (__cdecl * _PtFuncCompare)(const void *, const void *));
#ifdef __cplusplus
}
#endif


#endif//HWX_DEBUG_H