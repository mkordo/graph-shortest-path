#ifndef JOB_H
#define JOB_H

#include <cstdint>    /* For uint32_t */
#include <iostream>
#include "../parser/parser.h"

class Job
{
  public:
  	uint32_t id;
  	int type;
  	uint32_t me;
  	uint32_t neighbor;

    Job(uint32_t id_=0, int type_=0, uint32_t me_=0, uint32_t neighbor_=0);
    ~Job();

    int execute();
    void print();

};

std::ostream &operator<<(std::ostream &, Job const &);

#endif
