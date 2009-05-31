
#ifndef HWX_HWMUTEXLOCK_H
#define HWX_HWMUTEXLOCK_H

class HWMutexLock
{
protected:
	HANDLE  m_hMutex;
public:
	HWMutexLock(LPCTSTR);
	virtual ~HWMutexLock();
};

#endif//HWX_HWCRITICALSECTIONLOCK_H
