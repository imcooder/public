#include "stdafx.h"
#include "HWXReg.h"
#include <tchar.h>
#include <assert.h>
#define REG_BufferMaxLen		(256)
/*================================================================ 
* ��������    CXReg
* ������      (HKEY hRootKey) 
* ˵����      ������캯��������������ʹ��Ĭ�ϵĲ�����m_hRootKey����ʼ��
			  ΪHKEY_LOCAL_MACHINE, ������в����� m_hRootKeyΪָ����ֵ
================================================================*/ 
CXReg::CXReg(HKEY hRootKey) : m_hRootKey(hRootKey)
{	
}
 /************************************************************************
 ����:	SetRootKey
 ȫ��:	void CXReg::SetRootKey( HKEY hRootKey )
 ����:	public 
 ����ֵ:	void: 
 ����:	 ���ø���ֵ
 ����:	HKEY hRootKey: 
 ************************************************************************/
void CXReg::Attach( HKEY hRootKey )
{
	assert(NULL != hRootKey);
	m_hRootKey = hRootKey;
}

CXReg::~CXReg() //�����������йرմ�ע�����
{
	m_hRootKey = NULL;
}

/*================================================================ 
* ��������    VerifyKey
* ������      (HKEY hRootKey, LPCTSTR pszPath) 
* ��������:   �жϸ�����·���Ƿ���� (���д򿪵Ĺ���)
			  �����һ������ΪNULL����ʹ��Ĭ�ϵĸ�����
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::VerifyKey (LPCTSTR pszPath)
{
 	BOOL blRet = TRUE;
	HKEY hKey = NULL;
	if(ERROR_SUCCESS != RegOpenKeyEx (m_hRootKey, pszPath, 0L, KEY_ALL_ACCESS, &hKey))
	{	
		blRet = FALSE;		
	}
	if (hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return blRet;
}




/*================================================================ 
* ��������    VerifyValue
* ������      (LPCTSTR pszValue)
* ��������:   �ж�ָ���ļ����Ƿ����ĳ��ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::IsEqual(LPCTSTR pszKey, LPCTSTR pszValue, DWORD dwValue)
{
	DWORD dwTemp;
	if (!Read(pszKey, pszValue, dwTemp))
	{
		return FALSE;
	}		
	return dwTemp == dwValue;
}
BOOL CXReg::IsEqual(LPCTSTR pszKey, LPCTSTR pszValue,LPCTSTR lpszString)
{
	CXStringT str;
	if (!Read(pszKey, pszValue, str))
	{
		return FALSE;
	}	
	return str.CompareNoCase(lpszString);	
}


/*================================================================ 
* ��������    CreateKey
* ������      (HKEY hRootKey, LPCTSTR pszPath)
* ��������:   ����·��
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
HKEY CXReg::CreateKey (LPCTSTR pszPath, REGSAM sam)
{
	HKEY hKey = NULL;
	DWORD dwTmp;		
	RegCreateKeyEx (m_hRootKey, pszPath, 0L, NULL, REG_OPTION_NON_VOLATILE, sam, 
		NULL, &hKey, &dwTmp);	
	return hKey;
}


/*================================================================ 
* ��������    Write
* ������      (LPCTSTR lpszKeyName, DWORD dwVal)
* ��������:   д��DWORDֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Write (LPCTSTR lpszKeyName, LPCTSTR lpszValue, DWORD dwVal)
{
	BOOL blRet = FALSE;
	HKEY hKey = NULL;
	if (!lpszKeyName)
	{
		return FALSE;
	}
	VERIFY(hKey = CreateKey(lpszKeyName));	
	blRet = (ERROR_SUCCESS == ::RegSetValueEx (hKey, lpszValue, 0L, REG_DWORD,
		(const BYTE*) &dwVal, sizeof(DWORD)));
	if (hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return blRet;
}


/*================================================================ 
* ��������    Write
* ������      (LPCTSTR lpszKeyName, LPCTSTR pszData)
* ��������:   д���ַ���ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Write (LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR pszData)
{
	BOOL blRet = FALSE;
	HKEY hKey = NULL;
	if (!lpszKeyName)
	{
		return FALSE;
	}
	VERIFY(hKey = CreateKey(lpszKeyName));
	blRet = (ERROR_SUCCESS == RegSetValueEx (hKey, lpszValue, 0L, REG_SZ, (const BYTE*) pszData,
		(LONG)(_tcslen(pszData) + 1) * sizeof(TCHAR)));	
	if (hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return blRet;
}
/*================================================================ 
* ��������    Write
* ������      (LPCTSTR lpszKeyName, BYTE *pbData, long nSiz)
* ��������:   д�������
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Write (LPCTSTR lpszKeyName, LPCTSTR pszValue, const BYTE *pbData, DWORD dwSize)
{
	BOOL blRet = FALSE;
	HKEY hKey = NULL;
	if (!lpszKeyName)
	{
		return FALSE;
	}
	VERIFY(hKey = CreateKey(lpszKeyName));
	blRet = ERROR_SUCCESS == RegSetValueEx (hKey, pszValue, 0L, REG_BINARY,	(const BYTE*)pbData,
		dwSize);
	if (hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return blRet;
}
/*================================================================ 
* ��������    Read
* ������      (LPCTSTR lpszKeyName, DWORD& dwVal) ��2������ͨ�����ô��ݣ������ں������޸�ʵ��
* ��������:   ��ȡDWORDֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Read (LPCTSTR lpszKeyName, LPCTSTR lpszValue, DWORD& dwVal)
{
	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;	
	HKEY hSubKey = NULL;
	BOOL blRet = FALSE;
	hSubKey = OpenKey(lpszKeyName, KEY_READ);
	if (!hSubKey)
	{
		return FALSE;
	}
	if(ERROR_SUCCESS == RegQueryValueEx (hSubKey, lpszValue, NULL, &dwType, (BYTE *) &dwDest,
		&dwSize) && REG_DWORD == dwType)
	{
		dwVal = dwDest;
		blRet = TRUE;
	}
	if (hSubKey)
	{
		RegCloseKey(hSubKey);
		hSubKey = NULL;
	}
	return blRet;
}


/*================================================================ 
* ��������    Read
* ������      (LPCTSTR lpszKeyName, CString& sVal) ��2������ͨ�����ô��ݣ������ں������޸�ʵ��
* ��������:   ��ȡ�ַ���ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Read (LPCTSTR lpszKeyName, LPCTSTR lpszValue, CXString& sVal)
{	
	DWORD dwType;
	DWORD dwSize = REG_BufferMaxLen;
	TCHAR szString[REG_BufferMaxLen];
	HKEY hSubKey = NULL;
	BOOL blRet = FALSE;
	hSubKey = OpenKey(lpszKeyName, KEY_READ);
	if (!hSubKey)
	{
		return FALSE;
	}
	if(ERROR_SUCCESS == RegQueryValueEx (hSubKey, lpszValue, NULL, &dwType, (BYTE *)szString, 
		&dwSize) && REG_SZ == dwType)
	{
		sVal = szString;
		blRet = TRUE;
	}
	if (hSubKey)
	{
		RegCloseKey(hSubKey);
		hSubKey = NULL;
	}
	return blRet;
}

/*================================================================ 
* ��������    Read
* ������      (LPCTSTR lpszKeyName, BYTE *pbVal, long nBufferSize) ��2������ͨ��ָ�봫�ݣ������ں������޸�ʵ��
* ��������:   ��ȡ�ַ���ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Read (LPCTSTR lpszKeyName, LPCTSTR lpszValue, BYTE *&pbData, DWORD& dwSize)
{	
	assert(NULL != pbData && dwSize > 0);
	if (!pbData)
	{
		return FALSE;
	}
	DWORD dwType;
	HKEY hSubKey = NULL;
	BOOL blRet = FALSE;
	dwSize = 0;
	hSubKey = OpenKey(lpszKeyName, KEY_READ);
	if (!hSubKey)
	{
		return FALSE;
	}
	if(ERROR_SUCCESS == RegQueryValueEx (hSubKey, lpszValue, NULL,	&dwType, NULL, &dwSize) &&
		REG_BINARY == dwType)
	{		
		if (dwSize)
		{
			VERIFY(pbData = new BYTE[dwSize]);
			VERIFY(ERROR_SUCCESS == RegQueryValueEx (hSubKey, lpszValue, NULL,	&dwType, pbData, &dwSize));
		}
		blRet = TRUE;		
	}
	if (hSubKey)
	{
		RegCloseKey(hSubKey);
		hSubKey = NULL;
	}
	return blRet;
}

/*================================================================ 
* ��������    DeleteValue
* ������      (LPCTSTR pszValue) 
* ��������:   ɾ��ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::DeleteValue( LPCTSTR pszKey, LPCTSTR pszValue )
{
	BOOL blRet = TRUE;
	HKEY hSubKey = NULL;
	if (!(hSubKey = OpenKey(pszKey)))
	{
		return TRUE;
	}
	if(ERROR_SUCCESS != ::RegDeleteValue(hSubKey, pszValue))		
	{
		blRet = FALSE;
	}
	if (hSubKey)
	{
		RegCloseKey(hSubKey);
		hSubKey = NULL;
	}
	return blRet;
}
/*================================================================ 
* ��������    DeleteKey
* ������      (HKEY hRootKey, LPCTSTR pszPath) 
* ��������:   ɾ��·��
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
void CXReg::DeleteKey (LPCTSTR pszPath)
{	
	assert(NULL != pszPath);
	BOOL blRet = TRUE;	
	if (!pszPath)
	{		
		return;
	}
	HKEY hSubKey = OpenKey(pszPath);
	if (hSubKey)
	{
		DeletaKeyTree(hSubKey);
		RegCloseKey(hSubKey);
		hSubKey = NULL;
	}		
	if (ERROR_SUCCESS == RegDeleteKey(m_hRootKey, pszPath))
	{
		;		
	}
	return;
}
/*================================================================ 
* ��������    Close
* ������      
* ��������:   �ر�ע���
* ����ֵ��    void
* �� �ߣ�     
================================================================*/ 

BOOL CXReg::RestoreKey(LPCTSTR lpszKey, LPCTSTR lpFileName)
{	
	assert(lpFileName);
	BOOL blRet = FALSE;
	HKEY hKey = NULL;
	if (!(hKey = OpenKey(lpszKey)))
	{
		return FALSE;
	}	
	if(ERROR_SUCCESS == RegRestoreKey(hKey, lpFileName, REG_WHOLE_HIVE_VOLATILE))
	{
		blRet = TRUE;		
	}
	if (hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return blRet;
}

BOOL CXReg::SaveKey(LPCTSTR lpszKey, LPCTSTR lpFileName)
{	
	assert(lpFileName);
	BOOL blRet = FALSE;
	HKEY hKey = NULL;
	if (!(hKey = OpenKey(lpszKey)))
	{
		return FALSE;
	}	
	if(ERROR_SUCCESS == (blRet = RegSaveKey(hKey, lpFileName, NULL)))
	{
		blRet = TRUE;		
	}
	if (hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}	
	return blRet;
}
void  CXReg::DeletaKeyTree(HKEY hKey) 
{   
	DWORD   dwCount = 0;   
	TCHAR	szSubkeyName[128];   
	HKEY   hKeySub; 
   
	if (!hKey)
	{
		return;
	}
	if(ERROR_SUCCESS != RegQueryInfoKey(hKey, 0, 0, 0, &dwCount, 0, 0, 0, 0, 0, 0, 0))   
	{   		
		return;   
	}   
	else if(dwCount)   
	{
		for(DWORD i = 0; i < dwCount; i ++)   
		{   		 
			if(ERROR_SUCCESS != RegEnumKey(hKey, 0, szSubkeyName, 128))   
			{   
				assert(0);  					
				return;   
			}   			
			if(ERROR_SUCCESS != RegOpenKey(hKey, szSubkeyName, &hKeySub))   
			{   
				assert(0);   					
				return;   
			}   
			DeletaKeyTree(hKeySub);//���õݹ�   			 
			if(ERROR_SUCCESS != RegDeleteKey(hKey, szSubkeyName))   
			{   
				assert(0);   					  
				return;   
			}   
			RegCloseKey(hKeySub);   
		}  
	}		
} 
HKEY CXReg::OpenKey( LPCTSTR pthPath, REGSAM samReg)
{
	HKEY hKey = NULL;
	if (!pthPath)
	{
		return hKey;
	}
	RegOpenKeyEx (m_hRootKey, pthPath, 0L, samReg, &hKey);		
	return hKey;
}
/*================================================================ 
* ��������    VerifyValue
* ������      (LPCTSTR pszValue)
* ��������:   �жϸ�����ֵ�Ƿ���� �����ȵ���VerifyKey��Ȼ����ʹ�øú�����
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 

BOOL CXReg::VerifyValue( LPCTSTR pthKey, LPCTSTR pthValue)
{
	BOOL blExist = FALSE;
	HKEY subKey = NULL;
	if (!pthKey || !pthValue)
	{
		blExist = FALSE;
		return blExist;
	}	
	if(ERROR_SUCCESS != RegOpenKeyEx (m_hRootKey, pthKey, 0L,
		KEY_ALL_ACCESS, &subKey))
	{	
		blExist = FALSE;
		return blExist;
	}
	if(ERROR_SUCCESS == RegQueryValueEx(subKey, pthValue, NULL,
		NULL, NULL, NULL))
	{
		blExist = FALSE;
		return blExist;
	}
	if (subKey)
	{
		RegCloseKey(subKey);   
		subKey = NULL;
	}
	return blExist;
}
