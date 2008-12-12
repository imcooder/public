
#ifndef HWX_XOBJECTNAMESPACE_H
#define HWX_XOBJECTNAMESPACE_H

#include "Ext_Type.h"

class DLLXEXPORT CXCoreNameSpace
{
	CXCoreNameSpace(LPCTSTR);
public:  
	virtual ~CXCoreNameSpace();
	static CXCoreNameSpace*GetInstance();
	LPCTSTR GetNamespace() const;
	BOOL Succeed() const;
protected:
	BOOL m_bNamespaceOpened;
	TCHAR m_szNamespace[MAX_NAME];
	HANDLE m_hBoundary;
	HANDLE m_hNamespace;
private:
	TCHAR m_szBoundary[MAX_NAME];
};

#endif //HWX_XOBJECTNAMESPACE_H