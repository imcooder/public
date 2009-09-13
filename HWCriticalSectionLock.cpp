#include "stdafx.h"
#include "HWCriticalSectionLock.h"


CHWCriticalSectionLock::CHWCriticalSectionLock( LPCRITICAL_SECTION pCS )
{		
	if (pCS)
	{
		m_pCS = pCS;
		EnterCriticalSection(m_pCS);
	}	
}

CHWCriticalSectionLock::~CHWCriticalSectionLock( )
{
	if (m_pCS)
	{
		LeaveCriticalSection(m_pCS);
	}	
}