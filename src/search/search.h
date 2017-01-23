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

    Graph<Node> *graphOut;
    Graph<Node> *graphIn;

    Search(Graph<Node>*, Graph<Node>*);
    ~Search();

    int ShortestPath(uint32_t, uint32_t);

  private:
    void init(uint32_t, uint32_t);

    bool bfs(Graph<Node>*, Queue<uint32_t>&, bool*, bool*);
};

#endif
