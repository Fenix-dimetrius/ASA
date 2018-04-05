
#include "stdafx.h"
#include "ASATest.h"
#include "ASADlg.h"
#include "TimerCls.h"
#include <fstream>
#include "SumEpochClass.h"

std::vector<int> v_Available(150);// вектор сохранения вариантов ответов
std::string file_nameEn;
char * fileNameEn;
FILE * recordEn; // файл для записи в него значений
std::vector <__int64> tickVector(2); // вектор для сохранения значения тиков

std::vector <float> tempFirstTick;
std::vector <std::vector <float>> updInfVecChan;


//std::vector <__int64> freqVector(2);// вектор сохранения частоты процессора

std::vector <CString> TimeInterval(2); // вектор для сохранения момента времени выбора карты
std::vector <CString> ChouseCard(2); // вектор для сохранения выбора карты

std::vector <CString> TruOrFalseCard(2); // вектор для сохранения ответа на выбор карт(верно или нет)
std::vector <CString> NumActualCard(2); // вектор для сохранения текущей картинки


//int i001 = 0;
void testOut(DWORD dwObjectIndex, DWORD NumOfInstruments)
{
	//i001++;
	//	std::ofstream out("PlugIns/TestASA/TestOut.csv", std::ios::app);
	//out << "\n" << NumOfInstruments << "\n";
	//out.close();
}

void ThreadTimerTick(void* pParams); // отдельный поток с таймером

//void ImposEpoFunc(); // метод наложения эпох

ASATest::ASATest()
	//: v_AllUrl(0)
{
}


ASATest::~ASATest()
{
}

CString returnVal;// возвращает адрес картинки

CString ASATest::getUrlPic()
{
	int Rand1 = 0; // рандомный номер картинки
	int xmin = 0;

	LARGE_INTEGER NumTickProc; // переменная
	QueryPerformanceCounter(&NumTickProc); // сохраняем значение тиков ЦП
	

	if (v_Available.size() >= 2) // проверка вектора на длину
	{
		Rand1 = (rand() % (v_Available.size())); // генерируем рандомное число в пределах от 0 до размера вектора
											
	}
	else // при длине вектора ==1
	{	// присваеваем просто нуль
		Rand1 = 0; // т.к. осталась всего одна ячейка в векторе
		EndGenNumPic = true;
	}
		
	returnVal.Format("\%i", v_Available[Rand1]); //конвертируем число в ячейке вектора в строку

	v_Available.erase(v_Available.begin() + Rand1); // удаляем ячейку по номером Rand1
	std::vector<int>(v_Available).swap(v_Available); // обновляем вектор для изменения размера
		
	
												  
	// Применим метод Таратухина.

	int X1, X2;

	X2 = NumTickProc.QuadPart % 10; // делим число на 10 и запоминаем остаток. Это первый знак с конца числа NumTickProc.QuadPart

	X1 = ((NumTickProc.QuadPart % 100) - X2) / 10; // делим число на 100, запоминаем остаток и вычитаем из него Х1
												// После деления на 10 получим 2 знак с конца числа NumTickProc.QuadPart


	if ((X1 + X2) % 2 == 0) // получаем число тиков процессора проверяем на четность
	{

		if (GenNumPicBefore != true) // ключ метода генерации
		{
			UpdInfoVal.TruOrFalseCard = "True"; // верно или неверно выбранна карта
		}
		return returnVal; // если четно, то отправляем число, которое находится в сгенеренной ячейки
	}
	
	else // если нечетно 
	{
		if (GenNumPicBefore != true)// ключ метода генерации
		{
			UpdInfoVal.TruOrFalseCard = "False"; // верно или неверно выбранна карта
		}
		return CString("150"); // если нет, то серый фон
	}


}



// инициализация
bool ASATest::InitASATest()
{
	LARGE_INTEGER NumTickProc;
	QueryPerformanceCounter(&NumTickProc);
	srand(NumTickProc.QuadPart); // автоматическая рандомизация	
	v_Available.resize(150);
	//AfxMessageBox("init compl");
	EndGenNumPic = false;

	for (int i = 0; i < v_Available.size();i++)
		{
			v_Available[i] = i;
		}

	//if (StartRecorPlay == true)
	//{
		_beginthread(ThreadTimerTick, 0, NULL);// таймер 

	//}
	//else
	//{
	//	if (MessageBox(NULL, "Прибор не начал запись. Записывать данные в файл?", " ", MB_YESNO) == IDYES)
	//	{
	//		_beginthread(ThreadTimerTick, 0, NULL);// таймер 
	//	}
	//}
	//std::vector <int> respOpt1(2);// вектор сохранения вариантов ответов
	return false;
}


bool ASATest::EndGenNum()
{

	return EndGenNumPic;
}


int ASATest::GetSizeVec()
{
	return v_Available.size();
}


CString ASATest::GetActualNumPic()
{
	return returnVal;
}





//===================================== Запись в файл ==========




int MenOrWomen;



double totalTime = 0; // суммарное время записи 
SumEpochClass BufImposEpoch;// эро
void ImposEpochOut()
{
	int timeEpo = - m_BeforeShow - m_DelaySpeedMouse; //отсчет. в начале равен ...
	CString TimeIntervalEpo;// название временного интервала
	
	std::ofstream out;
	out.open(fileNameEn, std::ios::app);

	



	for (int i2 = 0; i2 < BufImposEpoch.ChanImpos.TrueSumEpoChan.size(); i2++)
	{
	
		if (timeEpo <= -m_BeforeShow)
		{
			TimeIntervalEpo = "BefRec";
		}

		if (timeEpo > -m_BeforeShow &&   timeEpo <= 0)
		{
			TimeIntervalEpo = "Before";
		}

		if (0 < timeEpo && timeEpo <= m_ShowTime)
		{
			TimeIntervalEpo = "Show";
		}

		if (m_ShowTime < timeEpo  && timeEpo <= m_ShowTime + m_AfterShow)
		{
			TimeIntervalEpo = "After";
		}

		out << timeEpo << ";" << TimeIntervalEpo << ";";

		// выводим значения эпох в файл
		//if(BufImposEpoch.ChanImpos.TrueSumEpoChan[0])
		for (int f1 = 0; f1 <BufImposEpoch.ChanImpos.TrueSumEpoChan[0].size();f1++)
		{

			out << BufImposEpoch.ChanImpos.TrueSumEpoChan[i2][f1] << ";" << BufImposEpoch.ChanImpos.SigmaTrueChan[i2][f1] << ";";

		}

		out << ";";

		for (int f1 = 0; f1 <BufImposEpoch.ChanImpos.FalseSumEpoChan[0].size();f1++)
		{

			out << BufImposEpoch.ChanImpos.FalseSumEpoChan[i2][f1] << ";" << BufImposEpoch.ChanImpos.SigmaFalseChan[i2][f1] << ";";
		
		}

		out << "\n";
		timeEpo = timeEpo + measureInterval;
	}


	// вывод необработанных эпох

	out << "\n" << "Необработанные эпохи:" << "\n";

	out << "\n" << "Верно:" << "\n";
	

	// цикл вывода выпавших номеров карт
	int ch1 = 0;
	if (BufImposEpoch.ChanImpos.TrueNumCard.empty() != true) // защита от пустого вектора. vec.size() == 0; vec[0] == err
	{
		for (int j2 = 0; j2 < BufImposEpoch.ChanImpos.TrueNumCard.size(); j2++)//size = 10;
		{
			out << ";" << BufImposEpoch.ChanImpos.TrueNumCard[j2];

			for (int f1 = 0; f1 < BufImposEpoch.ChanImpos.TrueSumEpoChan[0].size() - 1; f1++) // -1 т.к. перед номером 
																								//карты тоже есть ";"
			{
				out << ";" ;
			}
			

		}
		out << "\n";
		// выводим название каналов

		out << ";";
		for (int j3 = 0; j3 < BufImposEpoch.ChanImpos.TrueNumCard.size() * UpdInfoVal.TextInfChan.size(); j3++)
																	// умножаем кол-во каналов на кол-во ответов
		{

			out << UpdInfoVal.TextInfChan[ch1] << ";";
			//out << NameChannel[ch1] << ";";

			ch1++;
			if (ch1 > (UpdInfoVal.TextInfChan.size() - 1)) ch1 = 0; // выводим кол-во каналов через каждое
																	//число этих каналов =_= 
		}
		out << "\n";
	}
	
	else
	{
		out << "Нет верных ответов" << "\n";
	}


	// выводим название каналов
	//int ch1 = 0;
	//out << ";";
	//for (int j3 = 0; j3 < BufImposEpoch.ChanImpos.TrueNumCard.size()*4; j3++)//size = 10;
	//{
	//	
	//	out << NameChannel[ch1] << ";";
	//	
	//	ch1++;
	//	if (ch1 > 3) ch1 = 0;
	//}
	//out << "\n";
	

	timeEpo = -m_BeforeShow - m_DelaySpeedMouse; //отсчет. в начале равен ...
	
	int k1 = 0;
	if (BufImposEpoch.ChanImpos.TrueOnlyEpoch.empty() != true) // защита от пустого вектора. vec.size() == 0; vec[0] == err
	{
		


		if (BufImposEpoch.ChanImpos.TrueOnlyEpoch[0].empty() != true) // защита от пустого вектора. vec[0].size() == 0; vec[0][0] == err
		{
			for (int j1 = 0; j1 < BufImposEpoch.ChanImpos.TrueOnlyEpoch[0].size(); j1++)// TrueOnlyEpoch[k].size() при любом k один размер
			{

				for (k1 = 0; k1 < BufImposEpoch.ChanImpos.TrueOnlyEpoch.size(); k1++) // len = 3
				{

					if (BufImposEpoch.ChanImpos.TrueOnlyEpoch[0][0].empty() != true)
					{
						for (int i1 = 0; i1 < BufImposEpoch.ChanImpos.TrueOnlyEpoch[0][0].size();i1++)// TrueOnlyEpoch[k][j].size() при любом k и j один размер
						{
							
							if (i1 == 0 && k1 == 0)
							{
								out << timeEpo << ";";
								timeEpo = timeEpo + measureInterval;
							}
							out << BufImposEpoch.ChanImpos.TrueOnlyEpoch[k1][j1][i1] << ";";

							//out << BufImposEpoch.ChanImpos.TrueOnlyEpoch[k1][j1][i1] << ";";
						}
					}
					}
				out << "\n"; // перевод на новую строку
				if (k1 >= BufImposEpoch.ChanImpos.TrueOnlyEpoch.size()) k1 = 0; // какая то непонятная защита
				
			}
		}
	}
	else
	{
		out << "\n";
	}

	out << "\n" << "\n" << "Неверно:" << "\n";

	// цикл вывода выпавших номеров карт
	if (BufImposEpoch.ChanImpos.FalseNumCard.empty() != true) // защита от пустого вектора. vec.size() == 0; vec[0] == err
	{

		for (int j2 = 0; j2 < BufImposEpoch.ChanImpos.FalseNumCard.size(); j2++)//size = 10;
		{
			out << ";" << BufImposEpoch.ChanImpos.FalseNumCard[j2];// << ";" << ";" << ";";
			for (int f1 = 0; f1 < BufImposEpoch.ChanImpos.FalseSumEpoChan[0].size() - 1; f1++) // -1 т.к. перед номером 
																							  //карты тоже есть ";"
			{
				out << ";";
			}
		}

		out << "\n";

		// выводим название каналов
		ch1 = 0;
		out << ";";

		for (int j3 = 0; j3 < BufImposEpoch.ChanImpos.FalseOnlyEpoch.size() *  UpdInfoVal.TextInfChan.size(); j3++)//size = 10;
		{

			//out << NameChannel[ch1] << ";";

			out << UpdInfoVal.TextInfChan[ch1] << ";";
			ch1++;
			if (ch1 > (UpdInfoVal.TextInfChan.size()-1)) ch1 = 0;
		}
		out << "\n";
	}
	else
	{
		out << "Нет неверных ответов" << "\n";
	}


	timeEpo = -m_BeforeShow - m_DelaySpeedMouse; //отсчет. в начале равен ...
	
	k1 = 0;
	if (BufImposEpoch.ChanImpos.FalseOnlyEpoch.empty() != true) // защита от пустого вектора. vec.size() == 0; vec[0] == err
	{	

		if (BufImposEpoch.ChanImpos.FalseOnlyEpoch[0].empty() != true) // защита от пустого вектора. vec.size() == 0; vec[0] == err
		{
			for (int j1 = 0; j1 < BufImposEpoch.ChanImpos.FalseOnlyEpoch[0].size(); j1++)// TrueOnlyEpoch[k].size() при любом k один размер
			{

				for (k1 = 0; k1 < BufImposEpoch.ChanImpos.FalseOnlyEpoch.size(); k1++) // len = 3
				{

					if (BufImposEpoch.ChanImpos.FalseOnlyEpoch[0][0].empty() != true)
					{
						for (int i1 = 0; i1 < BufImposEpoch.ChanImpos.FalseOnlyEpoch[0][0].size();i1++)//  TrueOnlyEpoch[k][j].size() при любом k и j один размер
						{

							if (i1 == 0 && k1 == 0)
							{
								out << timeEpo << ";";
								timeEpo = timeEpo + measureInterval;
							}
							out << BufImposEpoch.ChanImpos.FalseOnlyEpoch[k1][j1][i1] << ";";

						}
					}

				}
				out << "\n"; // перевод на новую строку
				if (k1 >= BufImposEpoch.ChanImpos.TrueOnlyEpoch.size()) k1 = 0;
				
			}
		}
	}
	else
	{
		out << "\n";
	}

	out.close();

}

void dateTime2()
{
	char buffer1[100];
	char buffer2[100];
	time_t seconds = time(NULL);
	

	tm* timeinfo = localtime(&seconds); // получаем системное время в секундах
	
	//ASADlg dlg1;

	char* format1;
	char* format2;
	//dlg1.UpdateData(TRUE);
	//UpdateData(TRUE);
	switch (MenOrWomen)
	{
	case 0:
		format1 = "PlugIns/TestASA/Records/%Y.%m.%d(%H-%M-%S)MAN.csv";
		break;
	case 1:
		format1 = "PlugIns/TestASA/Records/%Y.%m.%d(%H-%M-%S)WOM.csv";
		break;
	default:
		format1 = "PlugIns/TestASA/Records/%Y.%m.%d(%H-%M-%S)En.csv";
		break;
	}
	
	
	//= "PlugIns/TestASA/Records/%Y.%m.%d(%H-%M-%S)En.csv";
	strftime(buffer1, 80, format1, timeinfo); //переводим его в формат 2015.02.09(HH-MM-SS) и дописываем расширение ".csv"
	std::string dataTimeStr1(buffer1, sizeof(buffer1)); // конвертируем char в string, получив, при этом, длину char
	file_nameEn = dataTimeStr1; // присваеваем полученное имя файла промежуточной переменной. Для En Excel
	fileNameEn = (char *)file_nameEn.c_str(); // создаем имя файла и при этом обратно конвертируем string в char


	double val1 = 0; // переменная результата вычисления.
	double val2 = 0; // переменная результата вычисления.
					 // Open the PROPERTY configuration for this plugin
					 //fp = fopen( g_csFileName.GetBuffer(-1),"wb" );

					 /*std::string resVec;
					 std::string pauseVec;*/
	strftime(buffer1, 80, "%Y.%m.%d(%H - %M - %S)", timeinfo);
	std::ofstream out;
	out.open(fileNameEn, std::ios::app);
	
	format2 = "%Y.%m.%d;%H-%M-%S";// Перевод в формат 2015.02.09;HH-MM-SS для удобства вывода в csv файл
	strftime(buffer2, 80, format2, timeinfo); //переводим его в формат 2015.02.09(HH-MM-SS) и дописываем расширение ".csv"
	out << "Тест завершился в: " << ";" << buffer2 << "\n";
	out <<"Студент:"<<"\n"<< UpdInfoVal.SureName << ";" << UpdInfoVal.Name <<";" << UpdInfoVal.SecName << "\n"<<"\n";
	out.close();




	// delete 
	//======================================== Наложение эпох================================================
	SumEpochClass EroImposEpoch;// эро
	SumEpochClass NegImposEpoch;// негатив
	SumEpochClass NeuImposEpoch;// нейтральные

	
	//-----------------Эро------------------------
	
	EroImposEpoch.OutImposEpo(updInfVecChan, TruOrFalseCard, NumActualCard, 0, 49, "Эротические", fileNameEn); //, updInfVecChan1, updInfVecChan2, updInfVecChan3,

	BufImposEpoch.ChanImpos = EroImposEpoch.ChanImpos; // присваеваем структуру с расчитанными векторами структуре 

	out.open(fileNameEn, std::ios::app);
	out << "\n" << "Наложение эпох" << "\n" << "\n";
	out << "Эротические" << "\n";


	out << "Верно:" << BufImposEpoch.ChanImpos.TrueNumCard.size()<<";";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size()*2; i1++)// 
	{
		out << ";" << " ";
	}
	out << ";" <<"Неверно:" << BufImposEpoch.ChanImpos.FalseNumCard.size()<<";"<<"\n";

	

	// шапки названий каналов
	out << "Time, ms" << ";" << "Time interval";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size()*2; i1++)// 
	{
		if (i1 == UpdInfoVal.TextInfChan.size() ) out << ";"<<"	";
		out << ";" << UpdInfoVal.TextInfChan[i1<UpdInfoVal.TextInfChan.size() ? i1 : (int)(i1/2.0)] << ";" << "Стандартная ошибка";
	}
	out << "\n";

	out.close(); // закрываем вывод в файл, тк в него же выводится данные из функции 	ImposEpochOut()	
	
	ImposEpochOut();// сбствн вывод в файл. Делаем так, для уменьшения кода
				
	// деструкторы
	
	EroImposEpoch.~SumEpochClass();


	////-----------------------Негативные----------------

	NegImposEpoch.OutImposEpo(updInfVecChan, TruOrFalseCard, NumActualCard, 50, 99, "Негативные", fileNameEn); //, updInfVecChan1, updInfVecChan2, updInfVecChan3,

	BufImposEpoch.ChanImpos = NegImposEpoch.ChanImpos; // присваеваем структуру с расчитанными векторами структуре 

	out.open(fileNameEn, std::ios::app);
	out << "\n" << "Наложение эпох" << "\n" << "\n";
	out << "Негативные" << "\n";


	out << "Верно:" << BufImposEpoch.ChanImpos.TrueNumCard.size() << ";";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size() * 2; i1++)// 
	{
		out << ";" << " ";
	}
	out << ";" << "Неверно:" << BufImposEpoch.ChanImpos.FalseNumCard.size() << ";" << "\n";



	// шапки названий каналов
	out << "Time, ms" << ";" << "Time interval";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size() * 2; i1++)// 
	{
		if (i1 == UpdInfoVal.TextInfChan.size()) out << ";" << "	";
		out << ";" << UpdInfoVal.TextInfChan[i1<UpdInfoVal.TextInfChan.size() ? i1 : (int)(i1 / 2.0)] << ";" << "Стандартная ошибка";
	}
	out << "\n";
	

	out.close(); // закрываем вывод в файл, тк в него же выводится данные из функции 	ImposEpochOut()	

	ImposEpochOut();// сбствн вывод в файл. Делаем так, для уменьшения кода

					
	NegImposEpoch.~SumEpochClass();



					////------------------------Нейтральные--------------

	NeuImposEpoch.OutImposEpo(updInfVecChan, TruOrFalseCard, NumActualCard, 100, 149, "Нейтральные", fileNameEn); //, updInfVecChan1, updInfVecChan2, updInfVecChan3,

	BufImposEpoch.ChanImpos = NeuImposEpoch.ChanImpos; // присваеваем структуру с расчитанными векторами структуре буфферного класса.

	out.open(fileNameEn, std::ios::app);
	out << "\n" << "Наложение эпох" << "\n" << "\n";
	out << "Нейтральные" << "\n";


	out << "Верно:" << BufImposEpoch.ChanImpos.TrueNumCard.size() << ";";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size() * 2; i1++)// 
	{
		out << ";" << " ";
	}
	out << ";" << "Неверно:" << BufImposEpoch.ChanImpos.FalseNumCard.size() << ";" << "\n";



	// шапки названий каналов
	out << "Time, ms" << ";" << "Time interval";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size() * 2; i1++)// 
	{
		if (i1 == UpdInfoVal.TextInfChan.size()) out << ";" << "	";
		out << ";" << UpdInfoVal.TextInfChan[i1<UpdInfoVal.TextInfChan.size() ? i1 : (int)(i1 / 2.0)] << ";" << "Стандартная ошибка";
	}
	out << "\n";
	

	out.close(); // закрываем вывод в файл, тк в него же выводится данные из функции 	ImposEpochOut()	

	ImposEpochOut();// сбствн вывод в файл. Делаем так, для уменьшения кода

					// деструкторы
	BufImposEpoch.~SumEpochClass();
	NeuImposEpoch.~SumEpochClass();




	// открываем файл для вывода необработанных значений
	out.open(fileNameEn, std::ios::app);
	
	
	out << "\n" << "\n" << "Необработанные значения:" << "\n";

	out << "Time, ms" ;
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size(); i1++)
	{
		out << ";" << UpdInfoVal.TextInfChan[i1];
	}

	out <<  ";" << " Time Interval" << ";" << "Chouse Card" << ";" << "TruOrFalseCard" << ";" << "NumActualCard" << "\n";

	for (int j = 1; j < updInfVecChan.size();j++)//j<tickVector.size()-2; j++)
	{

		//val1 = tickVector[j]*1000.0/(double)freqVector[j];
	
		// выводим время
		out << tickVector[j];

		//выводим показания каналов
		for (int i1 = 0; i1 < UpdInfoVal.updInfChan.size();i1++)
		{
			out << ";" << updInfVecChan[j][i1];
		}
		
		// выводим инфу о времени, выбранной карте, верном\неверном ответе, номере выпавшей карты
		 out << ";" << TimeInterval[j] << ";" << ChouseCard[j] << ";" << TruOrFalseCard[j] << ";" << NumActualCard[j] << "\n";
		//out << "\n";

		//out.close();
	}
	//std::ofstream out(fileNameEn, std::ios::app);
	out << "\n" << "ALL Time: " << totalTime << "\n";
	out.close();

	// сбрасываем массивы


	if (!updInfVecChan.empty())
	{
		for (int i1 = 0; i1 < updInfVecChan.size(); i1++)
		{
			updInfVecChan[i1].clear();
			updInfVecChan.shrink_to_fit();
		}
	}

	updInfVecChan.clear();
	updInfVecChan.shrink_to_fit();







//	tickVector.resize(2);
	tickVector.clear();
	tickVector.shrink_to_fit();
	

	//freqVector.resize(2);
	//TimeInterval.resize(2);

	TimeInterval.clear();
	TimeInterval.shrink_to_fit();

	//ChouseCard.resize(2);
	ChouseCard.clear();
	ChouseCard.shrink_to_fit();


//	TruOrFalseCard.resize(2); // вектор для сохранения ответа на выбор карт(верно или нет)
	TruOrFalseCard.clear();
	TruOrFalseCard.shrink_to_fit();

	//NumActualCard.resize(2); // вектор для сохранения текущей картинки
	NumActualCard.clear();
	NumActualCard.shrink_to_fit();

	

	MessageBox(NULL, "Record complete", "Rec", MB_OK);
}

int measureInterval = 40;
//bool accurateCounts = true;

void ThreadTimerTick(void* pParams)
{
	double n1 = 1;

	TimerCls mytimer;// инициализируем таймер

	LARGE_INTEGER Frequency, StartingTime, EndingTime;  // кол во тиков процессора

	DWORD_PTR oldMask2;

	oldMask2 = SetThreadAffinityMask(GetCurrentThread(), 1); // разрешаем использовать только второе ядро процессора
	
	QueryPerformanceCounter(&StartingTime);		// задаем начальное значение тиков

	mytimer.startTimer();        //старт таймера с указанным временем
	
	int kTrue = 0;
	int kFalse = 0;
	
	while (fullscr != false)
	{

		if (mytimer.readTimer() >= n1 * measureInterval) // выполняем через шаг n1
		{
			//cout <<mytimer.read_timer()<<"		"<< n1 << "\n";

			//tickVector[n1 - 1] = mytimer.readTimer(); //  записываем набежавшее количество тиков в вектор.
			//tickVector.resize(tickVector.size() + 1);  // увеличиваем размер веркотора на единицу.
			tickVector.push_back(mytimer.readTimer());

				updInfVecChan.push_back(UpdInfoVal.updInfChan);
		

			ChouseCard.push_back(UpdInfoVal.ChouseCard);
			//ChouseCard.resize(ChouseCard.size() + 1);

			TimeInterval.push_back(UpdInfoVal.TimeInterval);
			//TimeInterval.resize(TimeInterval.size() + 1);

			TruOrFalseCard.push_back(UpdInfoVal.TruOrFalseCard);
			//TruOrFalseCard.resize(TruOrFalseCard.size() + 1);

			NumActualCard.push_back(UpdInfoVal.NumActualCard);
			//NumActualCard.resize(NumActualCard.size() + 1);



			n1 += 1; //длительность шага
		}

		if (AccurInterval != true)
		{
			Sleep(5);

		}
		//	Sleep(5);


	}
	mytimer.stopTimer();          //остановка таймера

	QueryPerformanceCounter(&EndingTime); // обновляем количество тиков
	QueryPerformanceFrequency(&Frequency); // обновляем частоту
	SetThreadAffinityMask(GetCurrentThread(), oldMask2);   //восстановить маску использования ядер процессора  
	totalTime = 1000 * (EndingTime.QuadPart - StartingTime.QuadPart) / Frequency.QuadPart;	 // вычисляем ms с момента старта
	

	// высчитываем средние значения для наложения эпох

	

	mytimer.~TimerCls();
	dateTime2(); // запись из векторов в файл

	_endthread();
}
