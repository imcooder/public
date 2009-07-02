
#include "stdafx.h"
#include "HWMSGThread.h"
#include "Thread.h"
#include "HWDebug.h"
CHWMSGThread::CHWMSGThread()
{	
	m_hStartEvent = NULL;	
	m_blExit = FALSE;
}

CHWMSGThread::~CHWMSGThread()
{	
	Release();
}



LRESULT CHWMSGThread::DefThreadProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0L;
}
LRESULT CHWMSGThread::_Proc( UINT message, WPARAM wParam, LPARAM lParam)
{	
	return DefThreadProc(message, wParam, lParam);
}
BOOL CHWMSGThread::CreateThread()
{
	//create synchronization event for recognize thread
	m_hStartEvent = CreateEvent(NULL, FALSE, 	FALSE, 	NULL);
	if (!m_hStartEvent)
	{
		return FALSE;
	}
	__super::CreateThread();	
	if ( !m_hThread)
	{		
		return FALSE;
	}	
	::WaitForSingleObject(m_hStartEvent,INFINITE);	
	return TRUE;
}

BOOL CHWMSGThread::Release()
{
	if (m_hThread)
	{				
		if (WAIT_OBJECT_0 != WaitForSingleObject(m_hThread, 0))
		{
			HWTRACE(TEXT("The Thread is runing, can not Release\n"));
		}		
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	SAFE_CLOSE_HANDLE(m_hStartEvent);
	return TRUE;
}

LRESULT CHWMSGThread::_ThreadProc()
{	
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);

	if(!SetEvent(m_hStartEvent)) 
	{		
		return 1;
	}
	while(GetMessage(&msg, 0, 0, 0))
	{			
		_Proc(msg.message, msg.wParam, msg.lParam);					
	}	
	return 0;
}

BOOL CHWMSGThread::Terminate()
{				
	if (m_hThread)
	{		
		//HWTRACE(TEXT("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXBegin Terminate\n"));		
		PostMessage(WM_QUIT, 0, 0);				
		if (WAIT_OBJECT_0 != WaitForSingleObject(m_hThread, 300))
		{
			TerminateThread(m_hThread, 0);	
			WaitForSingleObject(m_hThread, INFINITE);
		}		
		SAFE_CLOSE_HANDLE(m_hThread);	
		//HWTRACE(TEXT("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXEnd Terminate\n"));
	}			
	//HWTRACE(TEXT(" CHWMSGThread::Terminate End............\n"));
	return TRUE;
}

BOOL CHWMSGThread::PostMessage( UINT message, WPARAM wParam, LPARAM lParam)
{	
	LONG nCode = PostThreadMessage(m_dwThreadID, message, wParam, lParam);
	if (!nCode)
	{
		//HWTRACE(TEXT("ThreadID %d Error :%d\n"),m_dwThreadID, ::GetLastError());
	}
	return nCode;
}

LRESULT CHWMSGThread::SendMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	//HWTRACE(TEXT("CHWMSGThread : SendMessage\n"));
	return _Proc(message, wParam, lParam);
}