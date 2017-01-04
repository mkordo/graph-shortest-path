#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cmath>

#include "hash.h"

using namespace std;

HashNode::HashNode(uint32_t size_)
{
  //cout << "Create hashed node\n";
  size = size_;
  inserted = 0;
  neighbor=NULL;
  inserted = 1;
  //size = HashNode::primeNext(size);
  //cout << "Size " << size << endl;
}

void HashNode::init(uint32_t size_)
{
  int i;
  size = size_;
  neighbor = (uint32_t*) malloc(sizeof(uint32_t) * size);
  if(neighbor==NULL) { std::cerr << "Node Constructor: Malloc" << std::endl; }
  //for(i=0; i<size; i++) neighbor[i]=UINT32_MAX;
  memset(neighbor, UINT32_MAX, size * sizeof(uint32_t));
}

HashNode::~HashNode()
{
  //cout << "Destroy hashed node : ";
  if(neighbor!=NULL) {
    //HashNode::print();
    free(neighbor);
  }
}

bool HashNode::insert(uint32_t neighbor_, uint32_t version_)
{
  if( ( ((double) inserted)/size ) > 0.5 ) {
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

    for( i=0; i<size; i++)
    {
      cell=HashNode::hash(neighbor_+(i*i));
      if(neighbor[cell]==UINT32_MAX) {
        //std::cout << "Insert at: " << cell << std::endl;
        neighbor[cell] = neighbor_;
        return true;
      }
      else if(neighbor[cell]==neighbor_) {
        //cout << "Found duplicate!\n";
        return false;
      }
    }

    // If we are here, then the neighbor was not inserted
    HashNode::expand();
    return HashNode::findCell(neighbor_);

    return false;
}

void HashNode::expand()
{
  uint32_t *old;
  uint32_t oldsize;
  int i;

  oldsize=size;
  size *= 2;
  //size = HashNode::primeNext(size);
  //std::cout << "doubled... New size: " << size << std::endl;
  old = neighbor;
  neighbor = (uint32_t*) malloc(sizeof(uint32_t) * size);
  if(neighbor==NULL) { std::cerr << "Hash Node Expand: Malloc" << std::endl; }
  //for(i=0; i<size; i++) neighbor[i]=UINT32_MAX;
  memset(neighbor, UINT32_MAX, size * sizeof(uint32_t));

  for(i=0; i<oldsize; i++) {
    if(old[i]!=UINT32_MAX)
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
    if(neighbor[i]!=UINT32_MAX)
      cout << " " << neighbor[i];
    else {
      //cout << "  _";
    }
  }
  cout << endl;
}
