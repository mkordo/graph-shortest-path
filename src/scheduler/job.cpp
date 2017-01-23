#include <string>
#include "job.h"

using namespace std;

Job::Job(uint32_t id_, int type_, uint32_t me_, uint32_t neighbor_)
{
	id = id_;
	type = type_;
	me = me_;
	neighbor = neighbor_;
}

Job::~Job()
{
  
}

int Job::execute()
{
	return 0;
}

void Job::print()
{
	if(type==GUST) { cout << "F\n"; return; }
	else if(type == INSERTION) cout << "A ";
	else if(type == QUESTION) cout << "Q ";

	cout << me << " " << neighbor << endl;
}


std::ostream &operator<<(std::ostream &os, Job const &theJob) { 
	string out;
	if(theJob.type==GUST) {
		out.assign("F");
		return os << out << "\n";
	}
	else if(theJob.type == INSERTION) out.assign("A ");
	else if(theJob.type == QUESTION) out.assign("Q ");

    return os << out << theJob.me << " " << theJob.neighbor << "\n";
}

////////////////

JobTools::JobTools()
{
	jobQueueMutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	resultsMutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	
	pthread_mutex_init(jobQueueMutex, NULL);
	pthread_mutex_init(resultsMutex, NULL);

	jobQueue = new Queue<Job>;
    //results = new Queue<int>;
}

JobTools::~JobTools()
{
	pthread_mutex_destroy(jobQueueMutex);
	pthread_mutex_destroy(resultsMutex);

	free(jobQueueMutex);
	free(resultsMutex);

	delete jobQueue;
	//delete results;

	delete search;
}

void JobTools::print()
{
	cout << "Printing mutexes: " << jobQueueMutex << endl;
}

void JobTools::SearchInit(Graph<Node> *graphOut, Graph<Node> *graphIn)
{
	search = new Search(graphOut, graphIn);
}

void JobTools::ResultsInit(Queue<int> *results_)
{
	results = results_;
}

void JobTools::Assign(Job newJob)
{
	//pthread_mutex_lock(jobQueueMutex);
	jobQueue->push(newJob);
	//pthread_mutex_unlock(jobQueueMutex);
}

void JobTools::LockQueue()
{
	pthread_mutex_lock(jobQueueMutex);
}

void JobTools::UnlockQueue()
{
	pthread_mutex_unlock(jobQueueMutex);
}