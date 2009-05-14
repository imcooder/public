
#ifndef HWX_MODULEEX_H
#define HWX_MODULEEX_H


#if _MSC_VER > 1000
#pragma once
#endif 
#include "Ext_Type.h"


class HWModule 
{
public:
	HWModule();
	virtual ~HWModule();		
	virtual BOOL LoadLibrary(LPCTSTR);
	virtual void FreeLibrary();
	virtual BOOL Succeed();
protected:	
	HMODULE		m_hModule;
	TCHAR			m_szModuleFilePath[MAX_PATH];
	BOOL			m_blSucceed;	
};

#endif //HWX_MODULEEX_H