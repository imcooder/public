/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XMath.h					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/09/01
*********************************************************************/
#ifndef  HWX_MATH_H
#define HWX_MATH_H
#include "Ext_Type.h"

template<typename LPXPoint>
RECT XMth_GetBoxEx(LPXPoint pBgn, LPXPoint pEnd);

template<typename LPXPoint>
RECT XMth_GetBox(LPXPoint pBgn, LPXPoint pEnd);


#include "XMath.cpp"
#endif // !defined(HWX_MATH_H)
