#include <iostream>

#include "statistics.h"

Statistics::Statistics() {
    sizeGraphOut = 0;
    sizeGraphIn = 0;

    duplicates = 0;
    insertions = 0;
    queries = 0;
}

Statistics::~Statistics() {}

void Statistics::Start() {
	std::cout << "Started Program\n\n";
	start = clock();
}

void Statistics::CreatedGraphs() {
	std::cout << "Created Graphs\n\n";
	created = clock();
}

void Statistics::ExecutedQueries() {
	executed = clock();
}

void Statistics::Print() {
	std::cout << "\n\nStatistics: \n\n";
	std::cout << "Graph Creation : " << double(created - start) / CLOCKS_PER_SEC << " secs\n";

	std::cout << "Query Execution : " << double(executed - created) / CLOCKS_PER_SEC << " secs\n";

	elapsedTime = double(executed - start) / CLOCKS_PER_SEC;
	std::cout << "Total time : " << elapsedTime << " secs\n\n";
}
