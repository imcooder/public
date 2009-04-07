

#ifndef HWX_RECT_H
#define HWX_RECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <windef.h>

BOOL WINAPI IsRectNULL(const RECT *);
BOOL WINAPI MoveRectTo(LPRECT, int, int);
#endif //HWX_RECT_H
