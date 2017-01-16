#include <iostream>
#include <stdlib.h>
#include "threadPool.h"
#include "scheduler.h"

using namespace std;

ThreadPool::ThreadPool(void *arg, int workers_)
{
	int i, errnum;

	workers = workers_;
	pool = (pthread_t *) malloc(workers * sizeof(pthread_t));
	if(pool == NULL) std::cerr << "Thread Pool Constructor : Malloc Error\n" ;

	for(i=0; i<workers; i++) {
		errnum = pthread_create(&pool[i], NULL, jobExecute, arg);
		if(errnum) { std::cerr << "Thread Pool Constructor : pthread_create error : " << errnum << "\n"; }
		cout << "Created thread with id: " << pool[i] << "\n";
	}
}

ThreadPool::~ThreadPool()
{
	int i, errnum;
	void *exitStatus;

	for(i=0; i<workers; i++) {
		cout << "Destroying thread with id: " << pool[i] << "\n";
		errnum = pthread_join(pool[i], &exitStatus);
		if(errnum) {
			std::cerr << "Thread Pool Destructor : In thread : " << pool[i] << " : Exit status : " << exitStatus << "\n";
			std::cerr << "Thread Pool Destructor : pthread_join error number : " << errnum;
			if(errnum==EDEADLK) std::cerr << " (EDEADLK)\n";
			else if(errnum==EINVAL) std::cerr << " (EINVAL)\n";
			else if(errnum==ESRCH) std::cerr << " (ESRCH)\n";
			else std::cerr << " (WTF?)\n";
		}
	}

	free(pool);
}

