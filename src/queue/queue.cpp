#include <iostream>
#include <stdlib.h>
#include <cstdint>    /* For uint32_t */

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
void Queue<T>::expand()
{
  size *= 2;
  queue = (T*) realloc(queue, sizeof(T) * size);
  if(queue==NULL) { std::cerr << "Queue Constructor: Malloc" << std::endl; }
}

template <class T>
T Queue<T>::pop()
{
  if(Queue<T>::isEmpty())
    return -1;
  else {    
    front++;
    return queue[front-1];
  }
}


template <class T>
void Queue<T>::print()
{
  if(Queue<T>::isEmpty())
    std::cout<<"\nSorry the queue is empty!";
  else
  {
    std::cout<<"\nQueue elements are : ";
    for(int i=front; i<next; i++)
    {
      std::cout << "\t" << queue[i];
    }
  }
  std::cout << "\n";
}


/* Inform the compiler about which types we are going to use the template */
template class Queue<uint32_t>;

