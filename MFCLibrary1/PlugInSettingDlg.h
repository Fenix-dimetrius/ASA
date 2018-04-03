#pragma once
#include "resource.h"
#include "afxwin.h"



extern int MenOrWomen;

// ���������� ���� PlugInSettingDlg

class PlugInSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PlugInSettingDlg)

public:
	PlugInSettingDlg(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~PlugInSettingDlg();
	bool ShowSettings();
// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()

private:

	
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
	// ���������� ������ �� �����
//	bool m_EndShowCheck;
	
//protected:
	//// ����� ������
	//float m_ShowTimeEdit;
	//// �������� �� ������
	//float m_BeforeShowEdit;
	////  �������� ����� ������
	//float m_AfterShowEdit;
//public:
	
//protected:
//
//	
//	// �������� �� ������
//	//float m_BeforeShowEdit;
//	// ����� ������
//	//float m_ShowTimeEdit;
//	// �������� ����� ������
//	//float m_AfterShowEdit;
private:

	


	//  ���������� ������ �� �����
	CButton m_EndShow;
	// �������� �� ������
	CEdit m_BeforeShowEdit;
	// ����� ������
	CEdit m_ShowTimeEdit;
	// �������� ����� ������
	CEdit m_AfterShowEdit;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	// ��������� �� ������
	CButton m_GenNumPicBefore;
	// ������ ��������� ��������
	CButton m_AccurInterval;
	// �������� ����� ������� ������
	CComboBox m_TimeIntervalTick;
	// ����������
	CEdit m_DelaySpeedMouseEdit;
	// ����� ������������ ��������������� ��������
	CComboBox AuxPlugInNum;
	// �������
	CEdit s_SureName;
	// ���
	CEdit s_Name;
	// ��������
	CEdit s_SecName;
	// ���
	BOOL s_ManWoman;
};
