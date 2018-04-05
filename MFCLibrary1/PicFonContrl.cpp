#include "stdafx.h"
#include "PicFonContrl.h"
#include "ASADlg.h"

CImage imgFon;
PicFonContrl::PicFonContrl()
{
	//CString  urk = "PlugIns/TestASA/img/img150.jpg";
	imgFon.Load(_T("PlugIns/TestASA/fonASA.jpg"));
	//imgFon.Load(_T(urk));
}


PicFonContrl::~PicFonContrl()
{

}
BEGIN_MESSAGE_MAP(PicFonContrl, CStatic)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


void PicFonContrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CStatic::OnPaint() для сообщений рисования
	CRect rect;
	GetClientRect(&rect);
	imgFon.AlphaBlend(dc, 0, 0, rect.right, rect.bottom, 0, 0, imgFon.GetWidth(), imgFon.GetHeight()); // выводим изображение фона на окно

	//SetWi
}

bool PicFonContrl::LoadImageFon(CString url1)
{
	imgFon.Destroy();
	imgFon.Load(_T(url1));
	return true;
}

RECT PicFonContrl::SetPosFon(RECT rect)
{
	RECT rcImage;
	float ratioImage;
	//ratioImage = imgFon.GetHeight() /(float) imgFon.GetWidth();
	ratioImage =imgFon.GetWidth() / (float)imgFon.GetHeight() ;
	rcImage.left = (rect.right - ratioImage * rect.bottom) / 2.0;
	rcImage.right = (ratioImage * rect.bottom); //rcImage.left + ratioImage * rect.bottom;
	rcImage.top = rect.top;
	rcImage.bottom = rect.bottom;

	return rcImage;
}


void PicFonContrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	ASADlg AsaDlgCl;
	AsaDlgCl.RBtnClckForm();

	CStatic::OnRButtonDown(nFlags, point);
}
