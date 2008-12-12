/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����:   HWXPackage.h          
�ļ�����:  ���ݰ����� ���������ڴ�Ĺ��� 
�汾��ʷ:  1.0
����:    xuejuntao xuejuntao@hanwang.com.cn 2008/02/26
*********************************************************************/
#include "stdafx.h"
#include "HWXPackage.h"
#include "Ext_Memory.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define PACKAGE_Mem_Inc    (256)
//////////////////////////////////////////////////////////////////////////
CXPackage::CXPackage(BOOL blAlign)
{
  m_pbBuffer = NULL;
  m_dwSize = 0;
  m_dwCapacity = CalcUsedBytes(m_dwSize);
  m_dwIncStep = PACKAGE_Mem_Inc;
  m_bl32BitAlign = blAlign;
}

CXPackage::CXPackage(const void *pvContent, DWORD dwSize, BOOL blAlign)
{
  m_pbBuffer = NULL;
  m_dwSize = 0;
  m_dwCapacity = CalcUsedBytes(m_dwSize);
  m_dwIncStep = PACKAGE_Mem_Inc;
  m_bl32BitAlign = blAlign;
  ResetEx(pvContent, dwSize);  
}

CXPackage::CXPackage(const CXPackage &tB)
{
  m_pbBuffer = NULL;
  m_dwSize = 0;
  m_dwCapacity = CalcUsedBytes(m_dwSize);
  m_dwIncStep = PACKAGE_Mem_Inc;
  m_bl32BitAlign = tB.m_bl32BitAlign;
  if (!tB.IsEmpty())
  {
    ResetEx(tB.m_pbBuffer, tB.m_dwSize);
  }  
}
//////////////////////////////////////////////////////////////////////////
CXPackage::~CXPackage()
{
  Release();
}

//�ͷŻ�����
void CXPackage::Release()
{
	SAFE_DELETE_AR(m_pbBuffer);
  //Mem_FreeMemory((void **)&m_pbBuffer);
  m_dwSize = 0;
  m_dwCapacity = 0;
}
//�������Ԫ��(���ͷ��ڴ�)
void CXPackage::Clear()
{
#if defined(_DEBUG) || defined(DEBUG)
  {
    if (m_dwCapacity)
    {
      assert(m_pbBuffer);
      ZeroMemory(m_pbBuffer, m_dwCapacity);
    }  
  }
#endif  
  m_dwSize = 0;  
}
//////////////////////////////////////////////////////////////////////////
//������������
BOOL CXPackage::Reset(const void *pvContent, DWORD dwSize)
{
  assert(pvContent);
  assert(m_pbBuffer != pvContent);
  Clear();
  return Push(pvContent, dwSize);  
}

BOOL CXPackage::ResetEx(const void *pvContent, DWORD dwSize)
{//Ϊ�˷�ֹ�ڴ���˷�  ��������Ч���ڴ��
  assert(pvContent);  
  assert(m_pbBuffer != pvContent);
  BOOL blRet = TRUE;
  BYTE *pBuffer = NULL;
  if (pvContent)
  {   
    DWORD dwNewSize = CalcUsedBytes(dwSize);
		if (dwNewSize > 0)
		{
			VERIFY(pBuffer = new BYTE[dwNewSize]);
			ZeroMemory(pBuffer, sizeof(*pBuffer) * dwNewSize);
			memmove(pBuffer, (void *)pvContent, _min(dwSize, dwNewSize));
		}
#ifdef _DEBUG
		ZeroMemory(m_pbBuffer, sizeof(*m_pbBuffer) * m_dwCapacity);
#endif
		SAFE_DELETE_AR(m_pbBuffer);

		m_pbBuffer = pBuffer;
		m_dwSize = dwSize;
		m_dwCapacity = dwNewSize;		
  }
  else
  {    
    Release();
  }
  return blRet;
}
//////////////////////////////////////////////////////////////////////////
//β��Push׷������
BOOL CXPackage::Push(const void *pvContent, DWORD dwSize)
{
  BOOL blRet = TRUE;
  assert(pvContent);  
  if (NULL == pvContent)
  {
    blRet = FALSE;
    goto _Exit;
  }
  VERIFY(FALSE != (blRet = Reserve(m_dwSize + dwSize)));
  assert(m_dwCapacity >= m_dwSize + dwSize);
  memmove(m_pbBuffer + m_dwSize, (void *)pvContent, dwSize);
  m_dwSize += dwSize;

_Exit:
  return blRet;
}
BOOL CXPackage::Push(const CXPackage *ptB)
{
  assert(ptB);

  BOOL blRet = TRUE;
  if (!ptB)
  {
    blRet = FALSE;
    goto _Exit;
  }
  if (ptB->IsEmpty())
  {
    goto _Exit;
  }
  blRet = Push(ptB->m_pbBuffer, ptB->m_dwSize);
_Exit:
  return blRet;
}
//////////////////////////////////////////////////////////////////////////
//ͷ��Push׷������
BOOL CXPackage::Push_Front(const void *pvContent, DWORD dwSize)
{
  assert(pvContent);
  BOOL blRet = TRUE;
    
  if (NULL == pvContent)
  {
    blRet = FALSE;
    goto _Exit;
  }
  VERIFY(FALSE != (blRet = Reserve(m_dwSize + dwSize)));
  assert(m_dwCapacity >= m_dwSize + dwSize);
  
  memmove(m_pbBuffer + dwSize, m_pbBuffer, m_dwSize);
  memmove(m_pbBuffer, (void *)pvContent, dwSize);
  m_dwSize += dwSize;
  
_Exit:
  return blRet;
}
BOOL CXPackage::Push_Front(const CXPackage *ptB)
{
  assert(ptB);
  BOOL blRet = TRUE;
  if (!ptB)
  {
    blRet = FALSE;
    goto _Exit;
  }
  if (ptB->IsEmpty())
  {
    goto _Exit;
  }
  blRet = Push_Front(ptB->m_pbBuffer, ptB->m_dwSize);
_Exit:
  return blRet;
}
//////////////////////////////////////////////////////////////////////////
//��������
BOOL CXPackage::Pop(DWORD dwSize, void *pvVariant)
{
  BOOL blRet = TRUE;  
  assert(dwSize >= 0);
  if (0 == dwSize)
  {
    goto _Exit;
  }  
  else if (dwSize > m_dwSize)
  {
    dwSize = m_dwSize;
  }
  assert(m_dwSize >= dwSize);
  if (pvVariant)
  {
    memmove(pvVariant, m_pbBuffer + m_dwSize - dwSize, dwSize);
  }
#if defined(_DEBUG) || defined(DEBUG)
	{
		ZeroMemory(m_pbBuffer + m_dwSize - dwSize, dwSize);
	}
#endif
  m_dwSize -= dwSize;
  assert(0 <= m_dwSize);
_Exit:

  return blRet;
}
BOOL CXPackage::Pop(DWORD dwSize, CXPackage* ptB)
{  
  assert(ptB);
  BOOL blRet = TRUE;
  if (0 == dwSize)
  {
    goto _Exit;
  }  
  else if (dwSize > m_dwSize)
  {
    dwSize = m_dwSize;
  }  
  assert(m_dwSize >= dwSize);
  if (FALSE == (blRet = ptB->Push(m_pbBuffer + m_dwSize - dwSize, dwSize)))
  {
    goto _Exit;
  }

#if defined(_DEBUG) || defined(DEBUG)
	{
		ZeroMemory(m_pbBuffer + m_dwSize - dwSize, dwSize);
	}
#endif
  m_dwSize -= dwSize;
  assert(0 <= m_dwSize);
_Exit:
  
  return blRet;
}
//////////////////////////////////////////////////////////////////////////
BOOL CXPackage::Pop_Front(DWORD dwSize, void *pvVariant)
{
  BOOL blRet = TRUE;
  
  assert(dwSize <= m_dwSize);
  if (0 == dwSize)
  {
    goto _Exit;
  }  
  else if (dwSize > m_dwSize)
  {
    dwSize = m_dwSize;
  }
  if (pvVariant)
  {
    memmove(pvVariant, m_pbBuffer, dwSize);
  }
  if (dwSize != m_dwSize)
  {
    memmove(m_pbBuffer, m_pbBuffer + dwSize, m_dwSize - dwSize);
  }
  
#if defined(_DEBUG) || defined(DEBUG)
	{
		ZeroMemory(m_pbBuffer + m_dwSize - dwSize, dwSize);
	}
#endif
  m_dwSize -= dwSize;
  assert(0 <= m_dwSize);
_Exit:
  
  return blRet;
}
BOOL CXPackage::Pop_Front(DWORD dwSize, CXPackage *ptB)
{
  BOOL blRet = TRUE;
  
  assert(dwSize <= m_dwSize);
  assert(ptB);
  if (0 == dwSize)
  {
    goto _Exit;
  }
  else if (dwSize > m_dwSize)
  {
    dwSize = m_dwSize;
  }
  if (FALSE == (blRet = ptB->Push(m_pbBuffer, dwSize)))
  {
    goto _Exit;
  }  
  if (dwSize != m_dwSize)
  {
    memmove(m_pbBuffer, m_pbBuffer + dwSize, m_dwSize - dwSize);
  }
  
#if defined(_DEBUG) || defined(DEBUG)
	{
		ZeroMemory(m_pbBuffer + m_dwSize - dwSize, dwSize);
	}
#endif
  m_dwSize -= dwSize;
  assert(0 <= m_dwSize);
  
_Exit:
  
  return blRet;
}
//////////////////////////////////////////////////////////////////////////
//���������ڴ�
void CXPackage::Shrink()
{  
  if (m_dwSize != m_dwCapacity)
  {    
    if (!IsEmpty())
    {
      DWORD dwShrinkedSize = CalcUsedBytes(m_dwSize);
			BYTE *pByte = NULL;
			VERIFY(pByte = new BYTE[dwShrinkedSize]);
#ifdef _DEBUG
			ZeroMemory(pByte, sizeof(*pByte) * dwShrinkedSize);
#endif
			memmove(pByte, m_pbBuffer, m_dwSize);
			SAFE_DELETE_AR(m_pbBuffer);
			m_pbBuffer = pByte;
			m_dwCapacity = dwShrinkedSize;      
    }
    else
    {
      Release();
    }
  }
  return;
}
//////////////////////////////////////////////////////////////////////////
void CXPackage::SetIncStep(DWORD dwStep)
{
  if (0 == dwStep)
  {
    m_dwIncStep = PACKAGE_Mem_Inc;
  }
  else
  {
    m_dwIncStep = dwStep;
  }
}
//////////////////////////////////////////////////////////////////////////
DWORD CXPackage::GetSize() const
{
  return m_dwSize;
}
DWORD CXPackage::GetCapacity() const
{
  return m_dwCapacity;  
}
const void *CXPackage::GetData() const
{
  return (const void *)m_pbBuffer;
}
BOOL CXPackage::IsEmpty() const
{
  return (0 == m_dwSize);
}
BOOL CXPackage::IsNull() const
{
  return (!m_pbBuffer);
}
//////////////////////////////////////////////////////////////////////////
//operator
BOOL CXPackage::operator==(const CXPackage& tB) const
{  
  return (m_dwSize == tB.m_dwSize && FALSE != Mem_EqualMemory(m_pbBuffer, tB.m_pbBuffer, m_dwSize));  
}
const CXPackage& CXPackage::operator=(const CXPackage& tRight)
{//Ϊ�˷�ֹ�ڴ���˷�  ���ﲻ������ȫ��� ֻ������Ч���ڴ��
  //���ܳ����Լ������Լ������ ��ʱrealloc������ܳ������ֵ
  assert(&tRight != this);
  if (&tRight != this)
  {//�Լ������Լ�
    if (!tRight.IsEmpty())
    {
      ResetEx(tRight.m_pbBuffer, tRight.m_dwSize);
    }
    else
    {
      Release();
    }
  }  
  return *this;
}
const CXPackage& CXPackage::operator+=(const CXPackage& tRight)
{//Ϊ�˷�ֹ�ڴ���˷�  ���ﲻ������ȫ��� ֻ������Ч���ڴ��    
  if (!tRight.IsEmpty())
  {
    Push(tRight.m_pbBuffer, tRight.m_dwSize);
  }
  
  return *this;
}
const CXPackage CXPackage::operator+(const CXPackage& tRight) const
{  
  CXPackage tRet(*this);
  tRet.Push(&tRight);    
  return tRet;
}
CXPackage::operator const BYTE *() const
{    
  return (const BYTE *)m_pbBuffer;
}
CXPackage::operator const TCHAR *() const 
{    
  return (const TCHAR *)m_pbBuffer;
}
//////////////////////////////////////////////////////////////////////////
///ɾ��Ԫ��
BOOL CXPackage::Erase(DWORD dwStart, DWORD dwSize)
{
  BOOL blRet = TRUE;
  DWORD dwNewSize = 0;
  
  assert(dwStart < m_dwSize);  
  assert(dwStart + dwSize <= m_dwSize);

  if (dwStart >= m_dwSize)
  {
    blRet = FALSE;
    goto _Exit;
  }
  if (0 == dwSize)
  {
    goto _Exit;
  }
  if (dwStart + dwSize >= m_dwSize)
  {
    dwSize = m_dwSize - dwStart;
  }
  assert(dwStart + dwSize <= m_dwSize);
  if (dwStart + dwSize < m_dwSize)
  {//��β������Ԫ��
    memmove(m_pbBuffer + dwStart, m_pbBuffer + (dwStart + dwSize), m_dwSize - (dwStart + dwSize));
  }
  dwNewSize = (long)m_dwSize - (long)dwSize;
#if defined(_DEBUG) || defined(DEBUG)
  {
    ZeroMemory(m_pbBuffer + dwNewSize, m_dwSize - dwNewSize);
  }
#endif
  m_dwSize = dwNewSize;
_Exit:
  return blRet;
}

//////////////////////////////////////////////////////////////////////////
///����Ԫ��
BOOL CXPackage::Insert(DWORD dwStart, const void *pvVariant, DWORD dwSize)
{  
  assert(pvVariant);  
  assert(dwStart <= m_dwSize);

  BOOL blRet = TRUE;
  CXPackage tTmp;
  if (dwSize <= 0)
  {
    goto _Exit;
  }
  if (dwStart > m_dwSize)
  {
    dwStart = m_dwSize;
  }  
  tTmp = *this;
  Clear();
  //һ���ڴ����
  VERIFY(Reserve(m_dwSize + dwSize));
  if (0 != dwStart)
  {
    if (FALSE == (blRet = tTmp.Pop_Front(dwStart, this)))
    {
      goto _Exit;
    }        
  }
  if (FALSE == (blRet = Push(pvVariant, dwSize)))
  {
    goto _Exit;
  }  
  if (!tTmp.IsEmpty())
  {
    if (FALSE == (blRet = Push(&tTmp)))
    {
      goto _Exit;
    }    
  }
_Exit:
  return blRet;
}

//////////////////////////////////////////////////////////////////////////
//Ԥ��һ�������� ����Ѿ��ﵽ��ô�� �򲻽��д��� 
BOOL CXPackage::Reserve(DWORD dwSize)
{  
  BOOL blRet = TRUE;
  DWORD dwExpMemSize;
  assert(m_dwSize <= m_dwCapacity);
  if (0 == dwSize)
  {
    dwSize = m_dwIncStep;
  }  
  if (dwSize < m_dwCapacity)
  {    
    goto _Exit;
  }
  
  dwExpMemSize = (dwSize + m_dwIncStep - 1) / m_dwIncStep * m_dwIncStep;
  dwExpMemSize = CalcUsedBytes(dwExpMemSize);	
  assert(dwExpMemSize >= m_dwIncStep);
  assert(m_dwCapacity <= dwExpMemSize);
  if (m_dwCapacity == dwExpMemSize)
  {
    goto _Exit;
  }
	BYTE *pByte = NULL;
	VERIFY(pByte = new BYTE[dwExpMemSize]);
#ifdef _DEBUG
	ZeroMemory(pByte, sizeof(*pByte) * dwExpMemSize);
#endif
	memmove(pByte, m_pbBuffer, _min(dwExpMemSize, m_dwCapacity));
	SAFE_DELETE_AR(m_pbBuffer);
	m_pbBuffer = pByte;
  m_dwCapacity = dwExpMemSize;    
_Exit:
  return blRet;
}
//�ڵ�ǰ��������Ӷ����Ļ����� ���ش˻�������ַ
BYTE *CXPackage::GetBufferEx(DWORD dwBufferSize)
{  
  BYTE *pbBuffer = NULL;
  if (FALSE == Reserve(m_dwSize + dwBufferSize))
  {
    goto Exit_;
  }
  pbBuffer = m_pbBuffer + m_dwSize;
Exit_:
  return pbBuffer;
}
//�ͷŻ����� ����������nbuffersize�ĳ������ݹ̻�����
BOOL CXPackage::ReleaseBufferEx(DWORD dwBufferSize)
{
  assert(dwBufferSize + m_dwSize <= m_dwCapacity);
  BOOL blRet = TRUE;
  if (!(dwBufferSize + m_dwSize <= m_dwCapacity))
  {
    blRet = FALSE;
    goto Exit_;
  }
  m_dwSize += dwBufferSize;
Exit_:
  return blRet;
}

//�ڵ�ǰ��������Ӷ����Ļ����� ���ش˻�������ַ
BYTE *CXPackage::GetBuffer(DWORD dwBufferSize)
{  	
  BYTE *pbBuffer = NULL;  
  if (FALSE == Reserve(dwBufferSize))
  {
    goto Exit_;
  }
  pbBuffer = m_pbBuffer;
Exit_:
  return pbBuffer;
}
//�ͷŻ����� ����������nbuffersize�ĳ������ݹ̻�����
BOOL CXPackage::ReleaseBuffer(DWORD dwBufferSize)
{
  assert(dwBufferSize <= m_dwCapacity);
  BOOL blRet = TRUE;
  if (!(dwBufferSize <= m_dwCapacity))
  {
    blRet = FALSE;
    goto Exit_;
  }
  m_dwSize = dwBufferSize;
Exit_:
  return blRet;
}
DWORD CXPackage::CalcUsedBytes( DWORD dwUsedBytes)
{
#if defined(_DEBUG) || defined(DEBUG)
  DWORD dwSize = dwUsedBytes;
#endif
  if( m_bl32BitAlign )
  { //if os is 64 bit , then maybe change code little.
    dwUsedBytes += dwUsedBytes > 0 ? (4 - (dwUsedBytes & 3) ) : 0;
  }
#if defined(_DEBUG) || defined(DEBUG)
  assert(dwUsedBytes >= dwSize);
#endif
  return dwUsedBytes;
}