/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XFlatCombo.cpp					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/19
*********************************************************************/
#include "stdafx.h"
#include "XFlatCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXFlatComboBox

CXFlatComboBox::CXFlatComboBox()
{
	m_bFlatLook = TRUE;
}

CXFlatComboBox::~CXFlatComboBox()
{

}

IMPLEMENT_DYNAMIC(CXFlatComboBox, CComboBox)

BEGIN_MESSAGE_MAP(CXFlatComboBox, CComboBox)
	//{{AFX_MSG_MAP(CXFlatComboBox)		
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXFlatComboBox message handlers

// Stoopid win95 accelerator key problem workaround - Matt Weagle.
BOOL CXFlatComboBox::PreTranslateMessage(MSG* pMsg) 
{
	// Make sure that the keystrokes continue to the appropriate handlers		
	return CComboBox::PreTranslateMessage(pMsg);
}

void CXFlatComboBox::NotifyOwner(UINT nCode)
{
	CWnd* pWndOwner = GetOwner();
	if (::IsWindow(pWndOwner->GetSafeHwnd()))
	{
		pWndOwner->SendMessage(WM_COMMAND,
			MAKEWPARAM(GetDlgCtrlID(), nCode), (LPARAM)m_hWnd);
	}
}


void CXFlatComboBox::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	__super::PreSubclassWindow();	
	ModifyStyleEx (WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,	0, SWP_FRAMECHANGED);
}
void CXFlatComboBox::OnPaint() 
{
	if (m_bFlatLook)
	{
		ModifyStyleEx (WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
			0, SWP_FRAMECHANGED);
	}
	else
	{
		ModifyStyleEx (0, WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
			SWP_FRAMECHANGED);
	}
	Default();
}
