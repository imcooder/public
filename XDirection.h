
/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XDirection.h					
�ļ�����:	    ���ͷ�������
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2007/08/01
*********************************************************************/
#ifndef X_Direction_
#define X_Direction_
#include "Ext_Type.h"


#ifdef __cplusplus
extern "C"{
#endif

	DLLXEXPORT LONG  WINAPI XDirection256(const LONG& nDeltaX, const LONG& nDeltaY );
	DLLXEXPORT LONG  WINAPI XDirection32(const LONG& nDeltaX, const LONG& nDeltaY );
	DLLXEXPORT LONG  WINAPI XDirection16(const LONG& nDeltaX, const LONG& nDeltaY );
	DLLXEXPORT LONG  WINAPI XDirection8(const LONG& nDeltaX, const LONG& nDeltaY );

#ifdef __cplusplus
}
#endif

#endif//X_Direction_
