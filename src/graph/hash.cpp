#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>

#include "hash.h"

using namespace std;

HashNode::HashNode(uint32_t size_)
{
  //cout << "Create hashed node\n";
  int i;
  size = size_;
  inserted = 0;

  size = HashNode::primeNext(size);
  //cout << "Size " << size << endl;

  neighbor = (uint32_t*) malloc(sizeof(uint32_t) * size);
  if(neighbor==NULL) { std::cerr << "Node Constructor: Malloc" << std::endl; }
  for(i=0; i<size; i++) neighbor[i]=-1;
}

HashNode::~HashNode()
{
  //cout << "Destroy hashed node : "; Node::print();
  free(neighbor);
}

bool HashNode::insert(uint32_t neighbor_, uint32_t version_)
{
  if( ( ((double) inserted)/size ) > 0.7 ) {
    HashNode::expand();
  }

  if( HashNode::findCell(neighbor_)==true ) {
    inserted++;
    //cout << "Density : " << ((double) inserted)/size << endl << endl;
    return true;
  }
  else return false;
}

bool HashNode::findCell(uint32_t neighbor_)
{
  uint32_t cell;
  int i;

  for( i=1, cell=HashNode::hash(neighbor_) ; ; i++)
  {
    if(neighbor[cell]==-1) {
      //std::cout << "Insert at: " << cell << std::endl;
      neighbor[cell] = neighbor_;
      return true;
    }
    else if(neighbor[cell]==neighbor_) {
      //cout << "Found duplicate!\n";
      return false;
    }
    else {
      //std::cout << "Colision at: " << cell;
      cell = HashNode::hash(neighbor_+(i^2));
      //std::cout << ". New cell: " << cell << std::endl;
    }
  }
}


void HashNode::expand()
{
  uint32_t *old;
  uint32_t oldsize;
  int i;

  oldsize=size;
  size *= 2;
  size = HashNode::primeNext(size);
  //std::cout << "doubled... New size: " << size << std::endl;
  old = neighbor;
  neighbor = (uint32_t*) malloc(sizeof(uint32_t) * size);
  if(neighbor==NULL) { std::cerr << "Hash Node Expand: Malloc" << std::endl; }
  for(i=0; i<size; i++) neighbor[i]=-1;

  for(i=0; i<oldsize; i++) {
    if(old[i]!=-1)
      HashNode::findCell(old[i]);
  }
  free(old);
}

uint32_t HashNode::hash(uint32_t me)
{
  return me%size;
}

uint32_t HashNode::primeNext(uint32_t candidate)
{
  int divisor=3;
  bool isPrime=false;

  if (candidate%2==0) candidate++; // Prime numbers are odd numbers

  while(isPrime==false) {
      isPrime=true;
      for(divisor=3; divisor<=sqrt(candidate); divisor+=2) {
          if(candidate%divisor == 0) {
            isPrime=false;
            break;
          }
      }
      if(isPrime==true) return candidate;
      candidate += 2;
  }

  return candidate;
}

void HashNode::print()
{
  int i;
  for(i=0; i<size; i++) {
    if(neighbor[i]!=-1)
      cout << " " << neighbor[i];
    else {
      //cout << "  _";
    }
  }
  cout << endl;
}
