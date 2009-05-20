
#ifndef HWX_HWSECURITY_H
#define HWX_HWSECURITY_H


#if _MSC_VER > 1000
#pragma once
#endif 
#include "Ext_Type.h"
#include <accctrl.h>
#include <winbase.h>
#include <windows.h>
#include <Sddl.h> 
#include <AclAPI.h>

#ifndef SECURITY_MANDATORY_UNTRUSTED_RID
#define SECURITY_MANDATORY_UNTRUSTED_RID            (0x00000000L)
#endif
#ifndef SECURITY_MANDATORY_LOW_RID
#define SECURITY_MANDATORY_LOW_RID                  (0x00001000L)
#endif
#ifndef SECURITY_MANDATORY_MEDIUM_RID
#define SECURITY_MANDATORY_MEDIUM_RID               (0x00002000L)
#endif
#ifndef SECURITY_MANDATORY_HIGH_RID
#define SECURITY_MANDATORY_HIGH_RID                 (0x00003000L)
#endif
#ifndef SECURITY_MANDATORY_SYSTEM_RID
#define SECURITY_MANDATORY_SYSTEM_RID               (0x00004000L)
#endif
#ifdef __cplusplus
extern "C"
{
#endif

	BOOL WINAPI HWSetObjectToLowIntegrity( HANDLE, SE_OBJECT_TYPE = SE_KERNEL_OBJECT);
	LONG WINAPI HWGetObjectIntegrityLevel(HANDLE, SE_OBJECT_TYPE = SE_KERNEL_OBJECT);
	BOOL WINAPI HWSetFileToLowIntegrity(LPCTSTR);
	LONG WINAPI HWGetFileIntegrityLevel(LPTSTR);

#ifdef __cplusplus
}
#endif


#endif //HWX_HWSECURITY_H