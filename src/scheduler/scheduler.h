#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <cstdint>    /* For uint32_t */
#include <string>
#include "../queue/queue.h"
#include "../graph/graph.h"
#include "../parser/parser.h"
#include "threadPool.h"

class JobTools
{
  public:
    Queue<Job> jobQueue;
    Queue<int> results;
    pthread_mutex_t jobQueueMutex;
    pthread_mutex_t resultsMutex;

    JobTools();
    ~JobTools();

    void print();
};

class Scheduler
{
  public:
  	ThreadPool *pool;
  	JobTools *info;

    Scheduler();
    ~Scheduler();

    void Assign(Job);
};

void* jobExecute(void *);

#endif
