#pragma once
class TimerCls
{
public:
	TimerCls();
	~TimerCls();

private:
	LARGE_INTEGER start;                        //��������� �����
	double freq;                                //������� �������
	double tickLen;                            //����� ����
	double currentTime;                        //������� �����
	double lastTime;                           //���������� �����
	void init();                                //�������������
	double getFreq();                          //������� �������    
public:
	void stopTimer();                          //��������� �������
	void startTimer();                      //����� ������� 
	double readTimer();                        //������� ����� (�� ���������� �������)
};

