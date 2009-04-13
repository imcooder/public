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

#ifndef _countof
#define _countof
#define _countof(_Array) (sizeof(_Array) / sizeof(*_Array))
#endif


#define INRANGE(low, Num, High) (((low) <= (Num)) && ((Num) <= (High)))
//	
#ifndef POINTSTOPOINT
#define POINTSTOPOINT(pt, pts)                          \
{ (pt).x = (LONG)(SHORT)LOWORD(*(LONG*)&pts);   \
	(pt).y = (LONG)(SHORT)HIWORD(*(LONG*)&pts); }
#endif

#ifndef POINTTOPOINTS
#define POINTTOPOINTS(pt)      (MAKELONG((short)((pt).x), (short)((pt).y)))
#endif

#ifndef MAKEWPARAM
#define MAKEWPARAM(l, h)      ((WPARAM)(DWORD)MAKELONG((l), (h)))
#endif

#ifndef MAKELPARAM
#define MAKELPARAM(l, h)      ((LPARAM)(DWORD)MAKELONG((l), (h)))
#endif

#ifndef MAKELRESULT
#define MAKELRESULT(l, h)     ((LRESULT)(DWORD)MAKELONG((l), (h)))
#endif

#ifndef MAKEDWORD
#define MAKEDWORD							MAKELONG
#endif
// Language ID
#ifndef MAKELANGID
#define MAKELANGID(p, s)       ((((WORD  )(s)) << 10) | (WORD  )(p))
#endif

#ifndef PRIMARYLANGID
#define PRIMARYLANGID(lgid)    ((WORD  )(lgid) & 0x3ff)
#endif

#ifndef SUBLANGID
#define SUBLANGID(lgid)        ((WORD  )(lgid) >> 10)
#endif

//	
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
#define MAX_SIZE_SSS					(64)	
#define MAX_SIZE_SS						(128)	
#define MAX_SIZE_S						(256)	
#define MAX_SIZE_M						(512)	
#define MAX_SIZE_L						(1024)
#define MAX_SIZE_LL						(2048)
#define MAX_SIZE_LLL					(4096)
#endif

#ifndef MAKEWORD
#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD)(a) & 0xff))   | ((WORD)((BYTE)((DWORD)(b) & 0xff))) << 8))
#endif
#ifndef MAKEDWORD
#define MAKEDWORD						MAKELONG
#endif
#ifndef MAKELONG
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD)(b) & 0xffff))) << 16))
#endif
#ifndef LOWORD
#define LOWORD(l)           ((WORD)((DWORD)(l) & 0xffff))
#endif
#ifndef HIWORD
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))
#endif
#ifndef LOBYTE
#define LOBYTE(w)           ((BYTE)((DWORD)(w) & 0xff))
#endif
#ifndef HIBYTE
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

#undef SAFE_REG_CLOSEKEY
#define SAFE_REG_CLOSEKEY(hKey) \
	if (hKey)\
{\
	::RegCloseKey(hKey);\
	hKey = NULL;\
} 

//////////////////////////////////////////////////////////////////////////
#undef SetControlText
#define SetControlText(hWnd, nID, szText)			::SetWindowText(::GetDlgItem((hWnd), (nID)), (szText))

		



//////////////////////////////////////////////////////////////////////////

#define VK_0    0x030
#define VK_1    0x031
#define VK_2    0x032
#define VK_3    0x033
#define VK_4    0x034
#define VK_5    0x035
#define VK_6    0x036
#define VK_7    0x037
#define VK_8    0x038
#define VK_9    0x039
#define VK_A    0x041
#define VK_B    0x042
#define VK_C    0x043
#define VK_D    0x044
#define VK_E    0x045
#define VK_F    0x046
#define VK_G    0x047
#define VK_H    0x048
#define VK_I    0x049
#define VK_J    0x04A
#define VK_K    0x04B
#define VK_L    0x04C
#define VK_M    0x04D
#define VK_N    0x04E
#define VK_O    0x04F
#define VK_P    0x050
#define VK_Q    0x051
#define VK_R    0x052
#define VK_S    0x053
#define VK_T    0x054
#define VK_U    0x055
#define VK_V    0x056
#define VK_W    0x057
#define VK_X    0x058
#define VK_Y    0x059
#define VK_Z    0x05A

#define VK_OEM_NUMBER   0x90            // NumLock
#define VK_OEM_SCROLL   0x91            // ScrollLock
#define VK_OEM_SHIFT    0x92            // ShiftLock
#define VK_OEM_0        0x0B9           //
#ifndef VK_OEM_1
#define VK_OEM_1        0x0BA           // ';:' for US
#endif
#ifndef VK_OEM_PLUS
#define VK_OEM_PLUS     0x0BB           // '+' any country
#endif
#ifndef VK_OEM_COMMA
#define VK_OEM_COMMA    0x0BC           // ',' any country
#endif
#ifndef VK_OEM_MINUS
#define VK_OEM_MINUS    0x00BD          // '-' any country
#endif
#ifndef VK_OEM_PERIOD
#define VK_OEM_PERIOD   0x0BE           // '.' any country
#endif
#ifndef VK_OEM_2
#define VK_OEM_2        0x0BF           // '/?' for US
#endif
#ifndef VK_OEM_3
#define VK_OEM_3        0x0C0           // '`~' for US
#endif
#ifndef VK_OEM_4
#define VK_OEM_4        0x0DB           // '[{' for US
#endif
#ifndef VK_OEM_5
#define VK_OEM_5        0x0DC           // '\|' for US
#endif
#ifndef VK_OEM_6
#define VK_OEM_6        0x0DD           // ']}' for US
#endif
#ifndef VK_OEM_7
#define VK_OEM_7        0x0DE           // ''"' for US
#endif
#ifndef VK_OEM_8
#define VK_OEM_8        0x0DF           // none for US
#endif
#ifndef VK_OEM_9
#define VK_OEM_9        0x0E0           // next available
#endif
#ifndef VK_OEM_AX
#define VK_OEM_AX       0x0E1           // AX key
#endif
#ifndef VK_OEM_BSLASH
#define VK_OEM_BSLASH   0x0E2           // additional Back Slash key for AX.
#endif

//////////////////////////////////////////////////////////////////////////

#endif//HWXUE_EXT_TYPE_H_INC

