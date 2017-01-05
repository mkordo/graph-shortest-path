#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "search.h"

using namespace std;

Search::Search() {
	stepsFront = 0;
    stepsBack = 0;
	size = 0;
	visitedIn = NULL;
	visitedOut = NULL;
}

Search::~Search()
{
	if(visitedIn!=NULL) free(visitedIn);
	if(visitedOut!=NULL) free(visitedOut);
}

int Search::ShortestPath(Graph<Node>& graphOut, Graph<Node>& graphIn, uint32_t nodeA, uint32_t nodeB)
{
	if(graphOut.validNode(nodeA)==false || graphIn.validNode(nodeB)==false) return -1;
	Search::init(graphIn.size, graphOut.size);
	bool found = false;

	while(!frontSearch.isEmpty() && !backSearch.isEmpty())
	{
		if(frontSearch.count() < backSearch.count()) // Always search the smallest queue!
		{
			stepsFront++;
			// found = Search::bfs
			if(found==true) {
				return stepsFront + stepsBack;
			}
		}
		else
		{
			stepsBack++;
			// found = Search::bfs
			if(found==true) {
				return stepsFront + stepsBack;
			}
		}

	}

	return -1;
}

bool Search::bfs(Graph<Node>& myGraph, Queue<uint32_t>& myQueue, bool* myVisited, bool* theirVisited)
{
	// We can get queue size with its count() method


	// With Queue.pushBlock, we can push all neighbors into the Queue quicklier than simple push()
	// myQueue.pushBlock(myGraph.getNodeNeighbor(current), myGraph.getNodeSize(current));
}

void Search::init(uint32_t sizeIn, uint32_t sizeOut)
{
	uint32_t max;

	/* Initialize local variables */
	stepsFront = 0;
    stepsBack = 0;

	/* Initialize visited array */
	if(sizeIn>=sizeOut) max = sizeIn;
	else max = sizeOut;

	if(max>size) {
		size = max;
		visitedIn = (bool*) realloc(visitedIn, sizeof(bool) * size);
		visitedOut = (bool*) realloc(visitedOut, sizeof(bool) * size);
		if(visitedIn==NULL) { cerr << "Search Init: Visited Realloc\n"; }
	}

	memset(visitedIn, false, sizeof(bool) * size);
	memset(visitedOut, false, sizeof(bool) * size);

	/* Initialize queues */
	frontSearch.init();
  	backSearch.init();
}
