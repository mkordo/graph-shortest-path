#include <iostream>
#include "job.h"

Job::Job()
{

}

Job::~Job()
{
  
}

std::ostream &operator<<(std::ostream &os, Job const &m) { 
    return os << m.la;
}