#pragma once
#include <vector>
#include <atlstr.h>
//#include <afxstr.h>
class SumEpochClass
{
public:
	SumEpochClass();
	virtual ~SumEpochClass();
public:
	

	//float * TrueSumEpoChan0; // ������ ��� ���������� �������� ������ 0
	//float * TrueSumEpoChan1; // ������ ��� ���������� �������� ������ 1
	//float *  TrueSumEpoChan2; // ������ ��� ���������� �������� ������ 2
	//float * TrueSumEpoChan3; // ������ ��� ���������� �������� ������ 3

	//float *  FalseSumEpoChan0; // ������ ��� ���������� �������� ������ 0
	//float * FalseSumEpoChan1; // ������ ��� ���������� �������� ������ 1
	//float * FalseSumEpoChan2; // ������ ��� ���������� �������� ������ 2
	//float *  FalseSumEpoChan3; // ������ ��� ���������� �������� ������ 3
							 
	//int positionNum[50];// �������� - 1; ���������� - 2;
struct MyStruct1
	{

		//std::vector <float> TrueSumEpoChan0; // ������ ��� ���������� �������� ������ 0
		//std::vector <float> TrueSumEpoChan1; // ������ ��� ���������� �������� ������ 1
		//std::vector <float> TrueSumEpoChan2; // ������ ��� ���������� �������� ������ 2
		//std::vector <float> TrueSumEpoChan3; // ������ ��� ���������� �������� ������ 3

		std::vector<std::vector<float>> TrueSumEpoChan;
		std::vector<std::vector<float>> FalseSumEpoChan;

		//std::vector <float> FalseSumEpoChan0; // ������ ��� ���������� �������� ������ 0
		//std::vector <float> FalseSumEpoChan1; // ������ ��� ���������� �������� ������ 1
		//std::vector <float> FalseSumEpoChan2; // ������ ��� ���������� �������� ������ 2
		//std::vector <float> FalseSumEpoChan3; // ������ ��� ���������� �������� ������ 3





		// ����������� ������
		std::vector <float> STrue;
		std::vector <float> SFalse;
		// ������������������ ����������
		std::vector <float> SigmaTrue;
		std::vector <float> SigmaFalse;

		// ������� ����������� ������
		std::vector <float> SigmaTempChan;
		std::vector <std::vector <float>> SigmaTrueChan; // ������ ��� ���������� �������� �������
		std::vector <std::vector <float>> SigmaFalseChan; // ������ ��� ���������� �������� ������ 0

		//std::vector <float> SigmaTrueChan0; // ������ ��� ���������� �������� ������ 0
		//std::vector <float> SigmaTrueChan1; // ������ ��� ���������� �������� ������ 1
		//std::vector <float> SigmaTrueChan2; // ������ ��� ���������� �������� ������ 2
		//std::vector <float> SigmaTrueChan3; // ������ ��� ���������� �������� ������ 3

		//std::vector <float> SigmaFalseChan0; // ������ ��� ���������� �������� ������ 0
		//std::vector <float> SigmaFalseChan1; // ������ ��� ���������� �������� ������ 1
		//std::vector <float> SigmaFalseChan2; // ������ ��� ���������� �������� ������ 2
		//std::vector <float> SigmaFalseChan3; // ������ ��� ���������� �������� ������ 3


		// ������ �������� ����

		std::vector< std::vector <std::vector <float>>> TrueOnlyEpoch; // ���������� ������ �������������� ����
																//�������. [k][j][i] �� �������� � ������, ��� i - �������, j - ������, k - ��������

		std::vector< std::vector <std::vector <float>>> FalseOnlyEpoch; // ���������� ������ �������������� ����
																	   //�������. [k][j][i] �� �������� � ������, ��� i - �������, j - ������, k - ��������
		// ������� ��� �������� ��������� ����
		std::vector <CString> TrueNumCard;
		std::vector <CString> FalseNumCard;

		void ClearVec();
		void ResizeVec(int SizeVec);
		int TrueNumEpoch;
		int FalseNumEpoch;
	}ChanImpos;
void OutImposEpo(std::vector<std::vector<float>> Chan, //std::vector <__int64> TimeVector,  
					std::vector <CString> truOrFalseCard, std::vector <CString> numActualCard,
					int firstNum, int lastNum, CString categoryName, char * FileName);
	void ResetVal();
	void SetSizeVec(int SizeVec);

private:
	std::vector <float> averageXTrue;
	std::vector <float> averageXFalse;

	

	void Sigma(int);// ����������� ������

};

