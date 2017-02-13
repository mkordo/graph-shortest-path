#ifndef STACK_H
#define STACK_H

#include <cstdint>    /* For uint32_t */

template <class T>
class Stack
{
  private:
	uint32_t front, next;
	T *stack;
	int size;

  public:

  	Stack(int size_ = 128);
  	~Stack();

  	void init();
	bool isEmpty();
	bool isFull();
	uint32_t spaceLeft();
	void push(T);
	void pushBlock(T*, uint32_t);
	T pop();
	void print();
	void expand(uint32_t minSize = 1);
	uint32_t count();
};

#endif
