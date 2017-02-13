#include <iostream>
#include <string.h>

#include "scc.h"

using namespace std;

template <class T>
scc<T>::scc(uint32_t size_)
{
  //cout << "Create Graph\n";
  uint32_t i;
  size = size_;
  //if(size<=1) cerr << "Given scc size is not valid" << endl;
  count = -1;
  version = 0;
  components = (T*) malloc(sizeof(T) * size);
  if(components==NULL) cerr << "scc Constructor : Malloc1" << endl;
  belongs=(uint32_t*) malloc(size*sizeof(uint32_t));
  if(belongs==NULL) cerr << "scc Constructor : Malloc2" << endl;
  for(i=0;i<size;i++){belongs[i]=-1;}
  new (components+0) T();
  //for(i=0; i<size; i++) new (buffer+i) T();
  memset(components, 0, sizeof(T) * size);
}

template <class T>
scc<T>::~scc()
{
  int i;
  //cout << "Destroy Graph\n";
  for(i=0; i<size; i++)
    (components+i)->~T();
  free(components);
  free(belongs);
}

template <class T>
void scc<T>::init(uint32_t size_){
	uint32_t i;
	bs=size_;
	belongs=(uint32_t*) malloc(bs*sizeof(uint32_t));
  if(belongs==NULL) cerr << "scc Constructor : Malloc2" << endl;
  for(i=0;i<bs;i++){belongs[i]=-1;}//cout<<belongs[i]<<" ";}cout<<endl;
}



template <class T>
bool scc<T>::insert( uint32_t neighbor)
{
  //if(count < me) count = me;
  if(size <= count) scc<T>::expand(count);
  if(components[count].included==NULL) components[count].init(count,128);
  belongs[neighbor]=count;//------------------------------------------------
	//cout<<neighbor<<"("<<belongs[neighbor]<<") ";
  return components[count].insert(neighbor);
}

template <class T>
void scc<T>::expand(uint32_t newC)
{
  uint32_t i;
  uint32_t newSize;
  newSize = size*2;
  while(newSize<=newC) { newSize *= 2; }
  components = (T*) realloc(components, sizeof(T) * newSize);
  if(components==NULL) { cerr << "scc Expand: realloc" << endl; }

  //for(i=size; i<newSize; i++)  new (buffer+i) T();
  memset(components+size, 0, sizeof(T) * (newSize-size));

  size=newSize;
  //cout << "Expand SCC : New size " << size << "\n";
}

template <class T>
bool scc<T>::validComponent(uint32_t me)
{
  if(me>=size) return false;                          // Componet is out of bounds
  else if(components[me].included==NULL) return false;    // Component is empty
  return true;
}

template <class T>
bool scc<T>::emptyComponent(uint32_t me)
{
  if(components[me].included==NULL) return false;         // Component is empty
  return true;
}

template <class T>
bool scc<T>::inBounds(uint32_t me)
{
  if(me<size) return true;                            // Component is in bounds
  return false;
}

template <class T>
uint32_t* scc<T>::getComponentNodes(uint32_t me)
{
  return components[me].included;
}

template <class T>
uint32_t scc<T>::getComponentSize(uint32_t me)
{
  return components[me].getSize();
}

template <class T>
void scc<T>::print()
{
  uint32_t i,m=0;
  
  cout << "Print components: \n";
  for(i=0; i<count+1; i++) {
		if(components[i].count<2) continue;
    if(components[i].included!=NULL){
      m++;
      cout << i << " : \t";
      components[i].print();
    }
  }
  cout << "printed " << m<<"/"<<count+1<<" components\n";
}

template <class T>
void scc<T>::printBelong()
{
	uint32_t i;
	for(i=0; i<bs; i++) {
		if(belongs[i]!=-1) cout << i << "->("<< belongs[i]<<")\n";
	}
	cout<<endl;
}

template <class T>
void scc<T>::printComponent(uint32_t me)
{
  if(components[me].included!=NULL)
  {
    components[me].print();
  }
}

template <class T>
void scc<T>::resize(uint32_t newSize)
{
  uint32_t i;
  if(size >= newSize) {
    cerr << "SCC Resize: Invalid new size\n";
    return;
  }
  components = (T*) realloc(components, sizeof(T) * newSize);
  if(components==NULL) { cerr << "SCC Resize: realloc" << endl; }

  for(i=size; i<newSize; i++) new (components+i) T();

  size=newSize;
  cout << "Resize SCC : New size " << size << "\n";
}

template <class T>
int scc<T>::findNodeSCC( uint32_t nodeId){
	return belongs[nodeId];
}


/* Inform the compiler about which types we are going to use the template */
template class scc<Component>;
