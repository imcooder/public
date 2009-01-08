

#include "stdafx.h"
#include "Asci.h" 
#include "UCSUTF.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

LONG WINAPI UTF16ToUTF8( LPCWSTR pszUTF16, LPSTR pszUTF8 )
{
	if (!pszUTF16)
	{
		return -1;
	}	
	LONG nLen = WideCharToMultiByte( CP_UTF8, 0, pszUTF16,	-1,	NULL, 0, NULL, NULL );
	if (pszUTF8)
	{
		nLen = WideCharToMultiByte( CP_UTF8, 0, pszUTF16,	-1, pszUTF8, nLen, NULL, NULL );
		pszUTF8[nLen] = 0;
	}	
	return nLen;
}

LONG WINAPI UTF8ToUTF16( LPCSTR pszUTF8, LPWSTR pszUTF16 )
{	
	LONG nLen = MultiByteToWideChar( CP_UTF8, 0, pszUTF8, 	-1,	NULL, 0);
	if (pszUTF16)
	{
		nLen = MultiByteToWideChar( CP_UTF8, 0, pszUTF8, -1,	pszUTF16, nLen);
		pszUTF16[nLen] = 0;
	}			
	return nLen;
}

DLLXEXPORT LONG WINAPI UCS4ToUTF16( const DWORD* pdwUCS4,SIZE_T nCount, LPWSTR pszUTF16 )
{	
	LONG nLen = 0;
	for (LONG nIndex = 0; nIndex < nCount; nIndex ++)
	{
		DWORD dwCode = pdwUCS4[nIndex];
		if (dwCode <= 0xFFFF)
		{
			if (pszUTF16)
			{
				pszUTF16[nLen] = dwCode & 0x0000FFFF;
			}
			nLen ++;			
		}
		else
		{
			dwCode -= 0x0010000UL;
			if (pszUTF16)
			{
				pszUTF16[nLen] = (WORD)((dwCode >> 10) + 0xD800);
				pszUTF16[nLen + 1] = (WORD)((dwCode & 0x03FFUL) + 0xDC00);
			}
			nLen += 2;			
		}
	}
	if (pszUTF16)
	{
		pszUTF16[nLen] = 0;
	}
	return nLen;
}
/*
LONG WINAPI UTF16ToUTF8(LPCWSTR pszUTF16, CHAR* pszUTF8)
{		
	if (!pszUTF16)
	{
		return -1;
	}
	LONG nLen = (LONG)wcslen(pszUTF16);
	LONG nNeed = 0;
	for (int i = 0; i < nLen; i ++)
	{
		if (pszUTF16[i] < 0x80)
		{
			if (pszUTF8)
			{
				pszUTF8[nNeed] = static_cast<char>(pszUTF16[i]);
			}			
			nNeed ++;
		}
		else if (pszUTF16[i] < 0x800)
		{
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0xc0 | pszUTF16[i] >> 6);
			}		
			nNeed ++;
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0x80 | pszUTF16[i] & 0x3f);
			}			
			nNeed ++;
		}
		else if (pszUTF16[i] < 0xd800 || pszUTF16[i] > 0xdbff)
		{
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0xe0 | pszUTF16[i] >> 12);
			}			
			nNeed ++;
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0x80 | pszUTF16[i] >> 6 & 0x3f);
			}			
			nNeed ++;
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0x80 | pszUTF16[i] & 0x3f);
			}			
			nNeed ++;

		}
		else
		{
			unsigned int offset = 0x10000 - (0xd800 << 10) - 0xdc00;
			unsigned int codepoint = (pszUTF16[i] << 10) + pszUTF16[i + 1] + offset;
			i ++;
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0xf0 | codepoint >> 18);
			}			
			nNeed ++;
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0x80 | codepoint >> 12 & 0x3f);	
			}			
			nNeed ++;
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0x80 | codepoint >> 6 & 0x3f);
			}			
			nNeed ++;
			if (pszUTF8)
			{
				pszUTF8[nNeed] = (0x80 | codepoint & 0x3F);
			}			
			nNeed ++;
		}
	}	
	return nNeed;
}


enum { bit7=0x80, bit6=0x40, bit5=0x20, bit4=0x10, bit3=8, bit2=4, bit1=2, bit0=1 };
LONG WINAPI UTF8ToUTF16(const CHAR *pszUTF8, LPWSTR pszUTF16)
{
	if (!pszUTF8)
	{
		return -1;
	}	
	LONG nLen = 0;
	CHAR a = 0, b = 0, c = 0;	
	while (*pszUTF8)
	{
		a = *pszUTF8 ++;
		if ((a & (bit7|bit6|bit5))==(bit7|bit6)) 
		{ // 0x000080-0x0007ff
			{
				b=*pszUTF8++;
			}
			if (pszUTF16)
			{
				pszUTF16[nLen] = ((a & (bit4|bit3|bit2)) >> 2) * 0x100;
				pszUTF16[nLen] += (((a & (bit1|bit0)) << 6) | (b & (bit5|bit4|bit3|bit2|bit1|bit0)));
			}			
		}
		else if ((a & (bit7|bit6|bit5|bit4))==(bit7|bit6|bit5)) // 0x000800-0x00ffff
		{
			b = *pszUTF8 ++;
			c = *pszUTF8 ++;
			if (pszUTF16)
			{
				pszUTF16[nLen] = (((a & (bit3|bit2|bit1|bit0)) << 4) | ((b & (bit5|bit4|bit3|bit2)) >> 2)) * 0x100;
				pszUTF16[nLen] += (((b & (bit1|bit0)) << 6) | (c & (bit5|bit4|bit3|bit2|bit1|bit0)));
			}			
		}
		else 
		{
			if (pszUTF16)
			{
				pszUTF16[nLen] = (0);
				pszUTF16[nLen] += (a);
			}			
		}
		nLen ++;
	}	
	return nLen;
}
*/
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
