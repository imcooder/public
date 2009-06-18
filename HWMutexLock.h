
#ifndef HWX_HWMUTEXLOCK_H
#define HWX_HWMUTEXLOCK_H

class HWMutexLock
{
protected:
	HANDLE  m_hMutex;
	BOOL		m_bCreate;
public:
	HWMutexLock(LPCWSTR);
	HWMutexLock(HANDLE);
	virtual ~HWMutexLock();
};

#endif//HWX_HWCRITICALSECTIONLOCK_H
