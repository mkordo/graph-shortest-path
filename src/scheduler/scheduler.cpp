#include <iostream>
#include <stdlib.h>

#include "job.h"
#include "scheduler.h"

using namespace std;

Scheduler::Scheduler()
{
	info = new JobTools;
	pool = new ThreadPool (info);
}

Scheduler::~Scheduler()
{
	//info->jobQueue.print();
	cout << "Job queue size: " << info->jobQueue.count() << "\n";
	delete pool;
	delete info;
}

void Scheduler::Assign(Job newJob)
{
	//cout << "Wtf? ";
	info->jobQueue.push(newJob);
}

////////////////

JobTools::JobTools()
{
	jobQueueMutex = PTHREAD_MUTEX_INITIALIZER;
    resultsMutex = PTHREAD_MUTEX_INITIALIZER;
}

JobTools::~JobTools()
{

}

void JobTools::print()
{

}



// Main mutex
// Job Queue
// Result Queue
void* jobExecute(void* info_)
{
	JobTools *info = (JobTools *) info_;




	fflush(stdout);
	return NULL;
}
/*
 	pthread_mutex_lock(&mutex);
    pthread_create(&thread, NULL, fooAPI, NULL);
    sleep(1);
    pthread_mutex_unlock(&mutex);
*/