/*
 * delayclass.h
 *
 *  Created on: 28.6.2012
 *      Author: kubanec
 */

#ifndef DELAYCLASS_H_
#define DELAYCLASS_H_

#include <new>

extern "C" void * _sbrk(int inc);

class delay_new
{
public:
	static void * operator new(size_t size)
	{
		return _sbrk(size);
	}
	/*
	static void operator delete(void * address)
	{
		return;
	}
	*/
};

class delay_class: public delay_new
{
public:
	delay_class(void (*funkc)(void *), void * args, uint32_t cykle, bool once =
			false);
	~delay_class();
	void ResetDelay(void);
	void SetDelay(uint32_t cykly);
	void Stop(void)
	{
		cycles = 0;
	}
	void Play(void);

private:
	void (*funkce)(void *);
	uint32_t cycles;
	uint32_t temp;
	void * arg;
	bool jednou;
};

template<class T, int S> class simple_list: public delay_new
{
public:
	simple_list(void)
	{
		Clear();
	}
	void push_back(T item);
	void Del(T item);
	int GetCount(void)
	{
		return count;
	}
	T GetItem(int index);
	void Clear(void)
	{
		count = 0;
	}

private:
	T item[S];
	int count;
};

class delay_process: public delay_new
{
public:
	delay_process();
	void Add(delay_class * trida);
	void Del(delay_class * trida);
	void Play(void);
	static delay_process * pointr;

private:
	simple_list<delay_class *, 10> seznam_opakovat;
};

#endif /* DELAYCLASS_H_ */
