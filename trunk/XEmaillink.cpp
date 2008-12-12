/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XEmaillink.cpp					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/22
*********************************************************************/
#include "stdafx.h"
#include "XEMailLink.h"
#include <mapi.h>
typedef ULONG (PASCAL *SENDMAIL)(ULONG, ULONG, MapiMessage*, FLAGS, ULONG);
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOOLTIP_ID 1

/////////////////////////////////////////////////////////////////////////////
// CXHyperLink

CXEMailLink::CXEMailLink()
{
	m_hLinkCursor       = NULL;                 // No cursor as yet
	m_crLinkColour      = RGB(  0,   0, 238);   // Blue
	m_crVisitedColour   = RGB( 85,  26, 139);   // Purple
	m_crHoverColour     = ::GetSysColor(COLOR_HIGHLIGHT);
	m_bOverControl      = FALSE;                // Cursor not yet over control
	m_bVisited          = FALSE;                // Hasn't been visited yet.
	m_bUnderline        = FALSE;                // Underline the link?
	m_bAdjustToFit      = TRUE;                 // Resize the window to fit the text?
	m_strURL.Empty();
}

CXEMailLink::~CXEMailLink()
{
	m_Font.DeleteObject();
}

BEGIN_MESSAGE_MAP(CXEMailLink, CXHyperLink)
	//{{AFX_MSG_MAP(CXEMailLink)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXEMailLink tMessage handlers

BOOL CXEMailLink::GotoURL(LPCTSTR url, int showcmd)
{	
	BOOL blSendOK = FALSE;	
	//������mapi����		
	SENDMAIL lpfnSendMail;
	HMODULE hMod = LoadLibrary(TEXT("MAPI32.DLL"));
	if (hMod)
	{					
		(FARPROC&)lpfnSendMail = GetProcAddress(hMod, "MAPISendMail");
		if (lpfnSendMail)
		{		
			//�ռ��˽ṹ��Ϣ
			MapiRecipDesc tRecip;
			MapiMessage tMessage;
			XMemZero(&tRecip, sizeof(MapiRecipDesc));
			XMemZero(&tMessage, sizeof(tMessage));
			CXStringA strEMailA = CXStringA::From(m_strURL);
			CXStringA strSubjectA("About HWNotes");
			CXStringA strContentA = CXStringA::From(url);	
			strContentA += ":\n";			
			tRecip.lpszAddress	= (LPSTR)(LPCSTR)strEMailA;
			tRecip.ulRecipClass = MAPI_TO;
			//�ʼ��ṹ��Ϣ				
			tMessage.nFileCount	= 0;						//�ļ�����
			tMessage.lpFiles		= NULL;					//�ļ���Ϣ
			tMessage.nRecipCount = 1;						//�ռ��˸���
			tMessage.lpRecips 	= &tRecip;			//�ռ���
			tMessage.lpszSubject	= (LPSTR)(LPCSTR)strSubjectA;	//����
			tMessage.lpszNoteText= (LPSTR)(LPCSTR)strContentA;	//��������		

			LONG nError = lpfnSendMail(0, 0,&tMessage, MAPI_LOGON_UI | MAPI_DIALOG, 0);
			if (nError == SUCCESS_SUCCESS || nError == MAPI_USER_ABORT 
				|| nError == MAPI_E_LOGIN_FAILURE)
			{
				blSendOK = TRUE;
			}			
			SAFE_FREE_LIBRARY(hMod);	
		}
	}				
	if (!blSendOK)
	{
		//Mapi����ʧ�ܺ� ������ShellExecute ����
		blSendOK = (LONG)ShellExecute(NULL,TEXT("open"), TEXT("mailto:") + m_strURL, NULL,
			NULL, SW_SHOWNORMAL) > HINSTANCE_ERROR;	
	}
	return blSendOK;
}
void CXEMailLink::ReportError()
{
	return;
}