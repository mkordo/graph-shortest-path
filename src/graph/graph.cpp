#include <iostream>
#include <string.h>

#include "graph.h"

using namespace std;

template <class T>
Graph<T>::Graph(uint32_t size_)
{
  //cout << "Create Graph\n";
  int i;
  size = size_;
  if(size<=1) cerr << "Given graph size is not valid" << endl;
  last = 0;
  version = 0;
  buffer = (T*) malloc(sizeof(T) * size);
  if(buffer==NULL) cerr << "Graph Constructor : Malloc" << endl;
  new (buffer+0) T();
  for(i=0; i<size; i++) new (buffer+i) T();
  //(i=0; i<size; i++) memcpy ( buffer+i, buffer, sizeof(T) );
}

template <class T>
Graph<T>::~Graph()
{
  int i;
  //cout << "Destroy Graph\n";
  for(i=0; i<size; i++)
    (buffer+i)->~T();
  free(buffer);
}

template <class T>
bool Graph<T>::insert(uint32_t me, uint32_t neighbor)
{
  if(last < me) last = me;
  if(size <= me) Graph<T>::expand(me);
  if(buffer[me].neighbor==NULL) buffer[me].init();
  return buffer[me].insert(neighbor, version);
}

template <class T>
void Graph<T>::expand(uint32_t newNode)
{
  int i;
  uint32_t newSize;
  newSize = size*2;
  while(newSize<=newNode) { newSize *= 2; }
  buffer = (T*) realloc(buffer, sizeof(T) * newSize);
  if(buffer==NULL) { cerr << "Graph Expand: realloc" << endl; }

  for(i=size; i<newSize; i++)  new (buffer+i) T();
  //new (buffer+size) T();
  //for(i=size+1; i<newSize; i++) memcpy ( buffer+i, buffer+size, sizeof(T) );

  size=newSize;
  cout << "Expand Graph : New size " << size << "\n";
}

template <class T>
void Graph<T>::resize(uint32_t newSize)
{
  int i;
  if(size >= newSize) {
    cerr << "Graph Resize: Invalid new size\n";
    return;
  }
  buffer = (T*) realloc(buffer, sizeof(T) * newSize);
  if(buffer==NULL) { cerr << "Graph Resize: realloc" << endl; }

  for(i=size; i<newSize; i++) new (buffer+i) T();

  size=newSize;
  cout << "Resize Graph : New size " << size << "\n";
}

template <class T>
bool Graph<T>::hasNode(uint32_t me)
{
  if(me>size) return false;                // Node is out of bounds
  else if(buffer[me].neighbor==NULL) return false;  // Node does not have neighbors
  else return true;
}

template <class T>
void Graph<T>::print()
{
  int i;
  cout << "Print graph: \n";
  for(i=0; i<last+1; i++) {
    if(buffer[i].neighbor!=NULL) {
      cout << i << ": \t";
      buffer[i].print();
    }
  }
  cout << "\n";
}


/* Inform the compiler about which types we are going to use the template */
template class Graph<Node>;
template class Graph<HashNode>;