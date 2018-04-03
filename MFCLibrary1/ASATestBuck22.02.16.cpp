
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
std::vector <float> updInfVecChan0(2); // ������ ��� ���������� �������� ������ 0
std::vector <float> updInfVecChan1(2); // ������ ��� ���������� �������� ������ 1
std::vector <float> updInfVecChan2(2); // ������ ��� ���������� �������� ������ 2
std::vector <float> updInfVecChan3(2); // ������ ��� ���������� �������� ������ 3
std::vector <__int64> freqVector(2);// ������ ���������� ������� ����������

std::vector <CString> TimeInterval(2); // ������ ��� ���������� ������� ������� ������ �����
std::vector <CString> ChouseCard(2); // ������ ��� ���������� ������ �����

std::vector <CString> TruOrFalseCard(2); // ������ ��� ���������� ������ �� ����� ����(����� ��� ���)
std::vector <CString> NumActualCard(2); // ������ ��� ���������� ������� ��������


//										// ��������� ���� ��� ������ �������
//
//std::vector <float> TrueEpoImposChan0(2); // ������ ��� ���������� �������� ������ 0
//std::vector <float> TrueEpoImposBufChan0(2); // ������ ��� ���������� �������� ������ 0
//
//std::vector <float> TrueEpoImposChan1(2); // ������ ��� ���������� �������� ������ 1
//std::vector <float> TrueEpoImposBufChan1(2); // ������ ��� ���������� �������� ������ 1
//
//std::vector <float> TrueEpoImposChan2(2); // ������ ��� ���������� �������� ������ 2
//std::vector <float> TrueEpoImposBufChan2(2); // ������ ��� ���������� �������� ������ 2
//
//std::vector <float> TrueEpoImposChan3(2); // ������ ��� ���������� �������� ������ 3
//std::vector <float> TrueEpoImposBufChan3(2); // ������ ��� ���������� �������� ������ 3
//
//
//										// ��������� ���� ��� �������� �������
//
//std::vector <float> FalseEpoImposChan0(2); // ������ ��� ���������� �������� ������ 0
//std::vector <float> FalseEpoImposBufChan0(2); // ������ ��� ���������� �������� ������ 0
//
//std::vector <float> FalseEpoImposChan1(2); // ������ ��� ���������� �������� ������ 1
//std::vector <float> FalseEpoImposBufChan1(2); // ������ ��� ���������� �������� ������ 1
//
//std::vector <float> FalseEpoImposChan2(2); // ������ ��� ���������� �������� ������ 2
//std::vector <float> FalseEpoImposBufChan2(2); // ������ ��� ���������� �������� ������ 2
//
//std::vector <float> FalseEpoImposChan3(2); // ������ ��� ���������� �������� ������ 3
//std::vector <float> FalseEpoImposBufChan3(2); // ������ ��� ���������� �������� ������ 3
//
////std::vector <CString> TruOrFalseCardEPO(2); // ������ ��� ���������� ������ �� ����� ����(����� ��� ���) ��� ��������� ����
//
//
//
//// ������� ����������� �������. ������ ������� - ���������� �������� ������� �� ���������. 1 � ������ - ��������� ��������, 0 - ���
//std::vector <float> Number049(1); // ������ ��� ���
//std::vector <float> Number5099(1); // ������ ��� ���������� �������
//std::vector <float> Number100149(1); // ������ ��� ����������� �������


//int i001 = 0;
void testOut(DWORD dwObjectIndex, DWORD NumOfInstruments)
{
	//i001++;
		std::ofstream out("PlugIns/Odata/TestOut.csv", std::ios::app);
	out << "\n" << NumOfInstruments << "\n";
	out.close();
}

void ThreadTimerTick(void* pParams); // ��������� ����� � ��������

void ImposEpoFunc(); // ����� ��������� ����

ASATest::ASATest()
	//: v_AllUrl(0)
{
}


ASATest::~ASATest()
{
}

CString returnVal;
// ���������� ����� ��������
CString ASATest::getUrlPic()
{
	int Rand1 = 0; // ��������� ����� ��������
	int xmin = 0;

	LARGE_INTEGER NumTickProc;
	QueryPerformanceCounter(&NumTickProc);


	if (v_Available.size() >= 2)
	{
		Rand1 = (rand() % (v_Available.size()));// - xmin + 1) + xmin); // ���������� ��������� ����� � �������� �� 0 �� ������� �������
											
	}
	else
	{
		Rand1 = 0;
		EndGenNumPic = true;
	}


	
	//returnVal.re
	//returnVal.Format("\%i", Rand1);

	//AfxMessageBox(returnVal);
	
	returnVal.Format("\%i", v_Available[Rand1]);

	v_Available.erase(v_Available.begin() + Rand1); // ������� ������ �� ������� Rand1
	std::vector<int>(v_Available).swap(v_Available); // ��������� ������ ��� ��������� �������

	
	

	if (NumTickProc.QuadPart % 2 == 0) // �������� ����� ����� ���������� ��������� �� ��������
	{

		if (GenNumPicBefore != true)
		{
			UpdInfoVal.TruOrFalseCard = "True";
		}
		return returnVal; // ���� �����, �� ���������� �����, ����������� � ����������� ������
	}
	
	else
	{
		if (GenNumPicBefore != true)
		{
			UpdInfoVal.TruOrFalseCard = "False";
		}
		return CString("150"); // ���� ���, �� ����� ���
	}

//	return CString();
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

	if (StartRecorPlay == true)
	{
		_beginthread(ThreadTimerTick, 0, NULL);// ������ 

	}
	else
	{
		if (MessageBox(NULL, "������ �� ����� ������. ���������� ������ � ����?", " ", MB_YESNO) == IDYES)
		{
			_beginthread(ThreadTimerTick, 0, NULL);// ������ 
		}
	}
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
	int timeEpo = -m_BeforeShow; //������. � ������ ����� ...
	CString TimeIntervalEpo;// �������� ���������� ���������
	
	std::ofstream out;
	out.open(fileNameEn, std::ios::app);
	for (int i2 = 0; i2 < BufImposEpoch.ChanImpos.TrueSumEpoChan0.size(); i2++)
	{
		if (timeEpo + m_BeforeShow <= m_BeforeShow)
		{
			TimeIntervalEpo = "Before";
		}

		if (m_BeforeShow < timeEpo + m_BeforeShow && timeEpo + m_BeforeShow <= m_BeforeShow + m_ShowTime)
		{
			TimeIntervalEpo = "Show";
		}

		if (m_BeforeShow + m_ShowTime < timeEpo + m_BeforeShow && timeEpo + m_BeforeShow <= m_BeforeShow + m_ShowTime + m_AfterShow)
		{
			TimeIntervalEpo = "After";
		}


		out << timeEpo << ";" << TimeIntervalEpo << ";" << BufImposEpoch.ChanImpos.TrueSumEpoChan0[i2] << ";" << BufImposEpoch.ChanImpos.TrueSumEpoChan1[i2] << ";" << BufImposEpoch.ChanImpos.TrueSumEpoChan2[i2] << ";" << BufImposEpoch.ChanImpos.TrueSumEpoChan3[i2] << ";"
			<< ";" << BufImposEpoch.ChanImpos.FalseSumEpoChan0[i2] << ";" << BufImposEpoch.ChanImpos.FalseSumEpoChan1[i2] << ";" << BufImposEpoch.ChanImpos.FalseSumEpoChan2[i2] << ";" << BufImposEpoch.ChanImpos.FalseSumEpoChan3[i2] << "\n";

		timeEpo = timeEpo + measureInterval;
	}
	out << "����������� ������:" << ";" << ";" << BufImposEpoch.ChanImpos.STrue[0] << ";" << BufImposEpoch.ChanImpos.STrue[1] << ";" << BufImposEpoch.ChanImpos.STrue[2] << ";" << BufImposEpoch.ChanImpos.STrue[3]  << " " << ";" << ";" << BufImposEpoch.ChanImpos.SFalse[0] << ";" << BufImposEpoch.ChanImpos.SFalse[1] << ";" << BufImposEpoch.ChanImpos.SFalse[2] << ";" << BufImposEpoch.ChanImpos.SFalse[3] << "\n";


	out.close();
}

void dateTime2()
{
	char buffer1[100];
	
	time_t seconds = time(NULL);
	

	tm* timeinfo = localtime(&seconds); // �������� ��������� ����� � ��������
	
	//ASADlg dlg1;

	char* format1;
	//dlg1.UpdateData(TRUE);
	//UpdateData(TRUE);
	switch (MenOrWomen)
	{
	case 0:
		format1 = "PlugIns/Odata/Records/%Y.%m.%d(%H-%M-%S)MAN.csv";
		break;
	case 1:
		format1 = "PlugIns/Odata/Records/%Y.%m.%d(%H-%M-%S)WOM.csv";
		break;
	default:
		format1 = "PlugIns/Odata/Records/%Y.%m.%d(%H-%M-%S)En.csv";
		break;
	}
	
	
	//= "PlugIns/Odata/Records/%Y.%m.%d(%H-%M-%S)En.csv";
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
	out << "���� ���������� �: " << ";" << buffer1 << "\n";
	out <<"�������:"<<"\n"<< UpdInfoVal.SureName << ";" << UpdInfoVal.Name <<";" << UpdInfoVal.SecName << "\n"<<"\n";
	

	//======================================== ��������� ����================================================
	SumEpochClass EroImposEpoch;// ���
	SumEpochClass NegImposEpoch;// ���
	SumEpochClass NeuImposEpoch;// ���



	//-----------------���------------------------
	EroImposEpoch.OutImposEpo(updInfVecChan0, updInfVecChan1, updInfVecChan2, updInfVecChan3, TruOrFalseCard, NumActualCard, 0, 49, "�����������", fileNameEn);

	BufImposEpoch.ChanImpos = EroImposEpoch.ChanImpos; // ����������� ��������� � ������������ ��������� ��������� ���������� ������.
	
	

	//int timeEpo = -m_BeforeShow; //������. � ������ ����� ...
	//CString TimeIntervalEpo;// �������� ���������� ���������
	
	out << "\n" << "��������� ����" << "\n" << "\n";
	out << "�����������" << "\n";
	out << "�����" << ";" << " " << ";" << " " << ";" << " " << ";" << " " << ";" << ";" << ";" << "�������" << ";" << "	" << ";" << " " << ";" << " " << "\n"; // ����� �������� �������
	

	out << "Time, ms" << ";" << "Time interval" << ";" << UpdInfoVal.TextInfChan0 << ";" << UpdInfoVal.TextInfChan1 << ";" << UpdInfoVal.TextInfChan2 << ";" << UpdInfoVal.TextInfChan3 << ";"
		<< ";" << UpdInfoVal.TextInfChan0 << ";" << UpdInfoVal.TextInfChan1 << ";" << UpdInfoVal.TextInfChan2 << ";" << UpdInfoVal.TextInfChan3 << "\n"; // ����� �������� �������

	out.close(); // ��������� ����� � ����, �� � ���� �� ��������� ������ �� ������� 	ImposEpochOut()	
	
	ImposEpochOut();// ������ ����� � ����. ������ ���, ��� ���������� ����
				
	// �����������
	BufImposEpoch.~SumEpochClass();
	EroImposEpoch.~SumEpochClass();

	//-----------------------����������----------------


	NegImposEpoch.OutImposEpo(updInfVecChan0, updInfVecChan1, updInfVecChan2, updInfVecChan3, TruOrFalseCard, NumActualCard, 50, 99, "����������", fileNameEn);

	BufImposEpoch.ChanImpos = NegImposEpoch.ChanImpos; // ����������� ��������� � ������������ ��������� ��������� ���������� ������.
	
	out.open(fileNameEn, std::ios::app);

	out << "\n" << "\n" << "����������" << "\n";
	out << "�����" << ";" << " " << ";" << " " << ";" << " " << ";" << " " << ";" << ";" << ";" << "�������" << ";" << "	" << ";" << " " << ";" << " " << "\n"; // ����� �������� �������
	out << "Time, ms" << ";" << "Time interval" << ";" << UpdInfoVal.TextInfChan0 << ";" << UpdInfoVal.TextInfChan1 << ";" << UpdInfoVal.TextInfChan2 << ";" << UpdInfoVal.TextInfChan3 << ";"
		<< ";" << UpdInfoVal.TextInfChan0 << ";" << UpdInfoVal.TextInfChan1 << ";" << UpdInfoVal.TextInfChan2 << ";" << UpdInfoVal.TextInfChan3 << "\n"; // ����� �������� �������

	out.close(); // ��������� ����� � ����, �� � ���� �� ��������� ������ �� ������� 	ImposEpochOut()	

	ImposEpochOut();// ������ ����� � ����. ������ ���, ��� ���������� ����.

	// �����������
	BufImposEpoch.~SumEpochClass();
	NegImposEpoch.~SumEpochClass();


	//------------------------�����������--------------
	NeuImposEpoch.OutImposEpo(updInfVecChan0, updInfVecChan1, updInfVecChan2, updInfVecChan3, TruOrFalseCard, NumActualCard, 100, 149, "�����������", fileNameEn);

	BufImposEpoch.ChanImpos = NeuImposEpoch.ChanImpos; // ����������� ��������� � ������������ ��������� ��������� ���������� ������.

	out.open(fileNameEn, std::ios::app);

	out << "\n" << "\n" << "�����������" << "\n";
	out << "�����" << ";" << " " << ";" << " " << ";" << " " << ";" << " " << ";" << ";" << ";" << "�������" << ";" << "	" << ";" << " " << ";" << " " << "\n"; // ����� �������� �������
	out << "Time, ms" << ";" << "Time interval" << ";" << UpdInfoVal.TextInfChan0 << ";" << UpdInfoVal.TextInfChan1 << ";" << UpdInfoVal.TextInfChan2 << ";" << UpdInfoVal.TextInfChan3 << ";"
		<< ";" << UpdInfoVal.TextInfChan0 << ";" << UpdInfoVal.TextInfChan1 << ";" << UpdInfoVal.TextInfChan2 << ";" << UpdInfoVal.TextInfChan3 << "\n"; // ����� �������� �������

	out.close(); // ��������� ����� � ����, �� � ���� �� ��������� ������ �� ������� 	ImposEpochOut()	

	ImposEpochOut();// ������ ����� � ����. ������ ���, ��� ���������� ����.

					// �����������
	BufImposEpoch.~SumEpochClass();
	NeuImposEpoch.~SumEpochClass();




	// ��������� ���� ��� ������ �������������� ��������
	out.open(fileNameEn, std::ios::app);
	
	
	out << "\n" << "\n" << "�������������� ��������:" << "\n";

	out << "Time, ms" << ";" << UpdInfoVal.TextInfChan0 << ";" << UpdInfoVal.TextInfChan1 << ";" << UpdInfoVal.TextInfChan2 << ";" << UpdInfoVal.TextInfChan3 << ";" << " Time Interval" << ";" << "Chouse Card" << ";" << "TruOrFalseCard" << ";" << "NumActualCard" << "\n";

	for (int j = 0; j<tickVector.size(); j++)
	{

		//val1 = tickVector[j]*1000.0/(double)freqVector[j];
	
		
		out << tickVector[j] << ";" << updInfVecChan0[j] << ";" << updInfVecChan1[j] << ";" << updInfVecChan2[j] << ";" << updInfVecChan3[j] << ";" <<TimeInterval[j] << ";" << ChouseCard[j] << ";" << TruOrFalseCard[j] << ";" << NumActualCard[j] <<"\n";
		//out.close();
	}
	//std::ofstream out(fileNameEn, std::ios::app);
	out << "\n" << "ALL Time: " << totalTime << "\n";
	out.close();

	// ���������� �������
	tickVector.resize(2);
	updInfVecChan0.resize(2);
	updInfVecChan1.resize(2);
	updInfVecChan2.resize(2);
	updInfVecChan3.resize(2);
	freqVector.resize(2);
	TimeInterval.resize(2);
	ChouseCard.resize(2);

	TruOrFalseCard.resize(2); // ������ ��� ���������� ������ �� ����� ����(����� ��� ���)
	NumActualCard.resize(2); // ������ ��� ���������� ������� ��������


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

			tickVector[n1 - 1] = mytimer.readTimer(); //  ���������� ���������� ���������� ����� � ������.
			tickVector.resize(tickVector.size() + 1);  // ����������� ������ ��������� �� �������.
			
			updInfVecChan0[n1 - 1] = UpdInfoVal.updInfChan0;
			updInfVecChan0.resize(updInfVecChan0.size() + 1);

			updInfVecChan1[n1 - 1] = UpdInfoVal.updInfChan1;
			updInfVecChan1.resize(updInfVecChan1.size() + 1);

			updInfVecChan2[n1 - 1] = UpdInfoVal.updInfChan2;
			updInfVecChan2.resize(updInfVecChan2.size() + 1);

			updInfVecChan3[n1 - 1] = UpdInfoVal.updInfChan3;
			updInfVecChan3.resize(updInfVecChan3.size() + 1);

			ChouseCard[n1 - 1] = UpdInfoVal.ChouseCard;
			ChouseCard.resize(ChouseCard.size() + 1);

			TimeInterval[n1 - 1] = UpdInfoVal.TimeInterval;
			TimeInterval.resize(TimeInterval.size() + 1);

			TruOrFalseCard[n1 - 1] = UpdInfoVal.TruOrFalseCard;
			TruOrFalseCard.resize(TruOrFalseCard.size() + 1);

			NumActualCard[n1 - 1] = UpdInfoVal.NumActualCard;
			NumActualCard.resize(NumActualCard.size() + 1);


			//// ������ ������ �� ��������� ������ ��� ������ ��������� ���� ��� ������ �������

			//if (UpdInfoVal.TimeInterval != " " && kTrue < TrueEpoImposBufChan0.size() && UpdInfoVal.TruOrFalseCard == "True")
			//{
			//	TrueEpoImposBufChan0[kTrue] = UpdInfoVal.updInfChan0;

			//	TrueEpoImposBufChan1[kTrue] = UpdInfoVal.updInfChan1;

			//	TrueEpoImposBufChan2[kTrue] = UpdInfoVal.updInfChan2;

			//	TrueEpoImposBufChan3[kTrue] = UpdInfoVal.updInfChan3;
			//	//EpoImposBuf.resize(EpoImposBuf.size() + 1);
			//	kTrue++;
			//}
			//else
			//{
			//	kTrue = 0;

			//}
			//
			//// ������ ������ �� ��������� ������ ��� ������ ��������� ���� ��� �������� �������

			//if (UpdInfoVal.TimeInterval != " " && kFalse < TrueEpoImposBufChan0.size() && UpdInfoVal.TruOrFalseCard == "False")
			//{
			//	FalseEpoImposBufChan0[kFalse] = UpdInfoVal.updInfChan0;

			//	FalseEpoImposBufChan1[kFalse] = UpdInfoVal.updInfChan1;

			//	FalseEpoImposBufChan2[kFalse] = UpdInfoVal.updInfChan2;

			//	FalseEpoImposBufChan3[kFalse] = UpdInfoVal.updInfChan3;
			//	//EpoImposBuf.resize(EpoImposBuf.size() + 1);
			//	kFalse++;
			//}
			//else
			//{
			//	kFalse = 0;

			//}



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

	


	dateTime2(); // ������ �� �������� � ����

	_endthread();
}
