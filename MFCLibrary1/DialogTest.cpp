// DialogTest.cpp: ���� ����������
//

#include "stdafx.h"
#include "DialogTest.h"
#include "afxdialogex.h"


// ���������� ���� DialogTest

IMPLEMENT_DYNAMIC(DialogTest, CDialogEx)

DialogTest::DialogTest(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}


DialogTest::~DialogTest()
{
	
	
}

void DialogTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogTest, CDialogEx)
//	ON_WM_DESTROY()
//	ON_WM_CLOSE()
//	ON_WM_CREATE()
ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// ����������� ��������� DialogTest


BOOL DialogTest::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������
	if (pMsg->message == WM_KEYDOWN)
		AfxMessageBox("DialogTest KEY PRESS!!!!!");
	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL DialogTest::ShowASADlg()
{
	//ASADlg dlg;
	//dlg.DoModal();
	return 0;
}



//void DialogTest::OnDestroy()
//{
//	CDialogEx::OnDestroy();
//	AfxMessageBox("OnDestroy KEY PRESS!!!!!");
//	// TODO: �������� ���� ��� ����������� ���������
//}


//void DialogTest::OnClose()
//{
//	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������
//	AfxMessageBox("OnClose KEY PRESS!!!!!");
//	CDialogEx::OnClose();
//}


//int DialogTest::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  �������� ������������������ ��� ��������
//	ASADlg dlg;
//	dlg.DoModal();
//	return 0;
//}


BOOL DialogTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �������� �������������� �������������
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����������: �������� ������� OCX ������ ���������� �������� FALSE
}


void DialogTest::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	//DialogTest::ShowWindow(SW_HIDE);
	
	dlg.DoModal();

	//dlg.OnBnClickedOk();
	//dlg.onBtnCloneFunc();
	
	// TODO: �������� ���� ��� ����������� ���������
}

void DialogTest::fulscr()
{
//	dlg.onBtnCloneFunc();
}
