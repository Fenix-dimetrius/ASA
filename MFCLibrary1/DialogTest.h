#pragma once
#include "resource.h"
#include "ASADlg.h"
// диалоговое окно DialogTest

class DialogTest : public CDialogEx
{
	DECLARE_DYNAMIC(DialogTest)

public:
	DialogTest(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~DialogTest();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	ASADlg dlg;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL ShowASADlg();
//	afx_msg void OnDestroy();
//	afx_msg void OnClose();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void fulscr();
};
