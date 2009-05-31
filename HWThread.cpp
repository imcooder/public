
#include "stdafx.h"
#include <windows.h> 
#include "HWThread.h"
#include "HWSecurity.h"

void CHWThread::TryExit(DWORD dwTime)
{
	if (!m_hTerminateEvent)
	{
		return;
	}		
	HWTRACE(TEXT("CHWThread::TryExit Begin\n"));
	if(WAIT_OBJECT_0 == WaitForSingleObject(m_hTerminateEvent, dwTime))   
	{			
		ResetEvent(m_hTerminateEvent);		
		ExitThread(NULL);			
	}
	HWTRACE(TEXT("CHWThread::TryExit End\n"));
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
		HWTRACE(TEXT("CHWThread::Terminate Begin\n"));
	//SetEvent(m_hTerminateEvent);		
		TerminateThread(m_hTerminateEvent, 0);
		WaitForSingleObject(m_hThread, INFINITE);	
		SAFE_CLOSE_HANDLE(m_hThread);		
		HWTRACE(TEXT("CHWThread::Terminate End\n"));
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