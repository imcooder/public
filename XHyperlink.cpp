/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XHyperlink.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/18
*********************************************************************/
#include "stdafx.h"
#include "XHyperLink.h"
#include <XStrHelper.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TOOLTIP_ID 1

/////////////////////////////////////////////////////////////////////////////
// CXHyperLink

CXHyperLink::CXHyperLink()
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
	m_blTransparent			= FALSE;
}

CXHyperLink::~CXHyperLink()
{
	m_Font.DeleteObject();
	m_blTransparent			= FALSE;
}

BEGIN_MESSAGE_MAP(CXHyperLink, CXTipStatic)
	//{{AFX_MSG_MAP(CXHyperLink)
	ON_CONTROL_REFLECT(STN_CLICKED, OnClicked)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXHyperLink message handlers

void CXHyperLink::OnClicked()
{
	if (!(m_bVisited = GotoURL(m_strURL, SW_SHOW)))
	{
		MessageBeep(MB_ICONEXCLAMATION);     // Unable to follow link
		ReportError();
	}		
	else 
	{
		SetVisited();                        // Repaint to show visited colour
	}
}

HBRUSH CXHyperLink::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	ASSERT(nCtlColor == CTLCOLOR_STATIC);
	HBRUSH hBrush = NULL;
	if (m_bOverControl)
	{
		pDC->SetTextColor(m_crHoverColour);
	}
	else if (m_bVisited)
	{
		pDC->SetTextColor(m_crVisitedColour);
	}
	else
	{
		pDC->SetTextColor(m_crLinkColour);
	}
	// transparent text.
	if (m_blTransparent)
	{
		pDC->SetBkMode(TRANSPARENT);
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	else
	{
		hBrush = CreateSolidBrush(nCtlColor);
	}
	//
	return hBrush;
}

void CXHyperLink::OnMouseMove(UINT nFlags, CPoint point) 
{
	__super::OnMouseMove(nFlags, point);

	if (m_bOverControl)        // Cursor is currently over control
	{
		CRect rect;
		GetClientRect(rect);

		if (!rect.PtInRect(point))
		{
			m_bOverControl = FALSE;
			ReleaseCapture();
			RedrawWindow();
			return;
		}
	}
	else// Cursor has just moved over control
	{
		m_bOverControl = TRUE;
		RedrawWindow();
		SetCapture();
	}
}

BOOL CXHyperLink::OnSetCursor(CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/) 
{
	if (m_hLinkCursor)
	{
		::SetCursor(m_hLinkCursor);
		return TRUE;
	}
	return FALSE;
}

void CXHyperLink::PreSubclassWindow() 
{
	// We want to get mouse clicks via STN_CLICKED
	DWORD dwStyle = GetStyle();
	::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	// Set the URL as the window text
	if (m_strURL.IsEmpty())
		GetWindowText(m_strURL);
	// Check that the window text isn't empty. If it is, set it as the URL.
	CString strWndText;
	GetWindowText(strWndText);
	if (strWndText.IsEmpty()) 
	{
		ASSERT(!m_strURL.IsEmpty());    // Window and URL both NULL. DUH!
		SetWindowText(m_strURL);
	}

	// Create the font
	LOGFONT lf;
	GetFont()->GetLogFont(&lf);
	lf.lfUnderline = m_bUnderline;
	m_Font.CreateFontIndirect(&lf);
	SetFont(&m_Font);

	PositionWindow();        // Adjust size of window to fit URL if necessary
	SetDefaultCursor();      // Try and load up a "hand" cursor

	// Create the tooltip
	//CRect rect; 
	//GetClientRect(rect);
	//m_ToolTip.Create(this);
	//m_ToolTip.AddTool(this, m_strURL, rect, TOOLTIP_ID);

	__super::PreSubclassWindow();
}

/////////////////////////////////////////////////////////////////////////////
// CXHyperLink operations
void CXHyperLink::SetURL(CString strURL)
{
	m_strURL = strURL;

	if (::IsWindow(GetSafeHwnd())) 
	{
		PositionWindow();		
	}
}

CString CXHyperLink::GetURL() const
{ 
	return m_strURL;   
}

void CXHyperLink::SetColours(COLORREF crLinkColour, COLORREF crVisitedColour,
														 COLORREF crHoverColour /* = -1 */) 
{ 
	m_crLinkColour    = crLinkColour; 
	m_crVisitedColour = crVisitedColour;

	if (crHoverColour == -1)
	{
		m_crHoverColour = ::GetSysColor(COLOR_HIGHLIGHT);
	}
	else
	{
		m_crHoverColour = crHoverColour;
	}

	if (::IsWindow(m_hWnd))
		Invalidate(); 
}

COLORREF CXHyperLink::GetLinkColour() const
{ 
	return m_crLinkColour; 
}

COLORREF CXHyperLink::GetVisitedColour() const
{
	return m_crVisitedColour; 
}

COLORREF CXHyperLink::GetHoverColour() const
{
	return m_crHoverColour;
}

void CXHyperLink::SetVisited(BOOL bVisited /* = TRUE */) 
{ 
	m_bVisited = bVisited; 

	if (::IsWindow(GetSafeHwnd()))
		Invalidate(); 
}

BOOL CXHyperLink::GetVisited() const
{ 
	return m_bVisited; 
}

void CXHyperLink::SetLinkCursor(HCURSOR hCursor)
{ 
	m_hLinkCursor = hCursor;
	if (m_hLinkCursor == NULL)
		SetDefaultCursor();
}

HCURSOR CXHyperLink::GetLinkCursor() const
{
	return m_hLinkCursor;
}

void CXHyperLink::SetUnderline(BOOL bUnderline /* = TRUE */)
{
	m_bUnderline = bUnderline;

	if (::IsWindow(GetSafeHwnd()))
	{
		LOGFONT lf;
		GetFont()->GetLogFont(&lf);
		lf.lfUnderline = m_bUnderline;

		m_Font.DeleteObject();
		m_Font.CreateFontIndirect(&lf);
		SetFont(&m_Font);

		Invalidate(); 
	}
}

BOOL CXHyperLink::GetUnderline() const
{ 
	return m_bUnderline; 
}

void CXHyperLink::SetAutoSize(BOOL bAutoSize /* = TRUE */)
{
	m_bAdjustToFit = bAutoSize;

	if (::IsWindow(GetSafeHwnd()))
		PositionWindow();
}

BOOL CXHyperLink::GetAutoSize() const
{ 
	return m_bAdjustToFit; 
}


// Move and resize the window so that the window is the same size
// as the hyperlink text. This stops the hyperlink cursor being active
// when it is not directly over the text. If the text is left justified
// then the window is merely shrunk, but if it is centred or right
// justified then the window will have to be moved as well.
//
// Suggested by P錶 K. T鴑der 

void CXHyperLink::PositionWindow()
{
	if (!::IsWindow(GetSafeHwnd()) || !m_bAdjustToFit) 
		return;

	// Get the current window position
	CRect rect;
	GetWindowRect(rect);

	CWnd* pParent = GetParent();
	if (pParent)
	{
		pParent->ScreenToClient(rect);
	}

	// Get the size of the window text
	CString strWndText;
	GetWindowText(strWndText);

	CDC* pDC = GetDC();
	CFont* pOldFont = pDC->SelectObject(&m_Font);
	CSize Extent = pDC->GetTextExtent(strWndText);
	pDC->SelectObject(pOldFont);
	ReleaseDC(pDC);

	// Get the text justification via the window style
	DWORD dwStyle = GetStyle();

	// Recalc the window size and position based on the text justification
	if (dwStyle & SS_CENTERIMAGE)
	{
		rect.DeflateRect(0, (rect.Height() - Extent.cy)/2);
	}
	else
	{
		rect.bottom = rect.top + Extent.cy;
	}

	if (dwStyle & SS_CENTER)   
	{
		rect.DeflateRect((rect.Width() - Extent.cx)/2, 0);
	}
	else if (dwStyle & SS_RIGHT) 
	{
		rect.left  = rect.right - Extent.cx;
	}
	else // SS_LEFT = 0, so we can't test for it explicitly 
	{
		rect.right = rect.left + Extent.cx;
	}
	// Move the window
	SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
}

/////////////////////////////////////////////////////////////////////////////
// CXHyperLink implementation
void CXHyperLink::SetDefaultCursor()
{
	if (m_hLinkCursor == NULL)                // No cursor handle - load our own
	{
		// Get the windows directory
		CString strWndDir;
		GetWindowsDirectory(strWndDir.GetBuffer(MAX_PATH), MAX_PATH);
		strWndDir.ReleaseBuffer();

		strWndDir += _T("\\winhlp32.exe");
		// This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
		HMODULE hModule = LoadLibrary(strWndDir);
		if (hModule) 
		{
			HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
			if (hHandCursor)
			{
				m_hLinkCursor = CopyCursor(hHandCursor);
			}
		}
		FreeLibrary(hModule);
	}
}

LONG CXHyperLink::GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
	HKEY hkey;
	LONG retval = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hkey);

	if (retval == ERROR_SUCCESS) 
	{
		LONG datasize = MAX_PATH;
		TCHAR data[MAX_PATH];
		RegQueryValue(hkey, NULL, data, &datasize);
		_tcscpy(retdata,data);
		RegCloseKey(hkey);
	}
	return retval;
}

void CXHyperLink::ReportError()
{
	CString str;
	switch (m_nErrorCode) 
	{
	case 0:                       str = _T("The operating system is out\nof memory or resources."); break;
	case SE_ERR_PNF:              str = _T("The specified path was not found."); break;
	case SE_ERR_FNF:              str = _T("The specified file was not found."); break;
	case ERROR_BAD_FORMAT:        str = _T("The .EXE file is invalid\n(non-Win32 .EXE or error in .EXE image)."); break;
	case SE_ERR_ACCESSDENIED:     str = _T("The operating system denied\naccess to the specified file."); break;
	case SE_ERR_ASSOCINCOMPLETE:  str = _T("The filename association is\nincomplete or invalid."); break;
	case SE_ERR_DDEBUSY:          str = _T("The DDE transaction could not\nbe completed because other DDE transactions\nwere being processed."); break;
	case SE_ERR_DDEFAIL:          str = _T("The DDE transaction failed."); break;
	case SE_ERR_DDETIMEOUT:       str = _T("The DDE transaction could not\nbe completed because the request timed out."); break;
	case SE_ERR_DLLNOTFOUND:      str = _T("The specified dynamic-link library was not found."); break;
	case SE_ERR_NOASSOC:          str = _T("There is no application associated\nwith the given filename extension."); break;
	case SE_ERR_OOM:              str = _T("There was not enough memory to complete the operation."); break;
	case SE_ERR_SHARE:            str = _T("A sharing violation occurred. ");
	default:                      str.Format(_T("Unknown Error (%d) occurred."), m_nErrorCode); break;
	}
	str = _T("Unable to open hyperlink:\n\n") + str;
	AfxMessageBox(str, MB_ICONEXCLAMATION | MB_OK);
}

BOOL CXHyperLink::GotoURL(LPCTSTR url, int showcmd)
{
	TCHAR key[MAX_PATH + MAX_PATH];
	// First try ShellExecute()
	m_nErrorCode = (LONG)ShellExecute(NULL, _T("open"), url, NULL, NULL, showcmd);

	// If it failed, get the .htm regkey and lookup the program
	if ((UINT)m_nErrorCode <= HINSTANCE_ERROR) 
	{
		if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) 
		{
			lstrcat(key, _T("\\shell\\open\\command"));
			if (GetRegKey(HKEY_CLASSES_ROOT, key, key) == ERROR_SUCCESS) 
			{
				TCHAR *pos;
				pos = _tcsstr(key, _T("\"%1\""));
				if (pos == NULL) 
				{                     // No quotes found
					pos = _tcsstr(key, _T("%1"));       // Check for %1, without quotes 
					if (pos == NULL)                   // No parameter at all...
						pos = key+_tcslen(key)-1;
					else
						*pos = _T('\0');                   // Remove the parameter
				}
				else
					*pos = _T('\0');                       // Remove the parameter

				lstrcat(pos, _T(" "));
				lstrcat(pos, url);  
				LPSTR lpszBuffer = TCharToChar(key);
				m_nErrorCode = WinExec(lpszBuffer, showcmd);
				XMemFree((void**)&lpszBuffer);
			}
		}
	}
	return m_nErrorCode > HINSTANCE_ERROR;
}
void CXHyperLink::SetTransparent( BOOL bTransparent/*= TRUE*/ )
{
	m_blTransparent = bTransparent;
}