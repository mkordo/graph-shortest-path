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
	if(visitedIn!=NULL) free(visitedIn);
	if(visitedOut!=NULL) free(visitedOut);
}

int Search::ShortestPath(Graph<Node>& graphOut, Graph<Node>& graphIn, uint32_t nodeA, uint32_t nodeB)
{
	uint32_t *neigb,size,i;
	if(graphOut.validNode(nodeA)==false || graphIn.validNode(nodeB)==false) return -1;
	Search::init(graphIn.size, graphOut.size);
	bool found = false;
//cout << "Searching from "<<nodeA<<" to "<<nodeB<<endl;
	/*v2
	frontSearch.push(nodeA);
	visitedOut[nodeA]=true;
	backSearch.push(nodeB);
	visitedIn[nodeB]=true;
	*/
	size=graphOut.getNodeSize(nodeA);
	neigb=graphOut.getNodeNeighbor(nodeA);
	frontSearch.pushBlock(neigb,size);
	//frontSearch.print();
	//------------------------------------
	size=graphIn.getNodeSize(nodeB);
	neigb=graphIn.getNodeNeighbor(nodeB);
	backSearch.pushBlock(neigb,size);
	//backSearch.print();
	//for(i=0;i<size;i++){cout<<neigb[i];}
	while(!frontSearch.isEmpty() && !backSearch.isEmpty())
	{
		/*if(frontSearch.count() < backSearch.count()) // Always search the smallest queue!
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
		}*/
		//cout<<"frontSearch: ";frontSearch.print();
		steps++;
		if ( Search::bfs(graphOut, frontSearch, visitedOut, visitedIn) == true ) return steps; //found a solution 
		//cout << "banana here!\n";
		//cout<<"backSearch: ";backSearch.print();
		steps++;
		if ( Search::bfs(graphIn, backSearch, visitedIn, visitedOut) == true ) return steps;   //found a solution
		//cout<<"banana there!\n";
		
		//break;
	}

	return -1;
}

bool Search::bfs(Graph<Node>& myGraph, Queue<uint32_t>& myQueue, bool* myVisited, bool* theirVisited)
{
	uint32_t max,i,head,*neigb,size,j;
	// We can get queue size with its count() method
	//cout << myQueue.count() <<endl;
	max=myQueue.count();
	for(i=0;i<max;i++){
		//myQueue.pushBlock
		head=myQueue.pop();
		if(myVisited[head]==false){
			//cout<< "banana!"<<endl;
			myVisited[head]=true;
			size=myGraph.getNodeSize(head);
			neigb=myGraph.getNodeNeighbor(head);
			myQueue.pushBlock(neigb,size);
			//------------------------------------------------------------v2
			//for(j=0;j<size;j++){
				//cout<<neigb[j]<<" ";
				//cout<<myVisited[neigb[j]]<<"+"<<theirVisited[j];
				//if(myVisited[neigb[j]]==false){myVisited[neigb[j]]=true; myQueue.push(neigb[j]);}
				//if (theirVisited[neigb[j]]==true) return true;
			//}//cout<<endl;
			//------------------------------------------------------------
			
		}
		if(theirVisited[head]==true) return true;
	}

	// With Queue.pushBlock, we can push all neighbors into the Queue quicklier than simple push()
	// myQueue.pushBlock(myGraph.getNodeNeighbor(current), myGraph.getNodeSize(current));
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
