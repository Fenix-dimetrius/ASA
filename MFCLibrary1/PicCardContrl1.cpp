#include "stdafx.h"
#include "PicCardContrl1.h"

CImage imgCard;
PicCardContrl1::PicCardContrl1()
{
	imgCard.Load(_T("PlugIns/TestASA/cardASA.jpg"));
}


PicCardContrl1::~PicCardContrl1()
{
}
BEGIN_MESSAGE_MAP(PicCardContrl1, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void PicCardContrl1::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CStatic::OnPaint() для сообщений рисования
	CRect rect;
	GetClientRect(&rect);
	imgCard.AlphaBlend(dc, 0, 0, rect.right, rect.bottom, 0, 0, imgCard.GetWidth(), imgCard.GetHeight()); // выводим изображение фона на окно

}
