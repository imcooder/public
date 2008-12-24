#include "StdAfx.h"
#include "Asci.h"

//是否是数字
BOOL WINAPI Asci_IsDigit( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if( ch > '9' || ch < '0' )
		return 0;
	return 1;
}

//是否是16进制数学字符(即0-9 A-F a-f )
BOOL WINAPI Asci_IsXDigit( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if( ( ch >= '0' && ch <= '9' )//Digit 
	 || ( ch >= 'A' && ch <= 'F' )//upper hex digit
	 || ( ch >= 'a' && ch <= 'f' ) )//lower hex digit
		return 1;
	return 0;
}

//是否控制字符
BOOL WINAPI Asci_iscntrl( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	//if (ptConstPara->m_abCharaAttribute[ch] & 0x20)
	//	return 1;
	//else
		return 0;
}

//是否空格、跳格符(制表符)或换行符
BOOL WINAPI Asci_isspace( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	//if (ptConstPara->m_abCharaAttribute[ch] & 0x40)
	//	return 1;
	//else
		return 0;
}

//是否是大写字母
BOOL WINAPI Asci_IsUpper( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if ( ch >= 'A' && ch <= 'Z' )
		return 1;
	return 0;
}

//是否是小写字母
BOOL WINAPI Asci_IsLower( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if ( ch >= 'a' && ch <= 'z' )
		return 1;
	return 0;
}

//是否是字母
BOOL WINAPI Asci_IsAlpha( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if ( (ch >= 'A' && ch <= 'Z')
	  || (ch >= 'a' && ch <= 'z') )
		return 1;
	return 0;
}

BOOL WINAPI Asci_IsPunctuation( LONG ch )
{
	if (ch < 0x7F)
	{
		if (!Asci_IsAlpha(ch) && !Asci_IsDigit(ch))
		{
			return 1;
		}
	}
	return 0;
}

WCHAR WINAPI Asci_HalfToFull( WCHAR wCharInput)
{	
	WCHAR wChar = wCharInput;
	if (wCharInput == TEXT(' '))
	{
		wChar = 0x3000;			
	}
	else if (wCharInput <= 0x7F)
	{
		wChar = wCharInput + 0xFEE0;
	}			
	return wChar;
}

BOOL WINAPI Asci_IsBelongTo( WCHAR wChr, LPCWSTR pszCharSet)
{
	if (!pszCharSet)
	{
		return FALSE;
	}
	LPWSTR pszPos = wcschr((LPWSTR)pszCharSet, wChr);
	if (!pszPos)
	{
		return FALSE;
	}
	return TRUE;
}