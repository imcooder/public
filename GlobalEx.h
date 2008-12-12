/********************************************************************
Copyright (c) 2002-2003 汉王科技有限公司. 版权所有.
文件名称: 	GlobalEx.h					
文件内容:	    一些全局函数
版本历史:	1.0
作者:		xuejuntao xuejuntao@hanwang.com.cn 2008/03/22
*********************************************************************/
#pragma once
#include "Ext_Type.h"

enum HWOSType
{
  OS__Unknown = 0, 
  OS__NT = 1,
  OS__WindowsNT4SP3OrLater = 2,
  OS__XP = 3, 
  OS__Vista = 4,
  OS__64 = 5
};


#ifdef __cplusplus
extern "C"{
#endif

  DLLXEXPORT HWOSType WINAPI XGetOSType();
  DLLXEXPORT float WINAPI XPixelsToTwips(const LONG& nDPI, const float& fPixels);
  DLLXEXPORT float WINAPI XTwipsToPixel(const LONG& nDPI, const float& nTwips);
  DLLXEXPORT float WINAPI XPixelToMillimeter(const LONG& nDPI, const float &fPiexls );
  DLLXEXPORT float WINAPI XPixelToInch(const LONG& nDPI, const float &fPiexls );
  DLLXEXPORT float WINAPI XMillimeterToPixel( const LONG& nDPI, const float &nMm );
  DLLXEXPORT float WINAPI XInchToPixel( const LONG& nDPI, const float &nInch );


#ifdef __cplusplus
}
#endif
