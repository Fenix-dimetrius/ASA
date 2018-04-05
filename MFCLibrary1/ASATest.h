#pragma once
#include <vector>

extern bool StartRecorPlay; // проверка на запуск записи
extern bool fullscr; // показывает, начат ли тест

//
//					 // наложение эпох при верных ответах
//extern std::vector <float> TrueEpoImposChan0; // вектор для сохранения значения канала 0
//extern std::vector <float> TrueEpoImposBufChan0; // вектор для сохранения значения канала 0
//
//extern std::vector <float> TrueEpoImposChan1; // вектор для сохранения значения канала 1
//extern std::vector <float> TrueEpoImposBufChan1; // вектор для сохранения значения канала 1
//
//extern std::vector <float> TrueEpoImposChan2; // вектор для сохранения значения канала 2
//extern std::vector <float> TrueEpoImposBufChan2; // вектор для сохранения значения канала 2
//
//extern std::vector <float> TrueEpoImposChan3; // вектор для сохранения значения канала 3
//extern std::vector <float> TrueEpoImposBufChan3; // вектор для сохранения значения канала 3
//
//
//					// наложение эпох при НЕверных ответах
//extern std::vector <float> FalseEpoImposChan0; // вектор для сохранения значения канала 0
//extern std::vector <float> FalseEpoImposBufChan0; // вектор для сохранения значения канала 0
//
//extern std::vector <float> FalseEpoImposChan1; // вектор для сохранения значения канала 1
//extern std::vector <float> FalseEpoImposBufChan1; // вектор для сохранения значения канала 1
//
//extern std::vector <float> FalseEpoImposChan2; // вектор для сохранения значения канала 2
//extern std::vector <float> FalseEpoImposBufChan2; // вектор для сохранения значения канала 2
//
//extern std::vector <float> FalseEpoImposChan3; // вектор для сохранения значения канала 3
//extern std::vector <float> FalseEpoImposBufChan3; // вектор для сохранения значения канала 3
//
//
//// вектора вероятности ответов. развер вектора - количество выпавших номеров из интервала. 1 в ячейке - правильно отгадано, 0 - нет
//extern std::vector <float> Number049; // вектор для сохранения значения канала 3
//extern std::vector <float> Number5099; // вектор для сохранения значения канала 3
//extern std::vector <float> Number100149; // вектор для сохранения значения канала 3

extern void testOut(DWORD dwObjectIndex, DWORD NumOfInstruments);
//extern std::vector <CString> TruOrFalseCardEPO; // вектор для сохранения ответа на выбор карт(верно или нет) для наложения эпох

class ASATest
{
public:
	ASATest();
	virtual ~ASATest();
	// возвращает адрес картинки
	CString getUrlPic();
private:
	//  содержит номера картинок
//	std::vector<int> v_AvailableUrl;
//	std::vector <int> respOpt1(2);// вектор сохранения вариантов ответов
	bool EndGenNumPic;
	
public:
	// инициализация
	bool InitASATest();
	bool EndGenNum();
	int GetSizeVec();
	CString GetActualNumPic();

	
	// наложение эпох
	//void ImposEpo(CString);
};

struct MyStruct
{
	// значения в каналах
	/*float updInfChan0;
	float updInfChan1;
	float updInfChan2;
	float updInfChan3;
	float updInfChan4;*/
	
	std::vector <float> updInfChan;


	// наименование каналов
	//CString TextInfChan0;
	//CString TextInfChan1;
	//CString TextInfChan2;
	//CString TextInfChan3;
	//CString TextInfChan4;
	//CString TextInfChan[4];

	std::vector <CString> TextInfChan;
	//выбранная карта
	CString ChouseCard;

	//Номер текущей картинки
	CString NumActualCard;

	//отгадана картинка?
	CString TruOrFalseCard;

	// Интервал времени
	CString TimeInterval;


	//Фамилия, имя, отчество
	CString SureName;
	CString Name;
	CString SecName;

	int SumChouseTrue;
	int SumChouseFalse;
	//std::vector <float> EpoImpos(2); // вектор для сохранения значения канала 0
	//std::vector <float> EpoImposBuf(2); // вектор для сохранения значения канала 0

};

extern MyStruct UpdInfoVal;