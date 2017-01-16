#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include "job.h"

class ThreadPool
{
  public:
    int workers;
    pthread_t *pool;

    ThreadPool(void *, int workers_ = 2);
    ~ThreadPool();
};



#endif
