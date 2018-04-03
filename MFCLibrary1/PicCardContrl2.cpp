#include "stdafx.h"
#include "PicCardContrl2.h"

 CImage imgCard2;
PicCardContrl2::PicCardContrl2()
{
	imgCard2.Load(_T("PlugIns/TestASA/cardASA.jpg"));
}


PicCardContrl2::~PicCardContrl2()
{
}
BEGIN_MESSAGE_MAP(PicCardContrl2, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void PicCardContrl2::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CStatic::OnPaint() для сообщений рисования
	CRect rect;
	GetClientRect(&rect);
	imgCard2.AlphaBlend(dc, 0, 0, rect.right, rect.bottom, 0, 0, imgCard2.GetWidth(), imgCard2.GetHeight()); // выводим изображение фона на окно

}
