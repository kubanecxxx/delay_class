/*
 * delayclass.cpp
 *
 *  Created on: 28.6.2012
 *      Author: kubanec
 */

#include "inttypes.h"
#include "delayclass.h"

delay_class * delay_process::first = 0;

/**
 * @note function with "once == true" will be executed only once but memory
 * for delay_class will not be freed
 */
delay_class::delay_class(void (*funkc)(void *), void * args, uint32_t cykle,
		bool once) :
		funkce(funkc), arg(args), cycles(cykle), temp(TimeCounter), jednou(
				once), next(0)
{
	Register();
}

void delay_class::Register()
{
	if (delay_process::first == 0)
	{
		delay_process::first = this;
	}
	else
	{
		delay_class * temp, *prev;
		temp = delay_process::first;

		while (temp != 0)
		{
			prev = temp;
			temp = temp->next;
		}
		prev->next = this;
	}
}

void delay_class::Unregister(void)
{
	//najit ten pointer před nim a nastavit to na ten dalši...
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
			temp = TimeCounter;
			funkce(arg);
			if (jednou)
			{
				Unregister();
			}
		}
	}
}
/*
 *********************************************************************
 */
/**
 * @brief run all registered delay_class's functions
 */
void delay_process::Play()
{
	delay_class * temp = first;

	while (temp)
	{
		temp->Play();
		temp = temp->next;
	}
}

