/*
 * delayclass.h
 *
 *  Created on: 28.6.2012
 *      Author: kubanec
 */

#ifndef DELAYCLASS_H_
#define DELAYCLASS_H_

#include "ch.h"
#define TimeCounter chTimeNow()

class delay_class
{
public:
	delay_class(void (*funkc)(void *), void * args, uint32_t cykle, bool once =
			false);
private:
	void (*funkce)(void *);
	void * arg;
	uint32_t cycles;
	uint32_t temp;
	bool jednou;
	delay_class * next;

	void Register(void);
	void Unregister(void);
	void Play(void);

	friend class delay_process;

public:
	inline void ResetDelay(void)
	{
		temp = TimeCounter;
	}
	inline void SetDelay(uint32_t cykly)
	{
		cycles = cykly;
		temp = TimeCounter;
	}
	inline void Stop(void)
	{
		cycles = 0;
	}
};

class delay_process
{
public:
	static void Play(void);

private:
	friend class delay_class;
	static delay_class * first;
};

#endif /* DELAYCLASS_H_ */
