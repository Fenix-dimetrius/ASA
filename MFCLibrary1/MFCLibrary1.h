// MFCLibrary1.h: ������� ���� ��������� ��� DLL MFCLibrary1
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������
#include <vector>

struct NameInstrument // ���������, ������� ����������� �� ��������������� dll
{
	
	//double *ArrVal;
	bool isInclude; // �������� � ������������ �� ������ �� ������
	std::vector <CString> TextInfCh; // �������� �������
	std::vector <float> valChannel; // ��������� �������

	
	int LinkInstr;

	

};

// CMFCLibrary1App
// ��� ���������� ������� ������ ��. MFCLibrary1.cpp
//

class CMFCLibrary1App : public CWinApp
{
public:
	CMFCLibrary1App();

// ���������������
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
