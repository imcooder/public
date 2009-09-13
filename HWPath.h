#ifndef HWX_HWPATH_H
#define HWX_HWPATH_H
#include "Ext_Type.h"

#ifndef _INC_SHLWAPI

#define PathAppend HWPathAppend
#define PathAppend_s HWPathAppend_s

#else

#define PathAppend_s HWPathAppend_s

#endif

#ifdef _UNICODE



#else



#endif


/*
#ifdef __cplusplus
extern "C"{
#endif*/

	//////////////////////////////////////////////////////////////////////////
	// >= 0 :file size
	// -1   :	Not enough memory
	// -2		: file not found	
	//////////////////////////////////////////////////////////////////////////
	DLLXEXPORT BOOL WINAPI HWPathAppend( LPWSTR, LPCWSTR);	
	DLLXEXPORT BOOL WINAPI HWPathAppend_s( LPWSTR, DWORD, LPCWSTR);	
/*
#ifdef __cplusplus
}
#endif*/


#endif//HWX_FILEEX_H 