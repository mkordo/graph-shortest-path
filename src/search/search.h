#ifndef SEARCH_H
#define SEARCH_H

#include <cstdint>    /* For uint32_t */
#include "../queue/queue.h"
#include "../graph/graph.h"
#include "../scc/scc.h"

class Search
{
  public:
    //int stepsFront;
    //int stepsBack;
    uint32_t steps;
    uint32_t size;
    bool *visitedIn;
    bool *visitedOut;

    Queue<uint32_t> frontSearch;
    Queue<uint32_t> backSearch;

    Search();
    ~Search();

    int ShortestPath(Graph<Node>&, Graph<Node>&, uint32_t, uint32_t);
    int ShortestPath(Graph<Node>&, Graph<Node>&, uint32_t, uint32_t, scc<Component>&);

  private:
    void init(uint32_t, uint32_t);

    bool bfs(Graph<Node>&, Queue<uint32_t>&, bool*, bool*);
    bool bfs(Graph<Node>&, Queue<uint32_t>&, bool*, bool*,uint32_t,uint32_t*&);
};

#endif
