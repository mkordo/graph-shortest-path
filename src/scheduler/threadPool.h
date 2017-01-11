#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include "job.h"

class ThreadPool
{
  public:
  	int max;
    int workers;
    pthread_t *pool;

    ThreadPool(int max_ = 2);
    ~ThreadPool();
};

void* jobExecute(void *);

#endif
