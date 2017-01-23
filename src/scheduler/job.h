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

    Job(uint32_t id_=0, int type_=0, uint32_t me_=0, uint32_t neighbor_=0);
    ~Job();

    int execute();
    void print();

};

std::ostream &operator<<(std::ostream &, Job const &);

class JobTools
{
  public:
    Queue<Job> *jobQueue;
    Queue<int> *results;
    Search *search;
    pthread_mutex_t *jobQueueMutex;
    pthread_mutex_t *resultsMutex;

    JobTools();
    ~JobTools();

    void SearchInit(Graph<Node> *graphOut, Graph<Node> *graphIn);
    void ResultsInit(Queue<int> *);
    void Assign(Job);
    void LockQueue();
    void UnlockQueue();
    void print();
};

#endif
