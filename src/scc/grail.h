#ifndef GRAIL_H
#define GRAIL_H

#include "../scc/tarjan.h"


class grail{
	 public:
			uint32_t *minRank;
			uint32_t *rank;
			uint32_t *minSoFar;
			bool *marked;
			uint32_t size;
			
			Stack<uint32_t> iteration;
			Stack<uint32_t> child;
			
			grail(uint32_t);
			~grail();
			
			int build(Graph<Node>& );
			int build(Graph<Node>&, Graph<Node>& );
			
			int postOrder(Graph<Node>& graph, Graph<Node>& graph2, uint32_t, uint32_t&);
			int postOrder(Graph<Node>& graph, uint32_t, uint32_t&);
			
			
			//bool isReachableGrailIndex(GrailIndex* index, uint32_t source_node, uint32_t target_node);
};

int HyperGraph(Graph<Node>&, Graph<HashNode>&,Graph<Node>& graph, scc<Component>& SCC);

//GrailIndex* buildGrailIndex(NodeIndex* graph, SCC* components);
//GRAIL_ANSWER isReachableGrailIndex(GrailIndex* index, uint32_t source_node,
//uint32_t target_node);
//OK_SUCCESS destroyGrailIndex(GrailIndex* index);


#endif
