// DialogTest.cpp: файл реализации
//

#include "stdafx.h"
#include "DialogTest.h"
#include "afxdialogex.h"


// диалоговое окно DialogTest

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


// обработчики сообщений DialogTest


BOOL DialogTest::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса
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
//	// TODO: добавьте свой код обработчика сообщений
//}


//void DialogTest::OnClose()
//{
//	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
//	AfxMessageBox("OnClose KEY PRESS!!!!!");
//	CDialogEx::OnClose();
//}


//int DialogTest::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  Добавьте специализированный код создания
//	ASADlg dlg;
//	dlg.DoModal();
//	return 0;
//}


BOOL DialogTest::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void DialogTest::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	//DialogTest::ShowWindow(SW_HIDE);
	
	dlg.DoModal();

	//dlg.OnBnClickedOk();
	//dlg.onBtnCloneFunc();
	
	// TODO: добавьте свой код обработчика сообщений
}

void DialogTest::fulscr()
{
//	dlg.onBtnCloneFunc();
}
