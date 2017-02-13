#include "../graph/graph.h"
#include "../parser/parser.h"
#include "../parser/writer.h"
#include "../queue/queue.h"
#include "../scc/scc.h"
#include "../search/search.h"
#include "../statistics/statistics.h"
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
  	uint32_t sizePanos;
  	
  	
		meTARZANyouJANE(uint32_t);
		int strongConnect(Graph<Node>&, uint32_t, uint32_t &, scc<Component> &);
		int tarjan(Graph<Node>& graph, scc<Component> &);
		
		
		~meTARZANyouJANE();
};





uint32_t min(uint32_t,uint32_t);
uint32_t max(uint32_t a,uint32_t b);
