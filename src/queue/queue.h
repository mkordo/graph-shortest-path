#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
  private:
	int front, next;
	T *queue;
	int size;

  public:

  	Queue(int size_ = 100);
  	~Queue();

  	void init();
	bool isEmpty();
	bool isFull();
	void push(T);
	T pop();
	void print();
	void expand();
};

#endif