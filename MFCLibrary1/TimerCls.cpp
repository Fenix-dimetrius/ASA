#include "stdafx.h"
#include "TimerCls.h"


TimerCls::TimerCls()
{
}


TimerCls::~TimerCls()
{
}

//инициализация
void TimerCls::init()
{
	freq = getFreq();
	tickLen = 1000.0 / freq; // длитильность тика 1 мс
}

//частота таймера
double TimerCls::getFreq()
{

	LARGE_INTEGER fr;
	if (!QueryPerformanceFrequency(&fr))
		return  0;
	return (double)fr.QuadPart;
}

//остановить таймер
void TimerCls::stopTimer()
{
	currentTime = 0;
	lastTime = 0;
}

//старт таймера
void TimerCls::startTimer()
{
	init();
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 2); ///использовать только 2 ядро процессора 
	QueryPerformanceCounter(&start);
	SetThreadAffinityMask(GetCurrentThread(), oldMask);
	lastTime = currentTime = readTimer();
}
//считывание времени
double TimerCls::readTimer()
{
	DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 2); //использовать только 2 ядро процессора (по идее 3 ядро, но почему то грузится только второе)
	LARGE_INTEGER currentTime;                                              //засечь текущее время
	QueryPerformanceCounter(&currentTime);                                  //восстановить маску использования ядер процессора
	SetThreadAffinityMask(GetCurrentThread(), oldMask);                      //вернуть текущее время
	return (currentTime.QuadPart - start.QuadPart) * tickLen; // возвращаем время в мс
}
