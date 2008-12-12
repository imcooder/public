
/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����:   Ext_Math.h          
�ļ�����:  �򵥵�һЩ������ѧ����
�汾��ʷ:  1.0
����:    xuejuntao xuejuntao@hanwang.com.cn 2008/02/26
*********************************************************************/
#ifndef  _HWXUE_Ext_Math_INC
#define _HWXUE_Ext_Math_INC
#include "Ext_Type.h"
#include <XNotesAPI.h>
//��㵽�߶ε���̾��� ����̾����
LONG Mth_GetMinDist(const HWPoint &tPtA, const HWPoint &tPtB, const HWPoint &tPtC, HWPoint &tNearestPt);
LONG DivRound(long x, long div);
LONG MulDivRound(long x, long mul, long div);

#ifdef __cplusplus
extern "C"{
#endif
  DLLXEXPORT long XSqrt(const long& nRoot);//��������������
  DLLXEXPORT void XQsort( void *base, long num, long width, long *pComp);//����������
  DLLXEXPORT void ZB_SwapIdx ( char *a,	char *b, unsigned long nIdxWidth);

#ifdef __cplusplus
}
#endif
template<typename XPoint>
static LONG IsLeft(const XPoint& tLineBgn, const XPoint& tLineEnd, const XPoint& tDst )
{
	return ((tLineEnd.x - tLineBgn.x) * (tDst.y - tLineBgn.y)
		- (tDst.x - tLineBgn.x) * (tLineEnd.y - tLineBgn.y));
}
template<typename XPoint>
LONG XGetMinDist(const XPoint &tPtA, const XPoint &tPtB, const XPoint &tPtC, 
								 XPoint &tNearestPt)
{  
	XPoint tPointAToB = XPoint(tPtB.x - tPtA.x, tPtB.y - tPtA.y);  
	XPoint tPointAToC = XPoint(tPtC.x - tPtA.x, tPtC.y - tPtA.y);      
	double dM = tPointAToB.x * tPointAToC.x + tPointAToB.y * tPointAToC.y;
	double dN = tPointAToB.x * tPointAToB.x + tPointAToB.y * tPointAToB.y;
	double dDelta = dM / dN;
	if (dDelta < 0.0)
	{
		tNearestPt = tPtA;    
	}
	else if (dDelta > 1.0)
	{
		tNearestPt = tPtB;    
	}
	else
	{
		tNearestPt = tPointAToB;
		tNearestPt.x *= dDelta;  
		tNearestPt.y *= dDelta;
		tNearestPt.x += tPtA.x;  
		tNearestPt.y += tPtA.y; 
	}    
	return std::sqrt(1.0 * (
		(tNearestPt.x - tPtC.x) * (tNearestPt.x - tPtC.x) + 
		(tNearestPt.y - tPtC.y) * (tNearestPt.y - tPtC.y))
		);
}
//************************************
// Method:    Ext_Mth_PtWithPolygon
// FullName:  Ext_Mth_PtWithPolygon
// Access:    public 
// Returns:   BOOL : 0 �ڶ���α��� -1 ���ڲ� 1 ���ⲿ
// Qualifier:�жϵ������εĹ�ϵ ��һ������ Ϊ��������˶��� 2 Ϊ������� 3 Ŀ�������
// Parameter: TPoint * ptPolygon
// Parameter: long nPtNum
// Parameter: TPoint * ptTarget
//************************************
template<typename XPoint, typename LPXPoint>
LONG Mth_PtWithPolygon(LPXPoint pBgn, LPXPoint pEnd, const XPoint& tTarget, XPoint&vValue)
{
	BOOL nRet = 1;
	LONG nTag = 0, nPos = -1;
	LONG nDistance = 0;
	XPoint tPointTmp;

	LPXPoint pIndexA = pBgn, pIndexB;
	nDistance = std::sqrt(1.0 * (pBgn->x - tTarget.x) * (pBgn->x - tTarget.x) +
		(pBgn->y - tTarget.y) * (pBgn->y - tTarget.y));
	vValue = *pBgn;
	tPointTmp = vValue;

	if (pBgn != pEnd)
	{
		//pIndexA ++;
		LONG nTmpDistance = nDistance;
		while (pIndexA != pEnd)
		{
			pIndexB = pIndexA + 1;
			if (pIndexB == pEnd)
			{
				pIndexB = pBgn;
			}
			//����㵽�߶εľ���
			nTmpDistance = XGetMinDist(*pIndexA, *pIndexB, tTarget, tPointTmp);
			if (nTmpDistance < nDistance)
			{
				nDistance = nTmpDistance;
				vValue = tPointTmp;
			}
			//��������߶εķ���
			if (0 != nRet)
			{
				if (pIndexA->y <= tTarget.y)
				{
					if (pIndexB->y > tTarget.y)
					{
						nPos = IsLeft(*pIndexA, *pIndexB, tTarget);
						if (nPos > 0)
						{
							nTag ++;
						}
						else if(0 == nPos)
						{
							nRet = 0;							
						}
					}
				}
				else
				{
					if (pIndexB->y <= tTarget.y)
					{
						nPos = IsLeft(*pIndexA, *pIndexB, tTarget);
						if (nPos < 0)
						{
							nTag -- ; 
						}
						else if (0 == nPos)
						{
							nRet = 0;							
						}
					}
				}
			}
			pIndexA ++;
		}
	}	
	if (0 != nRet)
	{
		if (0 != nTag)
		{
			nRet = -1;
		}
		else
		{
			nRet = 1;
		}
	}
	return nRet * nDistance;
}
#endif // !defined(_HWXUE_Ext_Math_INC)
