/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	ThreadEx.cpp
�ļ�����:	  �򵥵��߳�
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/04/30
*********************************************************************/
#include "StdAfx.h"
#include "Threadex.h"
#include <assert.h>
CXThread::CXThread()
{	
	m_pEvent = NULL;
	m_pThread = NULL;
	m_unDelay = 0;
}
CXThread::~CXThread()
{
	Stop();
}

void CXThread::Stop()
{
	if (NULL != m_pEvent)
	{
		m_pEvent->SetEvent();
		WaitForSingleObject(m_pThread->m_hThread, INFINITE);//�ȴ��߳̽���
		delete m_pThread;
		m_pThread = NULL;
		delete m_pEvent;
		m_pEvent = NULL;
	}
	else
	{
		assert(NULL == m_pThread);
	}
}

BOOL CXThread::Begin(AFX_THREADPROC pvCallBackFunction, void *pvVariant)
{
	assert(NULL != pvCallBackFunction);	
	if (NULL == pvCallBackFunction)
	{
		return FALSE;
	}
	if(NULL != m_pEvent)
	{//��ֹ�̻߳�û�н��� ����begin����
		assert(NULL != m_pThread);
		Stop();		
	}
	assert(NULL == m_pThread);
	m_pEvent = new CEvent(FALSE, TRUE);		
	
	m_pThread = AfxBeginThread((AFX_THREADPROC)pvCallBackFunction, pvVariant, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED );
	if (NULL != m_pThread)
	{
		m_pThread->m_bAutoDelete = FALSE;
		m_pThread->ResumeThread();
	}

	return(NULL != m_pThread);	
}

void CXThread::TryExit()
{
	if (NULL == m_pEvent)
	{//ֻ�е�ǰ�߳�����֮��ſ����ж��Ƿ���Խ���
		return;
	}	
	if(WAIT_OBJECT_0 == WaitForSingleObject(m_pEvent->m_hObject, m_unDelay))   
	{	
		m_pEvent->ResetEvent();		
		AfxEndThread(NULL);			
	}
}

void CXThread::SetDelay(unsigned long unDelay)
{
	m_unDelay = unDelay;
}