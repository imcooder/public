
#ifndef HWX_CODEEX_H
#define HWX_CODEEX_H
#include "XTypeEx.h"


//#define HW_CODE_TCTOSC
#define HW_CODE_SCTOTC


#define NUMCONV_NORMAL						0x00000001		// ¶þ©–©–°Ë
#define NUMCONV_NORMAL_UPPER			0x00000008		// ·¡ÁãÁã°Æ
#define NUMCONV_LOWER							0x00000002		// ¶þÇ§Áã°Ë
#define NUMCONV_UPPER							0x00000004		// ·¡ÇªÁã°Æ
#define NUMCONV_EN								0x00000010		//2,008
#ifdef __cplusplus
extern "C"{
#endif 	
#ifdef HW_CODE_TCTOSC
	DLLXEXPORT LONG WINAPI TCToSC(LPCWSTR, LPWSTR);	
#endif
#ifdef HW_CODE_SCTOTC
	DLLXEXPORT LONG WINAPI SCToTC(LPCWSTR, LPWSTR);		
#endif
	DLLXEXPORT LONG WINAPI NumberToString(LPCWSTR, LPWSTR, DWORD dwFlag);
	DLLXEXPORT LONG WINAPI ToFullWidth(LPCWSTR, LPWSTR);
	DLLXEXPORT LONG WINAPI PunEnToCn(LPCWSTR, LPWSTR);
	DLLXEXPORT LONG WINAPI HWToLower(LPCTSTR, LPTSTR);
	DLLXEXPORT LONG WINAPI HWToUpper(LPCTSTR, LPTSTR);
#ifdef __cplusplus
}
#endif
	

#endif //HWX_CODEEX_H