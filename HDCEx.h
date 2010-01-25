 /********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XDC.h					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/19
*********************************************************************/

#ifndef HWX_HDCEX_H
#define HWX_HDCEX_H

class CXUEMemDC
{
public:
	CXUEMemDC(HDC hDestDC, const LPRECT prcPaint);
	virtual ~CXUEMemDC();
	HDC	GetSafeHdc();
	BOOL Clear(COLORREF);
	BOOL SwapBuffer();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	void DrawDragRect(const LPRECT lpRect, SIZE size, const LPRECT lpRectLast, SIZE sizeLast, HBRUSH pBrush, HBRUSH pBrushLast);
	void FillSolidRect(LPCRECT lpRect, COLORREF clr);
	void FillSolidRect(int x, int y, int cx, int cy, COLORREF clr);
	void Draw3dRect(LPCRECT lpRect,COLORREF clrTopLeft, COLORREF clrBottomRight);
	void Draw3dRect(int x, int y, int cx, int cy, COLORREF clrTopLeft, COLORREF clrBottomRight);
	//////////////////////////////////////////////////////////////////////////
	HBRUSH GetHalftoneBrush();
protected:
	HDC			m_hDC;
	HDC     m_hDestDC;   
	HBITMAP m_hBitmap;    
	RECT		m_rtPaint;      
	HGDIOBJ m_hOldBitmap;
};

#endif //HWX_HDCEX_H