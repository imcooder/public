/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XBitmapEx.h					
�ļ�����:			Bitmap�򵥴���
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/04
*********************************************************************/

#ifndef X_BITMAPEX
#define X_BITMAPEX


#ifdef __cplusplus
extern "C"{
#endif

	DLLXEXPORT HBITMAP WINAPI CreateGrayscaleBitmap(HBITMAP hBitmap, COLORREF crTrans);
	DLLXEXPORT HBITMAP WINAPI CreateDarkerBitmap(HBITMAP hBitmap, COLORREF crTrans);
	DLLXEXPORT HBITMAP WINAPI CreateBitmapMask(HBITMAP hSourceBitmap, COLORREF crTransColor);


#ifdef __cplusplus
}
#endif


#endif //X_BITMAPEX