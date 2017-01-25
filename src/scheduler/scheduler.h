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
  	WorkerTools *info;

    uint32_t id;
    int workers;
    int workersTmp;
    int jobsFinished;

    pthread_cond_t *workerCondition;
    pthread_mutex_t *schedulerMutex;
    pthread_cond_t *schedulerCondition;

    Scheduler(Graph<Node> *graphOut, Graph<Node> *graphIn, int workers_ = 2);
    ~Scheduler();

    void Assign(Job);
    void Execute();
    void Init();
    void LockAll();
    void UnlockAll();
};

void* jobExecute(void *);

#endif