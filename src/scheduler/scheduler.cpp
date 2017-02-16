#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <unistd.h>

#include "scheduler.h"

using namespace std;

Scheduler::Scheduler(Graph<Node> *graphOut, Graph<Node> *graphIn, scc<Component>* SCC, grail *G, int workers_)
{
	int i;
	workers = workers_;
    workersTmp = 0;
    id=0;

    ////////////

    jobsFinished = 0;    
    schedulerMutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    schedulerCondition = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
    if(schedulerMutex==NULL || schedulerCondition==NULL) {
    	std::cerr << "Scheduler Constructor : Malloc Error\n" ;
    }

    pthread_mutex_init (schedulerMutex, NULL);
    pthread_cond_init (schedulerCondition , NULL);

    ////////////

    Scheduler::Lock();

	info = new WorkerTools [workers];
	for(i=0; i<workers; i++) {
		//cout<<"thread "<<i<<"initializing \n";
		info[i].SearchInit(graphOut, graphIn, SCC, G);
		//cout<<"OK\n";
		info[i].WorkerInit(&workers, &jobsFinished, schedulerMutex, schedulerCondition);
		//cout<<"OK\n";
		//info[i].Print();
	}

	Scheduler::Init();
	pool = new ThreadPool ((void*) info, workers);

	// Threads will wake the Scheduler when all of them are initialised
	// That way we ensure that none of them will miss the signal for work by accident
	Scheduler::Wait();
	Scheduler::Init();
	cout << "\nAll threads initialised\n\nExecuting Queries...\n";
}

Scheduler::~Scheduler()
{
	Scheduler::Unlock();

	delete pool;
	delete [] info;

	pthread_mutex_destroy(schedulerMutex);
	free(schedulerMutex);

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

void Scheduler::LockWorkers()
{
	int i;
	for(i=0; i<workers; i++) {
		info[i].Lock();
	}
}

void Scheduler::UnlockWorkers()
{
	int i;
	for(i=0; i<workers; i++) {
		info[i].Unlock();
	}
}

void Scheduler::Lock()
{
	pthread_mutex_lock(schedulerMutex);
}

void Scheduler::Unlock()
{
	pthread_mutex_unlock(schedulerMutex);
}

void Scheduler::Wait()
{
	pthread_cond_wait ( schedulerCondition, schedulerMutex );
}

void Scheduler::WakeAll()
{
	int i;
	for(i=0; i<workers; i++) {
		info[i].Wake();
	}
}

void Scheduler::StopAll()
{
	Job newJob;
	newJob.type = STOP;
	int i;
	for(i=0; i<workers; i++) {
		info[i].Assign(newJob);
	}	
}

void Scheduler::Init()
{
	int i;
	id = 0;
	workersTmp = 0;
	jobsFinished = 0;
	for(i=0; i<workers; i++) {
		info[i].jobQueue->init();
		info[i].resultQueue->init();
	}

}

void Scheduler::WriteResults(Writer& output)
{
	int i;
	int result;
	bool empty=false;
	while(empty==false) {
		for(i=0; i<workers; i++) {
			if(info[i].GetResult(result) == true) {
				output.writeInt(result);
			}
			else empty=true;
		}
	}
}



// Main mutex
// Job Queue
// Result Queue
void* jobExecute(void* info_)
{
	WorkerTools *info = (WorkerTools *) info_;
	Job newJob;
	bool endLoop;
	int searchResult;

	info[0].Lock();

	info[0].LockScheduler();
		//info[0].Print();
		//fflush(stdout);

		info[0].WorkFinished();
		if(info[0].AllWorkersFinished() == true) {
			info[0].WakeScheduler();
		}
	info[0].UnlockScheduler();

	endLoop=false;
	while(endLoop==false) {
		info[0].Wait();

		if(info[0].GetJob(newJob) != true) 
			cerr << "Thread: Job Execute: Received empty job list\n";

		if(newJob.type == STOP) {
			endLoop=true;
			break;
		}

		do {
			searchResult = info[0].search->ShortestPath(newJob.me, newJob.neighbor, newJob.version);
			info[0].resultQueue->push(searchResult);

		} while( info[0].GetJob(newJob) == true );

		info[0].LockScheduler();
			info[0].WorkFinished();
			if(info[0].AllWorkersFinished() == true) {
				info[0].WakeScheduler();
			}
		info[0].UnlockScheduler();	
	}

	info[0].Unlock();
	//cout << "Thread Exiting...\n";
	return NULL;
}

Scheduler::Scheduler(Graph<Node> *graphOut, Graph<Node> *graphIn, cc *CC, int workers_)
{
	int i;
	workers = workers_;
    workersTmp = 0;
    id=0;

    ////////////

    jobsFinished = 0;    
    schedulerMutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    schedulerCondition = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
    if(schedulerMutex==NULL || schedulerCondition==NULL) {
    	std::cerr << "Scheduler Constructor : Malloc Error\n" ;
    }

    pthread_mutex_init (schedulerMutex, NULL);
    pthread_cond_init (schedulerCondition , NULL);

    ////////////

    Scheduler::Lock();

	info = new WorkerTools [workers];
	for(i=0; i<workers; i++) {
		//cout<<"thread "<<i<<"initializing \n";
		info[i].SearchInit(graphOut, graphIn, CC);
		//cout<<"OK\n";
		info[i].WorkerInit(&workers, &jobsFinished, schedulerMutex, schedulerCondition);
		//cout<<"OK\n";
		//info[i].Print();
	}

	Scheduler::Init();
	pool = new ThreadPool ((void*) info, workers);

	// Threads will wake the Scheduler when all of them are initialised
	// That way we ensure that none of them will miss the signal for work by accident
	Scheduler::Wait();
	Scheduler::Init();
	cout << "\nAll threads initialised\n\nExecuting Queries...\n";
}
