#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

template <class T>
Queue<T>::Queue(int size_)
{
  front = 0;
  next = 0;
  size = size_;

  queue = (T*) malloc(sizeof(T) * size);
  if(queue==NULL) { std::cerr << "Queue Constructor: Malloc" << std::endl; }
  //std::cout << "Created queue - Size: " << size << std::endl;
}


template <class T>
Queue<T>::~Queue()
{
  free(queue);
  //std::cout << "Destroyed queue - Final size: " << size << "\n";
}

template <class T>
void Queue<T>::init()
{
  front = 0;
  next = 0;
}


template <class T>
bool Queue<T>::isEmpty()
{
  if( front==next )
    return true;
  else
    return false;
}


template <class T>
bool Queue<T>::isFull()
{
  if(next==size)
    return true;
  else
    return false;
}


template <class T>
void Queue<T>::push(T element)
{
  if(Queue<T>::isFull()) {
    Queue<T>::expand();
  }
  queue[next++]=element;
}

template <class T>
void Queue<T>::pushBlock(T* element, uint32_t elementSize)
{
  // Ensure that there is enough space for our copy
  if(Queue<T>::spaceLeft() < elementSize)
    Queue<T>::expand(elementSize);

  memcpy(queue+next, element, elementSize*sizeof(T));
  next += elementSize;
}

template <class T>
void Queue<T>::expand(uint32_t minSize)
{
  size *= 2;

  while(minSize>=Queue<T>::spaceLeft()) {
    size *= 2;
  }

  queue = (T*) realloc(queue, sizeof(T) * size);
  if(queue==NULL) { std::cerr << "Queue Constructor: Realloc" << std::endl; }
}

template <class T>
T Queue<T>::pop()
{
  if(Queue<T>::isEmpty())
    return UINT32_MAX;
  else {    
    front++;
    return queue[front-1];
  }
}

template <class T>
uint32_t Queue<T>::count()
{
  return (next - front);
}

template <class T>
uint32_t Queue<T>::spaceLeft()
{
  return (size - next);
}

template <class T>
void Queue<T>::print()
{
  if(Queue<T>::isEmpty())
    std::cout<<"Sorry the queue is empty!\n";
  else
  {
    for(int i=front; i<next; i++)
    {
      std::cout << "\t" << queue[i];
    }
  }
  std::cout << "\n";
}


/* Inform the compiler about which types we are going to use the template */
template class Queue<uint32_t>;

