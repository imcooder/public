
#include "stdafx.h"
#include "XObjectNameSpace.h"
#include <winbase.h>
#include <windows.h>
#include <Sddl.h> 

CXCoreNameSpace::CXCoreNameSpace( LPCTSTR pszNamespace) : 
m_hBoundary(NULL)
, m_hNamespace(NULL)
, m_bNamespaceOpened(FALSE)
{
	_tcscpy_s(m_szBoundary, MAX_NAME, TEXT("Xuejuntao@hanwang.com.cn"));
	if (!pszNamespace)
	{
		_tcscpy_s(m_szNamespace, MAX_NAME, TEXT("Xuejuntao"));
	}
	else
	{
		_tcscpy_s(m_szNamespace, MAX_NAME, pszNamespace);
	}
	m_hBoundary = CreateBoundaryDescriptor(m_szBoundary, 0);
	// Create a SID corresponding to the Local Administrator group
	BYTE localAdminSID[SECURITY_MAX_SID_SIZE];
	PSID pLocalAdminSID = &localAdminSID;
	DWORD cbSID = sizeof(localAdminSID);
	if (!CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, pLocalAdminSID, &cbSID))
	{			
			return;
	}
	if (!AddSIDToBoundaryDescriptor(&m_hBoundary, pLocalAdminSID)) 
	{		
		return;
	}

	// Create the namespace for Local Administrators only
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;
	if (!ConvertStringSecurityDescriptorToSecurityDescriptor(TEXT("D:(A;;GA;;;BA)"), SDDL_REVISION_1, &sa.lpSecurityDescriptor, NULL)) 
	{		
		return;
	}

	m_hNamespace =CreatePrivateNamespace(&sa, m_hBoundary, m_szNamespace);
	// Don't forget to release memory for the security descriptor
	LocalFree(sa.lpSecurityDescriptor);

	// Check the private namespace creation result
	DWORD dwLastError = GetLastError();
	if (!m_hNamespace) 
	{
		// Nothing to do if access is denied
		// --> this code must run under a Local Administrator account
		if (dwLastError == ERROR_ACCESS_DENIED)
		{
			TRACE(TEXT("Access denied when creating the namespace.\r\n"));
			TRACE(TEXT("You must be running as Administrator.\r\n\r\n"));
			return;
		}
		else
		{
			if (dwLastError == ERROR_ALREADY_EXISTS) 
			{
				// If another instance has already created the namespace,				
				TRACE(TEXT("CreatePrivateNamespace failed: %u\r\n"), dwLastError);
				m_hNamespace = OpenPrivateNamespace(m_hBoundary, m_szNamespace);
				if (!m_hNamespace) 
				{
					TRACE(TEXT(" and OpenPrivateNamespace failed: %u\r\n"),	dwLastError);
					return;
				} 
				else 
				{
					m_bNamespaceOpened = TRUE;
					TRACE(TEXT(" but OpenPrivateNamespace succeeded\r\n\r\n"));
				}
			} 
			else 
			{
				TRACE(TEXT("Unexpected error occurred: %u\r\n\r\n"), dwLastError);
				return;
			}
		}
	}
}
CXCoreNameSpace::~CXCoreNameSpace()
{
	if (m_hNamespace) 
	{
		if (m_bNamespaceOpened) 
		{ // Open namespace
			ClosePrivateNamespace(m_hNamespace, 0);
			m_hNamespace = NULL;
		} 
		else 
		{ // Created namespace
			ClosePrivateNamespace(m_hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
			m_hNamespace = NULL;
		}
	}

	if (m_hBoundary) 
	{
		DeleteBoundaryDescriptor(m_hBoundary);
		m_hBoundary = NULL;
	}
}
CXCoreNameSpace* CXCoreNameSpace::GetInstance()
{
	static CXCoreNameSpace xNameSpace(TEXT("xuejuntao"));
	return &xNameSpace;
}
LPCTSTR CXCoreNameSpace::GetNamespace() const
{
	return m_szNamespace;
}
BOOL CXCoreNameSpace::Succeed() const
{
	return (BOOL)m_hNamespace;
}