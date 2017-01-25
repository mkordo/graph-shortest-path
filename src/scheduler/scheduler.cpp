#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>

#include "scheduler.h"

using namespace std;

Scheduler::Scheduler(Graph<Node> *graphOut, Graph<Node> *graphIn, int workers_)
{
	int i;
	workers = workers_;
    workersTmp = 0;
    id=0;

    ////////////

    jobsFinished = 0;
    workerCondition = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
    schedulerMutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    schedulerCondition = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
    if(workerCondition==NULL || schedulerMutex==NULL || schedulerCondition==NULL) {
    	std::cerr << "Scheduler Constructor : Malloc Error\n" ;
    }

    pthread_mutex_init (schedulerMutex, NULL);
    pthread_cond_init (workerCondition , NULL);
    pthread_cond_init (schedulerCondition , NULL);

    ////////////

	info = new WorkerTools [workers];
	for(i=0; i<workers; i++) {
		info[i].SearchInit(graphOut, graphIn);
		info[i].WorkerInit(&workers, &jobsFinished, workerCondition, schedulerMutex, schedulerCondition);

		//info[i].Print();
	}

	pool = new ThreadPool ((void*) info, workers);
}

Scheduler::~Scheduler()
{
	//info->jobQueue.print();
	cout << "Job queue size: " << info->jobQueue->count() << "\n";
	delete pool;
	delete [] info;

	pthread_mutex_destroy(schedulerMutex);
	free(schedulerMutex);

	pthread_cond_destroy (workerCondition);
	free(workerCondition);

	pthread_cond_destroy (schedulerCondition);
	free(schedulerCondition);
}

void Scheduler::Assign(Job newJob)
{
	newJob.id = id++;
	info[workersTmp++].Assign(newJob);
	if(workersTmp == workers)
		workersTmp = 0;
}

void Scheduler::LockAll()
{
	int i;
	for(i=0; i<workers; i++) {
		info[i].LockWorker();
	}
}

void Scheduler::UnlockAll()
{
	int i;
	for(i=0; i<workers; i++) {
		info[i].UnlockWorker();
	}
}

void Scheduler::Init()
{
	int i;
	id = 0;
	workersTmp = 0;
	for(i=0; i<workers; i++) {
		info[0].jobQueue->init();
		info[0].results->init();
	}

}



// Main mutex
// Job Queue
// Result Queue
void* jobExecute(void* info_)
{
	WorkerTools *info = (WorkerTools *) info_;

/*
	//pthread_mutex_lock(info[0].schedulerMutex);
		int tmp=rand()%10 + 1;
		cout << "Sleeping for " << tmp << " ms\n\n";
		usleep(tmp);

		info[0].Print();
	//pthread_mutex_unlock(info[0].schedulerMutex);
*/
	fflush(stdout);
	return NULL;
}
