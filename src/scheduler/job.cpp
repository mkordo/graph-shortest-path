#include <string>
#include "job.h"

using namespace std;

Job::Job(uint32_t id_, int type_, uint32_t me_, uint32_t neighbor_, int version_)
{
	id = id_;
	type = type_;
	me = me_;
	neighbor = neighbor_;
	version = version_;
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

	workerCondition = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
	if(workerCondition==NULL) {
    	std::cerr << "Scheduler Constructor : Malloc Error\n" ;
    }
    pthread_cond_init (workerCondition , NULL);

	jobQueue = new Queue<Job>;
    resultQueue = new Queue<int>;
}

WorkerTools::~WorkerTools()
{
	//cout << "Job queue size: " << jobQueue->count() << "\n";

	pthread_mutex_destroy(workerMutex);
	free(workerMutex);

	pthread_cond_destroy (workerCondition);
	free(workerCondition);

	delete jobQueue;
	delete resultQueue;

	delete search;
}

void WorkerTools::SearchInit(Graph<Node> *graphOut, Graph<Node> *graphIn)
{
	search = new Search(graphOut, graphIn);
}

void WorkerTools::WorkerInit(int* totalWorkers_, int* jobsFinished_, pthread_mutex_t* schedulerMutex_, pthread_cond_t* schedulerCondition_)
{
    totalWorkers = totalWorkers_;
    jobsFinished = jobsFinished_;

    schedulerMutex = schedulerMutex_;
    schedulerCondition = schedulerCondition_;
}

void WorkerTools::Assign(Job newJob)
{
	jobQueue->push(newJob);
}

void WorkerTools::Lock()
{
	pthread_mutex_lock(workerMutex);
}

void WorkerTools::Unlock()
{
	pthread_mutex_unlock(workerMutex);
}

void WorkerTools::Wait()
{
	pthread_cond_wait ( workerCondition, workerMutex );
}

void WorkerTools::Wake()
{
	pthread_cond_signal(workerCondition);
}

void WorkerTools::LockScheduler()
{
	pthread_mutex_lock(schedulerMutex);
}

void WorkerTools::UnlockScheduler()
{
	pthread_mutex_unlock(schedulerMutex);
}

void WorkerTools::WorkFinished()
{
	(*jobsFinished)++;
}

bool WorkerTools::AllWorkersFinished()
{
	if( (*jobsFinished) != (*totalWorkers) )
		return false;
	else
		return true;
}

void WorkerTools::WakeScheduler()
{
	pthread_cond_signal(schedulerCondition);
}

bool WorkerTools::GetJob(Job& newJob)
{
	return jobQueue->pop(newJob);
}

bool WorkerTools::GetResult(int& popped)
{
	return resultQueue->pop(popped);
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
