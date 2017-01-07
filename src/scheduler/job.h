#ifndef JOB_H
#define JOB_H

#include <cstdint>    /* For uint32_t */
#include <iostream>

class Job
{
  public:
    int la;
    
    Job();
    ~Job();

};

std::ostream &operator<<(std::ostream &, Job const &);

#endif
