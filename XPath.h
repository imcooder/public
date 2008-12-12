/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XPath.h					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/22
*********************************************************************/
#ifndef HWX_PATH_H
#define HWX_PATH_H
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "HWXString.h"

class DLLXEXPORT CXPathA : public CXStringA
{
public:
	CXPathA(LPCSTR);
	CXPathA();
	virtual ~CXPathA();
	void Append(LPCSTR);
	BOOL FileExists() const;
	BOOL IsDirectory()	const;
	BOOL LongPathToShortPath();
	BOOL ShortPathToLongPath();
	BOOL FindExt(LPSTR) const;
	const CXPathA& operator=(LPCSTR);
};

class DLLXEXPORT CXPathW : public CXStringW
{
public:
	CXPathW(LPCWSTR);
	CXPathW();
	virtual ~CXPathW();
	void Append(LPCWSTR);
	BOOL FileExists() const;
	BOOL IsDirectory() const;
	BOOL LongPathToShortPath();
	BOOL ShortPathToLongPath();
	BOOL FindExt(LPWSTR) const;
	const CXPathW& operator=(LPCWSTR);
};


#ifdef UNICODE
typedef CXPathW CXPathT;
#else 
typedef CXPathA CXPathT;
#endif

typedef CXPathT CXPath;


#endif// HWX_PATH_H