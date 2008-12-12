/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XViewWnd.h					
�ļ�����:		��viewת��Ϊwndһ��ʹ��
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/04/05
*********************************************************************/
#pragma once

#include "stdafx.h"

class DLLXEXPORT CXViewWnd : public CScrollView
{  
  DECLARE_DYNCREATE(CXViewWnd)
public: 
  static CXString GetWndClass();
private:
  static BOOL RegisterWndClass();
private:
  static CXString m_strClassName;
  static CXString m_strDefWndName;
protected:	  
  CSize m_szPaper;  
  BOOL m_bActive;
  
public: 
	CXViewWnd(); 
  virtual ~CXViewWnd();
  virtual BOOL Create( CWnd *pParent, const CRect &rect, const CSize & = CSize(0, 0), 
    DWORD dwStyple = 0, DWORD dwStypleEx = 0, LPCTSTR pszWndName = NULL); 
  virtual BOOL Create( HWND hParent, const CRect &rect, const CSize & = CSize(0, 0), 
    DWORD dwStyple = 0, DWORD dwStypleEx = 0,  LPCTSTR pszWndName = NULL);   
  virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect,
    CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
  virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,  LPCTSTR lpszWindowName, DWORD dwStyle,
    const RECT& rect, CWnd* pParentWnd, UINT nID = 0, LPVOID lpParam = NULL);
  virtual void SetPageSize(CSize); 
	CSize GetPaperSize(); 
protected:
	void DocToClient(CRect& rect);
	void DocToClient(CPoint& point);
  void ClientToDoc(CPoint& point);
  void ClientToDoc(CRect& rect);    
	virtual void OnDraw(CDC* pDC);  	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif	
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);	 	
	virtual void Draw(HDC);

  	
protected:
	virtual void OnInitialUpdate(); 
	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
  

public:
	//{{AFX_MSG(CXViewWnd)	
	afx_msg virtual BOOL OnEraseBkgnd(CDC* pDC);			
	afx_msg void OnFilePrint();	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
  virtual void PostNcDestroy();  
  virtual afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	
  virtual void OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame);
	virtual void OnActivateView(BOOL bActivate, CView* pActiveView, CView* pDeactiveView);	
};
/////////////////////////////////////////////////////////////////////////////
