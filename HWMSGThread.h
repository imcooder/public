

#ifndef HW_HWMSGTHREAD_H
#define HW_HWMSGTHREAD_H

#include "HWThread.h"
#include <Ext_Type.h>
class CHWMSGThread : public CHWThread
{
protected:
	CHWMSGThread();
public:	
	virtual ~CHWMSGThread();
	virtual BOOL Terminate();	
	virtual BOOL CreateThread();
	virtual BOOL Release();	
	BOOL PostMessage(UINT, WPARAM, LPARAM);
	LRESULT SendMessage(UINT, WPARAM, LPARAM);
protected:	
	HANDLE m_hStartEvent;	
protected:	
	//////////////////////////////////////////////////////////////////////////		
	LRESULT DefThreadProc(UINT, WPARAM, LPARAM);
	virtual LRESULT _Proc(UINT, WPARAM, LPARAM);
	virtual LRESULT _ThreadProc();
	BOOL m_blExit;
};

#endif	//HW_HWMSGTHREAD_H
