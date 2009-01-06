
#ifndef HWX_AUTOPTR_H
#define HWX_AUTOPTR_H

#include "HWDebug.h"

template<class _Ty>
class CAutoPtr
{
public:
	CAutoPtr() : m_pPtr(NULL)
	{
		VERIFY(m_pPtr = new _Ty);
	}	
	explicit CAutoPtr(CAutoPtr<_Ty>& _Right)
		: m_pPtr(_Right.Release())
	{	

	}
	explicit CAutoPtr(_Ty *_Ptr = 0): m_pPtr(_Ptr)
	{

	}
	virtual ~CAutoPtr()
	{
		Destroy();
	}	
	_Ty* Release()
	{
		_Ty* pA = m_pPtr;
		m_pPtr = NULL;
		return pA;
	}	
	CAutoPtr<_Ty>& operator=(CAutoPtr<_Ty>& _Right) 
	{	
		Reset(_Right.Release());
		return (*this);
	}
	_Ty& operator*() const
	{	
		if (m_pPtr)
		{
			DEBUG_ERROR(TEXT("auto_ptr not dereferencable"));
		}
		return (*Get());
	}
	_Ty *operator->() const
	{	
		if (!m_pPtr)
		{
			DEBUG_ERROR(TEXT("auto_ptr not dereferencable"));
		}
		return (Get());
	}
	virtual BOOL AssertValid() const
	{
		return TRUE;
	}
	_Ty *Get()
	{
		return (m_pPtr);
	}
	void Reset(_Ty* _Ptr = 0)
	{	
		if (_Ptr != m_pPtr)
		{
			Destroy();
		}
		m_pPtr = _Ptr;
	}
protected:
	void Destroy()
	{
		SAFE_DELETE(m_pPtr);
	}		

protected:
	_Ty*	m_pPtr;
};





template<class _Ty>
class CAutoPtrArray
{
public:
	CAutoPtrArray(DWORD dwCount) : m_pPtr(NULL)
	{
		VERIFY(m_dwCount = dwCount);
		VERIFY(m_pPtr = new _Ty[dwCount]);		
	}	
	explicit CAutoPtrArray(CAutoPtrArray<_Ty>& _Right) : m_pPtr(_Right.Detach(&m_dwCount))
	{	
		
	}
	explicit CAutoPtrArray(_Ty *_Ptr, DWORD dwCount): m_pPtr(_Ptr), m_dwCount(dwCount)
	{

	}
	virtual ~CAutoPtrArray()
	{
		Destroy();
	}
	_Ty* Release(DWORD *pdwCount)
	{
		_Ty* pA = m_pPtr;
		m_pPtr = NULL;
		if (pdwCount)
		{
			*pdwCount = m_dwCount;
		}
		return pA;
	}	
	CAutoPtrArray<_Ty>& operator=(CAutoPtrArray<_Ty>& _Right) 
	{	
		DWORD dwCount = 0;
		_Ty pPointer = _Right.Release(&m_dwCount);
		Reset(pPointer, &dwCount);
		return (*this);
	}
	_Ty& operator*() const
	{	
		if (m_pPtr)
		{
			DEBUG_ERROR(TEXT("auto_ptr not dereferencable"));
		}
		return (*Get());
	}
	_Ty *operator->() const
	{	
		if (!m_pPtr)
		{
			DEBUG_ERROR(TEXT("auto_ptr not dereferencable"));
		}
		return (Get());
	}
	virtual BOOL AssertValid() const
	{
		BOOL blValid = TRUE;
		if (m_pPtr)
		{
			VERIFY(blValid = (m_dwCount));			
		}
		else
		{
			VERIFY(blValid = (!m_dwCount));	
		}
		return blValid;
	}
	_Ty *Get()
	{
		return (m_pPtr);
	}
	void Reset(_Ty*_Ptr, DWORD dwCount)
	{	
		if (_Ptr != m_pPtr)
		{
			Destroy();
		}
		m_pPtr = _Ptr;
		m_dwCount = dwCount;
	}

protected:

	void Destroy()
	{
		SAFE_DELETE_AR(m_pPtr);
		m_dwCount = 0;
	}	

protected:
	_Ty*	m_pPtr;
	DWORD m_dwCount;
};











#endif//HWX_AUTOPTR_H