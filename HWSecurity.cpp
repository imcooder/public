
#include "stdafx.h"
#include "HWSecurity.h"
#include "Ext_Type.h"
#include <shlobj.h>
#include "HWDebug.h"
#include <String.h>


//////////////////////////////////////////////////////////////////////////

LONG WINAPI HWGetObjectIntegrityLevel(HANDLE hHandle, SE_OBJECT_TYPE  objectType)
{	
	DWORD integrityLevel = SECURITY_MANDATORY_UNTRUSTED_RID;
	PSECURITY_DESCRIPTOR pSD = NULL;  
	PACL acl = 0;
	if (ERROR_SUCCESS == ::GetSecurityInfo(hHandle,	objectType,	LABEL_SECURITY_INFORMATION,	0,	0,	0,	&acl,	&pSD))
	{		
		if (0 != acl && 0 < acl->AceCount)
		{
			ASSERT(1 == acl->AceCount);
			SYSTEM_MANDATORY_LABEL_ACE* ace = 0;
			if(::GetAce(acl, 0,	reinterpret_cast<void**>(&ace)))
			{
				ASSERT(0 != ace);
				SID* sid = reinterpret_cast<SID*>(&ace->SidStart);
				integrityLevel = sid->SubAuthority[0];
			}			
		}
		if (pSD)
		{
			LocalFree ( pSD );
		}
	}		
	return integrityLevel;
}

#ifndef LABEL_SECURITY_INFORMATION
#define LABEL_SECURITY_INFORMATION       (0x00000010L)
#endif

BOOL WINAPI HWSetObjectToLowIntegrity( HANDLE hObject, SE_OBJECT_TYPE type) 
{ 
#if (WINVER >= 0x0600)	
	BOOL  blRet = TRUE;  
	{
		OSVERSIONINFO osVersionInfo;
		ZeroMemory(&osVersionInfo, sizeof(osVersionInfo));
		osVersionInfo.dwOSVersionInfoSize = sizeof(osVersionInfo);
		GetVersionEx(&osVersionInfo);		
		if (osVersionInfo.dwPlatformId >= VER_PLATFORM_WIN32_NT && osVersionInfo.dwMajorVersion >= 6)
		{	
			blRet = FALSE;		
			PSECURITY_DESCRIPTOR pSD = NULL;      
			PACL pSacl = NULL;                  // Œ¥∑÷≈‰  
			BOOL fSaclPresent = FALSE;  
			BOOL fSaclDefaulted = FALSE;  

			if (ConvertStringSecurityDescriptorToSecurityDescriptor(TEXT("S:(ML;;NW;;;LW)"), SDDL_REVISION_1, 	&pSD, NULL))
			{	
				if (GetSecurityDescriptorSacl(pSD, &fSaclPresent, &pSacl, &fSaclDefaulted))
				{
					blRet = (ERROR_SUCCESS  == SetSecurityInfo(hObject, type,   LABEL_SECURITY_INFORMATION, NULL, NULL, NULL, pSacl));
				} 			
				LocalFree ( pSD );
			}		
		}
	}
	return blRet;
#else
	return TRUE;
#endif
}


LONG WINAPI HWGetFileIntegrityLevel(LPTSTR pszFilePath)
{	
	DWORD integrityLevel = SECURITY_MANDATORY_UNTRUSTED_RID;
	PSECURITY_DESCRIPTOR pSD = NULL;  
	PACL acl = 0;
	if (ERROR_SUCCESS == ::GetNamedSecurityInfo(pszFilePath,	SE_FILE_OBJECT,	LABEL_SECURITY_INFORMATION,	0, 0,	0, &acl, &pSD))
	{		
		if (0 != acl && 0 < acl->AceCount)
		{
			ASSERT(1 == acl->AceCount);
			SYSTEM_MANDATORY_LABEL_ACE* ace = 0;
			if(::GetAce(acl, 0,	reinterpret_cast<void**>(&ace)))
			{
				ASSERT(0 != ace);
				SID* sid = reinterpret_cast<SID*>(&ace->SidStart);
				integrityLevel = sid->SubAuthority[0];
			}			
		}
		if (pSD)
		{
			LocalFree ( pSD );
		}
	}		
	return integrityLevel;
}


BOOL WINAPI HWSetFileToLowIntegrity(LPCTSTR pszFileName)
{	
#if (WINVER >= 0x0600)
	BOOL  b = TRUE; 
	{
		OSVERSIONINFO osVersionInfo;
		ZeroMemory(&osVersionInfo, sizeof(osVersionInfo));
		osVersionInfo.dwOSVersionInfoSize = sizeof(osVersionInfo);
		GetVersionEx(&osVersionInfo);		
		if (osVersionInfo.dwPlatformId >= VER_PLATFORM_WIN32_NT && osVersionInfo.dwMajorVersion >= 6)
		{	 
			b = FALSE;		
			PSECURITY_DESCRIPTOR pSD = NULL;      
			PACL pSacl = NULL;                  // Œ¥∑÷≈‰  
			BOOL fSaclPresent = FALSE;  
			BOOL fSaclDefaulted = FALSE;  

			if (ConvertStringSecurityDescriptorToSecurityDescriptor(TEXT("S:(ML;;NW;;;LW)"), SDDL_REVISION_1,	&pSD, NULL))
			{
				if (GetSecurityDescriptorSacl(pSD, &fSaclPresent,	&pSacl, &fSaclDefaulted))
				{
					b = ERROR_SUCCESS == SetNamedSecurityInfo((LPTSTR)pszFileName, SE_FILE_OBJECT,  LABEL_SECURITY_INFORMATION, NULL, NULL, NULL, pSacl);
				}
				LocalFree ( pSD );
			}	
		}
	}
	return b;
#else
	return TRUE;
#endif
}



BOOL WINAPI Helper_GetProcessElevation(BOOL* pIsElevation) 
{
	BOOL bIsAdmin = FALSE;
	BOOL bIsElevation = FALSE;
#if (WINVER >= 0x0600)
	{
		HANDLE hToken = NULL;
		DWORD dwSize;
		TOKEN_ELEVATION_TYPE ElevationType;
		// Get current process token
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		{
			bIsAdmin = IsUserAnAdmin();
		}	
		else
		{
			// Retrieve elevation type information
			if (GetTokenInformation(hToken, TokenElevationType,	&ElevationType, sizeof(TOKEN_ELEVATION_TYPE), &dwSize)) 
			{
				// Create the SID corresponding to the Administrators group
				BYTE adminSID[SECURITY_MAX_SID_SIZE];
				dwSize = sizeof(adminSID);
				CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, &adminSID, &dwSize);
				if (ElevationType == TokenElevationTypeLimited) 
				{
					// Get handle to linked token (will have one if we are lua)
					HANDLE hUnfilteredToken = NULL;
					GetTokenInformation(hToken, TokenLinkedToken, (VOID*)&hUnfilteredToken, sizeof(HANDLE), &dwSize);

					// Check if this original token contains admin SID
					CheckTokenMembership(hUnfilteredToken, &adminSID, &bIsAdmin); 
					// Don't forget to close the unfiltered token
					CloseHandle(hUnfilteredToken);
				} 
				else 
				{
					bIsAdmin = IsUserAnAdmin();					
				}
			}
			else
			{
				bIsAdmin = IsUserAnAdmin();
			}		
		}		

		CloseHandle(hToken);		
		if	(TokenElevationTypeDefault == ElevationType && TokenElevationTypeLimited == ElevationType)
		{
			
		}
		else if (TokenElevationTypeFull == ElevationType)
		{
			bIsElevation = FALSE;
		}
		
		return bIsAdmin;
	}
#else
	{
		bIsAdmin = IsUserAnAdmin();
	}
#endif
	if (pIsElevation)
	{
		*pIsElevation = bIsElevation;
	}
	return bIsAdmin;
}



LONG Helper_GetProcessIntegrityLevel(DWORD dwProcessId)
{	
	OSVERSIONINFO OSVersion;
	ZeroMemory( &OSVersion, sizeof( OSVersion ));
	OSVersion.dwOSVersionInfoSize = sizeof( OSVersion );
	GetVersionEx( &OSVersion );

	DWORD dwIL = SECURITY_MANDATORY_HIGH_RID;
	if(OSVersion.dwMajorVersion >= 6)
	{//Vista
		HANDLE hToken = NULL;
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
		if(hProcess)
		{
			if(OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
			{
				PTOKEN_MANDATORY_LABEL pTIL = NULL;
				DWORD dwSize=0;
				if (!GetTokenInformation(hToken, TokenIntegrityLevel, NULL, 0, &dwSize) 
					&& ERROR_INSUFFICIENT_BUFFER==GetLastError() && dwSize)
				{
					pTIL = (PTOKEN_MANDATORY_LABEL)HeapAlloc(GetProcessHeap(), 0, dwSize);
				}

				if(pTIL && GetTokenInformation(hToken, TokenIntegrityLevel, pTIL, dwSize, &dwSize))
				{
					LPBYTE lpb = GetSidSubAuthorityCount(pTIL->Label.Sid);
					if(lpb)
					{
						dwIL = *GetSidSubAuthority(pTIL->Label.Sid, *lpb - 1);
					}						
				}
				if(pTIL)
				{
					HeapFree(GetProcessHeap(), 0, pTIL);
				}
				CloseHandle(hToken);
			}
			CloseHandle(hProcess);
		}
		else 
		{
			dwIL = SECURITY_MANDATORY_UNTRUSTED_RID;
		}
	}	
	return dwIL;
}


PSID name_to_PSID(LPCTSTR pszFileName)
{
	SID_NAME_USE snu;
	TCHAR	szDomainName[512] = {0};
	DWORD	dwSidLen, dwNameLen;
	PSID  *pSid = NULL;
	dwSidLen = 512;
	pSid = (PSID*)calloc(1, dwSidLen);
	dwNameLen = sizeof(szDomainName);
	if ( !LookupAccountName(NULL, pszFileName, pSid, &dwSidLen, szDomainName, &dwNameLen, &snu) ) 
	{
		free(pSid);
		return	NULL;
	}
	return	pSid;
}

PACL	GenerateACL()
{
	PACL	pAcl = NULL;
	DWORD	szAcl = 0;
	PSID	sids[2];
	DWORD	AceMask;

	sids[0] = name_to_PSID(TEXT("everyone"));
	sids[1] = name_to_PSID(TEXT("administrators"));
	szAcl = sizeof(ACL) + ((sizeof(ACCESS_ALLOWED_ACE)-sizeof(DWORD))*sizeof(sids)/sizeof(PSID)) + GetLengthSid(sids[0]) + GetLengthSid(sids[1]);
	pAcl = (PACL) LocalAlloc(LPTR, szAcl);
	if ( !InitializeAcl(pAcl, szAcl, ACL_REVISION) ) 
	{
		LocalFree(pAcl);
		return	NULL;
	}
	AceMask = (1<<30) | (1<<31);
	if ( !AddAccessAllowedAce(pAcl, ACL_REVISION, AceMask, sids[0]) ) 
	{
		LocalFree(pAcl);
		return	NULL;
	}
	AceMask = (1<<28);
	if ( !AddAccessAllowedAce(pAcl, ACL_REVISION, AceMask, sids[1]) ) 
	{
		LocalFree(pAcl);
		return	NULL;
	}
	return	pAcl;
};

int AddAccessUser(LPTSTR pszFileName)
{
	if (!pszFileName)
	{
		return -1;
	}
	int	retval = 1;
	PACL myacl = GenerateACL();

	if ( ERROR_SUCCESS!=SetNamedSecurityInfo(pszFileName, SE_FILE_OBJECT, 	DACL_SECURITY_INFORMATION, 	NULL, NULL, myacl, NULL) ) 
	{
		retval = 0;
	}

	if ( NULL!=myacl ) 
	{
		LocalFree(myacl);
	}
	return retval;
}