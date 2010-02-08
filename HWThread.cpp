
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
	//HWTRACE(TEXT("CHWThread::TryExit Begin\n"));
	if(WAIT_OBJECT_0 == WaitForSingleObject(m_hTerminateEvent, dwTime))   
	{			
		ResetEvent(m_hTerminateEvent);		
		ExitThread(NULL);			
	}
	//HWTRACE(TEXT("CHWThread::TryExit End\n"));
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
	m_dwThreadID = 0;
	SAFE_CLOSE_HANDLE( m_hTerminateEvent);		
}

BOOL CHWThread::Terminate()
{	
	HWTRACE(TEXT("CHWThread::Terminate Begin\n"));
	if (m_hThread)
	{
		DWORD dwExitCode; 
		GetExitCodeThread( m_hThread, &dwExitCode ); 
		if (STILL_ACTIVE == dwExitCode)
		{
			SetEvent(m_hTerminateEvent);	
			DWORD dwWait = WaitForSingleObject(m_hThread, 300);
			switch (dwWait)
			{
			case WAIT_TIMEOUT:
				{					
					BOOL blValue = TerminateThread(m_hThread, 0);
					HWTRACEEX(!blValue, TEXT("TerminateThread Failed %d\n"), GetLastError());
					if (blValue)
					{
						WaitForSingleObject(m_hThread, INFINITE);		
					}						
				}
				break;
			case WAIT_FAILED:
				{

				}
				break;
			case WAIT_OBJECT_0:
				{

				}
				break;
			}				
		}	
		SAFE_CLOSE_HANDLE(m_hThread);		
		m_dwThreadID = 0;
	}	
	HWTRACE(TEXT("CHWThread::Terminate End\n"));
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
	m_dwThreadID = 0;
	m_hThread = ::CreateThread(NULL, 0, ThreadProc, reinterpret_cast<LPVOID>(this), 0, &m_dwThreadID);
	HWTRACEEX(!m_hThread, TEXT("CreateThread Failed %d\n"), GetLastError());
	return !!m_hThread;
}

BOOL CHWThread::SetThreadPriority( int nPriority)
{
	if (m_hThread)
	{
		return ::SetThreadPriority(m_hThread, nPriority);
	}
	return FALSE;
}

DWORD CHWThread::ResumeThread()
{
	return ::ResumeThread(m_hThread);
}

DWORD CHWThread::SuspendThread()
{
	return ::SuspendThread(m_hThread);
}