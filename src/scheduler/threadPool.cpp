#include <iostream>
#include <stdlib.h>
#include "threadPool.h"

using namespace std;

ThreadPool::ThreadPool(int max_)
{
	int i, errnum;

	max = max_;
	workers = 0;
	pool = (pthread_t *) malloc(max * sizeof(pthread_t));
	if(pool == NULL) std::cerr << "Thread Pool Constructor : Malloc Error\n" ;

	for(i=0; i<max; i++) {
		errnum = pthread_create(&pool[i], NULL, jobExecute, NULL);
		if(errnum) { std::cerr << "Thread Pool Constructor : pthread_create error : " << errnum << "\n"; }
	}

}

ThreadPool::~ThreadPool()
{
	int i, errnum, status;

	for(i=0; i<max; i++) {
		errnum = pthread_join(pool[i], (void **) &status);
		if(errnum) { std::cerr << "Thread Pool Destructor : pthread_join error : " << errnum << "\n"; }
	}

	free(pool);
}

void* jobExecute(void* task)
{
	cout << "Job Executed\n";
	return 0;
}
