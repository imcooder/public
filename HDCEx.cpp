/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XDC.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/19
*********************************************************************/

#include "stdafx.h"
#include "HDCEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif
#define COLORREF_NULL   (COLORREF)-1


//===========================================================================
// CXBufferDC class
//===========================================================================

CBufferDC::CBufferDC(HDC hDestDC, const RECT& rcPaint)
: m_hDestDC (hDestDC)
{
	m_rect = rcPaint;
	m_hMemDC = CreateCompatibleDC(hDestDC);
	if (!m_hMemDC)
		return;
	m_hBitmap = CreateCompatibleBitmap(m_hDestDC, _abs(m_rect.right - m_rect.left), _abs(m_rect.bottom - m_rect.top));	
	m_hOldBitmap = ::SelectObject (m_hMemDC, m_hBitmap);
}
CBufferDC::~CBufferDC()
{
	if (!m_hMemDC)
		return;

	if (m_hDestDC)
	{
		::BitBlt (m_hDestDC, m_rect.left, m_rect.top, _abs(m_rect.right - m_rect.left), _abs(m_rect.bottom - m_rect.top)
			, m_hMemDC, m_rect.left, m_rect.top, SRCCOPY);
	}
	::SelectObject (m_hMemDC, m_hOldBitmap);
	m_hOldBitmap = NULL;
	DeleteObject(m_hBitmap);
	m_hBitmap = NULL;
	DeleteDC(m_hMemDC);
	m_hMemDC = NULL;
}

HDC CBufferDC::GetHDC()
{
	return m_hMemDC;
}
//===========================================================================
// CXBufferDC class
//===========================================================================

CXBufferDCEx::CXBufferDCEx(HDC hDestDC, const RECT rcPaint) 
: m_hDestDC (hDestDC)
{
	m_rect = rcPaint;
	m_hMemDC = ::CreateCompatibleDC (m_hDestDC);
	m_bitmap = ::CreateCompatibleBitmap(m_hDestDC, _abs(m_rect.right - m_rect.left), _abs(m_rect.bottom - m_rect.top));

	m_hOldBitmap = ::SelectObject (m_hMemDC, m_bitmap);

	SetViewportOrgEx(m_hMemDC, -rcPaint.left, -rcPaint.top, NULL);
}

CXBufferDCEx::~CXBufferDCEx()
{
	SetViewportOrgEx(m_hMemDC, 0, 0, NULL);
	::BitBlt (m_hDestDC, m_rect.left, m_rect.top, _abs(m_rect.right - m_rect.left), _abs(m_rect.bottom - m_rect.top)
		, m_hMemDC, 0, 0, SRCCOPY);
	::SelectObject (m_hMemDC, m_hOldBitmap);
	::DeleteObject(m_bitmap);
	DeleteDC(m_hMemDC);
	m_hMemDC = NULL;
}

//===========================================================================
// CBitmapDC class
//===========================================================================

CBitmapDC::CBitmapDC(HDC hDC, HBITMAP hBitmap)
: m_hDC(hDC)
{
	m_hOldBitmap = SelectObject(m_hDC, hBitmap);
}

CBitmapDC::~CBitmapDC()
{
	::SelectObject(m_hDC, m_hOldBitmap);
}

void CBitmapDC::SetBitmap(HBITMAP hBitmap)
{
	::SelectObject(m_hDC, m_hOldBitmap);
	m_hOldBitmap = SelectObject(m_hDC, hBitmap);
}

//===========================================================================
// CXFontDC class
//===========================================================================

CFontDC::CFontDC(HDC hDC, HFONT hFont)
{
	assert(hDC);

	m_hDC = hDC;
	m_hOldFont = NULL;
	m_crOldTextColor = COLORREF_NULL;
	if (hFont)
	{
		SetFont(hFont);
	}
}

CFontDC::CFontDC(HDC hDC, HFONT hFont, COLORREF clrTextColor)
{
	ASSERT(hDC);
	ASSERT(clrTextColor != COLORREF_NULL);

	m_hDC = hDC;
	m_hOldFont = NULL;
	m_crOldTextColor = COLORREF_NULL;


	if (hFont)
	{
		SetFont(hFont);
	}

	SetColor(clrTextColor);
}

CFontDC::~CFontDC()
{
	ReleaseFont();
	ReleaseColor();
}

void CFontDC::SetFont(HFONT hFont)
{
	if (m_hDC && hFont)
	{
		if (m_hOldFont)
		{
			SelectObject(m_hDC, m_hOldFont);
			m_hOldFont = NULL;
		}
		m_hOldFont = (HFONT)SelectObject(m_hDC, hFont);
	}
}

void CFontDC::SetColor(COLORREF clrTextColor)
{
	ASSERT(clrTextColor != COLORREF_NULL);
	ASSERT(m_hDC);

	if (m_hDC && clrTextColor != COLORREF_NULL)
	{
		if (m_crOldTextColor != COLORREF_NULL)
		{
			SetTextColor(m_hDC, m_crOldTextColor);
			m_crOldTextColor = NULL;
		}
		m_crOldTextColor = SetTextColor(m_hDC, clrTextColor);	
	}
}

void CFontDC::SetFontColor(HFONT hFont, COLORREF clrTextColor)
{
	SetFont(hFont);
	SetColor(clrTextColor);
}

void CFontDC::ReleaseFont()
{
	ASSERT(m_hDC);
	if (m_hDC && m_hOldFont)
	{
		SelectObject(m_hDC, m_hOldFont);
		m_hOldFont = NULL;
	}
}

void CFontDC::ReleaseColor()
{
	ASSERT(m_hDC);
	if (m_hDC && m_crOldTextColor != COLORREF_NULL)
	{
		SetTextColor(m_hDC, m_crOldTextColor);
		m_crOldTextColor = COLORREF_NULL;
	}
}

//===========================================================================
// CXPenDC class
//===========================================================================

CPenDC::CPenDC(HDC hDC, HPEN hPen)
: m_hDC(hDC)
, m_hPen(NULL)
{
	assert(hDC);
	assert(hPen);
	m_hOldPen = (HPEN)::SelectObject(m_hDC, hPen);
}

CPenDC::CPenDC(HDC hDC, COLORREF crColor)
: m_hDC (hDC)
, m_hPen(NULL)
{
	VERIFY(m_hPen = CreatePen (PS_SOLID, 1, crColor));
	m_hOldPen = (HPEN)::SelectObject (m_hDC, m_hPen);
}

CPenDC::~CPenDC ()
{
	::SelectObject (m_hDC, m_hOldPen);
}

void CPenDC::Color(COLORREF crColor)
{
	if (m_hOldPen)
	{
		::SelectObject (m_hDC, m_hOldPen);
		m_hOldPen = NULL;
	}
	
	if (m_hPen)
	{
		DeleteObject(m_hPen);
		m_hPen = NULL;
	}	
	VERIFY(m_hPen = CreatePen (PS_SOLID, 1, crColor));
	m_hOldPen = (HPEN)::SelectObject (m_hDC, m_hPen);
}

//===========================================================================
// CXBrushDC class
//===========================================================================

CBrushDC::CBrushDC(HDC hDC, COLORREF crColor)
: m_hDC (hDC)
{
	VERIFY(m_hBrush = CreateSolidBrush (crColor));
	m_hOldBrush = (HBRUSH)::SelectObject (m_hDC, m_hBrush);
}

CBrushDC::~CBrushDC()
{
	if (m_hBrush)
	{
		DeleteObject(m_hBrush);
		m_hBrush = NULL;
	}
	::SelectObject(m_hDC, m_hOldBrush);
	m_hOldBrush = NULL;
}

void CBrushDC::Color(COLORREF crColor)
{
	if (m_hOldBrush)
	{
		::SelectObject(m_hDC, m_hOldBrush);
		m_hOldBrush = NULL;
	}
	if (m_hBrush)
	{
		DeleteObject(m_hBrush);
		m_hBrush = NULL;
	}
	
	VERIFY(m_hBrush = CreateSolidBrush(crColor));
	m_hOldBrush = (HBRUSH)::SelectObject (m_hDC, m_hBrush);
}

//===========================================================================
// CXCompatibleDC class
//===========================================================================

CCompatibleDC::CCompatibleDC(HDC hDC, HBITMAP hBitmap)
{
	m_hMemDC = CreateCompatibleDC(hDC);
	m_hOldBitmap = (HBITMAP)::SelectObject(m_hMemDC, hBitmap);
}

CCompatibleDC::~CCompatibleDC()
{
	if (m_hOldBitmap)
	{
		::SelectObject(m_hMemDC, m_hOldBitmap);
	}	
	DeleteDC(m_hMemDC);
}

HDC CCompatibleDC::GetHDC()
{
	return m_hMemDC;
}