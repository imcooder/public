
#ifndef HWX_CODEEX_H
#define HWX_CODEEX_H
#include "XTypeEx.h"

#define NUMCONV_NORMAL		0x00000001		// ¶þ©–©–°Ë
#define NUMCONV_LOWER			0x00000002		// ¶þÇ§Áã°Ë
#define NUMCONV_UPPER			0x00000004		// ·¡ÇªÁã°Æ

#ifdef __cplusplus
extern "C"{
#endif 
	DLLXEXPORT LONG WINAPI UTF16ToUTF8(LPCWSTR pszUTF16, LPSTR pszUTF8);
	DLLXEXPORT LONG WINAPI UTF8ToUTF16(const CHAR *src, LPWSTR pszUTF16);
	DLLXEXPORT LONG WINAPI TCToSC(LPCWSTR, LPWSTR);	
	DLLXEXPORT LONG WINAPI SCToTC(LPCWSTR, LPWSTR);	
	DLLXEXPORT LONG WINAPI NumberToStringD(double, LPWSTR, DWORD dwFlag);
	DLLXEXPORT LONG WINAPI NumberToStringINT(INT64, LPWSTR, DWORD dwFlag);
#ifdef __cplusplus
}
#endif
	

#endif //HWX_CODEEX_H