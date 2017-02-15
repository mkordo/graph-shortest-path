#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "search.h"

using namespace std;

Search::Search(Graph<Node> *graphOut_, Graph<Node> *graphIn_, scc<Component>* SCC_, grail *G_) {
	graphOut = graphOut_;
	graphIn = graphIn_;
	SCC=SCC_;
	G=G_;

	steps=0;
	size = 0;
	visitedIn = NULL;
	visitedOut = NULL;

	currentVersion=0;
}

void Search::init(uint32_t sizeIn, uint32_t sizeOut, int version_)
{
	uint32_t max;

	currentVersion = version_;

	/* Initialize local variables */
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
  	//cout<<"I am initialized! "<<size <<"\n";
}

Search::~Search()
{
	if(visitedIn!=NULL) free(visitedIn);
	if(visitedOut!=NULL) free(visitedOut);
}

int Search::ShortestPath(uint32_t nodeA, uint32_t nodeB, int version_)
{
  //cout<<"Searching from: "<<nodeA<<"to"<<nodeB<<endl;
	if(graphOut->inBounds(nodeA)==false || graphIn->inBounds(nodeB)==false) return -1;
	if(nodeA == nodeB) return 0;
	if(graphOut->getNodeSize(nodeA)==false || graphIn->getNodeSize(nodeB)==false) return -1;
	//SCC->printBelong();
	if(SCC->belongs[nodeA]==SCC->belongs[nodeB]){
					//cout<<"euruka!\n";
					return ShortestPath( nodeA, nodeB, version_, SCC);
					//cout<<result<<endl;
					// result;
	}
	else{
			if(G->maybe(SCC->belongs[nodeA],SCC->belongs[nodeB])){
					//cout<<"maybe"<<endl;
					//result=search.ShortestPath(graphOut, graphIn, me, neighbor);
					//cout<<result<<endl;
			}
			else{
				//cout<<"NO!"<<endl;
				return -1;
				//result=search->ShortestPath(graphOut, graphIn, me, neighbor);
					//cout<<result<<endl;
			}
			
	}
	
	//cout<<"i ll search now!\n";
	Search::init(graphIn->size, graphOut->size, version_);
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
	}

	return -1;
}

bool Search::bfs(Graph<Node>* myGraph, Queue<uint32_t>& myQueue, bool* myVisited, bool* theirVisited)
{
	uint32_t max, i, head, *neigb, size, j;
	int *myVersion;

	max=myQueue.count();
	for(i=0; i<max; i++){

		head=myQueue.pop();

		size=myGraph->getNodeSize(head);
		neigb=myGraph->getNodeNeighbor(head);
		myVersion=myGraph->getNodeVersion(head);

		for(j=0;j<size;j++){
			if(myVersion[j] > currentVersion) continue;

			if(myVisited[neigb[j]]==false) {
				myVisited[neigb[j]]=true;
				myQueue.push(neigb[j]); 
			}
			if (theirVisited[neigb[j]]==true) return true;
		}

		if(theirVisited[head]==true) return true;
	}
	return false;
}



int Search::ShortestPath( uint32_t nodeA, uint32_t nodeB, int version_, scc<Component>* SCC)
{
	//cout<<"same scc\n";
	//uint32_t *neigb,size,i;
	//if(graphOut->validNode(nodeA)==false || graphIn.validNode(nodeB)==false) return -1;
	Search::init(graphIn->size, graphOut->size, version_);
	//bool found = false;
  //if(SCC.belongs[nodeA]!=SCC.belongs[nodeB]) return -1;
	frontSearch.push(nodeA);//cout<<"ch1\n";
	backSearch.push(nodeB);//cout<<"ch3\n";
	//cout<<"size "<<size<<"vs"<<nodeA<<"\n";
	visitedOut[nodeA]=true;//cout<<"ch2\n";
	
	visitedIn[nodeB]=true;//cout<<"ch4\n"; 
 // cout<<"BANANA!\n";
	while(!frontSearch.isEmpty() && !backSearch.isEmpty())
	{
		if(frontSearch.count() < backSearch.count()) { // Always search the smallest queue!
			steps++;
			if ( Search::bfs(graphOut, frontSearch, visitedOut, visitedIn, SCC->belongs[nodeA], SCC->belongs) == true ) return steps; //found a solution 
		}
		else {
			steps++;
			if ( Search::bfs(graphIn, backSearch, visitedIn, visitedOut,SCC->belongs[nodeA], SCC->belongs) == true ) return steps;   //found a solution
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

bool Search::bfs(Graph<Node>* myGraph, Queue<uint32_t>& myQueue, bool* myVisited, bool* theirVisited,uint32_t me,uint32_t*& belongs)
{
	uint32_t max,i,head,*neigb,size,j;

	max=myQueue.count();
	for(i=0;i<max;i++){

		head=myQueue.pop();

		size=myGraph->getNodeSize(head);
		neigb=myGraph->getNodeNeighbor(head);
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


