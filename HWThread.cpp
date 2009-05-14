
#include "stdafx.h"
#include <windows.h> 
#include "HWThread.h"


void CHWThread::TryExit(DWORD dwTime)
{
	if (!m_hTerminateEvent)
	{
		return;
	}		
	if(WAIT_OBJECT_0 == WaitForSingleObject(m_hTerminateEvent, dwTime))   
	{			
		ResetEvent(m_hTerminateEvent);		
		ExitThread(NULL);			
	}
}

CHWThread::CHWThread()
{	
	m_hThread = NULL;		
	m_dwThreadID = 0;
	m_hTerminateEvent = CreateEvent(NULL, TRUE,  FALSE, NULL);
}

CHWThread::~CHWThread()
{
	SAFE_CLOSE_HANDLE(m_hThread);	
	SAFE_CLOSE_HANDLE( m_hTerminateEvent);		
}

BOOL CHWThread::Terminate()
{
	if (m_hThread)
	{
		SetEvent(m_hTerminateEvent);				
		WaitForSingleObject(m_hThread, INFINITE);	
		SAFE_CLOSE_HANDLE(m_hThread);		
	}
	else
	{
		
	}
	return TRUE;
}


DWORD WINAPI CHWThread::ThreadProc( LPVOID lpParam )
{
	CHWThread *pThis = reinterpret_cast<CHWThread*>(lpParam);
	pThis->_ThreadProc();
	return 0;
}

LRESULT CHWThread::_ThreadProc()
{
	TryExit(0);
	return TRUE;
}

BOOL CHWThread::CreateThread()
{	
	if (m_hThread)
	{
		return TRUE;
	}
	m_hThread = ::CreateThread(NULL, 0, ThreadProc, reinterpret_cast<LPVOID>(this), 0, &m_dwThreadID);
	return !!m_hThread;
}