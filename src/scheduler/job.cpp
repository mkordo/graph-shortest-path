#include <iostream>
#include "job.h"

Job::Job()
{

}

Job::~Job()
{
  
}

int Job::execute()
{
	return 0;
}



std::ostream &operator<<(std::ostream &os, Job const &m) { 
    return os << "Job Print";
}