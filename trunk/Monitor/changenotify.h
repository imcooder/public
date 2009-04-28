#ifndef HWX_CHANGENOTIFY_H
#define HWX_CHANGENOTIFY_H



#pragma once 
#define WM_MONITER					(WM_USER + 0X1000) 
#define WM_MONITER_EXIT			(WM_MONITER + 1) 
#define WM_MONITER_CHANGED	(WM_MONITER + 2) 

#define ERROR_NOTIFY 100000L 
#define ERROR_NOTIFY_ALREADY_START		 (ERROR_NOTIFY + 1) 

/////////////////////////////////////////////////////////////////////////////// 

DWORD CALLBACK ChangeMonitorThread(LPVOID pParam); 
class CChangeMonitor 
{ 
public: 
	CChangeMonitor(); 
	virtual ~CChangeMonitor(); 
	virtual BOOL StartMoniter(DWORD dwMonId,HWND hWnd); 
	virtual void EndMoniter( void ); 
	virtual void Pause( void ); 
	virtual void Resume( void ); 
protected: 
	virtual void SendNotify( UINT nMsg ); 
	virtual void CallNextMoniter( void ) = 0; 
	virtual DWORD WaitNotify( void ) = 0; 
protected: 
	DWORD m_dwMonId; 
	HANDLE m_hThread; 
	HWND m_hWnd; 
	DWORD m_dwThreadId;
	friend DWORD CALLBACK ChangeMonitorThread(LPVOID pParam); 
}; 


/////////////////////////////////////////////////////////////////////////////// 

class CDirectoryMonitor : public CChangeMonitor 
{ 
public: 
	CDirectoryMonitor(); 
	virtual ~CDirectoryMonitor(); 
	BOOL StartMoniter( DWORD dwMonId, HWND hWnd, LPCTSTR lpPath, BOOL bSubTree = TRUE, DWORD dwFilter = FILE_NOTIFY_CHANGE_LAST_WRITE ); 
	void EndMoniter( void ); 
protected: 
	virtual void CallNextMoniter( void ); 
	virtual DWORD WaitNotify( void ); 
protected: 
	HANDLE m_hNotify; 
}; 

/////////////////////////////////////////////////////////////////////////////// 

class CRegistryMonitor : public CChangeMonitor 
{ 
public: 
	CRegistryMonitor(); 
	virtual ~CRegistryMonitor(); 
	BOOL StartMoniter( DWORD dwMonId, HWND hWnd, HKEY hRoot, LPCTSTR lpSubKey, DWORD dwFilter = REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET ); 
	void EndMoniter( void ); 
protected: 
	virtual void CallNextMoniter( void ); 
	virtual DWORD WaitNotify( void ); 
protected: 
	HANDLE	m_hNotify; 
	HKEY		m_hKey; 
	DWORD		m_dwFilter; 
}; 



#endif //HWX_CHANGENOTIFY_H