#ifndef HWX_HWHASH_H
#define HWX_HWHASH_H
#include "Ext_Type.h"


#ifdef __cplusplus
extern "C"{
#endif

	unsigned long HWSDBMHash(const char *);
	unsigned long HWRSHash(const char *);
	unsigned long HWJSHash(const char *);
	unsigned long HWPJWHash(const char *);
	unsigned long HWELFHash(const char *);
	unsigned long HWBKDRHash(const char *);
	unsigned long HWDJBHash(const char *);
	unsigned long HWAPHash(const char *);
#ifdef __cplusplus
}
#endif


#endif//HWX_HWHASH_H 