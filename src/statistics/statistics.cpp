#include <iostream>

#include "statistics.h"

Statistics::Statistics() {
    sizeGraphOut = 0;
    sizeGraphIn = 0;

    duplicates = 0;
    duplicatesQA = 0;
    insertions = 0;
    queries = 0;
}

Statistics::~Statistics() {}

void Statistics::Start() {
	std::cout << "Started Program\n\n";
	start = clock();
}

void Statistics::CreatedGraphs() {
	std::cout << "\nCreated Graphs\n\n";
	created = clock();
}

void Statistics::ExecutedQueries() {
	executed = clock();
}

void Statistics::Print() {
	std::cout << "\nStatistics: \n\n";

  std::cout << "Duplicates in creation : " << duplicates << "\n";
  std::cout << "Duplicates in queries : " << duplicatesQA << "\n\n";

	std::cout << "Graph Creation : " << double(created - start) / CLOCKS_PER_SEC << " secs\n";

	std::cout << "Query Execution : " << double(executed - created) / CLOCKS_PER_SEC << " secs\n";

	elapsedTime = double(executed - start) / CLOCKS_PER_SEC;
	std::cout << "Total time : " << elapsedTime << " secs\n\n";
}
