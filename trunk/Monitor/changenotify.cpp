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
	// 判断是否已经启动监视 
	if (!m_hThread) 
	{ 
		SetLastError( ERROR_NOTIFY_ALREADY_START ); 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
		return FALSE; 
	} 
	// 检查参数 
	if (!hWnd) 
	{ 
		SetLastError( ERROR_INVALID_PARAMETER ); 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
		return FALSE; 
	} 
	m_dwMonId = dwMonId; 
	m_hWnd = hWnd; 
	// 创建监视线程 
	m_hThread = CreateThread(NULL, 0, ChangeMonitorThread, (LPVOID)this, CREATE_SUSPENDED, &m_dwThreadId ); 
	ASSERT(m_hThread); 
	return TRUE; 
} 

void CChangeMonitor::EndMoniter( void ) 
{ 
	// 判断线程是否存在 
	if ( m_hThread ) 
	{ 
		// 判断线程是否结束 
		DWORD dwExitCode; 
		VERIFY( GetExitCodeThread( m_hThread, &dwExitCode ) ); 
		if ( STILL_ACTIVE == dwExitCode ) 
		{ 
			ASSERT( m_dwThreadId != 0 ); 
			// 向线程发送退出消息 
			VERIFY( PostThreadMessage( m_dwThreadId, WM_MONITER_EXIT, 0, 0 ) ); 
			// 使线程继续，以便结束 
			Resume(); 
			// 等待线程退出 
			DWORD dwWaitResult = WaitForSingleObject( m_hThread, INFINITE ); 
			ASSERT( WAIT_FAILED != dwWaitResult ); 
			// 如果等待超时，强制结束线程 
			if ( WAIT_TIMEOUT == dwWaitResult ) 
			{ 
				if ( FALSE == TerminateThread( m_hThread, 0 ) ) 
				{ 
					HWTRACE(TEXT("LastError:%d"), GetLastError()); 
				} 
			} 
		} 
		// 关闭线程句柄，将线程相关数据置零 
		SAFE_CLOSE_HANDLE(m_hThread);
		m_dwThreadId = 0; 
	} 
	m_hWnd = NULL; // 通知窗体置零 
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
	// 检查通知窗体句柄是否存在 
	ASSERT(m_hWnd); 
	if (!m_hWnd)
	{
		return;
	}
	// 发送通知消息 
	if ( !PostMessage( m_hWnd, nMsg, m_dwMonId, 0 ) ) 
	{ 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
	} 
} 

DWORD CALLBACK ChangeMonitorThread( LPVOID pParam ) 
{ 
	// 检查参数是否为空 
	ASSERT( pParam != NULL ); 
	// 得到监视器类对象指针 
	CChangeMonitor *pChaMon = (CChangeMonitor*)pParam; 
	// 检查对象 
	ASSERT( pChaMon->m_hThread != NULL ); 
	ASSERT( pChaMon->m_hWnd != NULL ); 
	ASSERT( pChaMon->m_dwThreadId != 0 ); 
	// 进入线程消息循环 
	MSG msg; // 消息数据结构 
	while( !PeekMessage( &msg, NULL, WM_MONITER_EXIT, WM_MONITER_EXIT, PM_REMOVE ) ) 
	{ 
		// 以0超时等待通知，直接返回等待结果 
		DWORD dwWaitResult = pChaMon->WaitNotify(); 
		ASSERT( dwWaitResult != WAIT_FAILED ); 
		switch( dwWaitResult ) // 处理等待结果 
		{ 
		case WAIT_OBJECT_0: // 通知已接收 
			{
				// 向接收者发送通知消息 
			pChaMon->SendNotify( WM_MONITER_CHANGED ); 
			// 继续下一次等待 
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

// 构造函数 
CDirectoryMonitor::CDirectoryMonitor( void ) 
: m_hNotify( NULL ) 
{ 
} 

// 析构函数 
CDirectoryMonitor::~CDirectoryMonitor( void ) 
{ 
} 

// 启动监视 
BOOL CDirectoryMonitor::StartMoniter( DWORD dwMonId, HWND hWnd, LPCTSTR lpPath, 
																		 BOOL bSubTree, DWORD dwFilter ) 
{ 
	// 调用父类同名函数 
	if (!__super::StartMoniter( dwMonId, hWnd ) ) 
	{ 
		return FALSE; 
	} 
	// 创建监视 
	m_hNotify = FindFirstChangeNotification( lpPath, bSubTree, dwFilter ); 
	if ( INVALID_HANDLE_VALUE == m_hNotify ) 
	{ 
		m_hNotify = NULL; 
		EndMoniter(); 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
		return FALSE; 
	} 
	// 启动监视线程 
	VERIFY( ResumeThread( m_hThread ) ); 
	return TRUE; 
} 

void CDirectoryMonitor::EndMoniter( void ) 
{ 
	// 调用父类同名函数 
	__super::EndMoniter(); 
	// 判断通知句柄是否存在 
	if ( m_hNotify ) 
	{ 
		// 结束通知 
		VERIFY( FindCloseChangeNotification(m_hNotify)); 
		m_hNotify = NULL; // 通知句柄置零 
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

// 构造函数 
CRegistryMonitor::CRegistryMonitor( void ) 
: m_hKey( NULL ) 
, m_hNotify( NULL ) 
, m_dwFilter( 0 ) 
{ 

} 

// 析构函数 
CRegistryMonitor::~CRegistryMonitor( void ) 
{ 

} 

// 启动监视 
BOOL CRegistryMonitor::StartMoniter( DWORD dwMonId, HWND hWnd, HKEY hRoot, 
																		LPCTSTR lpSubKey, DWORD dwFilter ) 
{ 
	// 调用父类同名函数 
	if ( ! __super::StartMoniter( dwMonId, hWnd ) ) 
	{ 
		return FALSE; 
	} 
	// 成员数据赋值 
	m_dwFilter = dwFilter; 
	// 打开注册表键 
	LONG lr; 
	lr = RegOpenKeyEx( hRoot, lpSubKey, 0, KEY_NOTIFY, &m_hKey ); 
	if ( ERROR_SUCCESS != lr ) 
	{ 
		HWTRACE(TEXT("LastError:%d"), GetLastError()); 
		return FALSE; 
	} 
	// 创建通知事件句柄 
	m_hNotify = CreateEvent( NULL, FALSE, FALSE, NULL ); 
	ASSERT( NULL != m_hNotify ); 
	// 开始监视 
	CallNextMoniter(); 
	// 启动监视线程 
	VERIFY( ResumeThread(m_hThread)); 
	return TRUE; 
} 

// 结束监视 
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
	// 创建监视句柄 
	VERIFY( ERROR_SUCCESS == RegNotifyChangeKeyValue( m_hKey, TRUE, m_dwFilter, m_hNotify, TRUE )); 
} 

DWORD CRegistryMonitor::WaitNotify( void ) 
{ 
	return WaitForSingleObject( m_hNotify, 0 ); 
} 

