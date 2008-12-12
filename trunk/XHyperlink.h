/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XHyperlink.h					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/18
*********************************************************************/
#ifndef HWX_HYPERLINK_H
#define HWX_HYPERLINK_H
#include "XTipStatic.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CXHyperLink window

class DLLXEXPORT CXHyperLink : public CXTipStatic
{
	// Construction/destruction
public:
	CXHyperLink();
	virtual ~CXHyperLink();

	// Attributes
public:
	void SetURL(CString strURL);
	CString GetURL() const;
	void SetColours(COLORREF crLinkColour, COLORREF crVisitedColour, 
		COLORREF crHoverColour = -1);
	COLORREF GetLinkColour() const;
	COLORREF GetVisitedColour() const;
	COLORREF GetHoverColour() const;

	void SetVisited(BOOL bVisited = TRUE);
	BOOL GetVisited() const;

	void SetLinkCursor(HCURSOR hCursor);
	HCURSOR GetLinkCursor() const;

	void SetUnderline(BOOL bUnderline = TRUE);
	BOOL GetUnderline() const;

	void SetAutoSize(BOOL bAutoSize = TRUE);
	BOOL GetAutoSize() const;
	void SetTransparent(BOOL  = TRUE);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXHyperLink)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	virtual BOOL GotoURL(LPCTSTR url, int showcmd);
	virtual void ReportError();
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	void PositionWindow();
	void SetDefaultCursor();

	// Protected attributes
protected:
	COLORREF m_crLinkColour, m_crVisitedColour;     // Hyperlink colours
	COLORREF m_crHoverColour;                       // Hover colour
	BOOL     m_bOverControl;                        // cursor over control?
	BOOL     m_bVisited;                            // Has it been visited?
	BOOL     m_bUnderline;                          // underline hyperlink?
	BOOL     m_bAdjustToFit;                        // Adjust window size to fit text?
	CString  m_strURL;                              // hyperlink URL
	CFont    m_Font;                                // Underline font if necessary
	HCURSOR  m_hLinkCursor;                         // Cursor for hyperlink
	//CToolTipCtrl m_ToolTip;                         // The tooltip
	BOOL		 m_blTransparent;												// Transparent Text
	LONG		 m_nErrorCode;
	// Generated message map functions
protected:
	//{{AFX_MSG(CXHyperLink)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnClicked();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // HWX_HYPERLINK_H
