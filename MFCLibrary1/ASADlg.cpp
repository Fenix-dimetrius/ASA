// ASADlg.cpp: файл реализации
//

#include "stdafx.h"
#include "ASADlg.h"
#include "afxdialogex.h"
#include "DialogTest.h"
#include "ASATest.h"


// Время показа
int m_ShowTime;
// Задержка до показа
int m_BeforeShow;
//  Задержка после показа
int m_AfterShow;

//  Задержка после показа
int m_DelaySpeedMouse;


// завершить показ по клику
bool m_EndShowByClick = false;
// генерация до выбора
bool GenNumPicBefore = false;

// точные отсчеты
bool AccurInterval = false;

//  aux plugIns
int m_AuxPlugInNum = 6;



RECT sizeScrin; // размер окна в оконных координатах.
				//при втором мониторе можгут быть отриц знач

CString urlPic; // адрес картинки

extern void redrawPlugIn(CString urlPic);

ASATest TestBody;
// диалоговое окно ASADlg

IMPLEMENT_DYNAMIC(ASADlg, CDialogEx)

ASADlg::ASADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ASA, pParent)
	//, m_RadioMan(false)
	//, m_RadioWoman(false)
	, m_ManWoman(FALSE)
{

}

//CImage imgFon;

ASADlg::~ASADlg()
{
	
}



void ASADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CARD1, m_PicCard1);
	//	DDX_Control(pDX, IDC_FON, m_PicFon);
	DDX_Control(pDX, IDC_CARD2, m_PicCard2);
	DDX_Control(pDX, IDC_FON, m_Fon);
	DDX_Control(pDX, IDC_EDIT2, m_SureName);
	DDX_Control(pDX, IDC_EDIT3, m_Name);
	DDX_Control(pDX, IDC_EDIT4, m_SecName);
	DDX_Radio(pDX, IDC_RADIO1, m_ManWoman);
}


BEGIN_MESSAGE_MAP(ASADlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ASADlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_CARD1, &ASADlg::OnStnClickedCard1)
//	ON_BN_CLICKED(IDC_BUTTON1, &ASADlg::OnBnClickedButton1)
//	ON_WM_CLOSE()
//	ON_WM_SETFOCUS()
ON_WM_CLOSE()
ON_WM_PAINT()
ON_STN_CLICKED(IDC_CARD2, &ASADlg::OnStnClickedCard2)
ON_WM_TIMER()
ON_WM_SIZE()
ON_WM_CREATE()
ON_WM_CTLCOLOR()
//ON_STN_CLICKED(IDC_FON, &ASADlg::OnStnClickedFon)
ON_STN_CLICKED(IDC_FON, &ASADlg::OnStnClickedFon)
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// генерирование в момент нажатия
CString urlPicBuf;
void GenNumPic()
{
	

	urlPicBuf = TestBody.getUrlPic(); // буффер. генерируем номер стимула
	urlPic = "PlugIns/TestASA/img/img" + urlPicBuf + ".jpg"; // получаем номер картинки и собираем адрес картинки

	UpdInfoVal.NumActualCard = TestBody.GetActualNumPic(); // сохраняем номер картинки в структуре, для записи в файл
	
	
}


void TrueOeFalseClickCard(char Card) // правильно ли выбрали карту
{
	if (Card == 'R') // всегда четн
	{
		// если выпало четно, те не 150 то показываем картинку, так как угодали. если выпало нечет, то не угалали
		
		if (urlPicBuf != "150")
		{
			UpdInfoVal.TruOrFalseCard = "True";
		}
		else
		{
			UpdInfoVal.TruOrFalseCard = "False";
		}	

	}
	if (Card == 'L')// всегда не четн
	{
		// если выпало нечет, те 150, то показываем картинку, так как угодали. если выпало чет, то не угалали
		if (urlPicBuf == "150")
		{
			urlPic = "PlugIns/TestASA/img/img" + TestBody.GetActualNumPic() + ".jpg"; // получаем номер картинки и собираем адрес картинки
			UpdInfoVal.TruOrFalseCard = "True";
		}
		else
		{
			urlPic = "PlugIns/TestASA/img/img" + CString("150") + ".jpg";
			UpdInfoVal.TruOrFalseCard = "False";
		}

	}	
}



// обработчики сообщений ASADlg

bool fullscr = false;

//void ASADlg::onBtnCloneFunc()
//{
//	//MessageBoxA("Ok", "its work", NULL);
//	//OnBnClickedOk();
//	//CString Temp;
//	//UpdateData(TRUE);
//	//MenOrWomen = m_ManWoman;
//
//	UpdInfoVal.SumChouseTrue = 1;
//	UpdInfoVal.SumChouseFalse = 1;
//
//	/*m_SureName.GetWindowTextA(UpdInfoVal.SureName);
//	m_Name.GetWindowTextA(UpdInfoVal.Name);
//	m_SecName.GetWindowTextA(UpdInfoVal.SecName);*/
//
//	fullscr = false; // если эта кнопка видна, то это уже не полноэкранный режим
//
//	if (fullscr == false)
//	{
//		ModifyStyle(WS_CAPTION, 0);// скрываем поле заголовка окна
//		ModifyStyle(WS_EX_DLGMODALFRAME, 0); // скрываем рамки окна
//											 //ModifyStyle(WS_DLGFRAME, 0);
//											 //AfxGetMainWnd()->SetWindowPos()
//											 //this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WS_EX_TOPMOST);
//											 //	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), WS_EX_TOPMOST);
//
//		AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED); // разворачиваем окно
//		fullscr = true;
//
//
//	}
//	my_colorDlg.DeleteObject(); // удаляем старую кисть
//	my_colorDlg.CreateSolidBrush(RGB(0, 0, 0));		// создать кисть для окраски окна
//
//													// НЕ ЗАБЫТЬ РАСКОМЕНТИТЬ В РЕЛИЗЕ!!!!
//													//SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)1, 0); // устанавливаем минимальную скорость
//
//
//													//																												//загружаем картинку
//													//imgFon.Destroy();
//													//imgFon.Load(_T("PlugIns/TestASA/fonASA.jpg"));
//
//
//													// TODO: добавьте свой код обработчика уведомлений
//													// TODO: добавьте свой код обработчика уведомлений
//													// скрываем кнопку ОК
//	CWnd *hButOk = GetDlgItem(IDOK);
//	hButOk->ModifyStyle(WS_VISIBLE, 0);
//
//	// скрываем кнопку Отмена
//	CWnd *hButCan = GetDlgItem(IDCANCEL);
//	hButCan->ModifyStyle(WS_VISIBLE, 0);
//
//
//
//	// скрываем первый текст
//	CWnd *hText1 = GetDlgItem(IDC_STATICTEXT1);
//	hText1->ModifyStyle(WS_VISIBLE, 0);
//
//	// скрываем второй текст
//	CWnd *hText2 = GetDlgItem(IDC_STATICTEXT2);
//	hText2->ModifyStyle(WS_VISIBLE, 0);
//
//	// скрываем  текст "фамилия"
//	CWnd *hTextFam = GetDlgItem(IDC_STATICFAM);
//	hTextFam->ModifyStyle(WS_VISIBLE, 0);
//
//	// скрываем  текст "имя"
//	CWnd *hTextNam = GetDlgItem(IDC_STATICNAM);
//	hTextNam->ModifyStyle(WS_VISIBLE, 0);
//
//	// скрываем  текст "Отчество"
//	CWnd *hTextSecNam = GetDlgItem(IDC_STATICSECNAM);
//	hTextSecNam->ModifyStyle(WS_VISIBLE, 0);
//
//	// скрываем  текст "Вы"
//	CWnd *hTextYou = GetDlgItem(IDC_STATICYOU);
//	hTextYou->ModifyStyle(WS_VISIBLE, 0);
//
//	// скрываем радиокнопки
//	CWnd *hRadioMan = GetDlgItem(IDC_RADIO1);
//	hRadioMan->ModifyStyle(WS_VISIBLE, 0);
//
//	CWnd *hRadioWoman = GetDlgItem(IDC_RADIO2);
//	hRadioWoman->ModifyStyle(WS_VISIBLE, 0);
//
//	//Скрываем картинку предупреждения
//	CWnd *hRadioWarning = GetDlgItem(IDC_WARNING);
//	hRadioWarning->ModifyStyle(WS_VISIBLE, 0);
//
//	//Скрываем поля ввода
//	CWnd *hEditFam = GetDlgItem(IDC_EDIT2);
//	hEditFam->ModifyStyle(WS_VISIBLE, 0);
//
//	CWnd *hEditNam = GetDlgItem(IDC_EDIT3);
//	hEditNam->ModifyStyle(WS_VISIBLE, 0);
//
//	CWnd *hEditSecNam = GetDlgItem(IDC_EDIT4);
//	hEditSecNam->ModifyStyle(WS_VISIBLE, 0);
//
//
//	// показываем карты и фон
//	m_PicCard1.ModifyStyle(0, WS_VISIBLE);
//	m_PicCard2.ModifyStyle(0, WS_VISIBLE);
//
//	// делаем видимым contrl фона
//	CWnd *hFonContrl = GetDlgItem(IDC_FON);
//	hFonContrl->ModifyStyle(0, WS_VISIBLE);
//
//
//	//m_PicFon.ModifyStyle(0, WS_VISIBLE);
//	//обновляем экран
//	Invalidate();
//	UpdateWindow();
//
//	TestBody.InitASATest(); // инициализируем тело ASA теста
//
//	if (GenNumPicBefore == true)
//	{
//		GenNumPic(); // генерирование номера картинки
//	}
//
//}

void ASADlg::OnBnClickedOk()
{
	//CString Temp;
	//UpdateData(TRUE);
	//MenOrWomen = m_ManWoman;

	UpdInfoVal.SumChouseTrue = 1;
	UpdInfoVal.SumChouseFalse = 1;

	/*m_SureName.GetWindowTextA(UpdInfoVal.SureName);
	m_Name.GetWindowTextA(UpdInfoVal.Name);
	m_SecName.GetWindowTextA(UpdInfoVal.SecName);*/

	fullscr = false; // если эта кнопка видна, то это уже не полноэкранный режим

	if (fullscr == false)
	{
		ModifyStyle(WS_CAPTION, 0);// скрываем поле заголовка окна
		ModifyStyle(WS_EX_DLGMODALFRAME, 0); // скрываем рамки окна
											 //ModifyStyle(WS_DLGFRAME, 0);
											 //AfxGetMainWnd()->SetWindowPos()
											 //this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WS_EX_TOPMOST);
											 //	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), WS_EX_TOPMOST);

		AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED); // разворачиваем окно
		fullscr = true;
		

	}
	my_colorDlg.DeleteObject(); // удаляем старую кисть
	my_colorDlg.CreateSolidBrush(RGB(0, 0, 0));		// создать кисть для окраски окна
	
	// НЕ ЗАБЫТЬ РАСКОМЕНТИТЬ В РЕЛИЗЕ!!!!
	//SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)1, 0); // устанавливаем минимальную скорость
	
	
	//																												//загружаем картинку
	//imgFon.Destroy();
	//imgFon.Load(_T("PlugIns/TestASA/fonASA.jpg"));


	// TODO: добавьте свой код обработчика уведомлений
	// TODO: добавьте свой код обработчика уведомлений
	// скрываем кнопку ОК
	CWnd *hButOk = GetDlgItem(IDOK);
	hButOk->ModifyStyle(WS_VISIBLE, 0);

	// скрываем кнопку Отмена
	CWnd *hButCan = GetDlgItem(IDCANCEL);
	hButCan->ModifyStyle(WS_VISIBLE, 0);

	

	// скрываем первый текст
	CWnd *hText1 = GetDlgItem(IDC_STATICTEXT1);
	hText1->ModifyStyle(WS_VISIBLE, 0);

	// скрываем второй текст
	CWnd *hText2 = GetDlgItem(IDC_STATICTEXT2);
	hText2->ModifyStyle(WS_VISIBLE, 0);

	// скрываем  текст "фамилия"
	CWnd *hTextFam = GetDlgItem(IDC_STATICFAM);
	hTextFam->ModifyStyle(WS_VISIBLE, 0);

	// скрываем  текст "имя"
	CWnd *hTextNam = GetDlgItem(IDC_STATICNAM);
	hTextNam->ModifyStyle(WS_VISIBLE, 0);

	// скрываем  текст "Отчество"
	CWnd *hTextSecNam = GetDlgItem(IDC_STATICSECNAM);
	hTextSecNam->ModifyStyle(WS_VISIBLE, 0);

	// скрываем  текст "Вы"
	CWnd *hTextYou = GetDlgItem(IDC_STATICYOU);
	hTextYou->ModifyStyle(WS_VISIBLE, 0);

	// скрываем радиокнопки
	CWnd *hRadioMan = GetDlgItem(IDC_RADIO1);
	hRadioMan->ModifyStyle(WS_VISIBLE, 0);

	CWnd *hRadioWoman= GetDlgItem(IDC_RADIO2);
	hRadioWoman->ModifyStyle(WS_VISIBLE, 0);

	//Скрываем картинку предупреждения
	CWnd *hRadioWarning = GetDlgItem(IDC_WARNING);
	hRadioWarning->ModifyStyle(WS_VISIBLE, 0);

	//Скрываем поля ввода
	CWnd *hEditFam = GetDlgItem(IDC_EDIT2);
	hEditFam->ModifyStyle(WS_VISIBLE, 0);

	CWnd *hEditNam = GetDlgItem(IDC_EDIT3);
	hEditNam->ModifyStyle(WS_VISIBLE, 0);

	CWnd *hEditSecNam = GetDlgItem(IDC_EDIT4);
	hEditSecNam->ModifyStyle(WS_VISIBLE, 0);


	// показываем карты и фон
	m_PicCard1.ModifyStyle(0, WS_VISIBLE);
	m_PicCard2.ModifyStyle(0, WS_VISIBLE);

	// делаем видимым contrl фона
	 CWnd *hFonContrl = GetDlgItem(IDC_FON);
	 hFonContrl->ModifyStyle(0, WS_VISIBLE);


	//m_PicFon.ModifyStyle(0, WS_VISIBLE);
	//обновляем экран
	Invalidate();
	UpdateWindow();

	TestBody.InitASATest(); // инициализируем тело ASA теста

	if (GenNumPicBefore == true)
	{
		GenNumPic(); // генерирование номера картинки
	}

	//CDialogEx::OnOK();
}

bool ASADlg::ShowASA()
{
//	ASADlg dlg;
	
	return true;
}

//bool ShowASA()
//{
//	ASADlg dlg;
//	dlg.ShowWindow(SW_SHOW);
//	return true;
//}



//BOOL ASADlg::PreTranslateMessage(MSG* pMsg)
//{
//	// TODO: добавьте специализированный код или вызов базового класса
//	if (pMsg->message == WM_KEYDOWN)
//	AfxMessageBox("KEY PRESS!!!!!");
//	return CDialogEx::PreTranslateMessage(pMsg);
//}



BOOL ASADlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
	if (pMsg->message == WM_KEYDOWN && (GetKeyState(VK_ESCAPE) & 0x8000))
	{
		fullscr = false;
		my_colorDlg.DeleteObject(); // удаляем старую кисть
		my_colorDlg.CreateSolidBrush(RGB(240, 240, 240));		// создать кисть для окраски окна в стандартный цвет
		//my_colorDlg.CreateSysColorBrush();
		SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)10, 0); // устанавливаем стандартную скорость
	}

	//if (pMsg->message == WM_KEYDOWN && (GetKeyState(VK_F7) & 0x8000))
	//	//AfxMessageBox("ASADlg KEY PRESS!!!!!");
	//{	
	//
	//	FullScrAndStartTest();
	//	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)10, 0); // устанавливаем стандартную скорость

	//}
	return CDialogEx::PreTranslateMessage(pMsg);
}




void ASADlg::OnClose()
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CDialogEx::OnClose();
}



void ASADlg::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CDialogEx::OnPaint() для сообщений рисования
	CRect rect;
	
	GetClientRect(&rect);
//	imgFon.AlphaBlend(dc, 0, 0, rect.right, rect.bottom, 0, 0, imgFon.GetWidth(), imgFon.GetHeight()); // выводим изображение фона на окно
	//sizeScrin = rect;
	CWnd *hFonContrl = GetDlgItem(IDC_FON);
	RECT FonContlSize = m_Fon.SetPosFon(rect);
	//dc.SetBkColor(RGB(100, 0, 0));
	m_Fon.SetWindowPos(hFonContrl, FonContlSize.left, FonContlSize.top, FonContlSize.right, FonContlSize.bottom, SWP_NOZORDER);

	CRect rectCtl;
	m_PicCard1.GetClientRect(&rectCtl); // получаем размеры picture control


	m_PicCard1.MoveWindow(  150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // перемещаем контрол

	m_PicCard2.MoveWindow(rect.right - rectCtl.right - 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // перемещаем контрол


	// было расположение от центра
	//m_PicCard1.MoveWindow(rect.right / 2.0 - rectCtl.right - 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // перемещаем контрол

	//m_PicCard2.MoveWindow(rect.right / 2.0 + 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // перемещаем контрол


	//CDialogEx::OnPaint();
}




CString SelCard;
void ASADlg::OnStnClickedCard1()
{	
	UpdInfoVal.ChouseCard = "Left"; // Сохраняем информацию о выборе карты
	UpdInfoVal.TimeInterval = "Before"; // отмечаем начало интервала
	m_PicCard1.ModifyStyle(WS_VISIBLE, 0); // скрываем карту 1
	m_PicCard2.ModifyStyle(WS_VISIBLE, 0); // скрываем карту 2
	Invalidate(FALSE); 
	UpdateWindow(); 
	SelCard = "Selected left card"; // вывод на экран плагина (испытателя)
	if (!BeforeTimer) // проверка работы таймера
	{
		SetTimer(1, m_BeforeShow, NULL); //установка таймера
		BeforeTimer = true; // ключ таймера
	}
	if (GenNumPicBefore != true) // Проверка на выбор метода генерации
	{					// если нет галочки на генерацию до выбора, то 
		GenNumPic(); // генерирование номера картинки
	}
	else
	{
		TrueOeFalseClickCard('L'); // вспомогательная ф-я
	}

}


void ASADlg::OnStnClickedCard2()
{
	UpdInfoVal.ChouseCard = "Right";
	UpdInfoVal.TimeInterval = "Before";
	// TODO: добавьте свой код обработчика уведомлений
	m_PicCard1.ModifyStyle(WS_VISIBLE, 0);
	m_PicCard2.ModifyStyle(WS_VISIBLE, 0);
	Invalidate(FALSE);
	UpdateWindow();
	SelCard = "Selected right card";
	if (!BeforeTimer)
	{
		SetTimer(1, m_BeforeShow, NULL);
		BeforeTimer = true;
	}
	if (GenNumPicBefore != true)
	{
		GenNumPic(); // генерирование номера картинки
	}
	else
	{
		TrueOeFalseClickCard('L');
	}
	
}

//PicFonContrl fonLoad;
void ASADlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	int sm = 0; // скорость мыши
	switch (nIDEvent)//uTime - ID таймера
	{
	case 1://timer1 срабатывает после указанного времени
 	{
		if (BeforeTimer)
		{
			KillTimer(1);
			BeforeTimer = false;
		}
		

		m_Fon.LoadImageFon(urlPic);// загружаем картинку в окно теста
		redrawPlugIn(urlPic); // загружаем картинку в окно плагина
		
		Invalidate(FALSE);// обновляем экран (без мерцания?)
		UpdateWindow();

		if (!ShowTimer)
		{
			SetTimer(2, m_ShowTime, NULL); // запускаем второй таймер
			ShowTimer = true;
		}

		UpdInfoVal.TimeInterval = "Show";


	}

	break;

	case 2://timer2
	{
	
	
		m_Fon.LoadImageFon("PlugIns/TestASA/fonASA.jpg");
		SelCard = "";
		redrawPlugIn("PlugIns/TestASA/fonASA.jpg"); // загружаем картинку в окно плагина

		Invalidate(FALSE);// обновляем экран (без мерцания?)
		UpdateWindow();

		if (ShowTimer)
		{
			KillTimer(2);
			ShowTimer = false;
		}
		if (!AfterTimer)
		{
			SetTimer(3, m_AfterShow, NULL);
			AfterTimer = true;
		}

		UpdInfoVal.TimeInterval = "After";

	}
	break;
	case 3://timer2
	{
		CString BufAnsw = UpdInfoVal.TruOrFalseCard;
		UpdInfoVal.ChouseCard = " ";
		UpdInfoVal.TimeInterval = " ";
		UpdInfoVal.NumActualCard = " ";
		UpdInfoVal.TruOrFalseCard = " ";
	//	ClipCursor

		// перемещаем указатель мыши в центр окна





		GetWindowRect(&sizeScrin); // получаем оконные координаты окна

		SetCursorPos(sizeScrin.left + (sizeScrin.right - sizeScrin.left) / 2.0, sizeScrin.top + (sizeScrin.bottom - sizeScrin.top) / 2.0); // изменяет положение курсора (X,Y)
		if (AfterTimer)
		{
			KillTimer(3);
			AfterTimer = false;
		}
		//if (!DelaySpeedMouseTimer)
		//{
		//	SetTimer(4, m_DelaySpeedMouse, NULL);
		//	DelaySpeedMouseTimer = true;

		//	SystemParametersInfo(SPI_GETMOUSESPEED, 0, &sm, 0); // запоминаем скорость мыши до изменения
		//	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)1, 0); // устанавливаем минимальную скорость
		//	SetCursorPos(sizeScrin.right/2.0, sizeScrin.bottom); // изменяет положение курсора (X,Y)
		//}

		// показываем карты
		m_PicCard1.ModifyStyle(0, WS_VISIBLE); 
		m_PicCard2.ModifyStyle(0, WS_VISIBLE);

		Invalidate(FALSE);// обновляем экран (без мерцания?)
		UpdateWindow();
		
		

		if (GenNumPicBefore == true)
		{
			GenNumPic(); // генерирование номера картинки
		}


		//TestBody.ImposEpo(BufAnsw);

		if (TestBody.EndGenNum())
		{
			FullScrAndStartTest();
			MessageBox("Тест пройден", "Info", MB_OK);
		}


	}
	break;

	//case 4: // таймер на дадержку мыши
	//{	
	//	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)10, 0);
	//	if (DelaySpeedMouseTimer)
	//	{
	//		KillTimer(4);
	//		DelaySpeedMouseTimer = false;
	//	}
	//
	//}
	//break;

	}




	CDialogEx::OnTimer(nIDEvent);
}



void ASADlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	
	// TODO: добавьте свой код обработчика сообщений
	//Invalidate();
	//UpdateWindow();
}


int ASADlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания
	BeforeTimer = false;
	ShowTimer = false;
	AfterTimer = false;
	//DelaySpeedMouseTimer = false;

	my_colorDlg.DeleteObject(); // удаляем старую кисть
	my_colorDlg.CreateSolidBrush(RGB(240, 240, 240));		// создать кисть для окраски окна в стандартный цвет
	//TestBody.InitASATest(); // инициализируем тело ASA теста
	
	UpdInfoVal.SumChouseTrue = 1;	
	UpdInfoVal.SumChouseFalse = 1;// Время показа
	//m_ShowTime = 1000;
	//// Задержка до показа
	//m_BeforeShow = 1000;
	////  Задержка после показа
	//m_AfterShow = 1000;
	
														//MessageBox("Create Press", "Info", MB_OK);
	return 0;
}


HBRUSH ASADlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Измените любые атрибуты DC
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG: // изменяем только цвет диалога
	{
		return my_colorDlg;
	}

	default:
		return hbr;
	}
	//pDC->SetBkColor(RGB(240, 240, 240));pDC->
	//pDC->SetTextColor(RGB(240, 240, 240));
	// TODO:  Вернуть другое значение дескриптора кисти, если оно не определено по умолчанию
	//return my_colorDlg;
	
}


//void ASADlg::OnStnClickedFon()
//{
//	
//	
//}

void ASADlg::RBtnClckForm()
{
	// TODO: добавьте свой код обработчика уведомлений
	
}

void ASADlg::SetTimersInterval()
{
	m_AfterShow = 1000;
	m_ShowTime = 1000;
	m_BeforeShow = 1000;
	m_DelaySpeedMouse = 500;
}



void ASADlg::OnStnClickedFon()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (m_EndShowByClick == true)
	{
		KillTimer(2);
		KillTimer(3);

		UpdInfoVal.ChouseCard = " ";
		UpdInfoVal.TimeInterval = " ";
		UpdInfoVal.NumActualCard = " ";
		UpdInfoVal.TruOrFalseCard = " ";

		m_Fon.LoadImageFon("PlugIns/TestASA/fonASA.jpg");
		// показываем карты
		m_PicCard1.ModifyStyle(0, WS_VISIBLE);
		m_PicCard2.ModifyStyle(0, WS_VISIBLE);

		if (GenNumPicBefore == true) //если включена генерация до выбора
		{
			GenNumPic(); // генерирование номера картинки
		}

		Invalidate(FALSE);// обновляем экран (без мерцания?)
		UpdateWindow();

		SelCard = "";
		redrawPlugIn("PlugIns/TestASA/fonASA.jpg"); // загружаем картинку в окно плагина

		//test

	}
}


// Разворачивает(восстонавливает) окно и начинает(завершает) тест
void ASADlg::FullScrAndStartTest()
{
	if (fullscr == false)
	{
		//SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)1, 0); // устанавливаем минимальную скорость

		fullscr = true;
		UpdateData(TRUE);
		//MenOrWomen = m_ManWoman;

		if (GenNumPicBefore == true)
		{
			GenNumPic(); // генерирование номера картинки
		}
		//	m_PicFon.ModifyStyle(0, WS_VISIBLE);
		my_colorDlg.DeleteObject(); // удаляем старую кисть
		my_colorDlg.CreateSolidBrush(RGB(0, 0, 0));		// создать кисть для окраски окна

		ModifyStyle(WS_CAPTION, 0);// скрываем поле заголовка окна
		ModifyStyle(WS_EX_DLGMODALFRAME, 0); // скрываем рамки окна
											 //ModifyStyle(WS_DLGFRAME, 0);
											 //AfxGetMainWnd()->SetWindowPos()
											 //this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WS_EX_TOPMOST);
											 //	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), WS_EX_TOPMOST);

		AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED); // разворачиваем окно

													   // делаем видимым contrl фона
		CWnd *hFonContrl = GetDlgItem(IDC_FON);
		hFonContrl->ModifyStyle(0, WS_VISIBLE);

		// показываем карты и фон
		m_PicCard1.ModifyStyle(0, WS_VISIBLE);
		m_PicCard2.ModifyStyle(0, WS_VISIBLE);

		////загружаем картинку
		//imgFon.Destroy();
		//imgFon.Load(_T("PlugIns/TestASA/fonASA.jpg"));




		// скрываем кнопку ОК
		CWnd *hButOk = GetDlgItem(IDOK);
		hButOk->ModifyStyle(WS_VISIBLE, 0);

		// скрываем кнопку Отмена
		CWnd *hButCan = GetDlgItem(IDCANCEL);
		hButCan->ModifyStyle(WS_VISIBLE, 0);



		// скрываем первый текст
		CWnd *hText1 = GetDlgItem(IDC_STATICTEXT1);
		hText1->ModifyStyle(WS_VISIBLE, 0);

		// скрываем второй текст
		CWnd *hText2 = GetDlgItem(IDC_STATICTEXT2);
		hText2->ModifyStyle(WS_VISIBLE, 0);

		// скрываем  текст "фамилия"
		CWnd *hTextFam = GetDlgItem(IDC_STATICFAM);
		hTextFam->ModifyStyle(WS_VISIBLE, 0);

		// скрываем  текст "имя"
		CWnd *hTextNam = GetDlgItem(IDC_STATICNAM);
		hTextNam->ModifyStyle(WS_VISIBLE, 0);

		// скрываем  текст "Отчество"
		CWnd *hTextSecNam = GetDlgItem(IDC_STATICSECNAM);
		hTextSecNam->ModifyStyle(WS_VISIBLE, 0);

		// скрываем  текст "Вы"
		CWnd *hTextYou = GetDlgItem(IDC_STATICYOU);
		hTextYou->ModifyStyle(WS_VISIBLE, 0);

		// скрываем радиокнопки
		CWnd *hRadioMan = GetDlgItem(IDC_RADIO1);
		hRadioMan->ModifyStyle(WS_VISIBLE, 0);
		CWnd *hRadioWoman = GetDlgItem(IDC_RADIO2);
		hRadioWoman->ModifyStyle(WS_VISIBLE, 0);

		//Скрываем картинку предупреждения
		CWnd *hRadioWarning = GetDlgItem(IDC_WARNING);
		hRadioWarning->ModifyStyle(WS_VISIBLE, 0);

		//Скрываем поля ввода
		CWnd *hEditFam = GetDlgItem(IDC_EDIT2);
		hEditFam->ModifyStyle(WS_VISIBLE, 0);

		CWnd *hEditNam = GetDlgItem(IDC_EDIT3);
		hEditNam->ModifyStyle(WS_VISIBLE, 0);

		CWnd *hEditSecNam = GetDlgItem(IDC_EDIT4);
		hEditSecNam->ModifyStyle(WS_VISIBLE, 0);

		Invalidate();
		UpdateWindow();


		

		TestBody.InitASATest(); // инициализируем тело ASA теста
		//CRect rectCtl;
		//m_PicCard1.GetClientRect(&rectCtl); // получаем размеры picture control

		//m_PicCard1.MoveWindow(rect.right / 2.0 - rectCtl.right - 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // перемещаем контрол

		//m_PicCard2.MoveWindow(rect.right / 2.0 + 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // перемещаем контрол

	}

	else
	{
		//SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)10, 0); // устанавливаем минимальную скорость
		fullscr = false;
		my_colorDlg.DeleteObject(); // удаляем старую кисть
		my_colorDlg.CreateSolidBrush(RGB(240, 240, 240));		// создать кисть для окраски окна в стандартный цвет


		ModifyStyle(0, WS_CAPTION);//WS_CAPTION // показываем поле заголовка окна
		ModifyStyle(0, WS_EX_DLGMODALFRAME); // показываем рамку окна
											 //AfxGetMainWnd()->SetWindowPos()
											 //this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WS_EX_TOPMOST);
											 //	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), WS_EX_TOPMOST);

		AfxGetMainWnd()->ShowWindow(SW_RESTORE); // возвращаем окно в исходное состояние

												 //очищаем фон
												 //imgFon.Destroy();


												 // скрываем кнопку ОК
		CWnd *hButOk = GetDlgItem(IDOK);
		hButOk->ModifyStyle(0, WS_VISIBLE);

		// скрываем кнопку Отмена
		CWnd *hButCan = GetDlgItem(IDCANCEL);
		hButCan->ModifyStyle(0, WS_VISIBLE);

		// скрываем первый текст
		CWnd *hText1 = GetDlgItem(IDC_STATICTEXT1);
		hText1->ModifyStyle(0, WS_VISIBLE);

		// скрываем второй текст
		CWnd *hText2 = GetDlgItem(IDC_STATICTEXT2);
		hText2->ModifyStyle(0, WS_VISIBLE);

		// скрываем  текст "фамилия"
		CWnd *hTextFam = GetDlgItem(IDC_STATICFAM);
		hTextFam->ModifyStyle(0, WS_VISIBLE);

		// скрываем  текст "имя"
		CWnd *hTextNam = GetDlgItem(IDC_STATICNAM);
		hTextNam->ModifyStyle(0, WS_VISIBLE);

		// скрываем  текст "Отчество"
		CWnd *hTextSecNam = GetDlgItem(IDC_STATICSECNAM);
		hTextSecNam->ModifyStyle(0, WS_VISIBLE);

		// скрываем  текст "Вы"
		CWnd *hTextYou = GetDlgItem(IDC_STATICYOU);
		hTextYou->ModifyStyle(0, WS_VISIBLE);

		// скрываем радиокнопки
		CWnd *hRadioMan = GetDlgItem(IDC_RADIO1);
		hRadioMan->ModifyStyle(0, WS_VISIBLE);

		CWnd *hRadioWoman = GetDlgItem(IDC_RADIO2);
		hRadioWoman->ModifyStyle(0, WS_VISIBLE);

		//Скрываем картинку предупреждения
		CWnd *hRadioWarning = GetDlgItem(IDC_WARNING);
		hRadioWarning->ModifyStyle(0, WS_VISIBLE);

		//Скрываем поля ввода
		CWnd *hEditFam = GetDlgItem(IDC_EDIT2);
		hEditFam->ModifyStyle(0, WS_VISIBLE);

		CWnd *hEditNam = GetDlgItem(IDC_EDIT3);
		hEditNam->ModifyStyle(0, WS_VISIBLE);

		CWnd *hEditSecNam = GetDlgItem(IDC_EDIT4);
		hEditSecNam->ModifyStyle(0, WS_VISIBLE);


		// скрываем карты и фон
		m_PicCard1.ModifyStyle(WS_VISIBLE, 0);//(0, WS_VISIBLE);
		m_PicCard2.ModifyStyle(WS_VISIBLE, 0);
		// скрываем фон
		CWnd *hFonContrl = GetDlgItem(IDC_FON);
		hFonContrl->ModifyStyle(WS_VISIBLE, 0);

		//m_PicFon.ModifyStyle(WS_VISIBLE, 0);
		Invalidate();
		UpdateWindow();

		fullscr = false;
		//CRect rectCtl;
		//m_PicCard1.GetClientRect(&rectCtl); // получаем размеры picture control

		//m_PicCard1.MoveWindow(rect.right / 2.0 - rectCtl.right - 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // перемещаем контрол

		//m_PicCard2.MoveWindow(rect.right / 2.0 + 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // перемещаем контрол

		
	}
}


INT_PTR ASADlg::DoModal()
{
	// TODO: добавьте специализированный код или вызов базового класса
	//Sleep(100);
	
	return CDialogEx::DoModal();
}



void ASADlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	
	// TODO: добавьте свой код обработчика сообщений
	OnBnClickedOk();
	//onBtnCloneFunc();	
}
