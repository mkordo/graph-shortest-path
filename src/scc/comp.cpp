#include <iostream>
#include <string>
#include <stdlib.h>

#include "comp.h"

using namespace std;

Component::Component(uint32_t size_)
{
  //cout << "Create Component\n";
  uint32_t i;
  size = size_;
  count = 0;
  included=NULL;
  //count=1;
}

void Component::init(uint32_t id_,uint32_t size_)
{
    size = size_;
    included = (uint32_t*) malloc(sizeof(uint32_t) * size);
		id=id_;
    if(included==NULL) { std::cerr << "Component Constructor: Malloc" << endl; }
}

Component::Component(uint32_t size_, uint32_t *included_)
{
  //cout << "Create Component\n";

  uint32_t i;
  size = size_;
  count = 0;

  included = included_;
}

Component::~Component()
{
  //cout << "Destroy Component : "; Component::print();

  if(included!=NULL) {
    free(included);
  }
}

bool Component::insert(uint32_t new_)
{
  if(count<size) {
    included[count] = new_;
    count++;
  }
  else {
    Component::expand();
    Component::insert(new_);
  }
  return true;
}

void Component::print()
{
  uint32_t i=0;
  cout<<"Component " << id <<"  \t#nodes: ";
  cout<< count<<" |  ";
  //for(i=0; i<count; i++) cout << included[i]<< " " ;

  cout << endl;
}

uint32_t Component::getSize()
{
  return count;
}


void Component::expand()
{
  size *= 2;
  included = (uint32_t*) realloc(included, sizeof(uint32_t) * size);

  if(included==NULL) { cerr << "Component Expand: Realloc" << std::endl; }
}



