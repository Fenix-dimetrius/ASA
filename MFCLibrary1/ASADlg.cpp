// ASADlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "ASADlg.h"
#include "afxdialogex.h"
#include "DialogTest.h"
#include "ASATest.h"


// ����� ������
int m_ShowTime;
// �������� �� ������
int m_BeforeShow;
//  �������� ����� ������
int m_AfterShow;

//  �������� ����� ������
int m_DelaySpeedMouse;


// ��������� ����� �� �����
bool m_EndShowByClick = false;
// ��������� �� ������
bool GenNumPicBefore = false;

// ������ �������
bool AccurInterval = false;

//  aux plugIns
int m_AuxPlugInNum = 6;



RECT sizeScrin; // ������ ���� � ������� �����������.
				//��� ������ �������� ������ ���� ����� ����

CString urlPic; // ����� ��������

extern void redrawPlugIn(CString urlPic);

ASATest TestBody;
// ���������� ���� ASADlg

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


// ������������� � ������ �������
CString urlPicBuf;
void GenNumPic()
{
	

	urlPicBuf = TestBody.getUrlPic(); // ������. ���������� ����� �������
	urlPic = "PlugIns/TestASA/img/img" + urlPicBuf + ".jpg"; // �������� ����� �������� � �������� ����� ��������

	UpdInfoVal.NumActualCard = TestBody.GetActualNumPic(); // ��������� ����� �������� � ���������, ��� ������ � ����
	
	
}


void TrueOeFalseClickCard(char Card) // ��������� �� ������� �����
{
	if (Card == 'R') // ������ ����
	{
		// ���� ������ �����, �� �� 150 �� ���������� ��������, ��� ��� �������. ���� ������ �����, �� �� �������
		
		if (urlPicBuf != "150")
		{
			UpdInfoVal.TruOrFalseCard = "True";
		}
		else
		{
			UpdInfoVal.TruOrFalseCard = "False";
		}	

	}
	if (Card == 'L')// ������ �� ����
	{
		// ���� ������ �����, �� 150, �� ���������� ��������, ��� ��� �������. ���� ������ ���, �� �� �������
		if (urlPicBuf == "150")
		{
			urlPic = "PlugIns/TestASA/img/img" + TestBody.GetActualNumPic() + ".jpg"; // �������� ����� �������� � �������� ����� ��������
			UpdInfoVal.TruOrFalseCard = "True";
		}
		else
		{
			urlPic = "PlugIns/TestASA/img/img" + CString("150") + ".jpg";
			UpdInfoVal.TruOrFalseCard = "False";
		}

	}	
}



// ����������� ��������� ASADlg

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
//	fullscr = false; // ���� ��� ������ �����, �� ��� ��� �� ������������� �����
//
//	if (fullscr == false)
//	{
//		ModifyStyle(WS_CAPTION, 0);// �������� ���� ��������� ����
//		ModifyStyle(WS_EX_DLGMODALFRAME, 0); // �������� ����� ����
//											 //ModifyStyle(WS_DLGFRAME, 0);
//											 //AfxGetMainWnd()->SetWindowPos()
//											 //this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WS_EX_TOPMOST);
//											 //	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), WS_EX_TOPMOST);
//
//		AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED); // ������������� ����
//		fullscr = true;
//
//
//	}
//	my_colorDlg.DeleteObject(); // ������� ������ �����
//	my_colorDlg.CreateSolidBrush(RGB(0, 0, 0));		// ������� ����� ��� ������� ����
//
//													// �� ������ ������������ � ������!!!!
//													//SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)1, 0); // ������������� ����������� ��������
//
//
//													//																												//��������� ��������
//													//imgFon.Destroy();
//													//imgFon.Load(_T("PlugIns/TestASA/fonASA.jpg"));
//
//
//													// TODO: �������� ���� ��� ����������� �����������
//													// TODO: �������� ���� ��� ����������� �����������
//													// �������� ������ ��
//	CWnd *hButOk = GetDlgItem(IDOK);
//	hButOk->ModifyStyle(WS_VISIBLE, 0);
//
//	// �������� ������ ������
//	CWnd *hButCan = GetDlgItem(IDCANCEL);
//	hButCan->ModifyStyle(WS_VISIBLE, 0);
//
//
//
//	// �������� ������ �����
//	CWnd *hText1 = GetDlgItem(IDC_STATICTEXT1);
//	hText1->ModifyStyle(WS_VISIBLE, 0);
//
//	// �������� ������ �����
//	CWnd *hText2 = GetDlgItem(IDC_STATICTEXT2);
//	hText2->ModifyStyle(WS_VISIBLE, 0);
//
//	// ��������  ����� "�������"
//	CWnd *hTextFam = GetDlgItem(IDC_STATICFAM);
//	hTextFam->ModifyStyle(WS_VISIBLE, 0);
//
//	// ��������  ����� "���"
//	CWnd *hTextNam = GetDlgItem(IDC_STATICNAM);
//	hTextNam->ModifyStyle(WS_VISIBLE, 0);
//
//	// ��������  ����� "��������"
//	CWnd *hTextSecNam = GetDlgItem(IDC_STATICSECNAM);
//	hTextSecNam->ModifyStyle(WS_VISIBLE, 0);
//
//	// ��������  ����� "��"
//	CWnd *hTextYou = GetDlgItem(IDC_STATICYOU);
//	hTextYou->ModifyStyle(WS_VISIBLE, 0);
//
//	// �������� �����������
//	CWnd *hRadioMan = GetDlgItem(IDC_RADIO1);
//	hRadioMan->ModifyStyle(WS_VISIBLE, 0);
//
//	CWnd *hRadioWoman = GetDlgItem(IDC_RADIO2);
//	hRadioWoman->ModifyStyle(WS_VISIBLE, 0);
//
//	//�������� �������� ��������������
//	CWnd *hRadioWarning = GetDlgItem(IDC_WARNING);
//	hRadioWarning->ModifyStyle(WS_VISIBLE, 0);
//
//	//�������� ���� �����
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
//	// ���������� ����� � ���
//	m_PicCard1.ModifyStyle(0, WS_VISIBLE);
//	m_PicCard2.ModifyStyle(0, WS_VISIBLE);
//
//	// ������ ������� contrl ����
//	CWnd *hFonContrl = GetDlgItem(IDC_FON);
//	hFonContrl->ModifyStyle(0, WS_VISIBLE);
//
//
//	//m_PicFon.ModifyStyle(0, WS_VISIBLE);
//	//��������� �����
//	Invalidate();
//	UpdateWindow();
//
//	TestBody.InitASATest(); // �������������� ���� ASA �����
//
//	if (GenNumPicBefore == true)
//	{
//		GenNumPic(); // ������������� ������ ��������
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

	fullscr = false; // ���� ��� ������ �����, �� ��� ��� �� ������������� �����

	if (fullscr == false)
	{
		ModifyStyle(WS_CAPTION, 0);// �������� ���� ��������� ����
		ModifyStyle(WS_EX_DLGMODALFRAME, 0); // �������� ����� ����
											 //ModifyStyle(WS_DLGFRAME, 0);
											 //AfxGetMainWnd()->SetWindowPos()
											 //this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WS_EX_TOPMOST);
											 //	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), WS_EX_TOPMOST);

		AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED); // ������������� ����
		fullscr = true;
		

	}
	my_colorDlg.DeleteObject(); // ������� ������ �����
	my_colorDlg.CreateSolidBrush(RGB(0, 0, 0));		// ������� ����� ��� ������� ����
	
	// �� ������ ������������ � ������!!!!
	//SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)1, 0); // ������������� ����������� ��������
	
	
	//																												//��������� ��������
	//imgFon.Destroy();
	//imgFon.Load(_T("PlugIns/TestASA/fonASA.jpg"));


	// TODO: �������� ���� ��� ����������� �����������
	// TODO: �������� ���� ��� ����������� �����������
	// �������� ������ ��
	CWnd *hButOk = GetDlgItem(IDOK);
	hButOk->ModifyStyle(WS_VISIBLE, 0);

	// �������� ������ ������
	CWnd *hButCan = GetDlgItem(IDCANCEL);
	hButCan->ModifyStyle(WS_VISIBLE, 0);

	

	// �������� ������ �����
	CWnd *hText1 = GetDlgItem(IDC_STATICTEXT1);
	hText1->ModifyStyle(WS_VISIBLE, 0);

	// �������� ������ �����
	CWnd *hText2 = GetDlgItem(IDC_STATICTEXT2);
	hText2->ModifyStyle(WS_VISIBLE, 0);

	// ��������  ����� "�������"
	CWnd *hTextFam = GetDlgItem(IDC_STATICFAM);
	hTextFam->ModifyStyle(WS_VISIBLE, 0);

	// ��������  ����� "���"
	CWnd *hTextNam = GetDlgItem(IDC_STATICNAM);
	hTextNam->ModifyStyle(WS_VISIBLE, 0);

	// ��������  ����� "��������"
	CWnd *hTextSecNam = GetDlgItem(IDC_STATICSECNAM);
	hTextSecNam->ModifyStyle(WS_VISIBLE, 0);

	// ��������  ����� "��"
	CWnd *hTextYou = GetDlgItem(IDC_STATICYOU);
	hTextYou->ModifyStyle(WS_VISIBLE, 0);

	// �������� �����������
	CWnd *hRadioMan = GetDlgItem(IDC_RADIO1);
	hRadioMan->ModifyStyle(WS_VISIBLE, 0);

	CWnd *hRadioWoman= GetDlgItem(IDC_RADIO2);
	hRadioWoman->ModifyStyle(WS_VISIBLE, 0);

	//�������� �������� ��������������
	CWnd *hRadioWarning = GetDlgItem(IDC_WARNING);
	hRadioWarning->ModifyStyle(WS_VISIBLE, 0);

	//�������� ���� �����
	CWnd *hEditFam = GetDlgItem(IDC_EDIT2);
	hEditFam->ModifyStyle(WS_VISIBLE, 0);

	CWnd *hEditNam = GetDlgItem(IDC_EDIT3);
	hEditNam->ModifyStyle(WS_VISIBLE, 0);

	CWnd *hEditSecNam = GetDlgItem(IDC_EDIT4);
	hEditSecNam->ModifyStyle(WS_VISIBLE, 0);


	// ���������� ����� � ���
	m_PicCard1.ModifyStyle(0, WS_VISIBLE);
	m_PicCard2.ModifyStyle(0, WS_VISIBLE);

	// ������ ������� contrl ����
	 CWnd *hFonContrl = GetDlgItem(IDC_FON);
	 hFonContrl->ModifyStyle(0, WS_VISIBLE);


	//m_PicFon.ModifyStyle(0, WS_VISIBLE);
	//��������� �����
	Invalidate();
	UpdateWindow();

	TestBody.InitASATest(); // �������������� ���� ASA �����

	if (GenNumPicBefore == true)
	{
		GenNumPic(); // ������������� ������ ��������
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
//	// TODO: �������� ������������������ ��� ��� ����� �������� ������
//	if (pMsg->message == WM_KEYDOWN)
//	AfxMessageBox("KEY PRESS!!!!!");
//	return CDialogEx::PreTranslateMessage(pMsg);
//}



BOOL ASADlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	if (pMsg->message == WM_KEYDOWN && (GetKeyState(VK_ESCAPE) & 0x8000))
	{
		fullscr = false;
		my_colorDlg.DeleteObject(); // ������� ������ �����
		my_colorDlg.CreateSolidBrush(RGB(240, 240, 240));		// ������� ����� ��� ������� ���� � ����������� ����
		//my_colorDlg.CreateSysColorBrush();
		SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)10, 0); // ������������� ����������� ��������
	}

	//if (pMsg->message == WM_KEYDOWN && (GetKeyState(VK_F7) & 0x8000))
	//	//AfxMessageBox("ASADlg KEY PRESS!!!!!");
	//{	
	//
	//	FullScrAndStartTest();
	//	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)10, 0); // ������������� ����������� ��������

	//}
	return CDialogEx::PreTranslateMessage(pMsg);
}




void ASADlg::OnClose()
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������

	CDialogEx::OnClose();
}



void ASADlg::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
					   // TODO: �������� ���� ��� ����������� ���������
					   // �� �������� CDialogEx::OnPaint() ��� ��������� ���������
	CRect rect;
	
	GetClientRect(&rect);
//	imgFon.AlphaBlend(dc, 0, 0, rect.right, rect.bottom, 0, 0, imgFon.GetWidth(), imgFon.GetHeight()); // ������� ����������� ���� �� ����
	//sizeScrin = rect;
	CWnd *hFonContrl = GetDlgItem(IDC_FON);
	RECT FonContlSize = m_Fon.SetPosFon(rect);
	//dc.SetBkColor(RGB(100, 0, 0));
	m_Fon.SetWindowPos(hFonContrl, FonContlSize.left, FonContlSize.top, FonContlSize.right, FonContlSize.bottom, SWP_NOZORDER);

	CRect rectCtl;
	m_PicCard1.GetClientRect(&rectCtl); // �������� ������� picture control


	m_PicCard1.MoveWindow(  150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // ���������� �������

	m_PicCard2.MoveWindow(rect.right - rectCtl.right - 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // ���������� �������


	// ���� ������������ �� ������
	//m_PicCard1.MoveWindow(rect.right / 2.0 - rectCtl.right - 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // ���������� �������

	//m_PicCard2.MoveWindow(rect.right / 2.0 + 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // ���������� �������


	//CDialogEx::OnPaint();
}




CString SelCard;
void ASADlg::OnStnClickedCard1()
{	
	UpdInfoVal.ChouseCard = "Left"; // ��������� ���������� � ������ �����
	UpdInfoVal.TimeInterval = "Before"; // �������� ������ ���������
	m_PicCard1.ModifyStyle(WS_VISIBLE, 0); // �������� ����� 1
	m_PicCard2.ModifyStyle(WS_VISIBLE, 0); // �������� ����� 2
	Invalidate(FALSE); 
	UpdateWindow(); 
	SelCard = "Selected left card"; // ����� �� ����� ������� (����������)
	if (!BeforeTimer) // �������� ������ �������
	{
		SetTimer(1, m_BeforeShow, NULL); //��������� �������
		BeforeTimer = true; // ���� �������
	}
	if (GenNumPicBefore != true) // �������� �� ����� ������ ���������
	{					// ���� ��� ������� �� ��������� �� ������, �� 
		GenNumPic(); // ������������� ������ ��������
	}
	else
	{
		TrueOeFalseClickCard('L'); // ��������������� �-�
	}

}


void ASADlg::OnStnClickedCard2()
{
	UpdInfoVal.ChouseCard = "Right";
	UpdInfoVal.TimeInterval = "Before";
	// TODO: �������� ���� ��� ����������� �����������
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
		GenNumPic(); // ������������� ������ ��������
	}
	else
	{
		TrueOeFalseClickCard('L');
	}
	
}

//PicFonContrl fonLoad;
void ASADlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
	int sm = 0; // �������� ����
	switch (nIDEvent)//uTime - ID �������
	{
	case 1://timer1 ����������� ����� ���������� �������
 	{
		if (BeforeTimer)
		{
			KillTimer(1);
			BeforeTimer = false;
		}
		

		m_Fon.LoadImageFon(urlPic);// ��������� �������� � ���� �����
		redrawPlugIn(urlPic); // ��������� �������� � ���� �������
		
		Invalidate(FALSE);// ��������� ����� (��� ��������?)
		UpdateWindow();

		if (!ShowTimer)
		{
			SetTimer(2, m_ShowTime, NULL); // ��������� ������ ������
			ShowTimer = true;
		}

		UpdInfoVal.TimeInterval = "Show";


	}

	break;

	case 2://timer2
	{
	
	
		m_Fon.LoadImageFon("PlugIns/TestASA/fonASA.jpg");
		SelCard = "";
		redrawPlugIn("PlugIns/TestASA/fonASA.jpg"); // ��������� �������� � ���� �������

		Invalidate(FALSE);// ��������� ����� (��� ��������?)
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

		// ���������� ��������� ���� � ����� ����





		GetWindowRect(&sizeScrin); // �������� ������� ���������� ����

		SetCursorPos(sizeScrin.left + (sizeScrin.right - sizeScrin.left) / 2.0, sizeScrin.top + (sizeScrin.bottom - sizeScrin.top) / 2.0); // �������� ��������� ������� (X,Y)
		if (AfterTimer)
		{
			KillTimer(3);
			AfterTimer = false;
		}
		//if (!DelaySpeedMouseTimer)
		//{
		//	SetTimer(4, m_DelaySpeedMouse, NULL);
		//	DelaySpeedMouseTimer = true;

		//	SystemParametersInfo(SPI_GETMOUSESPEED, 0, &sm, 0); // ���������� �������� ���� �� ���������
		//	SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)1, 0); // ������������� ����������� ��������
		//	SetCursorPos(sizeScrin.right/2.0, sizeScrin.bottom); // �������� ��������� ������� (X,Y)
		//}

		// ���������� �����
		m_PicCard1.ModifyStyle(0, WS_VISIBLE); 
		m_PicCard2.ModifyStyle(0, WS_VISIBLE);

		Invalidate(FALSE);// ��������� ����� (��� ��������?)
		UpdateWindow();
		
		

		if (GenNumPicBefore == true)
		{
			GenNumPic(); // ������������� ������ ��������
		}


		//TestBody.ImposEpo(BufAnsw);

		if (TestBody.EndGenNum())
		{
			FullScrAndStartTest();
			MessageBox("���� �������", "Info", MB_OK);
		}


	}
	break;

	//case 4: // ������ �� �������� ����
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

	
	// TODO: �������� ���� ��� ����������� ���������
	//Invalidate();
	//UpdateWindow();
}


int ASADlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �������� ������������������ ��� ��������
	BeforeTimer = false;
	ShowTimer = false;
	AfterTimer = false;
	//DelaySpeedMouseTimer = false;

	my_colorDlg.DeleteObject(); // ������� ������ �����
	my_colorDlg.CreateSolidBrush(RGB(240, 240, 240));		// ������� ����� ��� ������� ���� � ����������� ����
	//TestBody.InitASATest(); // �������������� ���� ASA �����
	
	UpdInfoVal.SumChouseTrue = 1;	
	UpdInfoVal.SumChouseFalse = 1;// ����� ������
	//m_ShowTime = 1000;
	//// �������� �� ������
	//m_BeforeShow = 1000;
	////  �������� ����� ������
	//m_AfterShow = 1000;
	
														//MessageBox("Create Press", "Info", MB_OK);
	return 0;
}


HBRUSH ASADlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �������� ����� �������� DC
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG: // �������� ������ ���� �������
	{
		return my_colorDlg;
	}

	default:
		return hbr;
	}
	//pDC->SetBkColor(RGB(240, 240, 240));pDC->
	//pDC->SetTextColor(RGB(240, 240, 240));
	// TODO:  ������� ������ �������� ����������� �����, ���� ��� �� ���������� �� ���������
	//return my_colorDlg;
	
}


//void ASADlg::OnStnClickedFon()
//{
//	
//	
//}

void ASADlg::RBtnClckForm()
{
	// TODO: �������� ���� ��� ����������� �����������
	
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
	// TODO: �������� ���� ��� ����������� �����������
	if (m_EndShowByClick == true)
	{
		KillTimer(2);
		KillTimer(3);

		UpdInfoVal.ChouseCard = " ";
		UpdInfoVal.TimeInterval = " ";
		UpdInfoVal.NumActualCard = " ";
		UpdInfoVal.TruOrFalseCard = " ";

		m_Fon.LoadImageFon("PlugIns/TestASA/fonASA.jpg");
		// ���������� �����
		m_PicCard1.ModifyStyle(0, WS_VISIBLE);
		m_PicCard2.ModifyStyle(0, WS_VISIBLE);

		if (GenNumPicBefore == true) //���� �������� ��������� �� ������
		{
			GenNumPic(); // ������������� ������ ��������
		}

		Invalidate(FALSE);// ��������� ����� (��� ��������?)
		UpdateWindow();

		SelCard = "";
		redrawPlugIn("PlugIns/TestASA/fonASA.jpg"); // ��������� �������� � ���� �������

		//test

	}
}


// �������������(���������������) ���� � ��������(���������) ����
void ASADlg::FullScrAndStartTest()
{
	if (fullscr == false)
	{
		//SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)1, 0); // ������������� ����������� ��������

		fullscr = true;
		UpdateData(TRUE);
		//MenOrWomen = m_ManWoman;

		if (GenNumPicBefore == true)
		{
			GenNumPic(); // ������������� ������ ��������
		}
		//	m_PicFon.ModifyStyle(0, WS_VISIBLE);
		my_colorDlg.DeleteObject(); // ������� ������ �����
		my_colorDlg.CreateSolidBrush(RGB(0, 0, 0));		// ������� ����� ��� ������� ����

		ModifyStyle(WS_CAPTION, 0);// �������� ���� ��������� ����
		ModifyStyle(WS_EX_DLGMODALFRAME, 0); // �������� ����� ����
											 //ModifyStyle(WS_DLGFRAME, 0);
											 //AfxGetMainWnd()->SetWindowPos()
											 //this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WS_EX_TOPMOST);
											 //	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), WS_EX_TOPMOST);

		AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED); // ������������� ����

													   // ������ ������� contrl ����
		CWnd *hFonContrl = GetDlgItem(IDC_FON);
		hFonContrl->ModifyStyle(0, WS_VISIBLE);

		// ���������� ����� � ���
		m_PicCard1.ModifyStyle(0, WS_VISIBLE);
		m_PicCard2.ModifyStyle(0, WS_VISIBLE);

		////��������� ��������
		//imgFon.Destroy();
		//imgFon.Load(_T("PlugIns/TestASA/fonASA.jpg"));




		// �������� ������ ��
		CWnd *hButOk = GetDlgItem(IDOK);
		hButOk->ModifyStyle(WS_VISIBLE, 0);

		// �������� ������ ������
		CWnd *hButCan = GetDlgItem(IDCANCEL);
		hButCan->ModifyStyle(WS_VISIBLE, 0);



		// �������� ������ �����
		CWnd *hText1 = GetDlgItem(IDC_STATICTEXT1);
		hText1->ModifyStyle(WS_VISIBLE, 0);

		// �������� ������ �����
		CWnd *hText2 = GetDlgItem(IDC_STATICTEXT2);
		hText2->ModifyStyle(WS_VISIBLE, 0);

		// ��������  ����� "�������"
		CWnd *hTextFam = GetDlgItem(IDC_STATICFAM);
		hTextFam->ModifyStyle(WS_VISIBLE, 0);

		// ��������  ����� "���"
		CWnd *hTextNam = GetDlgItem(IDC_STATICNAM);
		hTextNam->ModifyStyle(WS_VISIBLE, 0);

		// ��������  ����� "��������"
		CWnd *hTextSecNam = GetDlgItem(IDC_STATICSECNAM);
		hTextSecNam->ModifyStyle(WS_VISIBLE, 0);

		// ��������  ����� "��"
		CWnd *hTextYou = GetDlgItem(IDC_STATICYOU);
		hTextYou->ModifyStyle(WS_VISIBLE, 0);

		// �������� �����������
		CWnd *hRadioMan = GetDlgItem(IDC_RADIO1);
		hRadioMan->ModifyStyle(WS_VISIBLE, 0);
		CWnd *hRadioWoman = GetDlgItem(IDC_RADIO2);
		hRadioWoman->ModifyStyle(WS_VISIBLE, 0);

		//�������� �������� ��������������
		CWnd *hRadioWarning = GetDlgItem(IDC_WARNING);
		hRadioWarning->ModifyStyle(WS_VISIBLE, 0);

		//�������� ���� �����
		CWnd *hEditFam = GetDlgItem(IDC_EDIT2);
		hEditFam->ModifyStyle(WS_VISIBLE, 0);

		CWnd *hEditNam = GetDlgItem(IDC_EDIT3);
		hEditNam->ModifyStyle(WS_VISIBLE, 0);

		CWnd *hEditSecNam = GetDlgItem(IDC_EDIT4);
		hEditSecNam->ModifyStyle(WS_VISIBLE, 0);

		Invalidate();
		UpdateWindow();


		

		TestBody.InitASATest(); // �������������� ���� ASA �����
		//CRect rectCtl;
		//m_PicCard1.GetClientRect(&rectCtl); // �������� ������� picture control

		//m_PicCard1.MoveWindow(rect.right / 2.0 - rectCtl.right - 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // ���������� �������

		//m_PicCard2.MoveWindow(rect.right / 2.0 + 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // ���������� �������

	}

	else
	{
		//SystemParametersInfo(SPI_SETMOUSESPEED, 0, (PVOID)10, 0); // ������������� ����������� ��������
		fullscr = false;
		my_colorDlg.DeleteObject(); // ������� ������ �����
		my_colorDlg.CreateSolidBrush(RGB(240, 240, 240));		// ������� ����� ��� ������� ���� � ����������� ����


		ModifyStyle(0, WS_CAPTION);//WS_CAPTION // ���������� ���� ��������� ����
		ModifyStyle(0, WS_EX_DLGMODALFRAME); // ���������� ����� ����
											 //AfxGetMainWnd()->SetWindowPos()
											 //this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), WS_EX_TOPMOST);
											 //	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN), WS_EX_TOPMOST);

		AfxGetMainWnd()->ShowWindow(SW_RESTORE); // ���������� ���� � �������� ���������

												 //������� ���
												 //imgFon.Destroy();


												 // �������� ������ ��
		CWnd *hButOk = GetDlgItem(IDOK);
		hButOk->ModifyStyle(0, WS_VISIBLE);

		// �������� ������ ������
		CWnd *hButCan = GetDlgItem(IDCANCEL);
		hButCan->ModifyStyle(0, WS_VISIBLE);

		// �������� ������ �����
		CWnd *hText1 = GetDlgItem(IDC_STATICTEXT1);
		hText1->ModifyStyle(0, WS_VISIBLE);

		// �������� ������ �����
		CWnd *hText2 = GetDlgItem(IDC_STATICTEXT2);
		hText2->ModifyStyle(0, WS_VISIBLE);

		// ��������  ����� "�������"
		CWnd *hTextFam = GetDlgItem(IDC_STATICFAM);
		hTextFam->ModifyStyle(0, WS_VISIBLE);

		// ��������  ����� "���"
		CWnd *hTextNam = GetDlgItem(IDC_STATICNAM);
		hTextNam->ModifyStyle(0, WS_VISIBLE);

		// ��������  ����� "��������"
		CWnd *hTextSecNam = GetDlgItem(IDC_STATICSECNAM);
		hTextSecNam->ModifyStyle(0, WS_VISIBLE);

		// ��������  ����� "��"
		CWnd *hTextYou = GetDlgItem(IDC_STATICYOU);
		hTextYou->ModifyStyle(0, WS_VISIBLE);

		// �������� �����������
		CWnd *hRadioMan = GetDlgItem(IDC_RADIO1);
		hRadioMan->ModifyStyle(0, WS_VISIBLE);

		CWnd *hRadioWoman = GetDlgItem(IDC_RADIO2);
		hRadioWoman->ModifyStyle(0, WS_VISIBLE);

		//�������� �������� ��������������
		CWnd *hRadioWarning = GetDlgItem(IDC_WARNING);
		hRadioWarning->ModifyStyle(0, WS_VISIBLE);

		//�������� ���� �����
		CWnd *hEditFam = GetDlgItem(IDC_EDIT2);
		hEditFam->ModifyStyle(0, WS_VISIBLE);

		CWnd *hEditNam = GetDlgItem(IDC_EDIT3);
		hEditNam->ModifyStyle(0, WS_VISIBLE);

		CWnd *hEditSecNam = GetDlgItem(IDC_EDIT4);
		hEditSecNam->ModifyStyle(0, WS_VISIBLE);


		// �������� ����� � ���
		m_PicCard1.ModifyStyle(WS_VISIBLE, 0);//(0, WS_VISIBLE);
		m_PicCard2.ModifyStyle(WS_VISIBLE, 0);
		// �������� ���
		CWnd *hFonContrl = GetDlgItem(IDC_FON);
		hFonContrl->ModifyStyle(WS_VISIBLE, 0);

		//m_PicFon.ModifyStyle(WS_VISIBLE, 0);
		Invalidate();
		UpdateWindow();

		fullscr = false;
		//CRect rectCtl;
		//m_PicCard1.GetClientRect(&rectCtl); // �������� ������� picture control

		//m_PicCard1.MoveWindow(rect.right / 2.0 - rectCtl.right - 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // ���������� �������

		//m_PicCard2.MoveWindow(rect.right / 2.0 + 150, rect.bottom / 2.0 - rectCtl.bottom / 2.0, rectCtl.right, rectCtl.bottom); // ���������� �������

		
	}
}


INT_PTR ASADlg::DoModal()
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	//Sleep(100);
	
	return CDialogEx::DoModal();
}



void ASADlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	
	// TODO: �������� ���� ��� ����������� ���������
	OnBnClickedOk();
	//onBtnCloneFunc();	
}
