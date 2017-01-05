#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "search.h"

using namespace std;

Search::Search() {
	steps = 0;
	size = 0;
	visitedIn = NULL;
	visitedOut = NULL;
	found=false;
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

	frontSearch.push(nodeA);
	backSearch.push(nodeB);

	while(!frontSearch.isEmpty() && !backSearch.isEmpty())
	{
		if(frontSearch.count() < backSearch.count()) // Always search the smallest queue!
		{
			Search::bfsFront();
		}
		else
		{
			Search::bfsBack();
		}

	}

	return steps;
}

int Search::bfsFront()
{
	frontSearch.pop();
}

int Search::bfsBack()
{
	backSearch.pop();
}

void Search::init(uint32_t sizeIn, uint32_t sizeOut)
{
	uint32_t max;

	/* Initialize local variables */
	steps = 0;
	found=false;

	/* Initialize visited array */
	if(sizeIn>=sizeOut) max = sizeIn;
	else max = sizeOut;

	if(max>size) {
		size = max;
		visitedIn = (bool*) realloc(visitedIn, sizeof(bool) * size);
		visitedOut = (bool*) realloc(visitedOut, sizeof(bool) * size);
	}

	memset(visitedIn, false, sizeof(bool) * size);
	memset(visitedOut, false, sizeof(bool) * size);

	/* Initialize queues */
	frontSearch.init();
  backSearch.init();
}
