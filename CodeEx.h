
#ifndef HWX_CODEEX_H
#define HWX_CODEEX_H
#include "XTypeEx.h"

#define NUMCONV_NORMAL						0x00000001		// ��������
#define NUMCONV_NORMAL_UPPER			0x00000008		// �������
#define NUMCONV_LOWER							0x00000002		// ��ǧ���
#define NUMCONV_UPPER							0x00000004		// ��Ǫ���
#define NUMCONV_EN								0x00000010		//2,008
#ifdef __cplusplus
extern "C"{
#endif 	
	DLLXEXPORT LONG WINAPI TCToSC(LPCWSTR, LPWSTR);	
	DLLXEXPORT LONG WINAPI SCToTC(LPCWSTR, LPWSTR);		
	DLLXEXPORT LONG WINAPI NumberToString(LPCWSTR, LPWSTR, DWORD dwFlag);
	DLLXEXPORT LONG WINAPI HalfToFull(LPCWSTR, LPWSTR);
	DLLXEXPORT LONG WINAPI PunEnToCn(LPCWSTR, LPWSTR);
#ifdef __cplusplus
}
#endif
	

#endif //HWX_CODEEX_H