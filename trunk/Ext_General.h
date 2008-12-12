#ifndef _DBG_General_H_INC_
#define _DBG_General_H_INC_
#include "stdafx.h"
#include "Ext_type.h"
#include "HWXPackage.h"
#include "HWXString.h"
#include "Ext_File.h"
#include "Ext_Math.h"
#include "XRect.h"
#include "HWXReg.h"
#include <GlobalEx.h>
#include <tchar.h>
#include <vector>
#include <XNotesAPI.h>
//#include <GdiPlus.h>

// #ifdef __cplusplus
// extern "C"{
// #endif
//��ͼģʽ���ݸ�ʽ
extern const HWPoint g_atEndMark[2];


typedef struct tagFormat_FMT
{
  WORD wPackageSize;    //һ�����ݰ����ܳ��ȣ��ֽڸ�����  
  WORD wStrLen;      //�ο�ID������
  BYTE *pbRefUnicode;    //�ο�ID//  
  const BYTE *pbTrace;
} TFormat_FMT, *LPTFormat_FMT;
typedef struct tagStroke
{
  LONG  m_nBeginPos;                          //�ʻ���ʼλ��
  LONG  m_nEndPos;                            //�ʻ�����λ��  
  LONG  m_nStrokeLen;                         //�ʻ�����  
  RECT  m_tBox;                  //�ʻ���Χ��  
} TStroke, *LPTStroke;
BOOL WCharToChar(HWX_IN const wchar_t* ,  HWX_OUT char* ,    HWX_IN long );
BOOL CharToWChar(HWX_IN const char* ,    HWX_OUT wchar_t* ,  HWX_IN long );




BOOL IsHexDigit(HWX_IN const TCHAR *pszStr);
HWX_OUT CRect GetRect(HWX_IN const HWPoint *ptTrace);
HWX_OUT CRect GetRect(HWX_IN const std::vector<HWPoint> &vStrokeTrace);
CRect GetTraceBoundbox(const std::vector<HWPoint> &);
BOOL FILE_GenFmt(HWX_IN const BYTE *pbData, HWX_OUT TFormat_FMT *ptFormatFmt);
BOOL Trc_GenStrokeInfo(HWX_IN const HWPoint *ptTrace, 
                       HWX_OUT TStroke *ptStroke, HWX_OUT long *pnStrokeCount);

HWPoint  TransformPos(HWX_IN const HWPoint &, HWX_IN const CRect& , 
                      HWX_IN const CRect& , BOOL = TRUE);
HWX_OUT BOOL TraceTransform(HWX_IN_OUT HWPoint *ptTrace, HWX_IN const CRect &rtRectS, 
                            HWX_IN const CRect &rtRectD);
HWX_OUT BOOL TraceTransform(HWX_IN_OUT std::vector<HWPoint>& vtTrace, 
                            HWX_IN const CRect &rtRectS, HWX_IN const CRect &rtRectD);

HWX_OUT HWPoint PtTrans(CPoint& tPt, CRect& in_srcRect, CRect& in_dstRect);

HWX_OUT HWPoint GetNearestPointOnTrace(const HWPoint *ptTrace, const HWPoint &tPtCur);
HWX_OUT HWPoint GetNearestPointOnLines(const std::vector<HWPoint> &, const HWPoint &tPtCur);
HWX_OUT BOOL  IsPointOnLines(const std::vector<HWPoint> &, const HWPoint &tPtCur);
// #ifdef __cplusplus
// }
// #endif
//��ȡ����ϵͳ����

CRect CalcBox(const std::vector<HWPoint> &);


#endif