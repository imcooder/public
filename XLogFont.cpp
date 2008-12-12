/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XLogFont.cpp					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/18
*********************************************************************/
#include "stdafx.h"
#include "XLogFont.h"

CXLogFont::CXLogFont()
: dwType(0)
{
	::ZeroMemory(this, sizeof(CXLogFont));
}

CXLogFont::CXLogFont(const LOGFONT& logfont)
: dwType(0)
{
	memcpy((void*)&*this, (const void*)&logfont, (DWORD)sizeof(LOGFONT));
}

void CXLogFont::operator=(LOGFONT& logfont)
{
	memcpy((void*)&*this, (const void*)&logfont, (DWORD)sizeof(LOGFONT));
}

const CXLogFont& CXLogFont::operator =(const CXLogFont& tLF)
{
	memcpy((void*)&*this, (const void*)&tLF, (DWORD)sizeof(LOGFONT));
	dwType = tLF.dwType;
	return *this;
}
const CXLogFont& CXLogFont::operator =(const LOGFONT& tLF)
{
	memcpy((void*)&*this, (const void*)&tLF, (DWORD)sizeof(LOGFONT));
	dwType = 0;
	return *this;
}
BOOL CXLogFont::operator <(const CXLogFont& tA)
{
	return _tcscmp(lfFaceName, tA.lfFaceName) < 0;
}