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
	CC=NULL;
  t=1;
	steps=0;
	size = 0;
	visitedIn = NULL;
	visitedOut = NULL;
	//cout<<"banana\n";
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
	if(t==1){ 
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
	}
	else{
			if(CC->belongs[nodeA]==CC->belongs[nodeB]){
							//cout<<"euruka!\n";
							CC->print();
							return ShortestPath( nodeA, nodeB, version_, CC);
							//cout<<result<<endl;
							// result;
			}
			else{
				bool f=false;
				uint32_t i;
				for(i=0;i<CC->updateIndexSize;i++){
						if( ( CC->UpdateIndex[0][i]==CC->belongs[nodeA] && CC->UpdateIndex[1][i]==CC->belongs[nodeB] ) || ( CC->UpdateIndex[0][i]==CC->belongs[nodeB] && CC->UpdateIndex[1][i]==CC->belongs[nodeA] ) )
						{
							f=true;
							break;
						}
				}
				if(f==false) return -1;
				
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

	Search::init(graphIn->size, graphOut->size, version_);
 
	frontSearch.push(nodeA);
	backSearch.push(nodeB);
	
	visitedOut[nodeA]=true;
	
	visitedIn[nodeB]=true;
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
	}

	return -1;
}

bool Search::bfs(Graph<Node>* myGraph, Queue<uint32_t>& myQueue, bool* myVisited, bool* theirVisited,uint32_t me,uint32_t*& belongs)
{
	uint32_t max,i,head,*neigb,size,j;
  int *myVersion;
	max=myQueue.count();
	for(i=0;i<max;i++){

		head=myQueue.pop();

		size=myGraph->getNodeSize(head);
		neigb=myGraph->getNodeNeighbor(head);
		myVersion=myGraph->getNodeVersion(head);
   // cout<<"head:"<<head<<" --";
		for(j=0;j<size;j++){
		//	cout<<" "<<neigb[j]<<"\t";
		//	cout<<"("<<belongs[neigb[j]]<<","<<me<<")";\
			if(belongs[neigb[j]]!=me){/*cout <<"avoiding "<<neigb[j]<<"!";*/ continue;}
			if(myVersion[j] > currentVersion) continue;

			if(myVisited[neigb[j]]==false){myVisited[neigb[j]]=true; myQueue.push(neigb[j]);}
			if (theirVisited[neigb[j]]==true) return true;
		}
			
		if(theirVisited[head]==true) return true;
	}

	return false;
}

Search::Search(Graph<Node>* graphOut_, Graph<Node>* graphIn_, cc* CC_){
	cout<<"--BANANA!\n";
	graphOut = graphOut_;
	graphIn = graphIn_;
	//CC_->print();
	CC=CC_;
	SCC=NULL;
	G=NULL;

	steps=0;
	size = 0;
	visitedIn = NULL;
	visitedOut = NULL;
	t=2;
	currentVersion=0;
}


int Search::ShortestPath(uint32_t nodeA, uint32_t nodeB, int version_,cc *CC)
{

	Search::init(graphIn->size, graphOut->size, version_);
 
	frontSearch.push(nodeA);
	backSearch.push(nodeB);
	
	visitedOut[nodeA]=true;
	
	visitedIn[nodeB]=true;
	while(!frontSearch.isEmpty() && !backSearch.isEmpty())
	{
		if(frontSearch.count() < backSearch.count()) { // Always search the smallest queue!
			steps++;
			if ( Search::bfs(graphOut, frontSearch, visitedOut, visitedIn, CC->belongs[nodeA], CC->belongs) == true ) return steps; //found a solution 
		}
		else {
			steps++;
			if ( Search::bfs(graphIn, backSearch, visitedIn, visitedOut, CC->belongs[nodeA], CC->belongs) == true ) return steps;   //found a solution
		}
	}

	return -1;
}



