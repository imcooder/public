
#include "stdafx.h"
#include "CmdLine.h"




CParseCmdLine::CParseCmdLine( LPCTSTR pszCmd)
{
	Parse(pszCmd);
}

CParseCmdLine::~CParseCmdLine()
{

}
void CParseCmdLine::Reset()
{
	ZeroMemory(m_szCmdLine, sizeof(m_szCmdLine));
	ZeroMemory(m_pszArg, sizeof(m_pszArg));	
	m_wArgCount = 0;;
}
void CParseCmdLine::Parse(LPCTSTR pszCmd)
{
	Reset();
	if (!pszCmd)
	{
		return;
	}
	TCHAR szCmdLine[MAX_SIZE_LL] = {0};
	_tcsncpy_s(szCmdLine, _countof(szCmdLine), pszCmd, _TRUNCATE);

	TCHAR szSeprateCmd[4][MAX_SIZE_SSS] = {0};		
	LPTSTR pszToken = NULL, pszNextToken = NULL;
	m_wArgCount = 0;
	pszToken = _tcstok_s(szCmdLine, TEXT("-\\/"), &pszNextToken);
	TCHAR szArg[MAX_SIZE_M] = {0};
	while (pszToken)
	{		
		_tcsncpy_s(szArg, _countof(szArg), pszToken, _TRUNCATE);
		StrTrim(szArg, TEXT(" \t"));
		if (m_wArgCount >= _countof(m_pszArg) - 2)
		{
			break;
		}
		if (szArg[0])
		{
			LPTSTR pszLocal = NULL;
			if (!m_wArgCount)
			{
				pszLocal = m_szCmdLine;
			}
			else
			{
				pszLocal = m_pszArg[m_wArgCount - 1];
				pszLocal += _tcslen(pszLocal) + 1;
			}
			if (pszLocal + _tcslen(szArg) < m_szCmdLine + _countof(m_szCmdLine) - 3)
			{
				*pszLocal = 0;// Important for _tcsncpy_s
				_tcscpy(pszLocal, szArg);
				m_pszArg[m_wArgCount] = pszLocal;
				m_wArgCount ++;
			}
			
		}	
		pszToken = _tcstok_s(NULL, TEXT("-\\/"), &pszNextToken);
	}
}

DWORD CParseCmdLine::GetCount() const
{
	return m_wArgCount;
}

LPCTSTR CParseCmdLine::GetArgument( DWORD dwIdx) const
{
	if (dwIdx >= m_wArgCount)
	{
		return NULL;
	}
	return m_pszArg[dwIdx];
}