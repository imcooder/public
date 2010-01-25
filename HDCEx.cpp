/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XDC.cpp					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/19
*********************************************************************/

#include "stdafx.h"
#include "HDCEx.h"




CXUEMemDC::CXUEMemDC(HDC hDestDC, const LPRECT prcPaint) 
: m_hDestDC (hDestDC)
, m_hBitmap(NULL)
, m_hOldBitmap(NULL)
{
	if (hDestDC || prcPaint)
	{
		m_rtPaint = *prcPaint;
		m_hDC = ::CreateCompatibleDC (m_hDestDC);
		if (m_hDC)
		{
			m_hBitmap = ::CreateCompatibleBitmap(m_hDestDC, _abs(m_rtPaint.right - m_rtPaint.left), _abs(m_rtPaint.bottom - m_rtPaint.top));
			if (m_hBitmap)
			{
				RECT rtClipbox = {0, 0, 0, 0};
				::GetClipBox(hDestDC, &rtClipbox);
				::IntersectClipRect(m_hDC, rtClipbox.left, rtClipbox.top, rtClipbox.right, rtClipbox.bottom);
				m_hOldBitmap = ::SelectObject (m_hDC, m_hBitmap);
				::SetViewportOrgEx(m_hDC, -m_rtPaint.left, -m_rtPaint.top, NULL);
			}			
		}		
	}
}

CXUEMemDC::~CXUEMemDC()
{
	if (!m_hDC)
	{
		return;
	}
	::SetViewportOrgEx(m_hDC, 0, 0, NULL);		

	if (m_hOldBitmap)
	{
		::SelectObject (m_hDC, m_hOldBitmap);
		m_hOldBitmap = NULL;
	}

	if (m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}

	::DeleteDC(m_hDC);
	m_hDC = NULL;	

}

HDC CXUEMemDC::GetSafeHdc()
{
	return m_hDC;
}

BOOL CXUEMemDC::SwapBuffer( )
{
	if (!m_hDestDC)
	{
		return FALSE;
	}
	::BitBlt (m_hDestDC, m_rtPaint.left, m_rtPaint.top, _abs(m_rtPaint.right - m_rtPaint.left), _abs(m_rtPaint.bottom - m_rtPaint.top), m_hDC, m_rtPaint.left, m_rtPaint.top, SRCCOPY);
	return TRUE;
}

BOOL CXUEMemDC::Clear( COLORREF crColor)
{
	if (!m_hDC)
	{
		return FALSE;
	}
	HBRUSH hBrush = ::CreateSolidBrush(crColor);	
	FillRect(m_hDC, &m_rtPaint, hBrush);
	DeleteObject(hBrush);
	hBrush = NULL;
	return TRUE;
}


HBRUSH CXUEMemDC::GetHalftoneBrush()
{
	HBRUSH halftoneBrush = NULL;
	WORD grayPattern[8];
	for(int i = 0; i < 8; i++)
	{
		grayPattern[i] = (WORD)(0x5555 << (i & 1));
	}
	HBITMAP grayBitmap = ::CreateBitmap(8, 8, 1, 1, &grayPattern);
	if(grayBitmap != NULL)
	{
		halftoneBrush = ::CreatePatternBrush(grayBitmap);
		DeleteObject(grayBitmap);
	}
	return halftoneBrush;
}

void CXUEMemDC::DrawDragRect(const LPRECT lpRect, SIZE size, const LPRECT lpRectLast, SIZE sizeLast, HBRUSH pBrush, HBRUSH pBrushLast)
{
	if (!GetSafeHdc())
	{
		return;
	}	
	// first, determine the update region and select it
	HRGN rgnNew = NULL;
	HRGN rgnOutside = NULL, rgnInside = NULL;
	rgnOutside = ::CreateRectRgnIndirect(lpRect);
	RECT rect = *lpRect;
	InflateRect(&rect, -size.cx, -size.cy);
	IntersectRect(&rect, &rect, lpRect);
	rgnInside = ::CreateRectRgnIndirect(&rect);
	rgnNew = ::CreateRectRgn(0, 0, 0, 0);
	::CombineRgn(rgnNew, rgnOutside, rgnInside, RGN_XOR);

	HBRUSH hBrushOld = NULL;
	if (pBrush == NULL)
	{
		pBrush = GetHalftoneBrush();
	}	

	if (pBrushLast == NULL)
	{
		pBrushLast = pBrush;
	}

	HRGN rgnLast = NULL, rgnUpdate = NULL;
	if (lpRectLast != NULL)
	{
		// find difference between new region and old region
		rgnLast = ::CreateRectRgn(0, 0, 0, 0);
		::SetRectRgn(rgnOutside, lpRectLast->left, lpRectLast->top, lpRectLast->right, lpRectLast->bottom);
		rect = *lpRectLast;
		InflateRect(&rect, -sizeLast.cx, -sizeLast.cy);
		IntersectRect(&rect, &rect, lpRectLast);
		::SetRectRgn(rgnInside, rect.left, rect.top, rect.right, rect.bottom);
		::CombineRgn(rgnLast, rgnOutside, rgnInside, RGN_XOR);

		// only diff them if brushes are the same
		if (pBrush == pBrushLast)
		{
			rgnUpdate = ::CreateRectRgn( 0, 0, 0, 0);
			::CombineRgn(rgnUpdate, rgnLast, rgnNew, RGN_XOR);
		}
	}
	if (pBrush != pBrushLast && lpRectLast != NULL)
	{
		// brushes are different -- erase old region first
		::SelectClipRgn(GetSafeHdc(), rgnLast);
		::GetClipBox(GetSafeHdc(), &rect);
		hBrushOld = (HBRUSH)SelectObject(GetSafeHdc(), pBrushLast);
		::PatBlt(GetSafeHdc(), rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, PATINVERT);
		::SelectObject(GetSafeHdc(), hBrushOld);
		hBrushOld = NULL;
	}

	// draw into the update/new region
	::SelectClipRgn(GetSafeHdc(), rgnUpdate != NULL ? rgnUpdate : rgnNew);
	::GetClipBox(GetSafeHdc(), &rect);
	hBrushOld = (HBRUSH)SelectObject(GetSafeHdc(), pBrush);
	::PatBlt(GetSafeHdc(), rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, PATINVERT);


	if (hBrushOld != NULL)
	{
		::SelectObject(GetSafeHdc(), hBrushOld);
		hBrushOld = NULL;
	}
	::SelectClipRgn(GetSafeHdc(), NULL);
}

void CXUEMemDC::FillSolidRect(LPCRECT lpRect, COLORREF clr)
{	
	if (!GetSafeHdc())
	{
		return;
	}	
	if (lpRect)
	{	
		::SetBkColor(GetSafeHdc(), clr);
		::ExtTextOut(GetSafeHdc(), 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
	}	
}

void CXUEMemDC::FillSolidRect(int x, int y, int cx, int cy, COLORREF clr)
{
	if (!GetSafeHdc())
	{
		return;
	}	
	::SetBkColor(GetSafeHdc(), clr);
	RECT rect = {x, y, x + cx, y + cy};
	::ExtTextOut(GetSafeHdc(), 0, 0, ETO_OPAQUE, &rect, NULL, 0, NULL);
}

void CXUEMemDC::Draw3dRect(LPCRECT lpRect,COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	if (lpRect)
	{
		Draw3dRect(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, clrTopLeft, clrBottomRight);
	}	
}

void CXUEMemDC::Draw3dRect(int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight)
{
	FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
	FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
	FillSolidRect(x + cx, y, -1, cy, clrBottomRight);
	FillSolidRect(x, y + cy, cx, -1, clrBottomRight);
}
