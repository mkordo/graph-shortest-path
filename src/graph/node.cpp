#include <iostream>
#include <string>
#include <stdlib.h>

#include "node.h"

using namespace std;

Node::Node(uint32_t size_)
{
  //cout << "Create node\n";
  int i;
  size = size_;
  current = 0;
  neighbor=NULL;
  current=1;
}

void Node::init(uint32_t size_)
{
    size = size_;
    neighbor = (uint32_t*) malloc(sizeof(uint32_t) * size);
    //version = (uint32_t*) malloc(sizeof(uint32_t) * size);

    if(neighbor==NULL) { std::cerr << "Node Constructor: Malloc" << std::endl; }
    //if(version==NULL) { std::cerr << "Node Constructor: Malloc" << std::endl; }
}

Node::Node(uint32_t size_, uint32_t *neighbor_)
{
  //cout << "Create node\n";

  int i;
  size = size_;
  current = 0;

  //version = (uint32_t*) calloc(size, sizeof(uint32_t));
  //if(version==NULL) { std::cerr << "Node Constructor: Malloc" << std::endl; }

  neighbor = neighbor_;
}

Node::~Node()
{
  //cout << "Destroy node : "; Node::print();

  if(neighbor!=NULL) {
    free(neighbor);
  //free(version);
  }
}

bool Node::insert(uint32_t neighbor_, uint32_t version_)
{
  if(current<size) {
    neighbor[current] = neighbor_;
    //version[current] = version_;
    current++;
  }
  else {
    Node::expand();
    Node::insert(neighbor_, version_);
  }
  return true;
}

void Node::print()
{
  int i=0;
  for(i=0; i<current; i++) cout << " " << neighbor[i];

  cout << endl;
}



void Node::expand()
{
  size *= 2;
  neighbor = (uint32_t*) realloc(neighbor, sizeof(uint32_t) * size);
  //version = (uint32_t*) realloc(version, sizeof(uint32_t) * size);

  if(neighbor==NULL) { std::cerr << "Node Expand: Realloc" << std::endl; }
  //if(version==NULL) { std::cerr << "Node Expand: Realloc" << std::endl; }
}
