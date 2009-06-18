#include "stdafx.h"
#include "HWMutexLock.h"
#include "HWSecurity.h"

HWMutexLock::HWMutexLock( LPCWSTR pszName)
: m_hMutex(NULL)
, m_bCreate(FALSE)
{			
	if (pszName[0])
	{		
		m_hMutex = CreateMutexW(NULL, FALSE, pszName);   
		if (m_hMutex && ERROR_ALREADY_EXISTS != GetLastError())
		{
			HWSetObjectToLowIntegrity(m_hMutex);
		}
		m_bCreate = TRUE;
	}	
	if (m_hMutex)
	{
		WaitForSingleObject(m_hMutex, INFINITE);
	}
}
HWMutexLock::HWMutexLock( HANDLE hMutex)
: m_hMutex(hMutex)
, m_bCreate(FALSE)
{				
	if (m_hMutex)
	{
		WaitForSingleObject(m_hMutex, INFINITE);
	}
}
HWMutexLock::~HWMutexLock( )
{
	if (m_hMutex)
	{
		ReleaseMutex(m_hMutex);
	}	
	if (m_bCreate)
	{
		SAFE_CLOSE_HANDLE(m_hMutex);
	}
}
