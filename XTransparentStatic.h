/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XTransparentStatic.h					
�ļ�����:			͸��CStatic
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/05
*********************************************************************/
#ifndef X_TRANSPARENTSTATIC
#define X_TRANSPARENTSTATIC

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
class DLLXEXPORT CXTransparentStatic :  public CStatic
{
	DECLARE_DYNCREATE(CXTransparentStatic)
// Construction
public:
	CXTransparentStatic();
	virtual ~CXTransparentStatic();	
protected:

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CXTransparentStatic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	virtual BOOL Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff );
	
// Implementation
protected:
	BOOL m_bAdjustToFit;
	// Generated message map functions
	//{{AFX_MSG(CXTransparentStatic)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColo);
	void PositionWindow();

};

#endif X_TRANSPARENTSTATIC
