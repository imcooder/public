#ifndef HWX_FILEEX_H
#define HWX_FILEEX_H
#include "Ext_Type.h"


#include <vector>



#ifdef _UNICODE

#define LoadFile			LoadFileW

#else

#define LoadFile			LoadFileW

#endif




#ifdef __cplusplus
extern "C"{
#endif
	//////////////////////////////////////////////////////////////////////////
	// >= 0 :file size
	// -1   :	Not enough memory
	// -2		: file not found	
	//////////////////////////////////////////////////////////////////////////
	DLLXEXPORT LONG WINAPI LoadFileA( LPCSTR, LPBYTE *);
	DLLXEXPORT LONG WINAPI LoadFileW(LPCWSTR, LPBYTE *);
#ifdef __cplusplus
}
#endif

#endif//HWX_FILEEX_H