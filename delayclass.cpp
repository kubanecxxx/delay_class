/*
 * delayclass.cpp
 *
 *  Created on: 28.6.2012
 *      Author: kubanec
 */

#include "stm32f4xx.h"
#include "delayclass.h"

extern uint32_t TimeCounter;

delay_process * delay_process::pointr = 0;

/**
 * @note function with "once == true" will be executed only once but memory
 * for delay_class will not be freed, only pointer will be freed
 */
delay_class::delay_class(void (*funkc)(void *), void * args, uint32_t cykle,
		bool once)
{
	funkce = funkc;
	arg = args;
	cycles = cykle;
	temp = TimeCounter;
	jednou = once;

	if (delay_process::pointr != 0)
		delay_process::pointr->Add(this);
}

delay_class::~delay_class()
{

}

void delay_class::ResetDelay(void)
{
	temp = TimeCounter;
}

void delay_class::SetDelay(uint32_t cykly)
{
	cycles = cykly;
	temp = TimeCounter;
}

/**
 * @brief run callback if time passed by
 */
void delay_class::Play()
{
	if (cycles != 0)
	{
		if (TimeCounter - temp > cycles)
		{
			funkce(arg);
			temp = TimeCounter;
			if (jednou)
			{
				delay_process::pointr->Del(this);
			}
		}
	}
}
/*
 * ********************************************************************
 */
delay_process::delay_process()
{
	if (pointr == 0)
		pointr = this;
	else
		while (1)
			;
}

void delay_process::Add(delay_class * trida)
{
	seznam_opakovat.push_back(trida);
}

void delay_process::Del(delay_class * trida)
{
	seznam_opakovat.Del(trida);
	;
}

/**
 * @brief run all registered delay_class's functions
 */
void delay_process::Play()
{
	for (int i = 0; i < seznam_opakovat.GetCount(); i++)
	{
		seznam_opakovat.GetItem(i)->Play();
	}
}

/*
 * ********************************************************************
 */
template<class T, int S> void simple_list<T, S>::push_back(T otem)
{
	item[count++] = otem;
}

template<class T, int S> void simple_list<T, S>::Del(T otem)
{
	for (int i = 0; i < count; i++)
	{
		if (item[i] == otem)
		{
			for (int j = i; j < count; j++)
			{
				item[j] = item[j + 1];
			}
			break;
		}
	}
	count--;
}

template<class T, int S> T simple_list<T, S>::GetItem(int index)
{
	if (index < count)
		return item[index];
	else
		return 0;
}

