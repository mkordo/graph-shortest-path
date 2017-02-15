#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "search.h"

using namespace std;

Search::Search() {
	//stepsFront = 0;
    //stepsBack = 0;
	steps=0;
	size = 0;
	visitedIn = NULL;
	visitedOut = NULL;
}

Search::~Search()
{
	//cout << "Destroy Search\n";
	if(visitedIn!=NULL) free(visitedIn);
	if(visitedOut!=NULL) free(visitedOut);
	//cout << "Destroy Search\n";
}

int Search::ShortestPath(Graph<Node>& graphOut, Graph<Node>& graphIn, uint32_t nodeA, uint32_t nodeB)
{
	uint32_t *neigb,size,i;
	if(graphOut.validNode(nodeA)==false || graphIn.validNode(nodeB)==false) return -1;
	Search::init(graphIn.size, graphOut.size);
	bool found = false;

	frontSearch.push(nodeA);
	visitedOut[nodeA]=true;
	backSearch.push(nodeB);
	visitedIn[nodeB]=true;

	while(!frontSearch.isEmpty() && !backSearch.isEmpty())
	{
		if(frontSearch.count() < backSearch.count()) { // Always search the smallest queue!
			steps++;
			if ( Search::bfs(graphOut, frontSearch, visitedOut, visitedIn) == true ) return steps; //found a solution 
		}
		else {
			steps++;
			if ( Search::bfs(graphIn, backSearch, visitedIn, visitedOut) == true ) return steps; //found a solution
		}
		//break;

		/*steps++;
		if ( Search::bfs(graphOut, frontSearch, visitedOut, visitedIn) == true ) return steps; //found a solution 

		steps++;
		if ( Search::bfs(graphIn, backSearch, visitedIn, visitedOut) == true ) return steps;   //found a solution

		//break;*/
	}

	return -1;
}

bool Search::bfs(Graph<Node>& myGraph, Queue<uint32_t>& myQueue, bool* myVisited, bool* theirVisited)
{
	uint32_t max,i,head,*neigb,size,j;

	max=myQueue.count();
	for(i=0;i<max;i++){

		head=myQueue.pop();

		size=myGraph.getNodeSize(head);
		neigb=myGraph.getNodeNeighbor(head);

		for(j=0;j<size;j++){

			if(myVisited[neigb[j]]==false){myVisited[neigb[j]]=true; myQueue.push(neigb[j]);}
			if (theirVisited[neigb[j]]==true) return true;
		}
			
		if(theirVisited[head]==true) return true;
	}

	return false;
}

void Search::init(uint32_t sizeIn, uint32_t sizeOut)
{
	uint32_t max;

	/* Initialize local variables */
	//stepsFront = 0;
    //stepsBack = 0;
	steps=0;
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

int Search::ShortestPath(Graph<Node>& graphOut, Graph<Node>& graphIn, uint32_t nodeA, uint32_t nodeB, scc<Component>& SCC)
{
	uint32_t *neigb,size,i;
	if(graphOut.validNode(nodeA)==false || graphIn.validNode(nodeB)==false) return -1;
	Search::init(graphIn.size, graphOut.size);
	bool found = false;
  if(SCC.belongs[nodeA]!=SCC.belongs[nodeB]) return -1;
	frontSearch.push(nodeA);
	visitedOut[nodeA]=true;
	backSearch.push(nodeB);
	visitedIn[nodeB]=true;

	while(!frontSearch.isEmpty() && !backSearch.isEmpty())
	{
		if(frontSearch.count() < backSearch.count()) { // Always search the smallest queue!
			steps++;
			if ( Search::bfs(graphOut, frontSearch, visitedOut, visitedIn, SCC.belongs[nodeA], SCC.belongs) == true ) return steps; //found a solution 
		}
		else {
			steps++;
			if ( Search::bfs(graphIn, backSearch, visitedIn, visitedOut,SCC.belongs[nodeA], SCC.belongs) == true ) return steps;   //found a solution
		}
		//break;
    
		/*steps++;
		//cout<<"\nFront\n";
		if ( Search::bfs(graphOut, frontSearch, visitedOut, visitedIn, SCC.belongs[nodeA], SCC.belongs) == true ) return steps; //found a solution 

		steps++;
		//cout<<"\nBAck\n";
		if ( Search::bfs(graphIn, backSearch, visitedIn, visitedOut,SCC.belongs[nodeA], SCC.belongs) == true ) return steps;   //found a solution

		//break;*/
	}

	return -1;
}

bool Search::bfs(Graph<Node>& myGraph, Queue<uint32_t>& myQueue, bool* myVisited, bool* theirVisited,uint32_t me,uint32_t*& belongs)
{
	uint32_t max,i,head,*neigb,size,j;

	max=myQueue.count();
	for(i=0;i<max;i++){

		head=myQueue.pop();

		size=myGraph.getNodeSize(head);
		neigb=myGraph.getNodeNeighbor(head);
   // cout<<"head:"<<head<<" --";
		for(j=0;j<size;j++){
		//	cout<<" "<<neigb[j]<<"\t";
		//	cout<<"("<<belongs[neigb[j]]<<","<<me<<")";
			if(belongs[neigb[j]]!=me){/*cout <<"avoiding "<<neigb[j]<<"!";*/ continue;}
			if(myVisited[neigb[j]]==false){myVisited[neigb[j]]=true; myQueue.push(neigb[j]);}
			if (theirVisited[neigb[j]]==true) return true;
		}
			
		if(theirVisited[head]==true) return true;
	}

	return false;
}


