#include "stdafx.h"
#include "ChangeNotify.h" 
#include "HWDebug.h"

CChangeMonitor::CChangeMonitor( void ) 
: m_hThread( NULL ) 
, m_hWnd( NULL ) 
, m_dwThreadId( 0 ) 
, m_dwMonId( 0 ) 
{ 

} 

CChangeMonitor::~CChangeMonitor( void ) 
{ 
	EndMoniter(); 
} 

BOOL CChangeMonitor::StartMoniter( DWORD dwMonId, HWND hWnd ) 
{ 
	// �ж��Ƿ��Ѿ��������� 
	if (!m_hThread) 
	{ 
		SetLastError( ERROR_NOTIFY_ALREADY_START ); 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
		return FALSE; 
	} 
	// ������ 
	if (!hWnd) 
	{ 
		SetLastError( ERROR_INVALID_PARAMETER ); 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
		return FALSE; 
	} 
	m_dwMonId = dwMonId; 
	m_hWnd = hWnd; 
	// ���������߳� 
	m_hThread = CreateThread(NULL, 0, ChangeMonitorThread, (LPVOID)this, CREATE_SUSPENDED, &m_dwThreadId ); 
	ASSERT(m_hThread); 
	return TRUE; 
} 

void CChangeMonitor::EndMoniter( void ) 
{ 
	// �ж��߳��Ƿ���� 
	if ( m_hThread ) 
	{ 
		// �ж��߳��Ƿ���� 
		DWORD dwExitCode; 
		VERIFY( GetExitCodeThread( m_hThread, &dwExitCode ) ); 
		if ( STILL_ACTIVE == dwExitCode ) 
		{ 
			ASSERT( m_dwThreadId != 0 ); 
			// ���̷߳����˳���Ϣ 
			VERIFY( PostThreadMessage( m_dwThreadId, WM_MONITER_EXIT, 0, 0 ) ); 
			// ʹ�̼߳������Ա���� 
			Resume(); 
			// �ȴ��߳��˳� 
			DWORD dwWaitResult = WaitForSingleObject( m_hThread, INFINITE ); 
			ASSERT( WAIT_FAILED != dwWaitResult ); 
			// ����ȴ���ʱ��ǿ�ƽ����߳� 
			if ( WAIT_TIMEOUT == dwWaitResult ) 
			{ 
				if ( FALSE == TerminateThread( m_hThread, 0 ) ) 
				{ 
					HWTRACE(TEXT("LastError:%d"), GetLastError()); 
				} 
			} 
		} 
		// �ر��߳̾�������߳������������ 
		SAFE_CLOSE_HANDLE(m_hThread);
		m_dwThreadId = 0; 
	} 
	m_hWnd = NULL; // ֪ͨ�������� 
} 

void CChangeMonitor::Pause( void ) 
{ 
	ASSERT(m_hThread); 
	if (m_hThread)
	{
		SuspendThread(m_hThread); 
	}	
} 

void CChangeMonitor::Resume( void ) 
{ 
	ASSERT( m_hThread ); 
	if (m_hThread)
	{
		ResumeThread( m_hThread ); 
	}	
} 

void CChangeMonitor::SendNotify( UINT nMsg ) 
{ 
	// ���֪ͨ�������Ƿ���� 
	ASSERT(m_hWnd); 
	if (!m_hWnd)
	{
		return;
	}
	// ����֪ͨ��Ϣ 
	if ( !PostMessage( m_hWnd, nMsg, m_dwMonId, 0 ) ) 
	{ 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
	} 
} 

DWORD CALLBACK ChangeMonitorThread( LPVOID pParam ) 
{ 
	// �������Ƿ�Ϊ�� 
	ASSERT( pParam != NULL ); 
	// �õ������������ָ�� 
	CChangeMonitor *pChaMon = (CChangeMonitor*)pParam; 
	// ������ 
	ASSERT( pChaMon->m_hThread != NULL ); 
	ASSERT( pChaMon->m_hWnd != NULL ); 
	ASSERT( pChaMon->m_dwThreadId != 0 ); 
	// �����߳���Ϣѭ�� 
	MSG msg; // ��Ϣ���ݽṹ 
	while( !PeekMessage( &msg, NULL, WM_MONITER_EXIT, WM_MONITER_EXIT, PM_REMOVE ) ) 
	{ 
		// ��0��ʱ�ȴ�֪ͨ��ֱ�ӷ��صȴ���� 
		DWORD dwWaitResult = pChaMon->WaitNotify(); 
		ASSERT( dwWaitResult != WAIT_FAILED ); 
		switch( dwWaitResult ) // ����ȴ���� 
		{ 
		case WAIT_OBJECT_0: // ֪ͨ�ѽ��� 
			{
				// ������߷���֪ͨ��Ϣ 
			pChaMon->SendNotify( WM_MONITER_CHANGED ); 
			// ������һ�εȴ� 
			pChaMon->CallNextMoniter(); 
			}
			break; 
		case WAIT_TIMEOUT: 
			{
				break; 
			}
		} 
		Sleep(50); 
	} 
	return 0; 
} 


/////////////////////////////////////////////////////////////////////////////// 
// CDirectoryMonitor 

// ���캯�� 
CDirectoryMonitor::CDirectoryMonitor( void ) 
: m_hNotify( NULL ) 
{ 
} 

// �������� 
CDirectoryMonitor::~CDirectoryMonitor( void ) 
{ 
} 

// �������� 
BOOL CDirectoryMonitor::StartMoniter( DWORD dwMonId, HWND hWnd, LPCTSTR lpPath, 
																		 BOOL bSubTree, DWORD dwFilter ) 
{ 
	// ���ø���ͬ������ 
	if (!__super::StartMoniter( dwMonId, hWnd ) ) 
	{ 
		return FALSE; 
	} 
	// �������� 
	m_hNotify = FindFirstChangeNotification( lpPath, bSubTree, dwFilter ); 
	if ( INVALID_HANDLE_VALUE == m_hNotify ) 
	{ 
		m_hNotify = NULL; 
		EndMoniter(); 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
		return FALSE; 
	} 
	// ���������߳� 
	VERIFY( ResumeThread( m_hThread ) ); 
	return TRUE; 
} 

void CDirectoryMonitor::EndMoniter( void ) 
{ 
	// ���ø���ͬ������ 
	__super::EndMoniter(); 
	// �ж�֪ͨ����Ƿ���� 
	if ( m_hNotify ) 
	{ 
		// ����֪ͨ 
		VERIFY( FindCloseChangeNotification(m_hNotify)); 
		m_hNotify = NULL; // ֪ͨ������� 
	} 
} 

void CDirectoryMonitor::CallNextMoniter( void ) 
{ 
	VERIFY(FindNextChangeNotification( m_hNotify )); 
} 

DWORD CDirectoryMonitor::WaitNotify( void ) 
{ 
	return WaitForSingleObject( m_hNotify, 0 ); 
} 



/////////////////////////////////////////////////////////////////////////////// 
// CRegistryMonitor 

// ���캯�� 
CRegistryMonitor::CRegistryMonitor( void ) 
: m_hKey( NULL ) 
, m_hNotify( NULL ) 
, m_dwFilter( 0 ) 
{ 

} 

// �������� 
CRegistryMonitor::~CRegistryMonitor( void ) 
{ 

} 

// �������� 
BOOL CRegistryMonitor::StartMoniter( DWORD dwMonId, HWND hWnd, HKEY hRoot, 
																		LPCTSTR lpSubKey, DWORD dwFilter ) 
{ 
	// ���ø���ͬ������ 
	if ( ! __super::StartMoniter( dwMonId, hWnd ) ) 
	{ 
		return FALSE; 
	} 
	// ��Ա���ݸ�ֵ 
	m_dwFilter = dwFilter; 
	// ��ע���� 
	LONG lr; 
	lr = RegOpenKeyEx( hRoot, lpSubKey, 0, KEY_NOTIFY, &m_hKey ); 
	if ( ERROR_SUCCESS != lr ) 
	{ 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
		return FALSE; 
	} 
	// ����֪ͨ�¼���� 
	m_hNotify = CreateEvent( NULL, FALSE, FALSE, NULL ); 
	ASSERT( NULL != m_hNotify ); 
	// ��ʼ���� 
	CallNextMoniter(); 
	// ���������߳� 
	VERIFY( ResumeThread(m_hThread)); 
	return TRUE; 
} 

// �������� 
void CRegistryMonitor::EndMoniter( void ) 
{ 
	CChangeMonitor::EndMoniter(); 
	if ( m_hNotify ) 
	{ 
		VERIFY( CloseHandle( m_hNotify ) ); 
		m_hNotify = NULL; 
	} 
	if ( m_hKey ) 
	{ 
		VERIFY( ERROR_SUCCESS == RegCloseKey( m_hKey ) ); 
		m_hKey = NULL; 
	} 
} 

void CRegistryMonitor::CallNextMoniter( void ) 
{ 
	ASSERT(m_hKey); 
	ASSERT(m_hNotify); 
	// �������Ӿ�� 
	VERIFY( ERROR_SUCCESS == RegNotifyChangeKeyValue( m_hKey, TRUE, m_dwFilter, m_hNotify, TRUE )); 
} 

DWORD CRegistryMonitor::WaitNotify( void ) 
{ 
	return WaitForSingleObject( m_hNotify, 0 ); 
} 

