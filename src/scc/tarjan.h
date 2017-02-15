#ifndef TARJAN_H
#define TARJAN_H

#include "../graph/graph.h"
#include "../queue/queue.h"
#include "../stack/stack.h"
#include "scc.h"

class meTARZANyouJANE
{
  public:
  	bool *onStack;
  	bool *defined;
  	bool *marked;
  	uint32_t *index;
  	uint32_t *lowlink;
  	Stack<uint32_t> SCC_stack;
  	Stack<uint32_t> Parent_stack;
  	Stack<uint32_t> Children_stack;
  	
  	
		meTARZANyouJANE(uint32_t);
		void saveSpace();
		int strongConnect(Graph<Node>&, uint32_t, uint32_t &, scc<Component> &);
		int tarjan(Graph<Node>& graph, scc<Component> &);
		
		
		~meTARZANyouJANE();
};





uint32_t min(uint32_t,uint32_t);
uint32_t max(uint32_t a,uint32_t b);



#endif
