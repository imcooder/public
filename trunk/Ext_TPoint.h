/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����:   Ext_TPoint.h          
�ļ�����:  �Զ�����ʵ�� ��Ϯ���ı��벿��TPoint�Ķ���
�汾��ʷ:  1.0
����:    xuejuntao xuejuntao@hanwang.com.cn 2008/02/26
*********************************************************************/

#ifndef  _HWXUE_Ext_TPoint_INC
#define _HWXUE_Ext_TPoint_INC
#include "Ext_Type.h"

#include <Gdiplus.h>

class CTPoint : public TPoint
{
public:
  CTPoint();
  CTPoint(long, long);
  CTPoint(const POINT&);
  CTPoint(const CPoint &);
  CTPoint(const CTPoint &);
  ~CTPoint();
  
  BOOL operator==(const CTPoint &) const;
  BOOL operator==(const POINT &) const;
  BOOL operator==(const CPoint &) const;
  BOOL operator!=(const CTPoint &) const;
  BOOL operator!=(const POINT &) const;
  BOOL operator!=(const CPoint &) const;  
  friend BOOL operator==(const POINT& tA, const CTPoint& tB);  
  friend BOOL operator==(const CPoint& tA, const CTPoint& tB);
  friend BOOL operator!=(const POINT& tA, const CTPoint& tB);  
  friend BOOL operator!=(const CPoint& tA, const CTPoint& tB);

  const CTPoint operator-()  const;
  const CTPoint operator+(long) const;
  const CTPoint operator+(const CTPoint &) const;
  const CTPoint operator+(const CSize &) const;
  const CTPoint &operator=(const POINT&);
  const CTPoint &operator=(const CPoint&);
  


  const CTPoint operator-(const CTPoint &) const;
  const CTPoint &operator -=(const CTPoint &);
  const CTPoint &operator +=(const CTPoint &);
  //����ת�� ����
  operator const POINT();
  operator const CPoint();
 
#ifdef _GDIPLUS_H
  operator const Gdiplus::Point() const;
#endif
  
  const double GetDistance(const CTPoint &) const;
  //������һЩvector����
  const double operator*(const CTPoint &) const;  
  
private:  
  BOOL Reset(long, long);
  BOOL Offset(long, long);

public:
//   short x;
//   short y;

};
typedef CTPoint* LPCTPoint;
typedef const CTPoint* LPCCTPoint;

#endif // !defined(_HWXUE_Ext_TPoint_INC)
