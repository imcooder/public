#include "stdafx.h"
#include "HWMutexLock.h"
#include "HWSecurity.h"

HWMutexLock::HWMutexLock( LPCTSTR pszName)
: m_hMutex(NULL)
{			
	if (pszName[0])
	{		
		m_hMutex = CreateMutex(NULL, FALSE, NULL);   
		if (m_hMutex && ERROR_ALREADY_EXISTS != GetLastError())
		{
			HWSetObjectToLowIntegrity(m_hMutex);
		}
	}	
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
	SAFE_CLOSE_HANDLE(m_hMutex);
}