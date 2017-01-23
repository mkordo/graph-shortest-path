#ifndef STATISTICS_H
#define STATISTICS_H

#include <cstdint>    /* For uint32_t */
#include <ctime>

class Statistics
{
  public:
    bool pleasePrint;

    clock_t start;
    clock_t created;
    clock_t executed;
    double elapsedTime;

    uint32_t sizeGraphOut;
    uint32_t sizeGraphIn;
    uint32_t sizeGraphDupl;

    uint32_t sizeGraphUsedOut;
    uint32_t sizeGraphUsedIn;
    uint32_t sizeGraphUsedDupl;

    uint32_t duplicates;
    uint32_t duplicatesQA;
    uint32_t insertions;
    uint32_t queries;
    uint32_t gusts;

    Statistics(bool pleasePrint_ = true);
    ~Statistics();

    void Start();
    void CreatedGraphs();
    void ExecutedQueries();
    void finalSizes(uint32_t, uint32_t, uint32_t);
    void finalUsedSizes(uint32_t, uint32_t, uint32_t);
    void Print();
    void Insertion();
    void Query();
    void Gust();
    uint32_t getQueries();
};

#endif
