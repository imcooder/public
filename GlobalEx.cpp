
/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	GlobalEx.h					
�ļ�����:	    һЩȫ�ֺ���
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/03/22
*********************************************************************/

#include "stdafx.h"
#include "GlobalEx.h"
#include <mbstring.h>
const LONG cnInchToPoint = 72; //1 inch = 72 points
const LONG cnInchToTwip = 1440;// 1 inch = 1440 twips
const LONG cnInchToEMU = 914400; // 1 inch = 914400 EMUs


HWOSType WINAPI HWGetOSType()
{
  HWOSType tRet = OS__Unknown;
  OSVERSIONINFO osVer;
  ZeroMemory(&osVer, sizeof(osVer));
  osVer.dwOSVersionInfoSize = sizeof(osVer);
  GetVersionEx (&osVer);	
  if (osVer.dwMajorVersion < 6)
  {//��vista
    tRet = OS__XP;	
  }
  else
  {//vista
    tRet = OS__Vista;	
  }	
  return tRet;
}

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS)(HANDLE, PBOOL);
BOOL WINAPI Is64BitProcess()
{  
  BOOL	bIsWow64 = FALSE;
  HINSTANCE	hDll = NULL; 
  __try
  {	  
    hDll = LoadLibrary(TEXT("KERNEL32.DLL"));
    if( hDll )
    {
      LPFN_ISWOW64PROCESS  fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress( hDll, "IsWow64Process");

      if(fnIsWow64Process)
        fnIsWow64Process( GetCurrentProcess(), &bIsWow64 );		  
    }
  }
  __finally
  {
    if (hDll)
    {
      FreeLibrary(hDll);
    }
  }  
  return bIsWow64;
}
HWOSType WINAPI XGetOSType()
{
  HWOSType tRet = OS__Unknown;

  OSVERSIONINFO	tOSV;
  int				    iServicePack;
  TCHAR         *pthPointer;   
  ZeroMemory(&tOSV, sizeof( tOSV ) );
  tOSV.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&tOSV);
  for (pthPointer = tOSV.szCSDVersion; *pthPointer  && !isdigit(*pthPointer); pthPointer ++);
  iServicePack = _ttoi(pthPointer); 
  if (tOSV.dwPlatformId == VER_PLATFORM_WIN32_NT)
  {     
    switch(tOSV.dwMajorVersion)
    {
    case 4:
      {
        if (iServicePack >= 3)
        {
          tRet = OS__WindowsNT4SP3OrLater;
        }
        else
        {
          tRet = OS__NT;
        }
        break;
      }
    case 5:
      {
        tRet = OS__XP;
        break;
      }
    case 6:
      {
        tRet = OS__Vista;
        break;
      }    
    }    
    if(Is64BitProcess())
    {
      tRet = OS__64;
    }
  }
  return tRet;
}

float WINAPI XPixelsToTwips(const LONG& nDPI, const float& fPixels)
{
  //��������ȷ�ķֱ���
  LONG nInnerDPI = nDPI;
  if (nInnerDPI < 70)
  {
    nInnerDPI = 300;
  }
  return ((float)(fPixels * cnInchToTwip)/(float)nInnerDPI);
}

float WINAPI XTwipsToPixel(const LONG& nDPI, const float& nTwips)
{
  //��������ȷ�ķֱ���
  LONG nInnerDPI = nDPI;
  if (nInnerDPI < 70)
  {
    nInnerDPI = 300;
  }
  return ((float)(nTwips * nInnerDPI)/(float)cnInchToTwip);
}
float WINAPI XPixelToMillimeter( const LONG& nDPI, const float &fPiexls )
{
  float nInch = XPixelToInch(nDPI, fPiexls);
  return nInch * 25.4;
}
float WINAPI XMillimeterToPixel( const LONG& nDPI, const float &nMm )
{
  float nInch = nMm / 25.4;
  return XInchToPixel(nDPI, nInch);  
}
float WINAPI XPixelToInch( const LONG& nDPI, const float &fPiexls )
{
  LONG nInnerDPI = nDPI;
  if (nInnerDPI < 70)
  {
    nInnerDPI = 300;
  }
  return (float)fPiexls / nDPI ;
}
float WINAPI XInchToPixel( const LONG& nDPI, const float &nInch )
{
  LONG nInnerDPI = nDPI;
  if (nInnerDPI < 70)
  {
    nInnerDPI = 300;
  }
  return nInch * nDPI;
}

