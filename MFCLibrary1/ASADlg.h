#pragma once

#include "resource.h"
#include "afxwin.h"
#include "PicCardContrl1.h"
#include "PicCardContrl2.h"
#include "PicFonContrl.h"



// диалоговое окно ASADlg
//extern bool m_EndShowByClick;


// Время показа
extern int m_ShowTime;
// Задержка до показа
extern int m_BeforeShow;
//  Задержка после показа
extern int m_AfterShow;

//  Задержка скорости перемещения мыши
extern int m_DelaySpeedMouse;


// завершить показ по клику
extern bool m_EndShowByClick;

// генерация до выбора
extern bool GenNumPicBefore;

// точные отсчеты
extern bool AccurInterval;

// интервал тиков таймера, для записи данных в файл
extern int measureInterval;

extern int m_AuxPlugInNum;






//std::vector <float> EpoImpos(2); // вектор для сохранения значения канала 0
//std::vector <float> EpoImposBuf(2); // вектор для сохранения значения канала 0
//extern std::vector <float> EpoImpos(2); // вектор для сохранения значения канала 0
//extern std::vector <float> EpoImposBuf(2); // вектор для сохранения значения канала 0

class ASADlg : public CDialogEx
{
	DECLARE_DYNAMIC(ASADlg)

public:
	ASADlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~ASADlg();
	

	
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

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
	//// Указывает, что вы - мужчина
	//bool m_RadioMan;
	//// Указывает, что вы - женщина
	//bool m_RadioWoman;
	afx_msg void OnStnClickedCard2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void onBtnCloneFunc(); // копия функции нажатия кнопки. вызывается из dialogTest.cpp

	bool BeforeTimer;
	bool ShowTimer;
	bool AfterTimer;
	//bool DelaySpeedMouseTimer;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// picture control для фона
	PicFonContrl m_Fon;

	// отрисовка при изменении цвета окна
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// кисть для окрашивания окна
	CBrush my_colorDlg;
//	afx_msg void OnStnClickedFon();





	void RBtnClckForm();
	void SetTimersInterval();

	afx_msg void OnStnClickedFon();

	
	// Разворачивает(восстонавливает) окно и начинает(завершает) тест
	void FullScrAndStartTest();
	// Фамилия
	CEdit m_SureName;
	// имя
	CEdit m_Name;
	// отчество
	CEdit m_SecName;

	
	// Группа радиокнопок для определения пола
	BOOL m_ManWoman;
	virtual INT_PTR DoModal();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
