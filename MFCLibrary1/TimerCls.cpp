#include "stdafx.h"
#include "TimerCls.h"


TimerCls::TimerCls()
{
}


TimerCls::~TimerCls()
{
}

//�������������
void TimerCls::init()
{
	freq = getFreq();
	tickLen = 1000.0 / freq; // ������������ ���� 1 ��
}

//������� �������
double TimerCls::getFreq()
{

	LARGE_INTEGER fr;
	if (!QueryPerformanceFrequency(&fr))
		return  0;
	return (double)fr.QuadPart;
}

//���������� ������
void TimerCls::stopTimer()
{
	currentTime = 0;
	lastTime = 0;
}

//����� �������
void TimerCls::startTimer()
{
	init();
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 2); ///������������ ������ 2 ���� ���������� 
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldMask);
	lastTime = currentTime = readTimer();
}
//���������� �������
double TimerCls::readTimer()
{
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 2); //������������ ������ 2 ���� ���������� (�� ���� 3 ����, �� ������ �� �������� ������ ������)
	LARGE_INTEGER currentTime;                                              //������ ������� �����
	QueryPerformanceCounter(&currentTime);                                  //������������ ����� ������������� ���� ����������
	SetThreadAffinityMask(GetCurrentThread(), oldMask);                      //������� ������� �����
	return (currentTime.QuadPart - start.QuadPart) * tickLen; // ���������� ����� � ��
}
