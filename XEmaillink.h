/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XEMaillink.h					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/21
*********************************************************************/
#ifndef HWX_EMAILLINK_H
#define HWX_EMAILLINK_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XHyperlink.h"
/////////////////////////////////////////////////////////////////////////////
// CXEMailLink window

class DLLXEXPORT CXEMailLink : public CXHyperLink
{
// Construction/destruction
public:
    CXEMailLink();
    virtual ~CXEMailLink();
// Attributes
public:

// Operations
public:    
    //}}AFX_VIRTUAL	
// Implementation
protected: 
	virtual BOOL GotoURL(LPCTSTR url, int showcmd);
	virtual void ReportError();
// Protected attributes
protected:   
protected:
    //{{AFX_MSG(CXEMailLink)    
    //}}AFX_MSG    
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // HWX_EMAILLINK_H
