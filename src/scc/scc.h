#ifndef SCC_H
#define SCC_H

#include "comp.h"

template <class T>
class scc
{
  public:
    uint32_t version;
    uint32_t size; //size of entire belongs with empty nodes
    uint32_t count; //realistic # of scc
    uint32_t *belongs; //inverted index
    uint32_t bs;
    T* components; // Components index - a vector which stores the components information

    scc(uint32_t size_ = 128);
    ~scc();
    
    void init(uint32_t size);

    bool insert( uint32_t);
    void resize(uint32_t);
    void print();
    void printBelong();
    bool validComponent(uint32_t);
    bool emptyComponent(uint32_t);
    bool inBounds(uint32_t);
    uint32_t getComponentSize(uint32_t);
    uint32_t* getComponentNodes(uint32_t);
    void printComponent(uint32_t);
    
    int findNodeSCC( uint32_t nodeId);

  private:
    void expand(uint32_t);
};

#endif
