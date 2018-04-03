// MFCLibrary1.h: главный файл заголовка для DLL MFCLibrary1
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы
#include <vector>

struct NameInstrument // структура, которая принимается из вспомогательных dll
{
	
	//double *ArrVal;
	bool isInclude; // подключе и показывается ли плагин на экране
	std::vector <CString> TextInfCh; // названия каналов
	std::vector <float> valChannel; // значнения каналов

	
	int LinkInstr;

	

};

// CMFCLibrary1App
// Про реализацию данного класса см. MFCLibrary1.cpp
//

class CMFCLibrary1App : public CWinApp
{
public:
	CMFCLibrary1App();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
