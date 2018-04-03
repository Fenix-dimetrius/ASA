// PlugInSettingDlg.cpp: ���� ����������
//

#include "stdafx.h"
#include "PlugInSettingDlg.h"
#include "afxdialogex.h"
#include "ASADlg.h"
#include "DialogTest.h"
#include "ASATest.h"
// ���������� ���� PlugInSettingDlg
//ASADlg AsaDlgClass; // ��������� ������ ���� ����� ASA
IMPLEMENT_DYNAMIC(PlugInSettingDlg, CDialogEx)

PlugInSettingDlg::PlugInSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SETTINGS, pParent)
	//, m_EndShowCheck(false)
	/*, m_EndShow(_T(""))
	, m_ShowTimeEdit(_T(""))
	, m_BeforeShowEdit(_T(""))
	, m_AfterShowEdit(_T(""))*/
	//, m_BeforeShowEdit(0)
	//, m_ShowTimeEdit(0)
	//, m_AfterShowEdit(0)
	, s_ManWoman(FALSE)
{
	
}

PlugInSettingDlg::~PlugInSettingDlg()
{
	

}

bool PlugInSettingDlg::ShowSettings()
{
	//PlugInSettingDlg dlg;
	//dlg.ShowWindow(SW_SHOW);
	return true;
}
void PlugInSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CHECK1, m_EndShow);
	//DDX_Control(pDX, IDC_EDIT1, m_BeforeShowEdit);
	//DDX_Control(pDX, IDC_EDIT5, m_ShowTimeEdit);
	//DDX_Control(pDX, IDC_EDIT6, m_AfterShowEdit);
	DDX_Control(pDX, IDC_CHECK1, m_EndShow);
	DDX_Control(pDX, IDC_EDIT1, m_BeforeShowEdit);
	DDX_Control(pDX, IDC_EDIT5, m_ShowTimeEdit);
	DDX_Control(pDX, IDC_EDIT6, m_AfterShowEdit);
	DDX_Control(pDX, IDC_CHECK2, m_GenNumPicBefore);
	DDX_Control(pDX, IDC_CHECK3, m_AccurInterval);
	DDX_Control(pDX, IDC_COMBO1, m_TimeIntervalTick);
	DDX_Control(pDX, IDC_EDIT7, m_DelaySpeedMouseEdit);
	DDX_Control(pDX, IDC_COMBO2, AuxPlugInNum);
	DDX_Control(pDX, IDC_EDIT2, s_SureName);
	DDX_Control(pDX, IDC_EDIT3, s_Name);
	DDX_Control(pDX, IDC_EDIT4, s_SecName);
	DDX_Radio(pDX, IDC_RADIO1, s_ManWoman);
}


BEGIN_MESSAGE_MAP(PlugInSettingDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON1, &PlugInSettingDlg::OnBnClickedButton1)
//	ON_WM_CREATE()
	ON_BN_CLICKED(IDOK, &PlugInSettingDlg::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ����������� ��������� PlugInSettingDlg




BOOL PlugInSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	//if (pMsg->message == WM_KEYDOWN)
		//AfxMessageBox("KEY PRESS!!!!!");
	return CDialogEx::PreTranslateMessage(pMsg);
}


//----------------����������� ����������� ��������� � �� ���������-----------
struct ENUM_DISP_ARG
{
	TCHAR msg[500];
	int monId; // ���������� ���������
	HDC m_dcMon[4]; // �������� ��������
	RECT m_pRcMon[4]; // ������������� ��������
};
ENUM_DISP_ARG* pArg;
// callback function called by EnumDisplayMonitors for each enabled monitor
BOOL CALLBACK EnumDispProc(HMONITOR hMon, HDC dcMon, RECT* pRcMon, LPARAM lParam)
{
	//system("pause");

	pArg = reinterpret_cast<ENUM_DISP_ARG*>(lParam);
	TCHAR str[100] = _T("");
	//StringCbPrintf(str, sizeof(str), _T("Monitor %d: %d x %d @ %d,%d\n"), pArg->monId,
	//pRcMon->right - pRcMon->left, pRcMon->bottom - pRcMon->top, pRcMon->left, pRcMon->top);
	//StringCbPrintf(pArg->msg, sizeof(pArg->msg), str);

	//cout << "Monitor " << pArg->monId << ":" <<
	//pRcMon->right - pRcMon->left << " x " << pRcMon->bottom - pRcMon->top << "\n";


	pArg->m_dcMon[pArg->monId] = dcMon;
	pArg->m_pRcMon[pArg->monId] = *pRcMon;
	pArg->monId++;

	return TRUE;

}
//-------------------------------------------------------------------------------



void PlugInSettingDlg::OnBnClickedButton1() // asa button - ������ ������
						// �� �������� ��� ��� ����� � ������ ������� ��������,
						// �� ��� ��� ������� ��������� � ���� ��������...
{
	//UpdateData(TRUE); // �������� ������ ���������� � ��������� �������� ����������.
	//if (m_EndShowCheck == true)
	//{
	//	m_EndShowByClick = true;
	//}
	//else
	//{
	//	m_EndShowByClick = false;
	//}

	
	


	//UpdInfoVal.SureName = 

	//OnBnClickedOk();
	//CDialogEx::OnOK();

}




//bool m_EndShowByClick;
void PlugInSettingDlg::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	
	// �������� ������ � ����� �����
	UpdateData(TRUE);
	MenOrWomen = int(s_ManWoman);
	

	s_SureName.GetWindowTextA(UpdInfoVal.SureName);
	s_Name.GetWindowTextA(UpdInfoVal.Name);
	s_SecName.GetWindowTextA(UpdInfoVal.SecName);

	//---------------


	CString Temp;
	

	m_EndShowByClick = m_EndShow.GetCheck();
	
	GenNumPicBefore = m_GenNumPicBefore.GetCheck();

	AccurInterval = m_AccurInterval.GetCheck();



	//UpdateData(FALSE); // �������� ������ ���������� � ��������� �������� ����������.

	m_DelaySpeedMouseEdit.GetWindowTextA(Temp);
	m_DelaySpeedMouse = atoi(Temp);
	
	m_AfterShowEdit.GetWindowTextA(Temp);
	m_AfterShow = atoi(Temp);

	m_ShowTimeEdit.GetWindowTextA(Temp);
	m_ShowTime = atoi(Temp);

	m_BeforeShowEdit.GetWindowTextA(Temp);
	m_BeforeShow = atoi(Temp);

	m_TimeIntervalTick.GetWindowTextA(Temp);
	measureInterval = atoi(Temp);

	AuxPlugInNum.GetWindowTextA(Temp);
	m_AuxPlugInNum = atoi(Temp);

	//AsaTestDlg.m_ShowTime = m_ShowTimeEdit;
	//AsaTestDlg.m_BeforeShow = m_BeforeShowEdit;

	// �������� ������ ��������
	float VecSize = (m_AfterShow + m_ShowTime + m_BeforeShow) / (float)measureInterval;



	

	CDialogEx::OnOK();

	DialogTest hideFrame;
	if (hideFrame) hideFrame.DestroyWindow();
	hideFrame.Create(IDD_DIALOG1, GetDesktopWindow()); // ������� ���� �����, �� �� ����������

													   // 
													   // ���������� � ���������� �������� � �� ����������
	ENUM_DISP_ARG arg = { 0 };
	arg.monId = 0;
	EnumDisplayMonitors(0, 0, EnumDispProc, reinterpret_cast<LPARAM>(&arg));
	int activeMon = 0;
	int secMon = 0;
	// ���������� ������� �������
	DISPLAY_DEVICE dd;

	for (int i = 0;;++i)
	{

		dd.cb = sizeof(dd);

		if (!EnumDisplayDevices(NULL, i, &dd, 0)) break;
		else
		{
			if (dd.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
			{
				if (dd.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
					activeMon = i;
				else
					secMon = i;
			}
			ZeroMemory(&dd, sizeof(dd));
		}
	}


	// ���������� ���� �� ������ �������
	if (pArg->m_pRcMon[secMon].left < 0) // ���� ������� �����
	{
		hideFrame.SetWindowPos(&CWnd::wndTopMost, pArg->m_pRcMon[secMon].left / 2, 50, 0, 0, SWP_NOSIZE);//pArg->m_pRcMon[activeMon].top - pArg->m_pRcMon[secMon].bottom)/2
	}
	else // ���� ������
	{
		hideFrame.SetWindowPos(&CWnd::wndTopMost, pArg->m_pRcMon[activeMon].right / 2 + pArg->m_pRcMon[secMon].right / 2, 50, 0, 0, SWP_NOSIZE);
	}

	// ���������� ���� �����
	hideFrame.ShowWindow(SW_SHOW);



	
	//OnBnClickedButton1();
}




void PlugInSettingDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

//	MessageBox("OnSize", "Info", MB_OK);

	
	// TODO: �������� ���� ��� ����������� ���������
}


void PlugInSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �������� ���� ��� ����������� ���������
					   // �� �������� CDialogEx::OnPaint() ��� ��������� ���������
	//ASADlg AsaTestDlg;
	CString Temp;
	//Temp.le


	Temp.Format("\%i", m_DelaySpeedMouse); // ������� ����� � ������.
									 //	MessageBox(Temp, "Info", MB_OK);
	m_DelaySpeedMouseEdit.SetWindowTextA(Temp); // ����� � edit


	Temp.Format("\%i", m_AfterShow); // ������� ����� � ������.
									 //	MessageBox(Temp, "Info", MB_OK);
	m_AfterShowEdit.SetWindowTextA(Temp); // ����� � edit

	Temp.Format("\%i", m_ShowTime); // ������� ����� � ������.
	m_ShowTimeEdit.SetWindowTextA(Temp); // ����� � edit

	Temp.Format("\%i", m_BeforeShow); // ������� ����� � ������.
	m_BeforeShowEdit.SetWindowTextA(Temp); // ����� � edit

	
	Temp.Format("\%i", measureInterval); // ������� ����� � ������.
	m_TimeIntervalTick.SetWindowTextA(Temp); // ����� � edit

	m_EndShow.SetCheck(m_EndShowByClick);

	m_GenNumPicBefore.SetCheck(GenNumPicBefore);

	m_AccurInterval.SetCheck(AccurInterval);

	Temp.Format("\%i", m_AuxPlugInNum);
	AuxPlugInNum.SetWindowTextA(Temp);


	CDialogEx::OnPaint();
}
