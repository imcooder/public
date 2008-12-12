#ifndef HWX_Asci_H
#define HWX_Asci_H
#include "XTypeEx.h"

#ifdef __cplusplus
extern "C"{
#endif
	BOOL WINAPI Asci_isdigit( LONG ch);
	BOOL WINAPI Asci_isxdigit( LONG ch);
	BOOL WINAPI Asci_iscntrl( LONG ch);
	BOOL WINAPI Asci_isspace( LONG ch);
	BOOL WINAPI Asci_isupper( LONG ch);
	BOOL WINAPI Asci_islower( LONG ch);
	BOOL WINAPI Asci_isalpha( LONG ch);

#ifdef __cplusplus
}
#endif

#endif//HWX_Asci_H
