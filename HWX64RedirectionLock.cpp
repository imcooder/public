#include "stdafx.h"
#include "HWX64RedirectionLock.h"
#include "HWDebug.h"

CHWWow64RedirectionLock::CHWWow64RedirectionLock()
: m_hKernel(NULL)
, m_pDisable(NULL)
, m_pRevert(NULL)
, m_pvOldState(NULL)
{		
	const LPCTSTR pszPath = TEXT("Kernel32.dll");	
	m_hKernel = ::LoadLibrary(pszPath);
	if (m_hKernel)
	{
		LONG nFailedFunctionCount = 0;
		if (!(m_pDisable = (LPWow64DisableWow64FsRedirection)GetProcAddress(m_hKernel, "Wow64DisableWow64FsRedirection")))
		{
			nFailedFunctionCount ++;
			HWTRACE(TEXT("GetProcAddress Wow64DisableWow64FsRedirection Function in Moudle %s failed\n"), pszPath);
		}

		if (!(m_pRevert = (LPWow64RevertWow64FsRedirection)GetProcAddress(m_hKernel, "Wow64RevertWow64FsRedirection")))
		{
			nFailedFunctionCount ++;
			HWTRACE(TEXT("GetProcAddress Wow64RevertWow64FsRedirection Function in Moudle %s failed\n"), pszPath);
		}
		if (nFailedFunctionCount)
		{
			Release();	
		}
	}
	else
	{
		HWTRACE(TEXT("CHWWow64RedirectionLock::LoadLibrary %s failed!\n"), pszPath);
	}	
	if (m_pDisable)
	{
		m_pDisable(&m_pvOldState);
	}
}

CHWWow64RedirectionLock::~CHWWow64RedirectionLock( )
{
	if (m_pRevert)
	{
		m_pRevert(m_pvOldState);
		m_pvOldState = NULL;
	}
	Release();
}

void CHWWow64RedirectionLock::Release()
{	
	m_pDisable = NULL;
	m_pRevert = NULL;	
	if (m_hKernel)
	{
		FreeLibrary(m_hKernel);
		m_hKernel = NULL;
	}
}