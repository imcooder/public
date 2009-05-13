#ifndef HWX_VIRTUALKEY_H
#define HWX_VIRTUALKEY_H
#include "XTypeEx.h"

#ifdef __cplusplus
extern "C"{
#endif

	BOOL WINAPI IsVKeyChar(LONG );	
	BOOL WINAPI IsVKeyNumPad(LONG);	
	BOOL WINAPI IsVKeyNum( LONG);	
	BOOL WINAPI IsVKeyF(LONG);
	BOOL WINAPI IsVKeySys(LONG);
#ifdef __cplusplus
}
#endif

#endif//HWX_VIRTUALKEY_H
