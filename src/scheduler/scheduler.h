#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cstdint>    /* For uint32_t */
#include "../queue/queue.h"
#include "../graph/graph.h"
#include "../parser/writer.h"
#include "threadPool.h"

template <class T>
class Scheduler
{
  public:
    Queue<T> results;


    Scheduler();
    ~Scheduler();
};

#endif
