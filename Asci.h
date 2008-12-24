#ifndef HWX_Asci_H
#define HWX_Asci_H
#include "XTypeEx.h"

#ifdef __cplusplus
extern "C"{
#endif
	BOOL WINAPI Asci_IsDigit( LONG ch);
	BOOL WINAPI Asci_IsXDigit( LONG ch);
	BOOL WINAPI Asci_iscntrl( LONG ch);
	BOOL WINAPI Asci_isspace( LONG ch);
	BOOL WINAPI Asci_IsUpper( LONG ch);
	BOOL WINAPI Asci_IsLower( LONG ch);
	BOOL WINAPI Asci_IsAlpha( LONG ch);
	BOOL WINAPI Asci_IsPunctuation(LONG ch);
	WCHAR WINAPI Asci_HalfToFull( WCHAR);
	BOOL WINAPI Asci_IsBelongTo(WCHAR, LPCWSTR);
#ifdef __cplusplus
}
#endif

#endif//HWX_Asci_H
