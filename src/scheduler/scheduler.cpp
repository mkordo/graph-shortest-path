#include <iostream>
#include <stdlib.h>

#include "scheduler.h"

using namespace std;

Scheduler::Scheduler(Graph<Node> *graphOut, Graph<Node> *graphIn, int workers_)
{
	int i;
	workers = workers_;
    workersTmp = 0;
    id=0;
    results = new Queue<int>;

	info = new JobTools [workers];
	for(i=0; i<workers; i++) {
		info[i].SearchInit(graphOut, graphIn);
		info[i].ResultsInit(results);
	}

	//Scheduler::LockAll();		// Ensure that no thread will read from Queue before master is ready
	pool = new ThreadPool ((void*) info, workers);
}

Scheduler::~Scheduler()
{
	//info->jobQueue.print();
	cout << "Job queue size: " << info->jobQueue->count() << "\n";
	delete pool;
	delete [] info;
	delete results;
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
		info[i].LockQueue();
	}
}

void Scheduler::UnlockAll()
{
	int i;
	for(i=0; i<workers; i++) {
		info[i].UnlockQueue();
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
	JobTools *info = (JobTools *) info_;

	//info[0].LockQueue();



	fflush(stdout);
	return NULL;
}
