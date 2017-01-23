#include <iostream>
#include <stdlib.h>

#include "scheduler.h"

using namespace std;

Scheduler::Scheduler(Graph<Node> *graphOut, Graph<Node> *graphIn, int workers_)
{
	int i;
	workers = workers_;
    workersTmp = 0;

	info = new JobTools [workers];
	for(i=0; i<workers; i++) 
		info[i].SearchInit(graphOut, graphIn);

	//pthread_mutex_lock(info->jobQueueMutex);	// Ensure that no thread will read from Queue before master is ready
	pool = new ThreadPool ((void*) info, workers);
}

Scheduler::~Scheduler()
{
	//info->jobQueue.print();
	cout << "Job queue size: " << info->jobQueue->count() << "\n";
	delete pool;
	delete [] info;
}

void Scheduler::Assign(Job newJob)
{
	info[0].Assign(newJob);
}





// Main mutex
// Job Queue
// Result Queue
void* jobExecute(void* info_)
{
	JobTools *info = (JobTools *) info_;

	info[0].print();



	fflush(stdout);
	return NULL;
}
/*
 	pthread_mutex_lock(&mutex);
    pthread_create(&thread, NULL, fooAPI, NULL);
    sleep(1);
    pthread_mutex_unlock(&mutex);
*/