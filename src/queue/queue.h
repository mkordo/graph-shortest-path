#ifndef QUEUE_H
#define QUEUE_H

#include <cstdint>    /* For uint32_t */

template <class T>
class Queue
{
  private:
	uint32_t front, next;
	T *queue;
	int size;

  public:

  	Queue(int size_ = 128);
  	~Queue();

  	void init();
	bool isEmpty();
	bool isFull();
	uint32_t spaceLeft();
	void push(T);
	void pushBlock(T*, uint32_t);
	bool pop(T&);
	T pop();
	void print();
	void expand(uint32_t minSize = 1);
	uint32_t count();
};

#endif
