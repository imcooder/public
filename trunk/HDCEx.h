 /********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	XDC.h					
文件内容:	
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/19
*********************************************************************/

#ifndef HWX_HDCEX_H
#define HWX_HDCEX_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBufferDC
{
public:
	CBufferDC(HDC hDestDC, const RECT& rcPaint);
	
	virtual ~CBufferDC();	
	HDC GetHDC();
protected:
	HDC     m_hDestDC;    // Handle to the destination device context.
	HDC m_hMemDC;
	HBITMAP m_hBitmap;     // Bitmap in memory device context
	RECT   m_rect;       // Size of the area to paint.
	HGDIOBJ m_hOldBitmap; // Handle to the previously selected bitmap.
};

class CXBufferDCEx
{
public:
	CXBufferDCEx(HDC hDestDC, const RECT rcPaint);
	virtual ~CXBufferDCEx();

protected:
	HDC m_hMemDC;
	HDC     m_hDestDC;    // Handle to the destination device context.
	HBITMAP m_bitmap;     // Bitmap in memory device context
	RECT   m_rect;       // Size of the area to paint.
	HGDIOBJ m_hOldBitmap; // Handle to the previously selected bitmap.
};

class CBitmapDC
{
public:	
	CBitmapDC(HDC, HBITMAP hBitmap);  
	virtual ~CBitmapDC();
	void SetBitmap(HBITMAP);
protected:
	HDC     m_hDC;        // Device context handle.
	HGDIOBJ m_hOldBitmap; // Handle to the previously selected bitmap.
};

class CFontDC
{
public:
	CFontDC(HDC, HFONT = NULL);
	CFontDC(HDC, HFONT, COLORREF clrTextColor); 
	virtual ~CFontDC();
	void SetFont(HFONT);
	void SetColor(COLORREF clrTextColor);	
	void SetFontColor(HFONT, COLORREF clrTextColor);
	void ReleaseFont();
	void ReleaseColor();

protected:
	HDC m_hDC;	
	HFONT m_hOldFont;
	COLORREF m_crOldTextColor; 
};
class CPenDC
{
public:
	CPenDC(HDC, HPEN);
	CPenDC(HDC hDC, COLORREF crColor); 
	virtual ~CPenDC();		
	void Color(COLORREF crColor); // <combine CXPenDC::Color>
protected:
	HPEN m_hPen; 
	HDC  m_hDC; 
	HPEN m_hOldPen; 
};

class CBrushDC
{
public:	
	CBrushDC(HDC hDC, COLORREF crColor);	
	virtual ~CBrushDC();	
	void Color(COLORREF crColor);
protected:
	HBRUSH m_hBrush; 
	HDC    m_hDC;
	HBRUSH m_hOldBrush; 
};

class CCompatibleDC
{
public:		
	CCompatibleDC(HDC, HBITMAP hBitmap); 	
	virtual ~CCompatibleDC();
	HDC GetHDC();
protected:
	HBITMAP m_hOldBitmap; 
	HDC m_hMemDC;
};

#endif //HWX_HDCEX_H