#pragma once
class TimerCls
{
public:
	TimerCls();
	~TimerCls();

private:
	LARGE_INTEGER start;                        //начальное время
	double freq;                                //частота таймера
	double tickLen;                            //длина тика
	double currentTime;                        //текущее время
	double lastTime;                           //предыдущее время
	void init();                                //инициализация
	double getFreq();                          //частота таймера    
public:
	void stopTimer();                          //остановка таймера
	void startTimer();                      //старт таймера 
	double readTimer();                        //вернуть время (от начального времени)
};

