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