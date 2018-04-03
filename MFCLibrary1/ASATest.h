#pragma once
#include <vector>

extern bool StartRecorPlay; // �������� �� ������ ������
extern bool fullscr; // ����������, ����� �� ����

//
//					 // ��������� ���� ��� ������ �������
//extern std::vector <float> TrueEpoImposChan0; // ������ ��� ���������� �������� ������ 0
//extern std::vector <float> TrueEpoImposBufChan0; // ������ ��� ���������� �������� ������ 0
//
//extern std::vector <float> TrueEpoImposChan1; // ������ ��� ���������� �������� ������ 1
//extern std::vector <float> TrueEpoImposBufChan1; // ������ ��� ���������� �������� ������ 1
//
//extern std::vector <float> TrueEpoImposChan2; // ������ ��� ���������� �������� ������ 2
//extern std::vector <float> TrueEpoImposBufChan2; // ������ ��� ���������� �������� ������ 2
//
//extern std::vector <float> TrueEpoImposChan3; // ������ ��� ���������� �������� ������ 3
//extern std::vector <float> TrueEpoImposBufChan3; // ������ ��� ���������� �������� ������ 3
//
//
//					// ��������� ���� ��� �������� �������
//extern std::vector <float> FalseEpoImposChan0; // ������ ��� ���������� �������� ������ 0
//extern std::vector <float> FalseEpoImposBufChan0; // ������ ��� ���������� �������� ������ 0
//
//extern std::vector <float> FalseEpoImposChan1; // ������ ��� ���������� �������� ������ 1
//extern std::vector <float> FalseEpoImposBufChan1; // ������ ��� ���������� �������� ������ 1
//
//extern std::vector <float> FalseEpoImposChan2; // ������ ��� ���������� �������� ������ 2
//extern std::vector <float> FalseEpoImposBufChan2; // ������ ��� ���������� �������� ������ 2
//
//extern std::vector <float> FalseEpoImposChan3; // ������ ��� ���������� �������� ������ 3
//extern std::vector <float> FalseEpoImposBufChan3; // ������ ��� ���������� �������� ������ 3
//
//
//// ������� ����������� �������. ������ ������� - ���������� �������� ������� �� ���������. 1 � ������ - ��������� ��������, 0 - ���
//extern std::vector <float> Number049; // ������ ��� ���������� �������� ������ 3
//extern std::vector <float> Number5099; // ������ ��� ���������� �������� ������ 3
//extern std::vector <float> Number100149; // ������ ��� ���������� �������� ������ 3

extern void testOut(DWORD dwObjectIndex, DWORD NumOfInstruments);
//extern std::vector <CString> TruOrFalseCardEPO; // ������ ��� ���������� ������ �� ����� ����(����� ��� ���) ��� ��������� ����

class ASATest
{
public:
	ASATest();
	virtual ~ASATest();
	// ���������� ����� ��������
	CString getUrlPic();
private:
	//  �������� ������ ��������
//	std::vector<int> v_AvailableUrl;
//	std::vector <int> respOpt1(2);// ������ ���������� ��������� �������
	bool EndGenNumPic;
	
public:
	// �������������
	bool InitASATest();
	bool EndGenNum();
	int GetSizeVec();
	CString GetActualNumPic();

	
	// ��������� ����
	//void ImposEpo(CString);
};

struct MyStruct
{
	// �������� � �������
	/*float updInfChan0;
	float updInfChan1;
	float updInfChan2;
	float updInfChan3;
	float updInfChan4;*/
	
	std::vector <float> updInfChan;


	// ������������ �������
	//CString TextInfChan0;
	//CString TextInfChan1;
	//CString TextInfChan2;
	//CString TextInfChan3;
	//CString TextInfChan4;
	//CString TextInfChan[4];

	std::vector <CString> TextInfChan;
	//��������� �����
	CString ChouseCard;

	//����� ������� ��������
	CString NumActualCard;

	//�������� ��������?
	CString TruOrFalseCard;

	// �������� �������
	CString TimeInterval;


	//�������, ���, ��������
	CString SureName;
	CString Name;
	CString SecName;

	int SumChouseTrue;
	int SumChouseFalse;
	//std::vector <float> EpoImpos(2); // ������ ��� ���������� �������� ������ 0
	//std::vector <float> EpoImposBuf(2); // ������ ��� ���������� �������� ������ 0

};

extern MyStruct UpdInfoVal;