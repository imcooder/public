
#ifndef HWX_HWCRITICALSECTIONLOCK_H
#define HWX_HWCRITICALSECTIONLOCK_H

class CHWCriticalSectionLock
{
protected:
	LPCRITICAL_SECTION  m_pCS;
public:
	CHWCriticalSectionLock(LPCRITICAL_SECTION);
	virtual ~CHWCriticalSectionLock();
};

#endif//HWX_HWCRITICALSECTIONLOCK_H
