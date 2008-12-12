/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XFlatEdit.h					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/19
*********************************************************************/

#ifndef HWX_XFLATEDIT_H
#define HWX_XFLATEDIT_H

#if _MSC_VER > 1000
#pragma once
#endif 
#define WM_CREATETOOLTIP			WM_USER + 100
#define WM_UPDATETIP					WM_USER + 101
#define WM_ENABLETIP					WM_USER + 102
class CXFlatEdit : public CEdit
{
	DECLARE_DYNAMIC(CXFlatEdit)
public:
	CXFlatEdit();	
	virtual ~CXFlatEdit();
public:
	void EnableToolTip(BOOL = TRUE);
	void SetToolTip(LPCTSTR);
	CString GetToolTip() const;
	void DisableFlatLook(BOOL bDisable);	
	BOOL IsFlat();
	virtual BOOL PointInRect();protected:
	static void DrawBorders(CDC* , CXFlatEdit*, const CRect&, BOOL blMouseOn = FALSE);
	DECLARE_MESSAGE_MAP()
	//{{AFX_MSG(CXFlatEdit)	
	afx_msg	void OnNcPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);	
protected:
	afx_msg LRESULT OnCreateTip(WPARAM, LPARAM l);
	afx_msg LRESULT OnUpdateTip(WPARAM, LPARAM);
	afx_msg LRESULT OnEnableToolTip(WPARAM w, LPARAM l);
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DrawBorders(CDC* , const CRect&);
	virtual void PreSubclassWindow();
protected:
	BOOL m_bPainted;  // Used during paint operations.
	BOOL m_bHasFocus; // TRUE if the control has focus.
	BOOL m_bFlatLook; // TRUE if the control is flat.
	DWORD m_nStyle;   // Stores the standard window styles for the control.
	DWORD m_nStyleEx; // Stores the extended window styles for the control.
	CString m_strToolTip;
	CToolTipCtrl m_ToolTip;	
};

//////////////////////////////////////////////////////////////////////


#endif // HWX_XFLATEDIT_H
