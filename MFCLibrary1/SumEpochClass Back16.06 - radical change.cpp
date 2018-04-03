#include "stdafx.h"
#include "SumEpochClass.h"
#include "ASADlg.h"
#include <fstream>
#include <exception>


SumEpochClass::SumEpochClass()
{

}


SumEpochClass::~SumEpochClass()
{
	ChanImpos.ClearVec();

	//освобождение векторов среднего значения, отклонения и ошибки
	averageXFalse.clear();
	averageXFalse.shrink_to_fit();


	averageXTrue.clear();
	averageXTrue.shrink_to_fit();

	ChanImpos.SigmaFalse.clear();
	ChanImpos.SigmaFalse.shrink_to_fit();

	ChanImpos.SigmaTrue.clear();
	ChanImpos.SigmaTrue.shrink_to_fit();

	ChanImpos.STrue.clear();
	ChanImpos.STrue.shrink_to_fit();


	ChanImpos.SFalse.clear();
	ChanImpos.SFalse.shrink_to_fit();
	


	



	



}


void SumEpochClass::OutImposEpo( std::vector<std::vector<float>> Chan, std::vector<CString> truOrFalseCard, std::vector<CString> numActualCard, int firstNum, int lastNum, CString categoryName, char * FileName)
{

			averageXTrue.resize(Chan[0].size()); // 4 канала
		averageXFalse.resize(Chan[0].size());

		ChanImpos.SigmaFalse.resize(Chan[0].size());
		ChanImpos.SigmaTrue.resize(Chan[0].size());
	
		ChanImpos.STrue.resize(Chan[0].size());
		ChanImpos.SFalse.resize(Chan[0].size());


		int vecSize = (m_AfterShow + m_ShowTime + m_BeforeShow + m_DelaySpeedMouse) / (float)measureInterval; // размер вектора эпохи - число строк эпохи =  его время.
		int k1 = 0;
	
		
		
		//MyStruct1 ChanVec;
	
		ChanImpos.TrueNumEpoch = 0; // количество эпох правильных выборов
		ChanImpos.FalseNumEpoch = 0; // количество эпох неправильных выборов
	
	
	
		//SetSizeVec(vecSize);
		ChanImpos.ResizeVec(vecSize+1 ); // задаем размер векторов, учитывая интервал предзаписи. 

		std::vector  <float> Truetemp0; // временный массив
		std::vector  <std::vector  <float>> Truetemp1; // временный массив

		std::vector  <float> Falsetemp0; // временный массив
		std::vector  <std::vector  <float>> Falsetemp1; // временный массив
		bool isTrueAns;

		std::vector<float> TempTrueSum;//(Chan[0].size());
		std::vector<float> TempFalseSum;//(Chan[0].size());

		int nBefRec = 0;
		nBefRec = m_DelaySpeedMouse / (float)measureInterval;
		for (int i1 = 0; i1 < numActualCard.size(); i1++)
		{
			
			//std::vector  <float> Truetemp0; // временный массив
			// находим сумму моментов времени каждой эпохи
			if (truOrFalseCard[i1] != " " && firstNum <= atoi(numActualCard[i1]) && atoi(numActualCard[i1]) <= lastNum && k1 <= vecSize)
			{
				
				if (truOrFalseCard[i1] == "True")
				{
					
					/*try
					{*/
						if (k1 == 0)
						{
							ChanImpos.TrueNumEpoch++;
							// сохраняем номер выбранной карты
							ChanImpos.TrueNumCard.push_back(numActualCard[i1]);
							isTrueAns = true;

							// Реализация предзаписи
							// вычисляем кол-во отсчетов времени предзаписи
						//	nBefRec = m_DelaySpeedMouse/(float)measureInterval;

							for (int t1 = nBefRec; t1 > 0;t1--)
							{
								if (k1 == nBefRec) break;
								for (int f1 = 0; f1 < Chan[0].size();f1++)
								{
									//ChanImpos.TrueSumEpoChan0[k1] = ChanImpos.TrueSumEpoChan0[k1] + Chan[f1][i1 - t1];
									/*if (t1 == nBefRec)
									{
										TempTrueSum.push_back(Chan[i1 - t1][f1]);
									}
									else
									{
										TempTrueSum.push_back(ChanImpos.TrueSumEpoChan[k1-1][f1] + Chan[i1 - t1][f1]);
									}*/
									TempTrueSum.push_back(Chan[i1 - t1][f1]);
									// необработанные эпохи
									Truetemp0.push_back(Chan[i1 - t1][f1]);


								}
								ChanImpos.TrueSumEpoChan.push_back(TempTrueSum);

								TempTrueSum.clear();
								TempTrueSum.shrink_to_fit();

								// и прибавляем строку
								Truetemp1.push_back(Truetemp0);
								// очистка одномерного временного массива
								Truetemp0.clear();
								Truetemp0.shrink_to_fit();
								k1++;
								//if (k1 == nBefRec) break;
							}
						}
					/*}
					catch (std::exception& e)
						{
						MessageBox(NULL, e.what(), "	", MB_OK);
						}*/
					for (int f1 = 0; f1 < Chan[0].size();f1++) // чет не доходит до сюда
					{

					
						TempTrueSum.push_back(ChanImpos.TrueSumEpoChan[k1-1][f1] + Chan[i1][f1]);
					

						// необработанные эпохи
						
						

						//ChanImpos.TrueSumEpoChan0[k1] = ChanImpos.TrueSumEpoChan0[k1] + Chan[f1][i1];
						//заполняем столбцы каналов
						Truetemp0.push_back(Chan[i1][f1]);
					}

					ChanImpos.TrueSumEpoChan.push_back(TempTrueSum);

					TempTrueSum.clear();
					TempTrueSum.shrink_to_fit();


					/*ChanImpos.TrueSumEpoChan0[k1] = ChanImpos.TrueSumEpoChan0[k1] + Chan0[i1];
					ChanImpos.TrueSumEpoChan1[k1] = ChanImpos.TrueSumEpoChan1[k1] + Chan1[i1];
					ChanImpos.TrueSumEpoChan2[k1] = ChanImpos.TrueSumEpoChan2[k1] + Chan2[i1];
					ChanImpos.TrueSumEpoChan3[k1] = ChanImpos.TrueSumEpoChan3[k1] + Chan3[i1];*/

					// для вывода необработанных эпох
					
					//заполняем столбцы каналов
					/*Truetemp0.push_back(Chan0[i1]);
					Truetemp0.push_back(Chan1[i1]);
					Truetemp0.push_back(Chan2[i1]);
					Truetemp0.push_back(Chan3[i1]);*/
					
					// и прибавляем строку
					Truetemp1.push_back(Truetemp0);
					
					// добавляется двумерный массив в трехмерный (добавляем лист)
					if (k1 == vecSize)
					{
						ChanImpos.TrueOnlyEpoch.push_back(Truetemp1);

						// очистка временного двумерного массива
						Truetemp1.clear();
						Truetemp1.shrink_to_fit();
					}
					// очистка одномерного временного массива
					Truetemp0.clear();
					Truetemp0.shrink_to_fit();
				}
				if (truOrFalseCard[i1] == "False")
				{
					

					if (k1 == 0)
					{
						ChanImpos.FalseNumEpoch++;
						// сохраняем номер выбранной карты
						ChanImpos.FalseNumCard.push_back(numActualCard[i1]);
						isTrueAns = false;
						// Реализация предзаписи
						// вычисляем кол-во отсчетов времени предзаписи
						//nBefRec = m_DelaySpeedMouse / (float)measureInterval;

						for (int t1 = nBefRec; t1 > 0; t1--)
						{
							//std::vector<float> TempTrueSum();
							//if (k1 == nBefRec) break;
							for (int f1 = 0; f1 < Chan[0].size();f1++)
							{
								//ChanImpos.TrueSumEpoChan0[k1] = ChanImpos.TrueSumEpoChan0[k1] + Chan[f1][i1 - t1];
								//if (t1 == nBefRec)
								//{
								//	TempFalseSum.push_back(Chan[i1 - t1][f1]);//TempFalseSum[f1]
								//}
								//else
								//{
								//	TempFalseSum.push_back(ChanImpos.FalseSumEpoChan[k1-1][f1] + Chan[i1 - t1][f1]);
								//	//TempFalseSum.push_back(ChanImpos.FalseSumEpoChan.back + Chan[i1 - t1][f1]);
								//}
								TempFalseSum.push_back(Chan[i1 - t1][f1]);
								// необработанные эпохи
								Falsetemp0.push_back(Chan[i1 - t1][f1]);

								
							}
							ChanImpos.FalseSumEpoChan.push_back(TempFalseSum);
							TempFalseSum.clear();
							TempFalseSum.shrink_to_fit();

							// и прибавляем строку
							Falsetemp1.push_back(Falsetemp0);
							// очистка одномерного временного массива
							Falsetemp0.clear();
							Falsetemp0.shrink_to_fit();
							k1++;
							
						}
					}




					for (int f1 = 0; f1 < Chan[0].size();f1++)
					{


						TempFalseSum.push_back(ChanImpos.FalseSumEpoChan[k1 - 1][f1 ] + Chan[i1][f1]);
						
						// необработанные эпохи
						//заполняем столбцы каналов
						Falsetemp0.push_back(Chan[i1][f1]);
					}

					ChanImpos.FalseSumEpoChan.push_back(TempFalseSum);

					TempFalseSum.clear();
					TempFalseSum.shrink_to_fit();

					// для вывода необработанных эпох
					// и прибавляем строку
					Falsetemp1.push_back(Falsetemp0);
				
					// добавляем двумерный массив в трехмерный (добавляем лист)
					if (k1 == vecSize)
					{
						ChanImpos.FalseOnlyEpoch.push_back(Falsetemp1);

						// очистка временного двумерного массива
						Falsetemp1.clear();
						Falsetemp1.shrink_to_fit();
					}
					// очистка одномерного временного массива
					Falsetemp0.clear();
					Falsetemp0.shrink_to_fit();
				}
	
				k1++;
			}		
							
				if (truOrFalseCard[i1] == " ")
				{
					k1 = 0;
				}
						
		}
	
		// делим сумму значений эпох на общее 
	
		for (int i2 = 0; i2 < ChanImpos.TrueSumEpoChan.size(); i2++)
		{

			for (int f1 = 0; f1 < Chan[0].size();f1++)
			{
				//FalseSumEpoChan[k1 - 1][f1]
				if (ChanImpos.TrueNumEpoch != 0 && !ChanImpos.TrueSumEpoChan.empty())
				{
					ChanImpos.TrueSumEpoChan[i2][f1] /=(float) ChanImpos.TrueNumEpoch;
				}
				else 
				{
					if (!ChanImpos.TrueSumEpoChan.empty())
					{
						ChanImpos.TrueSumEpoChan[i2][f1] = 0;
					}

				}

				if (ChanImpos.FalseNumEpoch != 0 && !ChanImpos.FalseSumEpoChan.empty())
				{
					ChanImpos.FalseSumEpoChan[i2][f1] /= (float)ChanImpos.FalseNumEpoch; // может быть /0
				}
				else
				{
					if (!ChanImpos.FalseSumEpoChan.empty())
					{
						ChanImpos.FalseSumEpoChan[i2][f1] = 0;
					}
					
				}
			}	
			
				Sigma(i2);//расчет стандартной ошибки
			
		}

	

		
		
}

void SumEpochClass::ResetVal()
{
}

void SumEpochClass::SetSizeVec(int SizeVec)
{
	
	
}

void SumEpochClass::Sigma(int j2)
{

	//int j0 = 0;
	// среднеквадратичное отклонение

	if (ChanImpos.TrueOnlyEpoch.empty() != true)
	{

		// находим сумму квадратов. СУММ по k0( Xk(j2) - Xcp(j2)), где k0 - номер эпохи(по счету ответ), j2 - отсчет момента времени
		for (int k0 = 0; k0 < ChanImpos.TrueOnlyEpoch.size(); k0++) //ChanImpos.TrueOnlyEpoch.size() - кол-во ответов в данной категории.
																	//ChanImpos.TrueOnlyEpoch[].size() - кол-во отсчетов времени в данной категории и равно vecSize.
																	//ChanImpos.TrueOnlyEpoch[][].size() - кол-во каналов.
		{

			for (int f1 = 0; f1 < ChanImpos.SigmaTrue.size();f1++)
			{
				ChanImpos.SigmaTrue[f1] += (ChanImpos.TrueOnlyEpoch[k0][j2][f1] - ChanImpos.TrueSumEpoChan[j2][f1])*(ChanImpos.TrueOnlyEpoch[k0][j2][f1] - ChanImpos.TrueSumEpoChan[j2][f1]); // возводим в квадрат и суммируем
			}

			//ChanImpos.SigmaTrue[0] += (ChanImpos.TrueOnlyEpoch[k0][j2][0] - ChanImpos.TrueSumEpoChan0[j2])*(ChanImpos.TrueOnlyEpoch[k0][j2][0] - ChanImpos.TrueSumEpoChan0[j2]); // возводим в квадрат и суммируем
			//ChanImpos.SigmaTrue[1] += (ChanImpos.TrueOnlyEpoch[k0][j2][1] - ChanImpos.TrueSumEpoChan1[j2])*(ChanImpos.TrueOnlyEpoch[k0][j2][1] - ChanImpos.TrueSumEpoChan1[j2]); // возводим в квадрат и суммируем
			//ChanImpos.SigmaTrue[2] += (ChanImpos.TrueOnlyEpoch[k0][j2][2] - ChanImpos.TrueSumEpoChan2[j2])*(ChanImpos.TrueOnlyEpoch[k0][j2][2] - ChanImpos.TrueSumEpoChan2[j2]); // возводим в квадрат и суммируем
			//ChanImpos.SigmaTrue[3] += (ChanImpos.TrueOnlyEpoch[k0][j2][3] - ChanImpos.TrueSumEpoChan3[j2])*(ChanImpos.TrueOnlyEpoch[k0][j2][3] - ChanImpos.TrueSumEpoChan3[j2]); // возводим в квадрат и суммируем

		}


		// берем корень из полученного результата
		int k1 = (ChanImpos.TrueOnlyEpoch.size()*(ChanImpos.TrueOnlyEpoch.size() - 1));// по формуле: (n(n-1)), где n - кол-во эпох
		
		if (k1 != 0) // защита от -nan в файле на выходе
		{
			try
			{
				for (int f1 = 0; f1 < ChanImpos.SigmaTrue.size();f1++)
				{
					ChanImpos.SigmaTempChan.push_back(sqrt(ChanImpos.SigmaTrue[f1] / (float)k1));
				}
				ChanImpos.SigmaTrueChan.push_back(ChanImpos.SigmaTempChan);
				// clear
				ChanImpos.SigmaTempChan.clear();
				ChanImpos.SigmaTempChan.shrink_to_fit();
			}
			
			catch (std::exception& e)
			{
				MessageBox(NULL, e.what(), "	", MB_OK);
			}

			

			//ChanImpos.SigmaTrueChan0[j2] = sqrt(ChanImpos.SigmaTrue[0] / k1);  // ChanImpos.SigmaTrue[0] - содержит формулу СУММ по k0( Xk(j2) - Xcp(j2)), где k0 - номер эпохи(по счету ответ), j2 - отсчет момента времени
			//ChanImpos.SigmaTrueChan1[j2] = sqrt(ChanImpos.SigmaTrue[1] / k1);
			//ChanImpos.SigmaTrueChan2[j2] = sqrt(ChanImpos.SigmaTrue[2] / k1);
			//ChanImpos.SigmaTrueChan3[j2] = sqrt(ChanImpos.SigmaTrue[3] / k1);
		}
		else
		{
			for (int f1 = 0; f1 < ChanImpos.SigmaTrue.size();f1++)
			{
				ChanImpos.SigmaTempChan.push_back(0);
			}

			ChanImpos.SigmaTrueChan.push_back(ChanImpos.SigmaTempChan);

			ChanImpos.SigmaTempChan.clear();
			ChanImpos.SigmaTempChan.shrink_to_fit();
/*
			ChanImpos.SigmaTrueChan0[j2] = 0;  
			ChanImpos.SigmaTrueChan1[j2] = 0;
			ChanImpos.SigmaTrueChan2[j2] = 0;
			ChanImpos.SigmaTrueChan3[j2] = 0;*/
		}
		// обнуляем вектора среднеквадр отклонения, сохраняя
		//размерность
		
		int tempSize = ChanImpos.SigmaTrue.size();
		ChanImpos.SigmaTrue.clear();
		ChanImpos.SigmaTrue.shrink_to_fit();
		ChanImpos.SigmaTrue.resize(tempSize);

	}
	else
	{
		for (int f1 = 0; f1 < ChanImpos.SigmaTrue.size();f1++)
		{
			ChanImpos.SigmaTempChan.push_back(0);
		}

		ChanImpos.SigmaTrueChan.push_back(ChanImpos.SigmaTempChan);

		ChanImpos.SigmaTempChan.clear();
		ChanImpos.SigmaTempChan.shrink_to_fit();


		/*	ChanImpos.SigmaTrueChan0[j2] = 0;
			ChanImpos.SigmaTrueChan1[j2] = 0;
			ChanImpos.SigmaTrueChan2[j2] = 0;
			ChanImpos.SigmaTrueChan3[j2] = 0;			*/

	}

	if (ChanImpos.FalseOnlyEpoch.empty() != true)
	{

		// находим сумму квадратов. СУММ по k0( Xk(j2) - Xcp(j2)), где k0 - номер эпохи(по счету ответ), j2 - отсчет момента времени
		for (int k0 = 0; k0 < ChanImpos.FalseOnlyEpoch.size(); k0++) //ChanImpos.TrueOnlyEpoch.size() - кол-во ответов в данной категории.
																	//ChanImpos.TrueOnlyEpoch[].size() - кол-во отсчетов времени в данной категории и равно vecSize.
																	//ChanImpos.TrueOnlyEpoch[][].size() - кол-во каналов.
		{
			
			for (int f1 = 0; f1 < ChanImpos.SigmaFalse.size();f1++)
			{
				//ChanImpos.SigmaFalse[f1] += (ChanImpos.FalseOnlyEpoch[k0][j2][0] - ChanImpos.TrueSumEpoChan[j2][f1])*(ChanImpos.TrueOnlyEpoch[k0][j2][0] - ChanImpos.TrueSumEpoChan[j2][f1]); // возводим в квадрат и суммируем
				ChanImpos.SigmaFalse[f1] += (ChanImpos.FalseOnlyEpoch[k0][j2][f1] - ChanImpos.FalseSumEpoChan[j2][f1])*(ChanImpos.FalseOnlyEpoch[k0][j2][f1] - ChanImpos.FalseSumEpoChan[j2][f1]); // возводим в квадрат и суммируем
			}

			//ChanImpos.SigmaFalse[0] += (ChanImpos.FalseOnlyEpoch[k0][j2][0] - ChanImpos.FalseSumEpoChan0[j2])*(ChanImpos.FalseOnlyEpoch[k0][j2][0] - ChanImpos.FalseSumEpoChan0[j2]); // возводим в квадрат и суммируем
			//ChanImpos.SigmaFalse[1] += (ChanImpos.FalseOnlyEpoch[k0][j2][1] - ChanImpos.FalseSumEpoChan1[j2])*(ChanImpos.FalseOnlyEpoch[k0][j2][1] - ChanImpos.FalseSumEpoChan1[j2]); // возводим в квадрат и суммируем
			//ChanImpos.SigmaFalse[2] += (ChanImpos.FalseOnlyEpoch[k0][j2][2] - ChanImpos.FalseSumEpoChan2[j2])*(ChanImpos.FalseOnlyEpoch[k0][j2][2] - ChanImpos.FalseSumEpoChan2[j2]); // возводим в квадрат и суммируем
			//ChanImpos.SigmaFalse[3] += (ChanImpos.FalseOnlyEpoch[k0][j2][3] - ChanImpos.FalseSumEpoChan3[j2])*(ChanImpos.FalseOnlyEpoch[k0][j2][3] - ChanImpos.FalseSumEpoChan3[j2]); // возводим в квадрат и суммируем


		}


		// берем корень из полученного результата
		int k1 = (ChanImpos.FalseOnlyEpoch.size()*(ChanImpos.FalseOnlyEpoch.size() - 1));// по формуле: (n(n-1)), где n - кол-во эпох

		// ChanImpos.SigmaTrue[0] - содержит формулу СУММ по k0( Xk(j2) - Xcp(j2)), где k0 - номер эпохи(по счету ответ), j2 - отсчет момента времени
		if (k1 != 0) // защита от -nan в файле на выходе
		{
			for (int f1 = 0; f1 < ChanImpos.SigmaTrue.size();f1++)
			{
				ChanImpos.SigmaTempChan.push_back(sqrt(ChanImpos.SigmaFalse[f1] / (float)k1));
			}

			ChanImpos.SigmaFalseChan.push_back(ChanImpos.SigmaTempChan);

			ChanImpos.SigmaTempChan.clear();
			ChanImpos.SigmaTempChan.shrink_to_fit();


			/*ChanImpos.SigmaFalseChan0[j2] = sqrt(ChanImpos.SigmaFalse[0] / k1);
			ChanImpos.SigmaFalseChan1[j2] = sqrt(ChanImpos.SigmaFalse[1] / k1);
			ChanImpos.SigmaFalseChan2[j2] = sqrt(ChanImpos.SigmaFalse[2] / k1);
			ChanImpos.SigmaFalseChan3[j2] = sqrt(ChanImpos.SigmaFalse[3] / k1);*/
		}

		else
		{
			for (int f1 = 0; f1 < ChanImpos.SigmaTrue.size();f1++)
			{
				ChanImpos.SigmaTempChan.push_back(0);
			}

			ChanImpos.SigmaFalseChan.push_back(ChanImpos.SigmaTempChan);

			ChanImpos.SigmaTempChan.clear();
			ChanImpos.SigmaTempChan.shrink_to_fit();
/*
			ChanImpos.SigmaFalseChan0[j2] = 0;
			ChanImpos.SigmaFalseChan1[j2] = 0;
			ChanImpos.SigmaFalseChan2[j2] = 0;
			ChanImpos.SigmaFalseChan3[j2] = 0;*/
		}
		// обнуляем вектора среднеквадр отклонения, сохраняя
		//размерность
		
		int tempSize = ChanImpos.SigmaFalse.size();
		ChanImpos.SigmaFalse.clear();
		ChanImpos.SigmaFalse.shrink_to_fit();
		ChanImpos.SigmaFalse.resize(tempSize);

	}
	else
	{
		
		for (int f1 = 0; f1 < ChanImpos.SigmaTrue.size();f1++)
		{
			ChanImpos.SigmaTempChan.push_back(0);
		}

		ChanImpos.SigmaFalseChan.push_back(ChanImpos.SigmaTempChan);

		ChanImpos.SigmaTempChan.clear();
		ChanImpos.SigmaTempChan.shrink_to_fit();
/*
		ChanImpos.SigmaFalseChan0[j2] = 0;
		ChanImpos.SigmaFalseChan1[j2] = 0;
		ChanImpos.SigmaFalseChan2[j2] = 0;
		ChanImpos.SigmaFalseChan3[j2] = 0;*/

	}



}

void SumEpochClass::MyStruct1::ClearVec()
{
	// очистка векторов
	TrueSumEpoChan.clear(); // вектор для сохранения значения канала 0
	//TrueSumEpoChan1.clear(); // вектор для сохранения значения канала 1
	//TrueSumEpoChan2.clear(); // вектор для сохранения значения канала 2
	//TrueSumEpoChan3.clear(); // вектор для сохранения значения канала 3

	FalseSumEpoChan.clear(); // вектор для сохранения значения канала 0
	//FalseSumEpoChan1.clear();// вектор для сохранения значения канала 1
	//FalseSumEpoChan2.clear(); // вектор для сохранения значения канала 2
	//FalseSumEpoChan3.clear(); // вектор для сохранения значения канала 3


							  // освобождения мощностей
	TrueSumEpoChan.shrink_to_fit(); // вектор для сохранения значения канала 0
	//TrueSumEpoChan1.shrink_to_fit(); // вектор для сохранения значения канала 1
	//TrueSumEpoChan2.shrink_to_fit(); // вектор для сохранения значения канала 2
	//TrueSumEpoChan3.shrink_to_fit(); // вектор для сохранения значения канала 3

	FalseSumEpoChan.shrink_to_fit(); // вектор для сохранения значения канала 0
	//FalseSumEpoChan1.shrink_to_fit();// вектор для сохранения значения канала 1
	//FalseSumEpoChan2.shrink_to_fit(); // вектор для сохранения значения канала 2
	//FalseSumEpoChan3.shrink_to_fit(); // вектор для сохранения значения канала 3



	SigmaTrueChan.clear();
	/*SigmaTrueChan1.clear();
	SigmaTrueChan2.clear();
	SigmaTrueChan3.clear();*/

	SigmaFalseChan.clear();
	/*SigmaFalseChan1.clear();
	SigmaFalseChan2.clear();
	SigmaFalseChan3.clear();*/


	SigmaTrueChan.shrink_to_fit();
	//SigmaTrueChan1.shrink_to_fit();
	//SigmaTrueChan2.shrink_to_fit();
	//SigmaTrueChan3.shrink_to_fit();

	SigmaFalseChan.shrink_to_fit();
	//SigmaFalseChan1.shrink_to_fit();
	//SigmaFalseChan2.shrink_to_fit();
	//SigmaFalseChan3.shrink_to_fit();

	TrueOnlyEpoch.clear();
	TrueOnlyEpoch.shrink_to_fit();

	FalseOnlyEpoch.clear();
	FalseOnlyEpoch.shrink_to_fit();
}

void SumEpochClass::MyStruct1::ResizeVec(int SizeVec)
{
	//TrueSumEpoChan0.resize(SizeVec); // вектор для сохранения значения канала 0
	//TrueSumEpoChan1.resize(SizeVec); // вектор для сохранения значения канала 1
	//TrueSumEpoChan2.resize(SizeVec); // вектор для сохранения значения канала 2
	//TrueSumEpoChan3.resize(SizeVec); // вектор для сохранения значения канала 3

	//FalseSumEpoChan0.resize(SizeVec); // вектор для сохранения значения канала 0
	//FalseSumEpoChan1.resize(SizeVec); // вектор для сохранения значения канала 1
	//FalseSumEpoChan2.resize(SizeVec); // вектор для сохранения значения канала 2
	//FalseSumEpoChan3.resize(SizeVec); // вектор для сохранения значения канала 3

	//SigmaTrueChan.resize(SizeVec);
	//SigmaFalseChan.resize(SizeVec);


	/*SigmaTrueChan0.resize(SizeVec);
	SigmaTrueChan1.resize(SizeVec);
	SigmaTrueChan2.resize(SizeVec);
	SigmaTrueChan3.resize(SizeVec);

	SigmaFalseChan0.resize(SizeVec);
	SigmaFalseChan1.resize(SizeVec);
	SigmaFalseChan2.resize(SizeVec);
	SigmaFalseChan3.resize(SizeVec);
*/

//// изменяем размер двумерного вектора
//	OnlyEpoch.resize(4); // по столбцам
//	for (int i1 = 0; i1 < OnlyEpoch.size();i1++)
//	{
//		OnlyEpoch[i1].resize(SizeVec);// по строкам
//	}
//
	//OnlyEpoch.resize(4);
}
