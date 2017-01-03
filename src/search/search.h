#ifndef SEARCH_H
#define SEARCH_H

#include <cstdint>    /* For uint32_t */
//#include "../queue/queue.h"

class Search
{
  public:
    uint32_t size;
    bool *visited;

    Search();
    ~Search();

};

#endif
