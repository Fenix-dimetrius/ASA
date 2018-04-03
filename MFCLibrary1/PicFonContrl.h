#pragma once
#include "afxwin.h"
#include "resource.h"
class PicFonContrl :
	public CStatic
{
public:
	PicFonContrl();
	virtual ~PicFonContrl();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	

	public:
		bool LoadImageFon(CString url1);
		RECT SetPosFon(RECT rect);
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

