
/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����: 	XLogFont.h					
�ļ�����:	
�汾��ʷ:	1.0
����:		xuejuntao xuejuntao@hanwang.com.cn 2008/08/18
*********************************************************************/
#ifndef HWX_LOGFONT_H
#define HWX_LOGFONT_H
class CXLogFont : public LOGFONT
{
public:
	CXLogFont();
	CXLogFont(const LOGFONT& logfont); //<combine CXLogFont::CXLogFont>
	const CXLogFont& operator=(const CXLogFont&);
	const CXLogFont& operator =(const LOGFONT&);
public:
	void operator=(LOGFONT& logfont);
	BOOL operator<(const CXLogFont&);

public:
	DWORD dwType;			// Used to hold the font type, i.e. TT_FONT, DEVICE_FONT.
};

#endif