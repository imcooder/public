/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����:   HWXString.h          
�ļ�����:    �Զ���String������
�汾��ʷ:    1.0
����:        xuejuntao xuejuntao@hanwang.com.cn 2008/03/06
*********************************************************************/
#ifndef HWXUE_CString_H_INC
#define HWXUE_CString_H_INC
//
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Ext_Memory.h"
#include "HWXPackage.h"
#include <vector>
#include <iostream>

const WCHAR g_awhDelimit[5] = {L'\n', L'\r', L'\t', L' ', 0x0};
const CHAR  g_achDelimit[5] = {'\n', '\r', '\t', ' ', 0x0};
class CXStringW;
class CXStringA;


#ifdef UNICODE
typedef CXStringW CXStringT;
#else 
typedef CXStringA CXStringT;
#endif
typedef CXStringT CXString;

typedef CXStringT CHWXString;

class DLLXEXPORT CXStringW
{  
private:  
  CHWXPackage m_tPackage;  
  LONG m_nIncStep;
  LONG m_nLength;
public:
  // Constructor/Destructor
  CXStringW();  
  CXStringW(LPCWSTR); 
  explicit CXStringW(const WCHAR &);
  CXStringW(LPCWSTR, LONG nLen);
  CXStringW(const CXStringW &);   
  virtual ~CXStringW();  
	void AssertValid() const;
  /************************************************************************
  ����:  Clear
  ȫ��:  void CHWXString::Clear(  )
  ����:  public 
  ����ֵ:  void: 
  ����:  ����ַ� 
  ************************************************************************/
  void Clear();

  /************************************************************************
  ����:  StrLen
  ȫ��:  LONG CHWXString::StrLen(  ) const
  ����:  public 
  ����ֵ:  LONG: 
  ����:  ��ȡ������ 
  ************************************************************************/
  LONG StrLen() const;
  /************************************************************************
  ����:  IsEmpty
  ȫ��:  bool CHWXString::IsEmpty(  ) const
  ����:  public 
  ����ֵ:  bool: 
  ����:  �Ƿ�Ϊ�� 
  ************************************************************************/
  BOOL IsEmpty() const;

  /************************************************************************
  ����:  C_Str
  ȫ��:  char * CHWXString::GetData(  ) const
  ����:  public 
  ����ֵ:  char *: 
  ����:  ��ȡ����
  ************************************************************************/
  LPCWSTR C_Str() const;


  WCHAR GetAt(LONG );  
  BOOL SetAt(LONG , WCHAR );
  //////////////////////////////////////////////////////////////////////////
  //��ת�ַ���
  void Reverse();
  //�ַ�����λ
  LONG FirstBelong(LPCWSTR);
  LONG FirstNoBelong(LPCWSTR);
  BOOL IsBelong(LPCWSTR);
  BOOL IsNoBelong(LPCWSTR);
  /************************************************************************
  ����:  MakeLower
  ȫ��:  void CHWXString::MakeLower(  )
  ����:  public 
  ����ֵ:  void: 
  ����:  ��Сд�任 
  ************************************************************************/
  void MakeLower();
  void MakeUpper();

  /************************************************************************
  ����:  Compare
  ȫ��:  bool CHWXString::Compare( const char *pchCompareString )
  ����:  public 
  ����ֵ:  bool: 
  ����:  �Ƚ� 
  ����:  const char * pchCompareString: 
  ************************************************************************/
  BOOL Compare(LPCWSTR) const;
  BOOL Compare(const CXStringW &) const;
  BOOL CompareNoCase(LPCWSTR) const;
  BOOL CompareNoCase(const CXStringW &) const;  

  /************************************************************************
  ����:  Find
  ȫ��:  LONG CHWXString::Find( LONG nStartIndex, LPCWSTR )
  ����:  public 
  ����ֵ:  LONG: 
  ����:  ���� 
  ����:  LONG nStartIndex: 
  ����:  char * pchStringToFind: 
  ************************************************************************/
  LONG Find(LONG , LPCWSTR);
  LONG Find(LPCWSTR);
  LONG Find(LONG ,WCHAR);
  LONG Find(WCHAR );
  LONG FindNoCase(LONG , LPCWSTR);
  LONG FindNoCase(LPCWSTR);
  LONG FindNoCase(LONG , WCHAR);
  LONG FindNoCase(WCHAR);  

  LONG ReverseFind(LONG , WCHAR);
  LONG ReverseFind(WCHAR );
  //////////////////////////////////////////////////////////////////////////
  CXStringW Left(LONG );
  CXStringW ExcludeLeft(LONG ); // remove first nCount chars
  CXStringW Mid(LONG , LONG );
  CXStringW Right(LONG );
  //thisΪ����������
  void InternalLeft(LONG); 
  void InternalExcludeLeft(LONG);   
  void InternalMid(LONG, LONG); 
  void InternalRight(LONG); 

  //����������  
  operator LPCWSTR () const;
  WCHAR operator[](LONG );
  CXStringW &operator =(LPCWSTR);  
  CXStringW &operator =(const CXStringW &);  
  CXStringW &operator +=(const CXStringW &);  
  CXStringW &operator +=(LPCWSTR);
  CXStringW &operator +=(const WCHAR &);  

  CXStringW operator +(const CXStringW &);
  CXStringW operator +(LPCWSTR);
  CXStringW operator +(const WCHAR & );

  //friend CXStringW operator+(const CXStringW &, const CXStringW &);
  //friend CXStringW operator+(const CXStringW &, LPCWSTR);
  friend CXStringW operator+(LPCWSTR, const CXStringW &);
  friend CXStringW operator+(const WCHAR &, const CXStringW &);

  BOOL operator ==(const CXStringW &) const;
  BOOL operator!=(const CXStringW &) const;
  BOOL operator ==(LPCWSTR) const;
  BOOL operator!=(LPCWSTR)const;
  BOOL operator==(const WCHAR) const;
  BOOL operator!=(const WCHAR) const;

  friend BOOL operator==(LPCWSTR, const CXStringW &);
  friend BOOL operator!=(LPCWSTR, const CXStringW &);
  friend BOOL operator!=(const WCHAR, const CXStringW &);  
  friend BOOL operator==(const WCHAR, const CXStringW &);
  /************************************************************************
  ����:  TrimLeft
  ȫ��:  void CHWXString::TrimLeft( WCHAR ch )
  ����:  public 
  ����ֵ:  void: 
  ����:  �޼����������ַ� 
  ����:  char ch: 
  ************************************************************************/
  void TrimLeft(const WCHAR );
  void TrimLeft(LPCWSTR = NULL);
  void TrimRight(const WCHAR );
  void TrimRight(LPCWSTR = NULL);
  void Trim(const WCHAR );
  void Trim(LPCWSTR = NULL);  

  /************************************************************************
  ����:  GetNumber
  ȫ��:  LONG CHWXString::GetNumber(  )
  ����:  public 
  ����ֵ:  LONG: 
  ����:  �����ַ����е����� 
  ************************************************************************/
  LONG  GetNumber();
  float  GetFloat();
  LONG  GetHex();
  /************************************************************************
  ����:  ReplaceChar
  ȫ��:  void CHWXString::ReplaceChar( char ch, char sReplacementChar )
  ����:  public 
  ����ֵ:  void: 
  ����:  �滻���� 
  ����:  char ch: 
  ����:  char sReplacementChar: 
  ************************************************************************/
  void ReplaceChar(const WCHAR , const WCHAR );
  void ReplaceCharWithString(const WCHAR , LPCWSTR); // szReplacementString==NULL allowed  
  void ReplaceCharWithString(const WCHAR , const CXStringW &);

	void Remove( const WCHAR);
  /************************************************************************
  ����:  Format
  ȫ��:  void Format(const char *pchFormat, ...)
  ����:  Public 
  ����ֵ:  void: 
  ����:  ��ʽ���ַ��� 
  ����:  const char *pchFormat:    �ο�printf
  ************************************************************************/
  void Format(LPCWSTR, ...);
  void FormatEx(LPCWSTR, ...);


  /************************************************************************
  ����:	Token
  ȫ��:	BOOL CHWXString::Token( const TCHAR *, std::vector<CHWXString> & )
  ����:	public 
  ����ֵ:	BOOL: 
  ����:	  ���ַ����ָ���ֶ���� 
  ����:	const TCHAR *: �ֶεķָ���
  ����:	std::vector<CHWXString> &: 
  ************************************************************************/
  BOOL Token(LPCWSTR, std::vector<CXStringW> &) const;
  BOOL Token(const WCHAR , std::vector<CXStringW> &) const;

  friend std::ostream &operator<<(std::ostream &, const CXStringW &a);
  //////////////////////////////////////////////////////////////////////////
  static CXStringW From(LPCSTR);
  static CXStringW From(LPCWSTR);
  static CXStringW From(LONG);
  static CXStringW From(DWORD);
  static CXStringW From(double);

  LPWSTR GetBuffer( const DWORD& dwSize);  
  void ReleaseBuffer();
protected:  
  /************************************************************************
  ����:  Reset
  ȫ��:  void CHWXString::Reset( const char *pchSource )
  ����:  private 
  ����ֵ:  void: 
  ����:  �������¸�ֵ 
  ����:  const char * pchSource: 
  ************************************************************************/
  void Reset(LPCWSTR);
  void Reset(LPCWSTR, LONG nLen);
  void Reset(const CXStringW &);

  //////////////////////////////////////////////////////////////////////////
  void Reserve(LONG nLen);
  //////////////////////////////////////////////////////////////////////////

  void Init();

  //////////////////////////////////////////////////////////////////////////
  BOOL Strcat(LPCWSTR);
  BOOL Strcat(const CXStringW &);
  BOOL Strcat(LPCWSTR , LONG nDstLen);  
};

class DLLXEXPORT CXStringA
{  
private:  
  CHWXPackage m_tPackage;  
  LONG m_nIncStep;
  LONG m_nLength;
public:
  // Constructor/Destructor
  CXStringA();  
  CXStringA(LPCSTR);  
  explicit CXStringA(const CHAR&);
  CXStringA(LPCSTR, LONG nLen);
  CXStringA(const CXStringA &);   
  virtual ~CXStringA();  

	void AssertValid() const;
  /************************************************************************
  ����:  Clear
  ȫ��:  void CHWXString::Clear(  )
  ����:  public 
  ����ֵ:  void: 
  ����:  ����ַ� 
  ************************************************************************/
  void Clear();

  /************************************************************************
  ����:  StrLen
  ȫ��:  LONG CHWXString::StrLen(  ) const
  ����:  public 
  ����ֵ:  LONG: 
  ����:  ��ȡ������ 
  ************************************************************************/
  LONG StrLen() const;
  /************************************************************************
  ����:  IsEmpty
  ȫ��:  bool CHWXString::IsEmpty(  ) const
  ����:  public 
  ����ֵ:  bool: 
  ����:  �Ƿ�Ϊ�� 
  ************************************************************************/
  BOOL IsEmpty() const;

  /************************************************************************
  ����:  C_Str
  ȫ��:  char * CHWXString::GetData(  ) const
  ����:  public 
  ����ֵ:  char *: 
  ����:  ��ȡ����
  ************************************************************************/
  LPCSTR C_Str() const;


  CHAR GetAt(LONG );  
  BOOL SetAt(LONG , CHAR );
  //////////////////////////////////////////////////////////////////////////
  //��ת�ַ���
  void Reverse();
  //�ַ�����λ
  LONG FirstBelong(LPCSTR);
  LONG FirstNoBelong(LPCSTR);
  BOOL IsBelong(LPCSTR);
  BOOL IsNoBelong(LPCSTR);
  /************************************************************************
  ����:  MakeLower
  ȫ��:  void CHWXString::MakeLower(  )
  ����:  public 
  ����ֵ:  void: 
  ����:  ��Сд�任 
  ************************************************************************/
  void MakeLower();
  void MakeUpper();

  /************************************************************************
  ����:  Compare
  ȫ��:  bool CHWXString::Compare( const char *pchCompareString )
  ����:  public 
  ����ֵ:  bool: 
  ����:  �Ƚ� 
  ����:  const char * pchCompareString: 
  ************************************************************************/
  BOOL Compare(LPCSTR) const;
  BOOL Compare(const CXStringA &) const;
  BOOL CompareNoCase(LPCSTR) const;
  BOOL CompareNoCase(const CXStringA &) const;  

  /************************************************************************
  ����:  Find
  ȫ��:  LONG CHWXString::Find( LONG nStartIndex, LPCWSTR )
  ����:  public 
  ����ֵ:  LONG: 
  ����:  ���� 
  ����:  LONG nStartIndex: 
  ����:  char * pchStringToFind: 
  ************************************************************************/
  LONG Find(LONG , LPCSTR);
  LONG Find(LPCSTR);
  LONG Find(LONG ,CHAR);
  LONG Find(CHAR );
  LONG FindNoCase(LONG , LPCSTR);
  LONG FindNoCase(LPCSTR);
  LONG FindNoCase(LONG , CHAR);
  LONG FindNoCase(CHAR);  

  LONG ReverseFind(LONG , CHAR);
  LONG ReverseFind(CHAR );
  //////////////////////////////////////////////////////////////////////////
  CXStringA Left(LONG );
  CXStringA ExcludeLeft(LONG ); // remove first nCount chars
  CXStringA Mid(LONG , LONG );
  CXStringA Right(LONG );
  //thisΪ����������
  void InternalLeft(LONG); 
  void InternalExcludeLeft(LONG);   
  void InternalMid(LONG, LONG); 
  void InternalRight(LONG); 

  //����������  
  operator LPCSTR () const;
  CHAR operator[](LONG );
  CXStringA &operator =(LPCSTR);  
  CXStringA &operator =(const CXStringA &);  
  CXStringA &operator +=(const CXStringA &);  
  CXStringA &operator +=(LPCSTR);
  CXStringA &operator +=(const CHAR&);  

  CXStringA operator +(const CXStringA &);
  CXStringA operator +(LPCSTR);
  CXStringA operator +(const CHAR );

  //friend CXStringA operator+(const CXStringA &, const CXStringA &);
  //friend CXStringA operator+(const CXStringA &, LPCSTR);
  friend CXStringA operator+(LPCSTR, const CXStringA &);
  friend CXStringA operator+(const CHAR &, const CXStringA&);

  BOOL operator ==(const CXStringA &) const;
  BOOL operator!=(const CXStringA &) const;
  BOOL operator ==(LPCSTR) const;
  BOOL operator!=(LPCSTR)const;
  BOOL operator==(const CHAR) const;
  BOOL operator!=(const CHAR) const;

  friend BOOL operator==(LPCSTR, const CXStringA &);
  friend BOOL operator!=(LPCSTR, const CXStringA &);
  friend BOOL operator!=(const CHAR, const CXStringA &);  
  friend BOOL operator==(const CHAR, const CXStringA &);
  /************************************************************************
  ����:  TrimLeft
  ȫ��:  void CHWXString::TrimLeft( WCHAR ch )
  ����:  public 
  ����ֵ:  void: 
  ����:  �޼����������ַ� 
  ����:  char ch: 
  ************************************************************************/
  void TrimLeft(const CHAR );
  void TrimLeft(LPCSTR = NULL);
  void TrimRight(const CHAR );
  void TrimRight(LPCSTR = NULL);
  void Trim(const CHAR );
  void Trim(LPCSTR = NULL);  

  /************************************************************************
  ����:  GetNumber
  ȫ��:  LONG CHWXString::GetNumber(  )
  ����:  public 
  ����ֵ:  LONG: 
  ����:  �����ַ����е����� 
  ************************************************************************/
  LONG  GetNumber();
  float  GetFloat();
  LONG  GetHex();
  /************************************************************************
  ����:  ReplaceChar
  ȫ��:  void CHWXString::ReplaceChar( char ch, char sReplacementChar )
  ����:  public 
  ����ֵ:  void: 
  ����:  �滻���� 
  ����:  char ch: 
  ����:  char sReplacementChar: 
  ************************************************************************/
  void ReplaceChar(const CHAR , const CHAR );
  void ReplaceCharWithString(const CHAR , LPCSTR); // szReplacementString==NULL allowed  
  void ReplaceCharWithString(const CHAR , const CXStringA &);
	
	void Remove(const CHAR);
  /************************************************************************
  ����:  Format
  ȫ��:  void Format(const char *pchFormat, ...)
  ����:  Public 
  ����ֵ:  void: 
  ����:  ��ʽ���ַ��� 
  ����:  const char *pchFormat:    �ο�printf
  ************************************************************************/
  void Format(LPCSTR, ...);
  void FormatEx(LPCSTR, ...);


  /************************************************************************
  ����:	Token
  ȫ��:	BOOL CHWXString::Token( const TCHAR *, std::vector<CHWXString> & )
  ����:	public 
  ����ֵ:	BOOL: 
  ����:	  ���ַ����ָ���ֶ���� 
  ����:	const TCHAR *: �ֶεķָ���
  ����:	std::vector<CHWXString> &: 
  ************************************************************************/
  BOOL Token(LPCSTR, std::vector<CXStringA> &) const;
  BOOL Token(const CHAR , std::vector<CXStringA> &) const;

  friend std::ostream &operator<<(std::ostream &, const CXStringA &a);
  static CXStringA  From(LPCWSTR);
  static CXStringA  From(LPCSTR);
  static CXStringA From(LONG);
  static CXStringA From(DWORD);
  static CXStringA From(double);

  LPSTR GetBuffer(const DWORD&);
  void ReleaseBuffer();
protected:  
  /************************************************************************
  ����:  Reset
  ȫ��:  void CHWXString::Reset( const char *pchSource )
  ����:  private 
  ����ֵ:  void: 
  ����:  �������¸�ֵ 
  ����:  const char * pchSource: 
  ************************************************************************/
  void Reset(LPCSTR);
  void Reset(LPCSTR, LONG nLen);
  void Reset(const CXStringA &);

  //////////////////////////////////////////////////////////////////////////
  void Reserve(LONG nLen);
  //////////////////////////////////////////////////////////////////////////

  void Init();

  //////////////////////////////////////////////////////////////////////////
  BOOL Strcat(LPCSTR);
  BOOL Strcat(const CXStringA &);
  BOOL Strcat(LPCSTR , LONG nDstLen);  
};


#endif //HWXUE_CString_H_INC


