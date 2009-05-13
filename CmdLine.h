

#ifndef HWX_CMDLINE_H
#define HWX_CMDLINE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_ARG						(50)

class CParseCmdLine
{
public:
	CParseCmdLine(LPCTSTR);
	virtual ~CParseCmdLine();
	DWORD GetCount() const;
	LPCTSTR GetArgument(DWORD) const;
protected:
	void Reset();
	void Parse(LPCTSTR);

protected:

	TCHAR m_szCmdLine[MAX_SIZE_LL];
	LPTSTR m_pszArg[MAX_ARG];
	WORD m_wArgCount;
};

#endif //HWX_CMDLINE_H
