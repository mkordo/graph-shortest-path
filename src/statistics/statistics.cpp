#include <iostream>

#include "statistics.h"

using namespace std;

Statistics::Statistics() {
    sizeGraphOut = 0;
    sizeGraphIn = 0;

    duplicates = 0;
    duplicatesQA = 0;
    insertions = 0;
    queries = 0;

    sizeGraphOut = 0;
    sizeGraphIn = 0;
    sizeGraphDupl = 0;

    sizeGraphUsedOut = 0;
    sizeGraphUsedIn = 0;
    sizeGraphUsedDupl = 0;
}

Statistics::~Statistics() {}

void Statistics::Start() {
	cout << "Started Program\n\n";
	start = clock();
}

void Statistics::CreatedGraphs() {
	created = clock();
	cout << "\nCreated Graphs\n\nExecuting Queries...\n";
}

void Statistics::ExecutedQueries() {
	executed = clock();
}

void Statistics::finalSizes(uint32_t out, uint32_t in, uint32_t dupl)
{
  sizeGraphOut = out;
  sizeGraphIn = in;
  sizeGraphDupl = dupl;
}
void Statistics::finalUsedSizes(uint32_t out, uint32_t in, uint32_t dupl)
{
  sizeGraphUsedOut = out;
  sizeGraphUsedIn = in;
  sizeGraphUsedDupl = dupl;
}

void Statistics::Print() {
	cout << "\nStatistics: \n\n";

  cout << "Duplicates in creation : " << duplicates << "\n";
  cout << "Duplicates in queries : " << duplicatesQA << "\n\n";

  cout << "Sise of graph used: Out: " << sizeGraphUsedOut << "\n";
  cout << "Sise of graph used: In: " << sizeGraphUsedIn << "\n";
  cout << "Sise of graph used: Dupl: " << sizeGraphUsedDupl << "\n\n";

  cout << "Sise of graph: Out: " << sizeGraphOut << "\n";
  cout << "Sise of graph: In: " << sizeGraphIn << "\n";
  cout << "Sise of graph: Dupl: " << sizeGraphDupl << "\n\n";

	cout << "Graph Creation : " << double(created - start) / CLOCKS_PER_SEC << " secs\n";
	cout << "Query Execution : " << double(executed - created) / CLOCKS_PER_SEC << " secs\n";
	cout << "Total time : " << double(executed - start) / CLOCKS_PER_SEC << " secs\n\n";
}
