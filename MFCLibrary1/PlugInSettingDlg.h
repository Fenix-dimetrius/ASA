#pragma once
#include "resource.h"
#include "afxwin.h"



extern int MenOrWomen;

// диалоговое окно PlugInSettingDlg

class PlugInSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PlugInSettingDlg)

public:
	PlugInSettingDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~PlugInSettingDlg();
	bool ShowSettings();
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()

private:

	
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton1();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedOk();
	// Завершение показа по клику
//	bool m_EndShowCheck;
	
//protected:
	//// Время показа
	//float m_ShowTimeEdit;
	//// Задержка до показа
	//float m_BeforeShowEdit;
	////  Задержка после показа
	//float m_AfterShowEdit;
//public:
	
//protected:
//
//	
//	// Задержка до показа
//	//float m_BeforeShowEdit;
//	// Время показа
//	//float m_ShowTimeEdit;
//	// Задержка после показа
//	//float m_AfterShowEdit;
private:

	


	//  завершение показа по клику
	CButton m_EndShow;
	// Задержка до показа
	CEdit m_BeforeShowEdit;
	// Время показа
	CEdit m_ShowTimeEdit;
	// Задержка после показа
	CEdit m_AfterShowEdit;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	// генерация до выбора
	CButton m_GenNumPicBefore;
	// точные интервалы отсчетов
	CButton m_AccurInterval;
	// интервал тиков таймера записи
	CComboBox m_TimeIntervalTick;
	// Предзапись
	CEdit m_DelaySpeedMouseEdit;
	// число подключаемых вспомогательных плагинов
	CComboBox AuxPlugInNum;
	// фамилия
	CEdit s_SureName;
	// Имя
	CEdit s_Name;
	// Отчество
	CEdit s_SecName;
	// Пол
	BOOL s_ManWoman;
};
