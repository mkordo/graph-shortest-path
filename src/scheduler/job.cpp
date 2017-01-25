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

WorkerTools::WorkerTools()
{
	workerMutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(workerMutex, NULL);

	jobQueue = new Queue<Job>;
    results = new Queue<int>;
}

WorkerTools::~WorkerTools()
{
	pthread_mutex_destroy(workerMutex);
	free(workerMutex);

	delete jobQueue;
	delete results;

	delete search;
}

void WorkerTools::SearchInit(Graph<Node> *graphOut, Graph<Node> *graphIn)
{
	search = new Search(graphOut, graphIn);
}

void WorkerTools::WorkerInit(int* totalWorkers_, int* jobsFinished_, pthread_cond_t* workerCondition_, pthread_mutex_t* schedulerMutex_, pthread_cond_t* schedulerCondition_)
{
    totalWorkers = totalWorkers_;
    jobsFinished = jobsFinished_;

    workerCondition = workerCondition_;

    schedulerMutex = schedulerMutex_;
    schedulerCondition = schedulerCondition_;
}

void WorkerTools::Assign(Job newJob)
{
	jobQueue->push(newJob);
}

void WorkerTools::LockWorker()
{
	pthread_mutex_lock(workerMutex);
}

void WorkerTools::UnlockWorker()
{
	pthread_mutex_unlock(workerMutex);
}

void WorkerTools::Print()
{
	cout << "\n";
	cout << "Total Workers : " << *totalWorkers << "\n";
	cout << "Jobs Finished : " << *jobsFinished << "\n";
	cout << "Print Mutexes : \n";
	cout << "  My Mutex : " << workerMutex << "\n";
	cout << "  Scheduler Mutex : " << schedulerMutex << "\n";
	cout << "Print Conditions :  \n";
	cout << "  Workers\' Condition : " << workerCondition << "\n";
	cout << "  Scheduler\'s Condition : " << schedulerCondition << "\n\n";
}
