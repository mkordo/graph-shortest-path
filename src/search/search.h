#ifndef SEARCH_H
#define SEARCH_H

#include <cstdint>    /* For uint32_t */
#include "../queue/queue.h"
#include "../graph/graph.h"
#include "../scc/grail.h"

class Search
{
  public:
    uint32_t steps;
    uint32_t size;
    int currentVersion;
    bool *visitedIn;
    bool *visitedOut;

    Queue<uint32_t> frontSearch;
    Queue<uint32_t> backSearch;

    Graph<Node> *graphOut;
    Graph<Node> *graphIn;
    
    scc<Component>* SCC; 
    grail *G;
    
    Search(Graph<Node>*, Graph<Node>*, scc<Component>* SCC, grail *G);
    ~Search();

    int ShortestPath(uint32_t, uint32_t, int);
    int ShortestPath(uint32_t, uint32_t, int, scc<Component>*);

  private:
    void init(uint32_t, uint32_t, int);

    bool bfs(Graph<Node>*, Queue<uint32_t>&, bool*, bool*);
    bool bfs(Graph<Node>*, Queue<uint32_t>&, bool*, bool*,uint32_t,uint32_t*&);
};

#endif
