#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "./stack.h"

using namespace std;

template <class T>
Stack<T>::Stack(int size_)
{
  front = 0;
  next = 0;
  size = size_;

  stack = (T*) malloc(sizeof(T) * size);
  if(stack==NULL) { cerr << "Stack Constructor: Malloc" << endl; }
  //cout << "Created stack - Size: " << size << std::endl;
}


template <class T>
Stack<T>::~Stack()
{
  if(stack!=NULL) free(stack);
  //cout << "Destroyed stack - Final size: " << size << "\n";
}

template <class T>
void Stack<T>::init()
{
  front = 0;
  next = 0;
}


template <class T>
bool Stack<T>::isEmpty()
{
  if( front==next )
    return true;
  else
    return false;
}


template <class T>
bool Stack<T>::isFull()
{
  if(next==size)
    return true;
  else
    return false;
}


template <class T>
void Stack<T>::push(T element)
{
  if(Stack<T>::isFull()) {
    Stack<T>::expand();
  }
  stack[next++]=element;
}

template <class T>
void Stack<T>::pushBlock(T* element, uint32_t elementSize)
{
  // Ensure that there is enough space for our copy
  if(Stack<T>::spaceLeft() < elementSize)
    Stack<T>::expand(elementSize);

  memcpy(stack+next, element, elementSize*sizeof(T));
  next += elementSize;
}

template <class T>
void Stack<T>::expand(uint32_t minSize)
{
  size *= 2;

  while(minSize>=Stack<T>::spaceLeft()) {
    size *= 2;
  }

  stack = (T*) realloc(stack, sizeof(T) * size);
  if(stack==NULL) { cerr << "Stack Constructor: Realloc" << std::endl; }
}

template <class T>
T Stack<T>::pop()
{
  if(Stack<T>::isEmpty())
    return UINT32_MAX;
  else {    
    next--;
    return stack[next];
  }
}

template <class T>
uint32_t Stack<T>::top(){
		return stack[next-1];
}

template <class T>
uint32_t Stack<T>::count()
{
  return (next - front);
}

template <class T>
uint32_t Stack<T>::spaceLeft()
{
  return (size - next);
}

template <class T>
void Stack<T>::print()
{
  if(Stack<T>::isEmpty())
    cout<<"-\n";
  else
  {
    for(int i=front; i<next; i++)
    {
      cout << "\t" << stack[i];
    }
  }
  cout << "\n";
}


/* Inform the compiler about which types we are going to use the template */
template class Stack<uint32_t>;

