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
	elapsedTime = double(executed - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time : " << elapsedTime << " secs\n\n";
}
