#ifndef JOB_H
#define JOB_H

#include <cstdint>    /* For uint32_t */
#include <iostream>
#include <pthread.h>
#include "../parser/parser.h"
#include "../queue/queue.h"
#include "../graph/graph.h"
#include "../search/search.h"

class Job
{
  public:
  	uint32_t id;
  	int type;
  	uint32_t me;
  	uint32_t neighbor;
    int version;

    Job(uint32_t id_=0, int type_=0, uint32_t me_=0, uint32_t neighbor_=0, int version_=0);
    ~Job();

    int execute();
    void print();

};

std::ostream &operator<<(std::ostream &, Job const &);

class WorkerTools
{
  public:
    Queue<Job> *jobQueue;
    Queue<int> *resultQueue;
    Search *search;

    int *jobsFinished;
    int *totalWorkers;

    pthread_mutex_t *workerMutex;
    pthread_cond_t *workerCondition;

    pthread_mutex_t *schedulerMutex;
    pthread_cond_t *schedulerCondition;

    WorkerTools();
    ~WorkerTools();

    void WorkerInit(int*, int*, pthread_mutex_t*, pthread_cond_t*);
    void SearchInit(Graph<Node> *graphOut, Graph<Node> *graphIn);
    void Print();
    void Assign(Job);
    void Lock();
    void Unlock();
    void LockScheduler();
	void UnlockScheduler();
    void Wait();
    void Wake();
    void WorkFinished();
    bool AllWorkersFinished();
    void WakeScheduler();
    bool GetJob(Job&);
    bool GetResult(int&);
};

#endif
