
#ifndef HWX_HWWOW64REDIRECTIONLOCK_H
#define HWX_HWWOW64REDIRECTIONLOCK_H

typedef BOOL (WINAPI *LPWow64DisableWow64FsRedirection)(PVOID*);
typedef BOOL (WINAPI *LPWow64RevertWow64FsRedirection)(PVOID);


class CHWWow64RedirectionLock
{
public:
	CHWWow64RedirectionLock();
	virtual ~CHWWow64RedirectionLock();
protected:	
	void Release();
protected:
	HMODULE m_hKernel;
	LPWow64DisableWow64FsRedirection	m_pDisable;
	LPWow64RevertWow64FsRedirection m_pRevert;
	PVOID m_pvOldState;

};

#endif//HWX_HWCRITICALSECTIONLOCK_H
