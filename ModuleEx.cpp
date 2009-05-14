
#include "stdafx.h"
#include "ModuleEx.h"
#include "Ext_Type.h"
#include "HWDebug.h"

//////////////////////////////////////////////////////////////////////////

HWModule::HWModule() : m_hModule(NULL)
{		
	m_szModuleFilePath[0] = 0;
}
HWModule::~HWModule()
{
	FreeLibrary();
}

BOOL HWModule::LoadLibrary( LPCTSTR pszPath)
{
	BOOL blReturn = FALSE;
	FreeLibrary();
	if (m_hModule = ::LoadLibrary(pszPath))
	{		
		_tcscpy_s(m_szModuleFilePath, MAX_PATH, pszPath);
		blReturn = TRUE;
	}
	else
	{		
		HWTRACE(TEXT("LoadLibrary %s failed\n"), pszPath);
	}	
	return blReturn;
}
void HWModule::FreeLibrary()
{
	SAFE_FREE_LIBRARY(m_hModule);
	m_szModuleFilePath[0] = 0;
	m_blSucceed = FALSE;
}

BOOL HWModule::Succeed()
{
	return m_hModule != NULL;
}


//////////////////////////////////////////////////////////////////////////