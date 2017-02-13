#ifndef COMP_H
#define COMP_H

#include <cstdint>    /* For uint32_t */
#include "../stack/stack.h"
#include "../stack/stack.h"

//int tarjan(Graph<Node>& graphOut){
//	Stack<uint32_t> dfs;
//}

class Component
{
  public:
	uint32_t size;
    uint32_t id; //current component id
    uint32_t count; //number of nodes in component
    uint32_t *included; //ids of included nodes

    Component(uint32_t size_ = 103);
    Component(uint32_t size_, uint32_t *);
    ~Component();

    bool insert(uint32_t);
    void print();
    void init(uint32_t,uint32_t size_ = 103);
    uint32_t getSize();

  private:
    void expand();
};


#endif
