#ifndef HWX_EXT_TYPE_H
#define HWX_EXT_TYPE_H

#include <assert.h>
#include <wtypes.h> 
#include <CRTDbg.h>
#include <tchar.h>
#ifdef XEXPORT
#define DLLXEXPORT   __declspec(dllexport) 
#else
#define DLLXEXPORT   //__declspec(dllimport) 
#endif


//////////////////////////////////////////////////////////////////////////
#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
typedef  unsigned char     BYTE;
#endif 
#ifndef _LPBYTE_DEFINED
#define _LPBYTE_DEFINED
typedef  BYTE*             LPBYTE;
#endif 
#ifndef _LPCBYTE_DEFINED
#define _LPCBYTE_DEFINED
typedef const BYTE *			 LPCBYTE;
#endif
//////////////////////////////////////////////////////////////////////////
#ifndef _CHAR_DEFINED
#define _CHAR_DEFINED
typedef     char             CHAR;
#endif
#ifndef _LPSTR_DEFINED
#define _LPSTR_DEFINED
typedef     CHAR*						 LPSTR;
#endif
#ifndef _LPCSTR_DEFINED
#define _LPCSTR_DEFINED
typedef     const CHAR*      LPCSTR;
#endif
//////////////////////////////////////////////////////////////////////////
#ifndef _SHORT_DEFINED
#define _SHORT_DEFINED
typedef		short								SHORT;
#endif // !_SHORT_DEFINED
#ifndef _LPSHORT_DEFINED
#define _LPSHORT_DEFINED
typedef		SHORT*							LPSHORT;
#endif // !_LPSHORT_DEFINED
#ifndef _LPCSHORT_DEFINED
#define _LPCSHORT_DEFINED
typedef		const SHORT*				LPCSHORT;
#endif // !_LPCSHORT_DEFINED

//////////////////////////////////////////////////////////////////////////
#ifndef _LONG_DEFINED
#define _LONG_DEFINED
typedef		long								LONG;
#endif // !_LONG_DEFINED
#ifndef _LPLONG_DEFINED
#define _LPLONG_DEFINED
typedef		LONG*									LPLONG;
#endif // !_LPLONG_DEFINED
#ifndef _LPCLONG_DEFINED
#define _LPCLONG_DEFINED
typedef const LONG*						LPCLONG;
#endif // !_LPCLONG_DEFINED

//////////////////////////////////////////////////////////////////////////
#ifndef _LPVOID_DEFINED
#define _LPVOID_DEFINED
typedef void *							LPVOID;
#endif
#ifndef _LPCVOID_DEFINED
#define _LPCVOID_DEFINED
typedef const void *				LPCVOID;
#endif
//////////////////////////////////////////////////////////////////////////
#ifndef _WORD_DEFINED
#define _WORD_DEFINED
typedef  unsigned short    WORD;
#endif 
#ifndef _LPWORD_DEFINED
#define _LPWORD_DEFINED
typedef  WORD*             LPWORD;
#endif
#ifndef _LPCWORD_DEFINED
#define _LPCWORD_DEFINED
typedef  const WORD*       LPCWORD;
#endif
//////////////////////////////////////////////////////////////////////////
#ifndef _DWORD_DEFINED
#define _DWORD_DEFINED
typedef   unsigned long     DWORD;
#endif
#ifndef _LPDWORD_DEFINED
#define _LPDWORD_DEFINED
typedef   DWORD*            LPDWORD;
#endif
#ifndef _LPCDWORD_DEFINED
#define _LPCDWORD_DEFINED
typedef     const DWORD*      LPCDWORD;
#endif

//////////////////////////////////////////////////////////////////////////
#ifndef	_WCHAR_T_DEFINED
#define	_WCHAR_T_DEFINED
typedef unsigned short				wchar_t;
#endif //_WCHAR_T_DEFINED
#ifndef _WCHAR_DEFINED
#define _WCHAR_DEFINED
typedef     wchar_t           WCHAR;
#endif //_WCHAR_DEFINED
#ifndef _LPWSTR_DEFINED
#define _LPWSTR_DEFINED
typedef     WCHAR *           LPWSTR;
#endif //_LPWSTR_DEFINED
#ifndef _LPCWSTR_DEFINED
#define _LPCWSTR_DEFINED
typedef     const WCHAR *     LPCWSTR; 
#endif //_LPCWSTR_DEFINED
//////////////////////////////////////////////////////////////////////////
#ifndef _LPCWSTR_DEFINED
#define _LPCWSTR_DEFINED
typedef     const WCHAR *     LPCWSTR; 
#endif //_LPCWSTR_DEFINED
//////////////////////////////////////////////////////////////////////////
#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
typedef unsigned int size_t;
#endif //_SIZE_T_DEFINED
//////////////////////////////////////////////////////////////////////////

typedef  TCHAR *  LPTSTR;
typedef  const TCHAR *				LPCTSTR;
//////////////////////////////////////////////////////////////////////////


#ifndef BOOL
typedef int     BOOL;
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef TRUE 
#define TRUE      1
#endif

#ifndef FALSE
#define FALSE     0
#endif

#ifndef NULL
#define NULL      0
#endif

#ifndef VOID
#define VOID      void
#endif

#ifndef HANDLE
typedef void*     HANDLE; 
#endif


typedef enum
{
	SUCCESS							=				0L,
	INVALID_FUNCTION		=       1L,
	FILE_NOT_FOUND      =       2L,
	INVALID_HANDLE			=       6L,
	NOT_ENOUGH_MEMORY		=       8L,
	INVALID_DATA				=       13L
} TError;



#ifndef ASSERT
#define ASSERT(str)		_ASSERT(str)
#endif

#ifndef assert
#define assert(str)		ASSERT(str)
#endif

#ifndef VERIFY
#ifdef _DEBUG
#define VERIFY(f)          assert((f))//_ASSERT((f))
#else
#define VERIFY(f)          ((void)(f))
#endif    
#endif
#define verify   VERIFY

#ifndef _abs
#define _abs(a) (((a)>0)?(a):(-(a)))
#endif

#ifndef _max
#define _max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef  _min
#define _min(a,b) ((a)<(b)?(a):(b))
#endif

#define _swap(a,b) {(a)^=(b);(b)^=(a);(a)^=(b);}

#ifndef _min3
#define  _min3(a, b, c) (_min(_min((a), (b)), (c)))
#endif

#ifndef _max3
#define  _max3(a, b, c) (_max(_max((a), (b)), (c)))
#endif

#define INRANGE(low, Num, High) (((low) <= (Num)) && ((Num) <= (High)))

#define MIN_CHAR        (0x80)        
#define MAX_CHAR        (0x7f)        
#define MIN_SHORT       (0x8000)      
#define MAX_SHORT       (0x7fff)      
#define MIN_LONG        (0x80000000)  
#define MAX_LONG        (0x7fffffff)  
#define MAX_BYTE        (0xff) 
#define MIN_WORD        (0x0)
#define MAX_WORD        (0xffff)  
#define MIN_DWORD       (0x0)
#define MAX_DWORD       (0xffffffff) 

#ifndef MAX_PATH
#define MAX_PATH          (512)
#endif
#define MAX_DRIVE         (3)  
#define MAX_DIR           (512) 
#define MAX_FNAME         (512) 
#define MAX_EXT           (512)
#define MAX_DIR						(512)
#ifndef MAX_NAME
#define MAX_NAME          MAX_PATH
#endif

#ifndef MAX_SIZE_S
#define MAX_SIZE_SS						(128)	
#define MAX_SIZE_S						(256)	
#define MAX_SIZE_M						(512)	
#define MAX_SIZE_L						(1024)
#define MAX_SIZE_LL						(2048)
#endif

#ifndef MAKEWORD
#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD)(a) & 0xff))   | ((WORD)((BYTE)((DWORD)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))
#endif
//笔画结束标记

//pot数据包头长度
#define    X_HEADERSIZE_POT        (0x6)


//高级结构
#ifndef _T_Point_
#define _T_Point_
typedef struct tagTPoint
{
	SHORT  x;
	SHORT  y;
} TPoint, *LPTPoint;
#endif

typedef struct tagCnd4
{
	WORD  m_wDistance;  
	WORD  m_wIndex;
} TCnd4, *LPTCnd4;

typedef struct tagCnd8
{
	int    m_nIndex;
	int    m_nDistance;
}TCnd8, *LPTCnd8;
//函数参数前 表示传入, 传出
#define HWX_IN    
#define HWX_OUT   
#define HWX_IN_OUT


#ifndef PIE
#define     PIE         (3.14159265358979323846)
#define     PIE_2       (1.57079632679489661923)
#define     PIE_4       (0.785398163397448309616)
#endif

#define HW_StrokeEndMark  (-1)


#ifndef ZeroMemory 
#define ZeroMemory(pVoid, nLen) memset((pVoid), 0, (nLen))
#endif

//#define SAFE_DELETE(ptr)
#undef SAFE_DELETE
#define SAFE_DELETE(ptr) \
	if ((ptr))\
{ \
	delete (ptr);\
	(ptr) = NULL; \
}

//#define SAFE_DELETE_AR(ptr)
#undef SAFE_DELETE_AR
#define SAFE_DELETE_AR(ptr) \
	if ((ptr)) \
{ \
	delete [] (ptr); \
	(ptr) = NULL; \
}

//#define SAFE_DELETE_HICON(hIcon)
#undef SAFE_DELETE_HICON
#define SAFE_DELETE_HICON(hIcon) \
	if ((hIcon)) \
{\
	::DestroyIcon((hIcon)); \
	(hIcon) = NULL;\
}

#undef SAFE_DELETE_HMENU
#define SAFE_DELETE_HMENU(hMenu) \
	if(hMenu) \
{ \
	::DestroyMenu(hMenu); \
	hMenu = NULL; \
}

//#define SAFE_DELETE_OBJECT(obj)
#undef SAFE_DELETE_OBJECT
#define SAFE_DELETE_OBJECT(hObj) \
	if (hObj) \
{\
	::DeleteObject(hObj);\
	hObj = NULL;\
}

#undef SAFE_FREE_LIBRARY
#define SAFE_FREE_LIBRARY(hModel) \
	if (hModel)\
{\
	::FreeLibrary(hModel);\
	hModel = NULL;\
}

#undef SAFE_CLOSE_HANDLE
#define SAFE_CLOSE_HANDLE(hHandle) \
	if (hHandle)\
{\
	::CloseHandle(hHandle);\
	hHandle = NULL;\
} 


#undef SAFE_DESTROY_WINDOW
#define SAFE_DESTROY_WINDOW(hWindow) \
	if (::IsWindow(hWindow))\
{\
	::DestroyWindow(hWindow);\
	hWindow = NULL;\
} 


#undef SAFE_DELETE_DC
#define SAFE_DELETE_DC(hDC) \
	if (hDC)\
{\
	::DeleteDC(hDC);\
	hDC = NULL;\
} 

#endif//HWXUE_EXT_TYPE_H_INC

