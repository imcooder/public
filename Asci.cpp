#include "StdAfx.h"
#include "Asci.h"

//是否是数字
BOOL WINAPI Asci_isdigit( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if( ch > '9' || ch < '0' )
		return 0;
	return 1;
}

//是否是16进制数学字符(即0-9 A-F a-f )
BOOL WINAPI Asci_isxdigit( LONG ch)
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
BOOL WINAPI Asci_isupper( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if ( ch >= 'A' && ch <= 'Z' )
		return 1;
	return 0;
}

//是否是小写字母
BOOL WINAPI Asci_islower( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if ( ch >= 'a' && ch <= 'z' )
		return 1;
	return 0;
}

//是否是字母
BOOL WINAPI Asci_isalpha( LONG ch)
{
	if (ch < 0)
		ch += 256;
	
	if ( (ch >= 'A' && ch <= 'Z')
	  || (ch >= 'a' && ch <= 'z') )
		return 1;
	return 0;
}
