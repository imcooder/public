

#include "stdafx.h"
#include "Asci.h" 
#include "UCSUTF.h"
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


/* 转换UCS4编码或者UCS2编码到UTF8编码 */
int Conv_UCS4_To_UTF8( unsigned long dwCode, unsigned char* pUTF8Str )
{
	int i, iLen;
	unsigned char bSum, bStep;

	if( dwCode < 0x10000 )
	{
		if( dwCode < 0x80 )				// U+00000000 ～ U+0000007F
			iLen = 1;
		else if( dwCode < 0x800 )		// U+00000080 ～ U+000007FF
			iLen = 2;
		else							// U+00000800 ～ U+0000FFFF
			iLen = 3;
	}
	else
	{
		if( dwCode < 0x200000 )			// U+00010000 ～ U+001FFFFF
			iLen = 4;
		else if( dwCode < 0x4000000 )	// U+00200000 ～ U+03FFFFFF
			iLen = 5;
		else if( dwCode < 0x80000000 )	// U+04000000 ～ U+7FFFFFFF
			iLen = 6;
		else
			return 0;					// 无效的UCS4编码
	}

	if( pUTF8Str != NULL )
	{
		bSum = 0;
		bStep = 0x80;
		for( i = iLen - 1; i >= 0; i-- )
		{
			bSum += bStep;
			bStep >>= 1;
			if( i == 0 )
			{
				if( iLen != 1 )dwCode += bSum;
				pUTF8Str[i] = (unsigned char)dwCode;
			}
			else
			{
				pUTF8Str[i] = (unsigned char)(dwCode % 64 + 0x80);
				dwCode >>= 6;
			}
		}
	}

	return iLen;
}

/* 转换UTF8编码到UCS4编码 */
int Conv_UTF8_To_UCS4( const unsigned char* pUTF8Str, unsigned long* pdwCode )
{
	int i, iLen;
	unsigned char b;
	unsigned long dwCode;

	b = *pUTF8Str++;
	if( b < 0x80 )
	{
		dwCode = b;
		*pdwCode = dwCode;
		return 1;
	}

	if( b < 0xC0 || b > 0xFD )return 0; /* 非法UTF8 */

	if( b < 0xE0 )
	{
		dwCode = b & 0x1F;
		iLen = 2;
	}
	else if( b < 0xF0 )
	{
		dwCode = b & 0x0F;
		iLen = 3;
	}
	else if( b < 0xF8 )
	{
		dwCode = b & 7;
		iLen = 4;
	}
	else if( b < 0xFC )
	{
		dwCode = b & 3;
		iLen = 5;
	}
	else
	{
		dwCode = b & 1;
		iLen = 6;
	}

	for( i = 1; i < iLen; i++ )
	{
		b = *pUTF8Str++;
		if( b < 0x80 || b > 0xBF ) /* 非法UTF8 */
			break;

		dwCode = (dwCode << 6) + (b - 0x80);			
	}

	if( i < iLen )
		return 0;
	else
	{
		*pdwCode = dwCode;
		return iLen;
	}
}

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

/*

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
}*/


DLLXEXPORT LONG WINAPI UTF32ToUTF16( const DWORD* pdwUCS4,SIZE_T nCount, LPWSTR pszUTF16 )
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

/* 转换UTF16编码到UCS4编码 */
LONG WINAPI UTF16ToUTF32( LPCWSTR pUTF16Str, LPDWORD pdwCode )
{
	WCHAR w1 = 0, w2 = 0;

	w1 = pUTF16Str[0];
	if( w1 >= 0xD800 && w1 <= 0xDBFF )
	{
		w2 = pUTF16Str[1];
		if( w2 >= 0xDC00 && w2 <= 0xDFFF )
		{
			*pdwCode = (w2 & 0x03FF) + (((w1 & 0x03FF) + 0x40) << 10);
			return 2;
		}
		else
		{
			return 0;	// 非法UTF16编码
		}
	}
	else
	{
		*pdwCode = w1;
		return 1;
	}
}

LPWSTR WINAPI HWCharNext( LPCWSTR pszStr)
{
	LPWSTR pszNext = (LPWSTR)pszStr;	
	if (!pszNext)
	{
		return pszNext;
	}	
	WCHAR w1 = 0, w2 = 0;
	DWORD dwLen = wcslen(pszNext);		
	w1 = pszNext[0];
	if( w1 >= 0xD800 && w1 <= 0xDBFF )
	{
		w2 = pszNext[1];
		if( w2 >= 0xDC00 && w2 <= 0xDFFF )
		{			
			pszNext += 2;
		}
		else
		{
			pszNext = NULL;
		}
	}
	else
	{
		pszNext += 1;
	}
	return pszNext;
}
LONG WINAPI HWCharCount( LPCWSTR pszStr)
{
	if (!pszStr)
	{
		return -1;
	}
	LONG nCount = 0;	
	LPCTSTR pszIndex = pszStr;	
	while(pszIndex[0])
	{		
		nCount ++;
		pszIndex = HWCharNext(pszIndex);		
	}
	return nCount;
}
LPWSTR WINAPI HWStrLocate(LPCWSTR pszStr, DWORD dwIdx)
{
	LPWSTR pszLocate = (LPWSTR)pszStr;
	if (!pszStr)
	{
		return pszLocate;
	}		
	while (pszLocate && pszLocate[0] && dwIdx)
	{
		dwIdx --;
		pszLocate = HWCharNext(pszLocate);
	}
	if (dwIdx)
	{
		pszLocate = NULL;
	}
	else if (pszLocate && !pszLocate[0])
	{
		pszLocate = NULL;
	}
	return pszLocate;
}

DWORD WINAPI HWGetChar(LPCWSTR pszStr, DWORD dwIdx)
{
	DWORD dwCode = 0;
	LPWSTR pszLocate = HWStrLocate(pszStr, dwIdx);
	if (pszLocate)
	{
		WORD w1 = pszLocate[0];
		if( w1 >= 0xD800 && w1 <= 0xDBFF )
		{
			WORD w2 = pszLocate[1];
			if( w2 >= 0xDC00 && w2 <= 0xDFFF )
			{			
				dwCode = MAKELONG(w2, w1);
			}
			else
			{
				dwCode = 0;
			}
		}
		else
		{
			dwCode = MAKELONG(w1, 0);
		}
	}
	return dwCode;
}
LPWSTR WINAPI HWCharPrev(LPCWSTR lpszStart, LPCWSTR lpszCurrent)
{
	if (!lpszStart || !lpszCurrent)
	{
		return NULL;
	}
	WCHAR w1 = 0, w2 = 0;
	LPTSTR pszPre = NULL;
	if (lpszCurrent <= lpszStart)
	{
		return NULL;
	}
	if (0 >= lpszCurrent - lpszStart)
	{
		return NULL;
	}
	else if (1 == lpszCurrent - lpszStart)
	{
		w2 = *lpszStart;
		if( !(w2 >= 0xD800 && w2 <= 0xDBFF) )
		{
			pszPre = (LPWSTR)lpszStart;
		}		
	}
	else if (1 < lpszCurrent - lpszStart)
	{
		w1 = *(lpszCurrent - 2);
		w2 = *(lpszCurrent - 1);
		if( w1 >= 0xD800 && w1 <= 0xDBFF )
		{			
			if( w2 >= 0xDC00 && w2 <= 0xDFFF )
			{			
				pszPre = (LPWSTR)(lpszCurrent - 2);
			}
			else
			{
				pszPre = NULL;	
			}
		}
		else
		{
			if (!(w2 >= 0xD800 && w2 <= 0xDBFF))
			{
				pszPre = (LPWSTR)(lpszCurrent - 1);
			}
			else 
			{
				pszPre = NULL;
			}
		}
	}	
	return pszPre;
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
