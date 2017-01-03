#ifndef SEARCH_H
#define SEARCH_H

#include <cstdint>    /* For uint32_t */
#include "../queue/queue.h"
#include "../graph/graph.h"

class Search
{
  public:
    uint32_t steps;
    uint32_t size;
    bool *visitedIn;
    bool *visitedOut;

    Queue<uint32_t> frontSearch;
    Queue<uint32_t> backSearch;

    Search();
    ~Search();

    uint32_t ShortestPath(Graph<HashNode>&, Graph<Node>&, uint32_t, uint32_t);

  private:
    void init(uint32_t, uint32_t);
    uint32_t bfs();
};

#endif
