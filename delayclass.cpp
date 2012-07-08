/*
 * delayclass.cpp
 *
 *  Created on: 28.6.2012
 *      Author: kubanec
 */

#include "stm32f4xx.h"
#include "delayclass.h"

extern uint32_t TimeCounter;

delay_process * pointer = 0;

delay_class::delay_class(void (*funkc)(void *), void * args , uint32_t cykle, bool once)
{
	constructor(funkc,args,cykle, once);
}

delay_class::~delay_class()
{
	destructor();
}

void delay_class::destructor(void)
{
	if (pointer != 0)
	{
		pointer->Del(this);
	}
}

void delay_class::constructor(void (*funkc)(void *), void * args , uint32_t cykle, bool once)
{
	funkce = funkc;
	arg = args;
	cycles = cykle;
	temp = TimeCounter;
	jednou = once;

	if (pointer != 0)
		pointer->Add(this);

	//zaregistrovat někam véš
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

void delay_class::Play()
{
	if (cycles != 0)
	{
		if (TimeCounter - temp > cycles)
		{
			funkce(arg);
			temp = TimeCounter;
			if (jednou)
				destructor();
		}
	}
}

delay_process::delay_process()
{
	constructor();
}

void delay_process::constructor(void)
{
	pointer = this;
}

void delay_process::Add(delay_class * trida)
{
	seznam_opakovat.push_back(trida);
}

void delay_process::Del(delay_class * trida)
{
	seznam_opakovat.Del(trida);;
}

void delay_process::Play()
{
	for (int i = 0 ; i < seznam_opakovat.GetCount() ; i++)
	{
		seznam_opakovat.GetItem(i)->Play();
	}
}

template <class T> void simple_list<T>::push_back (T  otem)
{
	item[count++] = otem;
}

template <class T> void simple_list<T>::Del (T  otem)
{
	for (int i = 0 ; i < count ; i++)
	{
		if (item[i] == otem)
		{
			for (int j = i ; j < count ; j++)
			{
				item[j] = item[j+1];
			}
			break;
		}
	}
	count--;
}

template <class T> T simple_list<T>::GetItem(int index)
{
	if (index < count)
		return item[index];
	else
		return 0;
}
