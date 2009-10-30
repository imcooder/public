#include "stdafx.h"
#include "HWHash.h"
#include <StrSafe.h>

unsigned long HWSDBMHash(const char *str)
{
	unsigned long hash = 0;
	while (*str)
	{
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}
	return (hash & 0x7FFFFFFF);
}

// RS Hash 
unsigned long HWRSHash(const char *str)
{
	unsigned long b = 378551;
	unsigned long a = 63689;
	unsigned long hash = 0;
	while (*str)
	{
		hash = hash * a + (*str++);
		a *= b;
	}
	return (hash & 0x7FFFFFFF);
}

// JS Hash 
unsigned long HWJSHash(const char *str)
{
	unsigned long hash = 1315423911;
	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}
	return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash 
unsigned long HWPJWHash(const char *str)
{
	unsigned long BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	unsigned long ThreeQuarters	= (unsigned int)((BitsInUnignedInt  * 3) / 4);
	unsigned long OneEighth = (unsigned int)(BitsInUnignedInt / 8);
	unsigned long HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
	unsigned long hash	= 0;
	unsigned long test	= 0;
	while (*str)
	{
		hash = (hash << OneEighth) + (*str++);
		if ((test = hash & HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}
	return (hash & 0x7FFFFFFF);
}

// ELF Hash 
unsigned long HWELFHash(const char *str)
{
	unsigned long hash = 0;
	unsigned long x	= 0;
	while (*str)
	{
		hash = (hash << 4) + (*str++);
		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}
	return (hash & 0x7FFFFFFF);
}

// BKDR Hash 
unsigned long HWBKDRHash(const char *str)
{
	unsigned long seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned long hash = 0;
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

// DJB Hash 
unsigned long HWDJBHash(const char *str)
{
	unsigned long hash = 5381;
	while (*str)
	{
		hash += (hash << 5) + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

// AP Hash 
unsigned long HWAPHash(const char *str)
{
	unsigned long hash = 0;
	long i;
	for (i=0; *str; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}
	return (hash & 0x7FFFFFFF);
}