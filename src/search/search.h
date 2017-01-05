#ifndef SEARCH_H
#define SEARCH_H

#include <cstdint>    /* For uint32_t */
#include "../queue/queue.h"
#include "../graph/graph.h"

class Search
{
  public:
    int steps;
    uint32_t size;
    bool *visitedIn;
    bool *visitedOut;
    bool found;

    Queue<uint32_t> frontSearch;
    Queue<uint32_t> backSearch;

    Search();
    ~Search();

    int ShortestPath(Graph<Node>&, Graph<Node>&, uint32_t, uint32_t);

  private:
    void init(uint32_t, uint32_t);

    int bfsFront();
    int bfsBack();
};

#endif
