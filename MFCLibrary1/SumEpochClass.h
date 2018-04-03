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
	

	//float * TrueSumEpoChan0; // вектор для сохранения значения канала 0
	//float * TrueSumEpoChan1; // вектор для сохранения значения канала 1
	//float *  TrueSumEpoChan2; // вектор для сохранения значения канала 2
	//float * TrueSumEpoChan3; // вектор для сохранения значения канала 3

	//float *  FalseSumEpoChan0; // вектор для сохранения значения канала 0
	//float * FalseSumEpoChan1; // вектор для сохранения значения канала 1
	//float * FalseSumEpoChan2; // вектор для сохранения значения канала 2
	//float *  FalseSumEpoChan3; // вектор для сохранения значения канала 3
							 
	//int positionNum[50];// отгадано - 1; неотгадано - 2;
struct MyStruct1
	{

		//std::vector <float> TrueSumEpoChan0; // вектор для сохранения значения канала 0
		//std::vector <float> TrueSumEpoChan1; // вектор для сохранения значения канала 1
		//std::vector <float> TrueSumEpoChan2; // вектор для сохранения значения канала 2
		//std::vector <float> TrueSumEpoChan3; // вектор для сохранения значения канала 3

		std::vector<std::vector<float>> TrueSumEpoChan;
		std::vector<std::vector<float>> FalseSumEpoChan;

		//std::vector <float> FalseSumEpoChan0; // вектор для сохранения значения канала 0
		//std::vector <float> FalseSumEpoChan1; // вектор для сохранения значения канала 1
		//std::vector <float> FalseSumEpoChan2; // вектор для сохранения значения канала 2
		//std::vector <float> FalseSumEpoChan3; // вектор для сохранения значения канала 3





		// стандартная ошибка
		std::vector <float> STrue;
		std::vector <float> SFalse;
		// среднеквадратичное отклонение
		std::vector <float> SigmaTrue;
		std::vector <float> SigmaFalse;

		// вектора стандартных ошибок
		std::vector <float> SigmaTempChan;
		std::vector <std::vector <float>> SigmaTrueChan; // вектор для сохранения значения каналов
		std::vector <std::vector <float>> SigmaFalseChan; // вектор для сохранения значения канала 0

		//std::vector <float> SigmaTrueChan0; // вектор для сохранения значения канала 0
		//std::vector <float> SigmaTrueChan1; // вектор для сохранения значения канала 1
		//std::vector <float> SigmaTrueChan2; // вектор для сохранения значения канала 2
		//std::vector <float> SigmaTrueChan3; // вектор для сохранения значения канала 3

		//std::vector <float> SigmaFalseChan0; // вектор для сохранения значения канала 0
		//std::vector <float> SigmaFalseChan1; // вектор для сохранения значения канала 1
		//std::vector <float> SigmaFalseChan2; // вектор для сохранения значения канала 2
		//std::vector <float> SigmaFalseChan3; // вектор для сохранения значения канала 3


		// чистые значения эпох

		std::vector< std::vector <std::vector <float>>> TrueOnlyEpoch; // трехмерный вектор необработанных эпох
																//каналов. [k][j][i] по аналогии с книгой, где i - столбцы, j - строки, k - страницы

		std::vector< std::vector <std::vector <float>>> FalseOnlyEpoch; // трехмерный вектор необработанных эпох
																	   //каналов. [k][j][i] по аналогии с книгой, где i - столбцы, j - строки, k - страницы
		// вектора для зранения выбранных карт
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

	

	void Sigma(int);// стандартная ошибка

};

