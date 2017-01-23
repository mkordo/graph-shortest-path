#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cstdint>    /* For uint32_t */
#include <string>
#include "../queue/queue.h"
#include "../graph/graph.h"
#include "../parser/writer.h"
#include "../parser/parser.h"
#include "job.h"
#include "threadPool.h"

class Scheduler
{
  public:
  	ThreadPool *pool;
  	JobTools *info;
    int workers;
    int workersTmp;

    Scheduler(Graph<Node> *graphOut, Graph<Node> *graphIn, int workers_ = 2);
    ~Scheduler();

    void Assign(Job);
};

void* jobExecute(void *);

#endif
