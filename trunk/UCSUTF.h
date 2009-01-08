
#ifndef HWX_UCSUTF_H
#define HWX_UCSUTF_H
#include "Ext_Type.h"


#ifdef __cplusplus
extern "C"{
#endif 
	DLLXEXPORT LONG WINAPI UTF16ToUTF8(LPCWSTR pszUTF16, LPSTR pszUTF8);
	DLLXEXPORT LONG WINAPI UTF8ToUTF16(const CHAR *src, LPWSTR pszUTF16);
	DLLXEXPORT LONG WINAPI UCS4ToUTF16(const DWORD* ,SIZE_T n, LPWSTR pszUTF16);
	
#ifdef __cplusplus
}
#endif
	

#endif //HWX_UCSUTF_H