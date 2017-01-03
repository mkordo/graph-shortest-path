#ifndef STATISTICS_H
#define STATISTICS_H

#include <cstdint>    /* For uint32_t */
#include <ctime>

class Statistics
{
    clock_t start;
    clock_t created;
    clock_t executed;
    double elapsedTime;

    uint32_t sizeGraphOut;
    uint32_t sizeGraphIn;

    uint32_t duplicates;
    uint32_t insertions;
    uint32_t queries;

  public:

    Statistics();
    ~Statistics();

    void Start();
    void CreatedGraphs();
    void ExecutedQueries();
    void Print();
};

#endif
