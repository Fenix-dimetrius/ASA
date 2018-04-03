#pragma once

#include "resource.h"
#include "afxwin.h"
#include "PicCardContrl1.h"
#include "PicCardContrl2.h"
#include "PicFonContrl.h"


// ���������� ���� ASADlg
//extern bool m_EndShowByClick;


// ����� ������
extern int m_ShowTime;
// �������� �� ������
extern int m_BeforeShow;
//  �������� ����� ������
extern int m_AfterShow;

//  �������� �������� ����������� ����
extern int m_DelaySpeedMouse;


// ��������� ����� �� �����
extern bool m_EndShowByClick;

// ��������� �� ������
extern bool GenNumPicBefore;

// ������ �������
extern bool AccurInterval;

// �������� ����� �������, ��� ������ ������ � ����
extern int measureInterval;

extern int m_AuxPlugInNum;






//std::vector <float> EpoImpos(2); // ������ ��� ���������� �������� ������ 0
//std::vector <float> EpoImposBuf(2); // ������ ��� ���������� �������� ������ 0
//extern std::vector <float> EpoImpos(2); // ������ ��� ���������� �������� ������ 0
//extern std::vector <float> EpoImposBuf(2); // ������ ��� ���������� �������� ������ 0

class ASADlg : public CDialogEx
{
	DECLARE_DYNAMIC(ASADlg)

public:
	ASADlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~ASADlg();
	

	
// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	bool ShowASA();
	PicCardContrl1 m_PicCard1;
	//PicFonContrl m_PicFon;
	PicCardContrl2 m_PicCard2;

	//CStatic 
	afx_msg void OnStnClickedCard1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnClose();
	
	afx_msg void OnPaint();
	//// ���������, ��� �� - �������
	//bool m_RadioMan;
	//// ���������, ��� �� - �������
	//bool m_RadioWoman;
	afx_msg void OnStnClickedCard2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void onBtnCloneFunc(); // ����� ������� ������� ������. ���������� �� dialogTest.cpp

	bool BeforeTimer;
	bool ShowTimer;
	bool AfterTimer;
	//bool DelaySpeedMouseTimer;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// picture control ��� ����
	PicFonContrl m_Fon;

	// ��������� ��� ��������� ����� ����
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// ����� ��� ����������� ����
	CBrush my_colorDlg;
//	afx_msg void OnStnClickedFon();





	void RBtnClckForm();
	void SetTimersInterval();

	afx_msg void OnStnClickedFon();

	
	// �������������(���������������) ���� � ��������(���������) ����
	void FullScrAndStartTest();
	// �������
	CEdit m_SureName;
	// ���
	CEdit m_Name;
	// ��������
	CEdit m_SecName;

	
	// ������ ����������� ��� ����������� ����
	BOOL m_ManWoman;
	virtual INT_PTR DoModal();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
