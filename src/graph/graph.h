#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "hash.h"

template <class T>
class Graph
{
  public:
    uint32_t version;
    uint32_t size;
    uint32_t last;
    T* buffer;

    Graph(uint32_t size_ = 100);
    ~Graph();

    bool insert(uint32_t, uint32_t);
    void resize(uint32_t);
    void print();
    bool validNode(uint32_t);
    bool emptyNode(uint32_t);
    bool inBounds(uint32_t);
    uint32_t getNodeSize(uint32_t);
    uint32_t* getNodeNeighbor(uint32_t);
    int* getNodeVersion(uint32_t);
    void printNode(uint32_t);
    void changeVersion();

  private:
    void expand(uint32_t);
};

#endif
