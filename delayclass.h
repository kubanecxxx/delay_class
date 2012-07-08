/*
 * delayclass.h
 *
 *  Created on: 28.6.2012
 *      Author: kubanec
 */

#ifndef DELAYCLASS_H_
#define DELAYCLASS_H_

class delay_class
{
public:
	delay_class(void (*funkc)(void *), void * args , uint32_t cykle, bool once = false);
	~delay_class();
	void constructor(void (*funkc)(void *), void * args , uint32_t cykle, bool once = false);
	void ResetDelay(void);
	void destructor(void);
	void SetDelay(uint32_t cykly);
	void Stop (void){ cycles = 0;}
	void Play(void);

private:
	void (* funkce) (void *);
	uint32_t cycles;
	uint32_t temp;
	void * arg;
	bool jednou;
};

template<class T> class simple_list
{
public:
	simple_list(void) {Clear();}
	void push_back (T  item);
	void Del (T item);
	int GetCount (void) {return count;}
	T GetItem (int index) ;
	void Clear(void) {count = 0;}

private:
	T  item[10];
	int count;
};

class delay_process
{
public:
	delay_process();
	void constructor(void);
	void Add(delay_class * trida);
	void Del(delay_class * trida);
	void Play(void);

private:
	simple_list<delay_class *> seznam_opakovat;
};



#endif /* DELAYCLASS_H_ */
