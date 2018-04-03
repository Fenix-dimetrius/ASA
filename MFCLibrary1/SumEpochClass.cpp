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

	//������������ �������� �������� ��������, ���������� � ������
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
	

	if (!ChanImpos.TrueSumEpoChan.empty())
	{
		for (int i1 = 0; i1 < ChanImpos.TrueSumEpoChan.size(); i1++)
		{
			ChanImpos.TrueSumEpoChan[i1].clear();
			ChanImpos.TrueSumEpoChan[i1].shrink_to_fit();
		}
	}
	
	ChanImpos.TrueSumEpoChan.clear();
	ChanImpos.TrueSumEpoChan.shrink_to_fit();



	if (!ChanImpos.FalseSumEpoChan.empty())
	{
		for (int i1 = 0; i1 < ChanImpos.FalseSumEpoChan.size(); i1++)
		{
			ChanImpos.FalseSumEpoChan[i1].clear();
			ChanImpos.FalseSumEpoChan[i1].shrink_to_fit();
		}
	}

	ChanImpos.FalseSumEpoChan.clear();
	ChanImpos.FalseSumEpoChan.shrink_to_fit();

	//MessageBeep(MB_ICONWARNING);

}


void SumEpochClass::OutImposEpo( std::vector<std::vector<float>> Chan, std::vector<CString> truOrFalseCard, std::vector<CString> numActualCard, int firstNum, int lastNum, CString categoryName, char * FileName)
{

			averageXTrue.resize(Chan[0].size()); // 4 ������
		averageXFalse.resize(Chan[0].size());

		ChanImpos.SigmaFalse.resize(Chan[0].size());
		ChanImpos.SigmaTrue.resize(Chan[0].size());
	
		ChanImpos.STrue.resize(Chan[0].size());
		ChanImpos.SFalse.resize(Chan[0].size());

		

		int vecSize = (m_AfterShow + m_ShowTime + m_BeforeShow + m_DelaySpeedMouse) / (float)measureInterval; // ������ ������� ����� - ����� ����� ����� =  ��� �����.
		int k1 = 0;
	
		
		
		//MyStruct1 ChanVec;
	
		ChanImpos.TrueNumEpoch = 0; // ���������� ���� ���������� �������
		ChanImpos.FalseNumEpoch = 0; // ���������� ���� ������������ �������
	
	
		// resize new vector for sum epo ChanImpos.TrueSumEpoChan[k1-1][f1]
		
		ChanImpos.TrueSumEpoChan.resize(vecSize+1);
		ChanImpos.FalseSumEpoChan.resize(vecSize + 1);
			for (int i1 = 0; i1 < ChanImpos.TrueSumEpoChan.size(); i1++)
			{
				ChanImpos.TrueSumEpoChan[i1].resize(Chan[0].size());
				ChanImpos.FalseSumEpoChan[i1].resize(Chan[0].size());
			}

		//SetSizeVec(vecSize);
		//ChanImpos.ResizeVec(vecSize+1 ); // ������ ������ ��������, �������� �������� ����������. 

		std::vector  <float> Truetemp0; // ��������� ������
		std::vector  <std::vector  <float>> Truetemp1; // ��������� ������

		std::vector  <float> Falsetemp0; // ��������� ������
		std::vector  <std::vector  <float>> Falsetemp1; // ��������� ������
		bool isTrueAns;
//
		//std::vector<float> TempTrueSum;//(Chan[0].size());
		//std::vector<float> TempFalseSum;//(Chan[0].size());

		int nBefRec = 0;
		nBefRec = m_DelaySpeedMouse / (float)measureInterval;
		for (int i1 = 0; i1 < truOrFalseCard.size(); i1++)//Chan.size(); i1++)
		{
			
			//std::vector  <float> Truetemp0; // ��������� ������
			// ������� ����� �������� ������� ������ �����
			if (truOrFalseCard[i1] != " " && firstNum <= atoi(numActualCard[i1]) && atoi(numActualCard[i1]) <= lastNum && k1 <= vecSize)
			{
				
				if (truOrFalseCard[i1] == "True")
				{
					
					
						if (k1 == 0)
						{
							ChanImpos.TrueNumEpoch++;
							// ��������� ����� ��������� �����
							ChanImpos.TrueNumCard.push_back(numActualCard[i1]);
							isTrueAns = true;

							// ���������� ����������
							// ��������� ���-�� �������� ������� ����������
						//	nBefRec = m_DelaySpeedMouse/(float)measureInterval;

							for (int t1 = nBefRec; t1 > 0;t1--)
							{
								//if (k1 == nBefRec) break;
								for (int f1 = 0; f1 < Chan[0].size();f1++)
								{
									////ChanImpos.TrueSumEpoChan0[k1] = ChanImpos.TrueSumEpoChan0[k1] + Chan[f1][i1 - t1];
									//if (t1 == nBefRec)
									//{
									//	TempTrueSum.push_back(Chan[i1 - t1][f1]);
									//}
									//else
									//{
									//	TempTrueSum.push_back(ChanImpos.TrueSumEpoChan[k1-1][f1] + Chan[i1 - t1][f1]);
									//}
									//TempTrueSum.push_back(Chan[i1 - t1][f1]);

									// summ all epo in category before chouse
									ChanImpos.TrueSumEpoChan[k1][f1] = ChanImpos.TrueSumEpoChan[k1][f1] + Chan[i1 - t1][f1];

									// �������������� �����
									Truetemp0.push_back(Chan[i1 - t1][f1]);


								}
								//ChanImpos.TrueSumEpoChan.push_back(TempTrueSum);

								//TempTrueSum.clear();
								//TempTrueSum.shrink_to_fit();

								// � ���������� ������
								Truetemp1.push_back(Truetemp0);
								// ������� ����������� ���������� �������
								Truetemp0.clear();
								Truetemp0.shrink_to_fit();
								k1++;
								//if (k1 == nBefRec) break;
							}
						}
					
					for (int f1 = 0; f1 < Chan[0].size();f1++) // ��� �� ������� �� ����
					{

					
						//TempTrueSum.push_back(ChanImpos.TrueSumEpoChan[k1-1][f1] + Chan[i1][f1]);
						// summ epo all category after chouse
						ChanImpos.TrueSumEpoChan[k1][f1] = ChanImpos.TrueSumEpoChan[k1][f1] + Chan[i1][f1];
						//��������� ������� �������
						Truetemp0.push_back(Chan[i1][f1]);
					}

					//ChanImpos.TrueSumEpoChan.push_back(TempTrueSum);

					//TempTrueSum.clear();
					//TempTrueSum.shrink_to_fit();

					// � ���������� ������
					Truetemp1.push_back(Truetemp0);
					
					// ����������� ��������� ������ � ���������� (��������� ����)
					if (k1 == vecSize)
					{
						ChanImpos.TrueOnlyEpoch.push_back(Truetemp1);

						// ������� ���������� ���������� �������
						Truetemp1.clear();
						Truetemp1.shrink_to_fit();
					}

					// ������� ����������� ���������� �������
					Truetemp0.clear();
					Truetemp0.shrink_to_fit();
				}
				if (truOrFalseCard[i1] == "False")
				{
					

					if (k1 == 0)
					{
						ChanImpos.FalseNumEpoch++;
						// ��������� ����� ��������� �����
						ChanImpos.FalseNumCard.push_back(numActualCard[i1]);
						isTrueAns = false;
						// ���������� ����������
						// ��������� ���-�� �������� ������� ����������
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
								//TempFalseSum.push_back(Chan[i1 - t1][f1]);

								ChanImpos.FalseSumEpoChan[k1][f1] = ChanImpos.FalseSumEpoChan[k1][f1] + Chan[i1 - t1][f1];

								// �������������� �����
								Falsetemp0.push_back(Chan[i1 - t1][f1]);

								
							}
							//ChanImpos.FalseSumEpoChan.push_back(TempFalseSum);
							//TempFalseSum.clear();
							//TempFalseSum.shrink_to_fit();

							// � ���������� ������
							Falsetemp1.push_back(Falsetemp0);
							// ������� ����������� ���������� �������
							Falsetemp0.clear();
							Falsetemp0.shrink_to_fit();
							k1++;
							
						}
					}




					for (int f1 = 0; f1 < Chan[0].size();f1++)
					{


						//TempFalseSum.push_back(ChanImpos.FalseSumEpoChan[k1 - 1][f1 ] + Chan[i1][f1]);
						
						ChanImpos.FalseSumEpoChan[k1][f1] = ChanImpos.FalseSumEpoChan[k1][f1] + Chan[i1][f1];
						// �������������� �����
						//��������� ������� �������
						Falsetemp0.push_back(Chan[i1][f1]);
					}

				//	ChanImpos.FalseSumEpoChan.push_back(TempFalseSum);

					//TempFalseSum.clear();
					//TempFalseSum.shrink_to_fit();

					// ��� ������ �������������� ����
					// � ���������� ������
					Falsetemp1.push_back(Falsetemp0);
				
					// ��������� ��������� ������ � ���������� (��������� ����)
					if (k1 == vecSize)
					{
						ChanImpos.FalseOnlyEpoch.push_back(Falsetemp1);

						// ������� ���������� ���������� �������
						Falsetemp1.clear();
						Falsetemp1.shrink_to_fit();
					}
					// ������� ����������� ���������� �������
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
	
		// ����� ����� �������� ���� �� ����� 
	
		for (int i2 = 0; i2 < ChanImpos.TrueSumEpoChan.size(); i2++)
		{

			for (int f1 = 0; f1 < Chan[0].size();f1++)
			{
				////FalseSumEpoChan[k1 - 1][f1]
				//if (ChanImpos.TrueNumEpoch != 0 && !ChanImpos.TrueSumEpoChan.empty())
				//{
				//	ChanImpos.TrueSumEpoChan[i2][f1] /=(float) ChanImpos.TrueNumEpoch;
				//}
				//else 
				//{
				//	if (!ChanImpos.TrueSumEpoChan.empty())
				//	{
				//		ChanImpos.TrueSumEpoChan[i2][f1] = 0;
				//	}

				//}

				//if (ChanImpos.FalseNumEpoch != 0 && !ChanImpos.FalseSumEpoChan.empty())
				//{
				//	ChanImpos.FalseSumEpoChan[i2][f1] /= (float)ChanImpos.FalseNumEpoch; // ����� ���� /0
				//}
				//else
				//{
				//	if (!ChanImpos.FalseSumEpoChan.empty())
				//	{
				//		ChanImpos.FalseSumEpoChan[i2][f1] = 0;
				//	}
				//	
				//}
				if (ChanImpos.TrueNumEpoch != 0)
				{
					ChanImpos.TrueSumEpoChan[i2][f1] /= ChanImpos.TrueNumEpoch;
				}
				else
				{
					ChanImpos.TrueSumEpoChan[i2][f1] = 0; 
				}


				if (ChanImpos.FalseNumEpoch != 0)
				{
					ChanImpos.FalseSumEpoChan[i2][f1] /= ChanImpos.FalseNumEpoch;
				}
				else
				{
					ChanImpos.FalseSumEpoChan[i2][f1] = 0;
				}
				//ChanImpos.FalseSumEpoChan0[i2] /= ChanImpos.FalseNumEpoch;


			}	
			
				Sigma(i2);//������ ����������� ������
			
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
	// ������������������ ����������

	if (ChanImpos.TrueOnlyEpoch.empty() != true)
	{

		// ������� ����� ���������. ���� �� k0( Xk(j2) - Xcp(j2)), ��� k0 - ����� �����(�� ����� �����), j2 - ������ ������� �������
		for (int k0 = 0; k0 < ChanImpos.TrueOnlyEpoch.size(); k0++) //ChanImpos.TrueOnlyEpoch.size() - ���-�� ������� � ������ ���������.
																	//ChanImpos.TrueOnlyEpoch[].size() - ���-�� �������� ������� � ������ ��������� � ����� vecSize.
																	//ChanImpos.TrueOnlyEpoch[][].size() - ���-�� �������.
		{

			for (int f1 = 0; f1 < ChanImpos.SigmaTrue.size();f1++)
			{
				ChanImpos.SigmaTrue[f1] += (ChanImpos.TrueOnlyEpoch[k0][j2][f1] - ChanImpos.TrueSumEpoChan[j2][f1])*(ChanImpos.TrueOnlyEpoch[k0][j2][f1] - ChanImpos.TrueSumEpoChan[j2][f1]); // �������� � ������� � ���������
			}

			//ChanImpos.SigmaTrue[0] += (ChanImpos.TrueOnlyEpoch[k0][j2][0] - ChanImpos.TrueSumEpoChan0[j2])*(ChanImpos.TrueOnlyEpoch[k0][j2][0] - ChanImpos.TrueSumEpoChan0[j2]); // �������� � ������� � ���������
			//ChanImpos.SigmaTrue[1] += (ChanImpos.TrueOnlyEpoch[k0][j2][1] - ChanImpos.TrueSumEpoChan1[j2])*(ChanImpos.TrueOnlyEpoch[k0][j2][1] - ChanImpos.TrueSumEpoChan1[j2]); // �������� � ������� � ���������
			//ChanImpos.SigmaTrue[2] += (ChanImpos.TrueOnlyEpoch[k0][j2][2] - ChanImpos.TrueSumEpoChan2[j2])*(ChanImpos.TrueOnlyEpoch[k0][j2][2] - ChanImpos.TrueSumEpoChan2[j2]); // �������� � ������� � ���������
			//ChanImpos.SigmaTrue[3] += (ChanImpos.TrueOnlyEpoch[k0][j2][3] - ChanImpos.TrueSumEpoChan3[j2])*(ChanImpos.TrueOnlyEpoch[k0][j2][3] - ChanImpos.TrueSumEpoChan3[j2]); // �������� � ������� � ���������

		}


		// ����� ������ �� ����������� ����������
		int k1 = (ChanImpos.TrueOnlyEpoch.size()*(ChanImpos.TrueOnlyEpoch.size() - 1));// �� �������: (n(n-1)), ��� n - ���-�� ����
		
		if (k1 != 0) // ������ �� -nan � ����� �� ������
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

			

			//ChanImpos.SigmaTrueChan0[j2] = sqrt(ChanImpos.SigmaTrue[0] / k1);  // ChanImpos.SigmaTrue[0] - �������� ������� ���� �� k0( Xk(j2) - Xcp(j2)), ��� k0 - ����� �����(�� ����� �����), j2 - ������ ������� �������
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
		// �������� ������� ����������� ����������, ��������
		//�����������
		
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

		// ������� ����� ���������. ���� �� k0( Xk(j2) - Xcp(j2)), ��� k0 - ����� �����(�� ����� �����), j2 - ������ ������� �������
		for (int k0 = 0; k0 < ChanImpos.FalseOnlyEpoch.size(); k0++) //ChanImpos.TrueOnlyEpoch.size() - ���-�� ������� � ������ ���������.
																	//ChanImpos.TrueOnlyEpoch[].size() - ���-�� �������� ������� � ������ ��������� � ����� vecSize.
																	//ChanImpos.TrueOnlyEpoch[][].size() - ���-�� �������.
		{
			
			for (int f1 = 0; f1 < ChanImpos.SigmaFalse.size();f1++)
			{
				//ChanImpos.SigmaFalse[f1] += (ChanImpos.FalseOnlyEpoch[k0][j2][0] - ChanImpos.TrueSumEpoChan[j2][f1])*(ChanImpos.TrueOnlyEpoch[k0][j2][0] - ChanImpos.TrueSumEpoChan[j2][f1]); // �������� � ������� � ���������
				ChanImpos.SigmaFalse[f1] += (ChanImpos.FalseOnlyEpoch[k0][j2][f1] - ChanImpos.FalseSumEpoChan[j2][f1])*(ChanImpos.FalseOnlyEpoch[k0][j2][f1] - ChanImpos.FalseSumEpoChan[j2][f1]); // �������� � ������� � ���������
			}

			//ChanImpos.SigmaFalse[0] += (ChanImpos.FalseOnlyEpoch[k0][j2][0] - ChanImpos.FalseSumEpoChan0[j2])*(ChanImpos.FalseOnlyEpoch[k0][j2][0] - ChanImpos.FalseSumEpoChan0[j2]); // �������� � ������� � ���������
			//ChanImpos.SigmaFalse[1] += (ChanImpos.FalseOnlyEpoch[k0][j2][1] - ChanImpos.FalseSumEpoChan1[j2])*(ChanImpos.FalseOnlyEpoch[k0][j2][1] - ChanImpos.FalseSumEpoChan1[j2]); // �������� � ������� � ���������
			//ChanImpos.SigmaFalse[2] += (ChanImpos.FalseOnlyEpoch[k0][j2][2] - ChanImpos.FalseSumEpoChan2[j2])*(ChanImpos.FalseOnlyEpoch[k0][j2][2] - ChanImpos.FalseSumEpoChan2[j2]); // �������� � ������� � ���������
			//ChanImpos.SigmaFalse[3] += (ChanImpos.FalseOnlyEpoch[k0][j2][3] - ChanImpos.FalseSumEpoChan3[j2])*(ChanImpos.FalseOnlyEpoch[k0][j2][3] - ChanImpos.FalseSumEpoChan3[j2]); // �������� � ������� � ���������


		}


		// ����� ������ �� ����������� ����������
		int k1 = (ChanImpos.FalseOnlyEpoch.size()*(ChanImpos.FalseOnlyEpoch.size() - 1));// �� �������: (n(n-1)), ��� n - ���-�� ����

		// ChanImpos.SigmaTrue[0] - �������� ������� ���� �� k0( Xk(j2) - Xcp(j2)), ��� k0 - ����� �����(�� ����� �����), j2 - ������ ������� �������
		if (k1 != 0) // ������ �� -nan � ����� �� ������
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
		// �������� ������� ����������� ����������, ��������
		//�����������
		
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
	// ������� ��������
	TrueSumEpoChan.clear(); // ������ ��� ���������� �������� ������ 0
	//TrueSumEpoChan1.clear(); // ������ ��� ���������� �������� ������ 1
	//TrueSumEpoChan2.clear(); // ������ ��� ���������� �������� ������ 2
	//TrueSumEpoChan3.clear(); // ������ ��� ���������� �������� ������ 3

	FalseSumEpoChan.clear(); // ������ ��� ���������� �������� ������ 0
	//FalseSumEpoChan1.clear();// ������ ��� ���������� �������� ������ 1
	//FalseSumEpoChan2.clear(); // ������ ��� ���������� �������� ������ 2
	//FalseSumEpoChan3.clear(); // ������ ��� ���������� �������� ������ 3


							  // ������������ ���������
	TrueSumEpoChan.shrink_to_fit(); // ������ ��� ���������� �������� ������ 0
	//TrueSumEpoChan1.shrink_to_fit(); // ������ ��� ���������� �������� ������ 1
	//TrueSumEpoChan2.shrink_to_fit(); // ������ ��� ���������� �������� ������ 2
	//TrueSumEpoChan3.shrink_to_fit(); // ������ ��� ���������� �������� ������ 3

	FalseSumEpoChan.shrink_to_fit(); // ������ ��� ���������� �������� ������ 0
	//FalseSumEpoChan1.shrink_to_fit();// ������ ��� ���������� �������� ������ 1
	//FalseSumEpoChan2.shrink_to_fit(); // ������ ��� ���������� �������� ������ 2
	//FalseSumEpoChan3.shrink_to_fit(); // ������ ��� ���������� �������� ������ 3



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
	//TrueSumEpoChan0.resize(SizeVec); // ������ ��� ���������� �������� ������ 0
	//TrueSumEpoChan1.resize(SizeVec); // ������ ��� ���������� �������� ������ 1
	//TrueSumEpoChan2.resize(SizeVec); // ������ ��� ���������� �������� ������ 2
	//TrueSumEpoChan3.resize(SizeVec); // ������ ��� ���������� �������� ������ 3

	//FalseSumEpoChan0.resize(SizeVec); // ������ ��� ���������� �������� ������ 0
	//FalseSumEpoChan1.resize(SizeVec); // ������ ��� ���������� �������� ������ 1
	//FalseSumEpoChan2.resize(SizeVec); // ������ ��� ���������� �������� ������ 2
	//FalseSumEpoChan3.resize(SizeVec); // ������ ��� ���������� �������� ������ 3

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

//// �������� ������ ���������� �������
//	OnlyEpoch.resize(4); // �� ��������
//	for (int i1 = 0; i1 < OnlyEpoch.size();i1++)
//	{
//		OnlyEpoch[i1].resize(SizeVec);// �� �������
//	}
//
	//OnlyEpoch.resize(4);
}
