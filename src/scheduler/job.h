#ifndef JOB_H
#define JOB_H

#include <cstdint>    /* For uint32_t */
#include <iostream>

class Job
{
  public:
    int result;
    
    Job();
    ~Job();

    int execute();

};

std::ostream &operator<<(std::ostream &, Job const &);

#endif
