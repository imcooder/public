
#ifndef HWX_THREAD_H
#define HWX_THREAD_H

#include <windows.h>

class CHWThread  
{
protected:
	CHWThread();
public:	
	virtual ~CHWThread();
	virtual BOOL Terminate();		
	virtual BOOL CreateThread();
	virtual BOOL SetThreadPriority(int);
protected:
	HANDLE m_hThread;		
	HANDLE m_hTerminateEvent;
	DWORD m_dwThreadID;
protected:
	void TryExit(DWORD = 0);
	virtual LRESULT _ThreadProc();	
	static DWORD WINAPI ThreadProc(LPVOID lpParam);
};

#endif//HWX_THREAD_H

