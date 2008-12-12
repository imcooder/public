/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����:   HWXPackage.h          
�ļ�����:  ���ݰ����� ���������ڴ�Ĺ��� 
�汾��ʷ:  1.0
����:    xuejuntao xuejuntao@hanwang.com.cn 2008/02/26
*********************************************************************/
#ifndef HWXUE_DBG_TPackage_H_Inc
#define HWXUE_DBG_TPackage_H_Inc
#include "Ext_Type.h"

class DLLXEXPORT CXPackage
{   
private:
  DWORD m_dwCapacity;
  DWORD m_dwSize;
  DWORD m_dwIncStep;
  BOOL m_bl32BitAlign;
  BYTE *m_pbBuffer;  
public:
  //////////////////////////////////////////////////////////////////////////
  CXPackage(BOOL = TRUE);
  CXPackage(const void *, DWORD, BOOL = TRUE);
  virtual ~CXPackage();
  CXPackage(const CXPackage &);
  //����ÿ�������� ����ʵ��������������� ��ò�ͣ���������ڴ� Ӱ���ٶ� Ĭ���� PACKAGE_Mem_Inc BYTE
  void SetIncStep(DWORD);
  DWORD GetSize() const;
  DWORD GetCapacity() const;
  const void *GetData() const;
  //////////////////////////////////////////////////////////////////////////
  //�������洦��
  BYTE *GetBuffer(DWORD);
  BOOL ReleaseBuffer(DWORD);
  //��ԭ����Ļ��������� �ͷź� ԭ�������ݲ��� ֻ������
  BYTE *GetBufferEx(DWORD);
  BOOL ReleaseBufferEx(DWORD);
  //////////////////////////////////////////////////////////////////////////
  //��������buffer���� buffer������Ԥ�ڵĴ�
  BOOL Reset(const void *, DWORD);
  //Buffer�����պ�
  BOOL ResetEx(const void *, DWORD);
  
  //////////////////////////////////////////////////////////////////////////
  //�������Ԫ��(���ͷ��ڴ�)
  void Clear();
  //�ͷ���Դ 
  void Release();
  //////////////////////////////////////////////////////////////////////////
  //BOOL
  BOOL IsEmpty() const;  
  BOOL IsNull() const;
  //////////////////////////////////////////////////////////////////////////
  //�ö�ջ β��׷��
  BOOL Push(const void *, DWORD);
  BOOL Push(const CXPackage *);
  //////////////////////////////////////////////////////////////////////////
  //ͷ��Push׷������
  BOOL Push_Front(const void *, DWORD);
  BOOL Push_Front(const CXPackage *);
  //////////////////////////////////////////////////////////////////////////
  //��������  
  BOOL Pop(DWORD , void *pvVariant = NULL);
  BOOL Pop(DWORD , CXPackage* );
  //////////////////////////////////////////////////////////////////////////
  //ͷ����������
  BOOL Pop_Front(DWORD , void *pvVariant = NULL);
  BOOL Pop_Front(DWORD , CXPackage* );
  //////////////////////////////////////////////////////////////////////////
  void Shrink();
  //////////////////////////////////////////////////////////////////////////
  //ɾ��Ԫ��
  BOOL Erase(DWORD, DWORD);
  //////////////////////////////////////////////////////////////////////////
  //����Ԫ��
  BOOL Insert(DWORD , const void *pvVariant, DWORD);
  //////////////////////////////////////////////////////////////////////////
  //��������
  BOOL operator==(const CXPackage& ) const;
  const CXPackage  &operator=(const CXPackage& );
  const CXPackage  &operator+=(const CXPackage& );
  const CXPackage  operator+(const CXPackage& ) const;
  operator const BYTE *() const;  
  operator const TCHAR *() const;  
private:
  //////////////////////////////////////////////////////////////////////////
  //Ԥ��һ������ ����Ѿ����ڴ���� �򲻽��д���
  BOOL Reserve(DWORD);
  inline DWORD CalcUsedBytes( DWORD dwBits);
};

typedef CXPackage CHWXPackage;

#endif//HWXUE_DBG_TPackage_H_Inc