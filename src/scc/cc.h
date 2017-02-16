#ifndef CC_H
#define CC_H

#include <cstdint>    /* For uint32_t */
#include "../queue/queue.h"
#include "../graph/graph.h"
using namespace std;
class cc{
	public: 
		
		cc(uint32_t size_ = 128);
		~cc();
		
		uint32_t *belongs;
		uint32_t *marked;
		uint32_t size;
		uint32_t count;
		uint32_t index;
		uint32_t *UpdateIndex[2];
		uint32_t updateIndexCount;
		uint32_t updateIndexSize;
		uint32_t metric;
		
		void assign(uint32_t source, uint32_t target, Graph<Node>& graphOut, Graph<Node>& graphIn);
		void expand(uint32_t newC);
		void print();
		void run(Graph<Node>&,Graph<Node>&);
		
		void bfs_dual(Graph<Node>& graphIn, Graph<Node>& graphOut, Queue<uint32_t>& myQueue);
		void init(uint32_t size_);
};


#endif
