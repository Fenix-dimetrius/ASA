
#include "stdafx.h"
#include "ASATest.h"
#include "ASADlg.h"
#include "TimerCls.h"
#include <fstream>
#include "SumEpochClass.h"

std::vector<int> v_Available(150);// ������ ���������� ��������� �������
std::string file_nameEn;
char * fileNameEn;
FILE * recordEn; // ���� ��� ������ � ���� ��������
std::vector <__int64> tickVector(2); // ������ ��� ���������� �������� �����

std::vector <float> tempFirstTick;
std::vector <std::vector <float>> updInfVecChan;


//std::vector <__int64> freqVector(2);// ������ ���������� ������� ����������

std::vector <CString> TimeInterval(2); // ������ ��� ���������� ������� ������� ������ �����
std::vector <CString> ChouseCard(2); // ������ ��� ���������� ������ �����

std::vector <CString> TruOrFalseCard(2); // ������ ��� ���������� ������ �� ����� ����(����� ��� ���)
std::vector <CString> NumActualCard(2); // ������ ��� ���������� ������� ��������


//int i001 = 0;
void testOut(DWORD dwObjectIndex, DWORD NumOfInstruments)
{
	//i001++;
	//	std::ofstream out("PlugIns/TestASA/TestOut.csv", std::ios::app);
	//out << "\n" << NumOfInstruments << "\n";
	//out.close();
}

void ThreadTimerTick(void* pParams); // ��������� ����� � ��������

//void ImposEpoFunc(); // ����� ��������� ����

ASATest::ASATest()
	//: v_AllUrl(0)
{
}


ASATest::~ASATest()
{
}

CString returnVal;// ���������� ����� ��������

CString ASATest::getUrlPic()
{
	int Rand1 = 0; // ��������� ����� ��������
	int xmin = 0;

	LARGE_INTEGER NumTickProc; // ����������
	QueryPerformanceCounter(&NumTickProc); // ��������� �������� ����� ��
	

	if (v_Available.size() >= 2) // �������� ������� �� �����
	{
		Rand1 = (rand() % (v_Available.size())); // ���������� ��������� ����� � �������� �� 0 �� ������� �������
											
	}
	else // ��� ����� ������� ==1
	{	// ����������� ������ ����
		Rand1 = 0; // �.�. �������� ����� ���� ������ � �������
		EndGenNumPic = true;
	}
		
	returnVal.Format("\%i", v_Available[Rand1]); //������������ ����� � ������ ������� � ������

	v_Available.erase(v_Available.begin() + Rand1); // ������� ������ �� ������� Rand1
	std::vector<int>(v_Available).swap(v_Available); // ��������� ������ ��� ��������� �������
		
	
												  
	// �������� ����� ����������.

	int X1, X2;

	X2 = NumTickProc.QuadPart % 10; // ����� ����� �� 10 � ���������� �������. ��� ������ ���� � ����� ����� NumTickProc.QuadPart

	X1 = ((NumTickProc.QuadPart % 100) - X2) / 10; // ����� ����� �� 100, ���������� ������� � �������� �� ���� �1
												// ����� ������� �� 10 ������� 2 ���� � ����� ����� NumTickProc.QuadPart


	if ((X1 + X2) % 2 == 0) // �������� ����� ����� ���������� ��������� �� ��������
	{

		if (GenNumPicBefore != true) // ���� ������ ���������
		{
			UpdInfoVal.TruOrFalseCard = "True"; // ����� ��� ������� �������� �����
		}
		return returnVal; // ���� �����, �� ���������� �����, ������� ��������� � ����������� ������
	}
	
	else // ���� ������� 
	{
		if (GenNumPicBefore != true)// ���� ������ ���������
		{
			UpdInfoVal.TruOrFalseCard = "False"; // ����� ��� ������� �������� �����
		}
		return CString("150"); // ���� ���, �� ����� ���
	}


}



// �������������
bool ASATest::InitASATest()
{
	LARGE_INTEGER NumTickProc;
	QueryPerformanceCounter(&NumTickProc);
	srand(NumTickProc.QuadPart); // �������������� ������������	
	v_Available.resize(150);
	//AfxMessageBox("init compl");
	EndGenNumPic = false;

	for (int i = 0; i < v_Available.size();i++)
		{
			v_Available[i] = i;
		}

	//if (StartRecorPlay == true)
	//{
		_beginthread(ThreadTimerTick, 0, NULL);// ������ 

	//}
	//else
	//{
	//	if (MessageBox(NULL, "������ �� ����� ������. ���������� ������ � ����?", " ", MB_YESNO) == IDYES)
	//	{
	//		_beginthread(ThreadTimerTick, 0, NULL);// ������ 
	//	}
	//}
	//std::vector <int> respOpt1(2);// ������ ���������� ��������� �������
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





//===================================== ������ � ���� ==========




int MenOrWomen;



double totalTime = 0; // ��������� ����� ������ 
SumEpochClass BufImposEpoch;// ���
void ImposEpochOut()
{
	int timeEpo = - m_BeforeShow - m_DelaySpeedMouse; //������. � ������ ����� ...
	CString TimeIntervalEpo;// �������� ���������� ���������
	
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

		// ������� �������� ���� � ����
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


	// ����� �������������� ����

	out << "\n" << "�������������� �����:" << "\n";

	out << "\n" << "�����:" << "\n";
	

	// ���� ������ �������� ������� ����
	int ch1 = 0;
	if (BufImposEpoch.ChanImpos.TrueNumCard.empty() != true) // ������ �� ������� �������. vec.size() == 0; vec[0] == err
	{
		for (int j2 = 0; j2 < BufImposEpoch.ChanImpos.TrueNumCard.size(); j2++)//size = 10;
		{
			out << ";" << BufImposEpoch.ChanImpos.TrueNumCard[j2];

			for (int f1 = 0; f1 < BufImposEpoch.ChanImpos.TrueSumEpoChan[0].size() - 1; f1++) // -1 �.�. ����� ������� 
																								//����� ���� ���� ";"
			{
				out << ";" ;
			}
			

		}
		out << "\n";
		// ������� �������� �������

		out << ";";
		for (int j3 = 0; j3 < BufImposEpoch.ChanImpos.TrueNumCard.size() * UpdInfoVal.TextInfChan.size(); j3++)
																	// �������� ���-�� ������� �� ���-�� �������
		{

			out << UpdInfoVal.TextInfChan[ch1] << ";";
			//out << NameChannel[ch1] << ";";

			ch1++;
			if (ch1 > (UpdInfoVal.TextInfChan.size() - 1)) ch1 = 0; // ������� ���-�� ������� ����� ������
																	//����� ���� ������� =_= 
		}
		out << "\n";
	}
	
	else
	{
		out << "��� ������ �������" << "\n";
	}


	// ������� �������� �������
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
	

	timeEpo = -m_BeforeShow - m_DelaySpeedMouse; //������. � ������ ����� ...
	
	int k1 = 0;
	if (BufImposEpoch.ChanImpos.TrueOnlyEpoch.empty() != true) // ������ �� ������� �������. vec.size() == 0; vec[0] == err
	{
		


		if (BufImposEpoch.ChanImpos.TrueOnlyEpoch[0].empty() != true) // ������ �� ������� �������. vec[0].size() == 0; vec[0][0] == err
		{
			for (int j1 = 0; j1 < BufImposEpoch.ChanImpos.TrueOnlyEpoch[0].size(); j1++)// TrueOnlyEpoch[k].size() ��� ����� k ���� ������
			{

				for (k1 = 0; k1 < BufImposEpoch.ChanImpos.TrueOnlyEpoch.size(); k1++) // len = 3
				{

					if (BufImposEpoch.ChanImpos.TrueOnlyEpoch[0][0].empty() != true)
					{
						for (int i1 = 0; i1 < BufImposEpoch.ChanImpos.TrueOnlyEpoch[0][0].size();i1++)// TrueOnlyEpoch[k][j].size() ��� ����� k � j ���� ������
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
				out << "\n"; // ������� �� ����� ������
				if (k1 >= BufImposEpoch.ChanImpos.TrueOnlyEpoch.size()) k1 = 0; // ����� �� ���������� ������
				
			}
		}
	}
	else
	{
		out << "\n";
	}

	out << "\n" << "\n" << "�������:" << "\n";

	// ���� ������ �������� ������� ����
	if (BufImposEpoch.ChanImpos.FalseNumCard.empty() != true) // ������ �� ������� �������. vec.size() == 0; vec[0] == err
	{

		for (int j2 = 0; j2 < BufImposEpoch.ChanImpos.FalseNumCard.size(); j2++)//size = 10;
		{
			out << ";" << BufImposEpoch.ChanImpos.FalseNumCard[j2];// << ";" << ";" << ";";
			for (int f1 = 0; f1 < BufImposEpoch.ChanImpos.FalseSumEpoChan[0].size() - 1; f1++) // -1 �.�. ����� ������� 
																							  //����� ���� ���� ";"
			{
				out << ";";
			}
		}

		out << "\n";

		// ������� �������� �������
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
		out << "��� �������� �������" << "\n";
	}


	timeEpo = -m_BeforeShow - m_DelaySpeedMouse; //������. � ������ ����� ...
	
	k1 = 0;
	if (BufImposEpoch.ChanImpos.FalseOnlyEpoch.empty() != true) // ������ �� ������� �������. vec.size() == 0; vec[0] == err
	{	

		if (BufImposEpoch.ChanImpos.FalseOnlyEpoch[0].empty() != true) // ������ �� ������� �������. vec.size() == 0; vec[0] == err
		{
			for (int j1 = 0; j1 < BufImposEpoch.ChanImpos.FalseOnlyEpoch[0].size(); j1++)// TrueOnlyEpoch[k].size() ��� ����� k ���� ������
			{

				for (k1 = 0; k1 < BufImposEpoch.ChanImpos.FalseOnlyEpoch.size(); k1++) // len = 3
				{

					if (BufImposEpoch.ChanImpos.FalseOnlyEpoch[0][0].empty() != true)
					{
						for (int i1 = 0; i1 < BufImposEpoch.ChanImpos.FalseOnlyEpoch[0][0].size();i1++)//  TrueOnlyEpoch[k][j].size() ��� ����� k � j ���� ������
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
				out << "\n"; // ������� �� ����� ������
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
	

	tm* timeinfo = localtime(&seconds); // �������� ��������� ����� � ��������
	
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
	strftime(buffer1, 80, format1, timeinfo); //��������� ��� � ������ 2015.02.09(HH-MM-SS) � ���������� ���������� ".csv"
	std::string dataTimeStr1(buffer1, sizeof(buffer1)); // ������������ char � string, �������, ��� ����, ����� char
	file_nameEn = dataTimeStr1; // ����������� ���������� ��� ����� ������������� ����������. ��� En Excel
	fileNameEn = (char *)file_nameEn.c_str(); // ������� ��� ����� � ��� ���� ������� ������������ string � char


	double val1 = 0; // ���������� ���������� ����������.
	double val2 = 0; // ���������� ���������� ����������.
					 // Open the PROPERTY configuration for this plugin
					 //fp = fopen( g_csFileName.GetBuffer(-1),"wb" );

					 /*std::string resVec;
					 std::string pauseVec;*/
	strftime(buffer1, 80, "%Y.%m.%d(%H - %M - %S)", timeinfo);
	std::ofstream out;
	out.open(fileNameEn, std::ios::app);
	
	format2 = "%Y.%m.%d;%H-%M-%S";// ������� � ������ 2015.02.09;HH-MM-SS ��� �������� ������ � csv ����
	strftime(buffer2, 80, format2, timeinfo); //��������� ��� � ������ 2015.02.09(HH-MM-SS) � ���������� ���������� ".csv"
	out << "���� ���������� �: " << ";" << buffer2 << "\n";
	out <<"�������:"<<"\n"<< UpdInfoVal.SureName << ";" << UpdInfoVal.Name <<";" << UpdInfoVal.SecName << "\n"<<"\n";
	out.close();




	// delete 
	//======================================== ��������� ����================================================
	SumEpochClass EroImposEpoch;// ���
	SumEpochClass NegImposEpoch;// �������
	SumEpochClass NeuImposEpoch;// �����������

	
	//-----------------���------------------------
	
	EroImposEpoch.OutImposEpo(updInfVecChan, TruOrFalseCard, NumActualCard, 0, 49, "�����������", fileNameEn); //, updInfVecChan1, updInfVecChan2, updInfVecChan3,

	BufImposEpoch.ChanImpos = EroImposEpoch.ChanImpos; // ����������� ��������� � ������������ ��������� ��������� 

	out.open(fileNameEn, std::ios::app);
	out << "\n" << "��������� ����" << "\n" << "\n";
	out << "�����������" << "\n";


	out << "�����:" << BufImposEpoch.ChanImpos.TrueNumCard.size()<<";";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size()*2; i1++)// 
	{
		out << ";" << " ";
	}
	out << ";" <<"�������:" << BufImposEpoch.ChanImpos.FalseNumCard.size()<<";"<<"\n";

	

	// ����� �������� �������
	out << "Time, ms" << ";" << "Time interval";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size()*2; i1++)// 
	{
		if (i1 == UpdInfoVal.TextInfChan.size() ) out << ";"<<"	";
		out << ";" << UpdInfoVal.TextInfChan[i1<UpdInfoVal.TextInfChan.size() ? i1 : (int)(i1/2.0)] << ";" << "����������� ������";
	}
	out << "\n";

	out.close(); // ��������� ����� � ����, �� � ���� �� ��������� ������ �� ������� 	ImposEpochOut()	
	
	ImposEpochOut();// ������ ����� � ����. ������ ���, ��� ���������� ����
				
	// �����������
	
	EroImposEpoch.~SumEpochClass();


	////-----------------------����������----------------

	NegImposEpoch.OutImposEpo(updInfVecChan, TruOrFalseCard, NumActualCard, 50, 99, "����������", fileNameEn); //, updInfVecChan1, updInfVecChan2, updInfVecChan3,

	BufImposEpoch.ChanImpos = NegImposEpoch.ChanImpos; // ����������� ��������� � ������������ ��������� ��������� 

	out.open(fileNameEn, std::ios::app);
	out << "\n" << "��������� ����" << "\n" << "\n";
	out << "����������" << "\n";


	out << "�����:" << BufImposEpoch.ChanImpos.TrueNumCard.size() << ";";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size() * 2; i1++)// 
	{
		out << ";" << " ";
	}
	out << ";" << "�������:" << BufImposEpoch.ChanImpos.FalseNumCard.size() << ";" << "\n";



	// ����� �������� �������
	out << "Time, ms" << ";" << "Time interval";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size() * 2; i1++)// 
	{
		if (i1 == UpdInfoVal.TextInfChan.size()) out << ";" << "	";
		out << ";" << UpdInfoVal.TextInfChan[i1<UpdInfoVal.TextInfChan.size() ? i1 : (int)(i1 / 2.0)] << ";" << "����������� ������";
	}
	out << "\n";
	

	out.close(); // ��������� ����� � ����, �� � ���� �� ��������� ������ �� ������� 	ImposEpochOut()	

	ImposEpochOut();// ������ ����� � ����. ������ ���, ��� ���������� ����

					
	NegImposEpoch.~SumEpochClass();



					////------------------------�����������--------------

	NeuImposEpoch.OutImposEpo(updInfVecChan, TruOrFalseCard, NumActualCard, 100, 149, "�����������", fileNameEn); //, updInfVecChan1, updInfVecChan2, updInfVecChan3,

	BufImposEpoch.ChanImpos = NeuImposEpoch.ChanImpos; // ����������� ��������� � ������������ ��������� ��������� ���������� ������.

	out.open(fileNameEn, std::ios::app);
	out << "\n" << "��������� ����" << "\n" << "\n";
	out << "�����������" << "\n";


	out << "�����:" << BufImposEpoch.ChanImpos.TrueNumCard.size() << ";";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size() * 2; i1++)// 
	{
		out << ";" << " ";
	}
	out << ";" << "�������:" << BufImposEpoch.ChanImpos.FalseNumCard.size() << ";" << "\n";



	// ����� �������� �������
	out << "Time, ms" << ";" << "Time interval";
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size() * 2; i1++)// 
	{
		if (i1 == UpdInfoVal.TextInfChan.size()) out << ";" << "	";
		out << ";" << UpdInfoVal.TextInfChan[i1<UpdInfoVal.TextInfChan.size() ? i1 : (int)(i1 / 2.0)] << ";" << "����������� ������";
	}
	out << "\n";
	

	out.close(); // ��������� ����� � ����, �� � ���� �� ��������� ������ �� ������� 	ImposEpochOut()	

	ImposEpochOut();// ������ ����� � ����. ������ ���, ��� ���������� ����

					// �����������
	BufImposEpoch.~SumEpochClass();
	NeuImposEpoch.~SumEpochClass();




	// ��������� ���� ��� ������ �������������� ��������
	out.open(fileNameEn, std::ios::app);
	
	
	out << "\n" << "\n" << "�������������� ��������:" << "\n";

	out << "Time, ms" ;
	for (int i1 = 0; i1 < UpdInfoVal.TextInfChan.size(); i1++)
	{
		out << ";" << UpdInfoVal.TextInfChan[i1];
	}

	out <<  ";" << " Time Interval" << ";" << "Chouse Card" << ";" << "TruOrFalseCard" << ";" << "NumActualCard" << "\n";

	for (int j = 1; j < updInfVecChan.size();j++)//j<tickVector.size()-2; j++)
	{

		//val1 = tickVector[j]*1000.0/(double)freqVector[j];
	
		// ������� �����
		out << tickVector[j];

		//������� ��������� �������
		for (int i1 = 0; i1 < UpdInfoVal.updInfChan.size();i1++)
		{
			out << ";" << updInfVecChan[j][i1];
		}
		
		// ������� ���� � �������, ��������� �����, ������\�������� ������, ������ �������� �����
		 out << ";" << TimeInterval[j] << ";" << ChouseCard[j] << ";" << TruOrFalseCard[j] << ";" << NumActualCard[j] << "\n";
		//out << "\n";

		//out.close();
	}
	//std::ofstream out(fileNameEn, std::ios::app);
	out << "\n" << "ALL Time: " << totalTime << "\n";
	out.close();

	// ���������� �������


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


//	TruOrFalseCard.resize(2); // ������ ��� ���������� ������ �� ����� ����(����� ��� ���)
	TruOrFalseCard.clear();
	TruOrFalseCard.shrink_to_fit();

	//NumActualCard.resize(2); // ������ ��� ���������� ������� ��������
	NumActualCard.clear();
	NumActualCard.shrink_to_fit();

	

	MessageBox(NULL, "Record complete", "Rec", MB_OK);
}

int measureInterval = 40;
//bool accurateCounts = true;

void ThreadTimerTick(void* pParams)
{
	double n1 = 1;

	TimerCls mytimer;// �������������� ������

	LARGE_INTEGER Frequency, StartingTime, EndingTime;  // ��� �� ����� ����������

	DWORD_PTR oldMask2;

	oldMask2 = SetThreadAffinityMask(GetCurrentThread(), 1); // ��������� ������������ ������ ������ ���� ����������
	
	QueryPerformanceCounter(&StartingTime);		// ������ ��������� �������� �����

	mytimer.startTimer();        //����� ������� � ��������� ��������
	
	int kTrue = 0;
	int kFalse = 0;
	
	while (fullscr != false)
	{

		if (mytimer.readTimer() >= n1 * measureInterval) // ��������� ����� ��� n1
		{
			//cout <<mytimer.read_timer()<<"		"<< n1 << "\n";

			//tickVector[n1 - 1] = mytimer.readTimer(); //  ���������� ���������� ���������� ����� � ������.
			//tickVector.resize(tickVector.size() + 1);  // ����������� ������ ��������� �� �������.
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



			n1 += 1; //������������ ����
		}

		if (AccurInterval != true)
		{
			Sleep(5);

		}
		//	Sleep(5);


	}
	mytimer.stopTimer();          //��������� �������

	QueryPerformanceCounter(&EndingTime); // ��������� ���������� �����
	QueryPerformanceFrequency(&Frequency); // ��������� �������
	SetThreadAffinityMask(GetCurrentThread(), oldMask2);   //������������ ����� ������������� ���� ����������  
	totalTime = 1000 * (EndingTime.QuadPart - StartingTime.QuadPart) / Frequency.QuadPart;	 // ��������� ms � ������� ������
	

	// ����������� ������� �������� ��� ��������� ����

	

	mytimer.~TimerCls();
	dateTime2(); // ������ �� �������� � ����

	_endthread();
}
