/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XMath.cpp					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/09/01
*********************************************************************/

#include "stdafx.h"
//#include "XMath.h"
#include <cmath>



template<typename LPXPoint>
RECT XMth_GetBoxEx(LPXPoint pBgn, LPXPoint pEnd)
{	
	assert(pBgn && pEnd);
	CRect rtBox(0, 0, 0, 0);
	LPXPoint pIndex = pBgn;
	if (!pBgn || !pEnd)
	{
		return rtBox;
	}
	while (pIndex != pEnd)
	{
		if (!(-1 == pIndex->x && (-1 == pIndex->y || 0 == pIndex->y)))
		{
			rtBox.SetRect(pIndex->x, pIndex->y, pIndex->x, pIndex->y);
			break;
		}        
		pIndex ++;
	}
	while (pIndex != pEnd && !(-1 == pIndex->x && -1 == pIndex->y))
	{
		if (!(-1 == pIndex->x && 0 == pIndex->y))
		{
			if (rtBox.left > pIndex->x)
			{
				rtBox.left = pIndex->x;
			}
			else if (rtBox.right < pIndex->x)
			{
				rtBox.right = pIndex->x;
			}
			if (rtBox.top > pIndex->y)
			{
				rtBox.top = pIndex->y;
			}
			else if (rtBox.bottom < pIndex->y)
			{
				rtBox.bottom = pIndex->y;
			}
		}  
		pIndex ++;
	}	  
	return rtBox;
}

template<typename LPXPoint>
RECT XMth_GetBox(LPXPoint pBgn, LPXPoint pEnd)
{//ֻ��һ���ʼ� �ڲ�������Ч��
	assert(pBgn && pEnd);
	CRect rtBox(0, 0, 0, 0);  
	LPXPoint pIndex = pBgn;
	if (!pBgn || !pEnd)
	{
		return rtBox;
	}	  

	if (pIndex != pEnd)
	{
		rtBox.left = rtBox.right = pIndex->x;
		rtBox.top = rtBox.bottom = pIndex->y;
		pIndex ++;
		while (pIndex != pEnd)
		{
			if (rtBox.left > pIndex->x)
			{
				rtBox.left = pIndex->x;
			}
			else if(rtBox.right < pIndex->x)
			{
				rtBox.right = pIndex->x;
			}
			if (rtBox.top > pIndex->y)
			{
				rtBox.top = pIndex->y;
			}
			else if(rtBox.bottom < pIndex->y)
			{
				rtBox.bottom = pIndex->y;
			}
			pIndex ++;
		}				
	}    
	return rtBox;
}

