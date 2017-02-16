#include <iostream>
#include <string.h>

#include "cc.h"

cc::cc(uint32_t size_){
	uint32_t j,i;
	size=0;
	count=-1;
	metric=20;
	belongs=NULL;
	updateIndexSize=10;//min(size,metric);
	updateIndexCount=0;
	for(j=0;j<2;j++){
		UpdateIndex[j]=(uint32_t*) malloc(updateIndexSize*sizeof(uint32_t));
		if(UpdateIndex[j]==NULL) cerr << "cc contructor : Malloc" << endl;
		for(i=0;i<updateIndexSize;i++){
			UpdateIndex[j][i]=0;
		}
	}
  init(size_);
}
void cc::init(uint32_t size_){
	
	uint32_t i,j;
  index = 0;
  count = -1;
//cout << "checkpoint7 ---- " << endl;
 //if(size<size_) { 
		size = size_;
		if(belongs!=NULL) free(belongs);
		belongs=(uint32_t*) malloc(size*sizeof(uint32_t));
		if(belongs==NULL) cerr << "cc init : Malloc" << endl;
		
		//if(marked!=NULL) free(marked);
		//marked=(bool*) malloc(size*sizeof(bool));
		//if(marked==NULL) cerr << "cc init 2 : Malloc" << endl;
	//}
	//cout << "checkpoint8 ---- " << endl;
	for(j=0;j<2;j++){
		for(i=0;i<updateIndexSize;i++){
			UpdateIndex[j][i]=0;
		}
	}
  for(i=0;i<size;i++){belongs[i]=-1;/*marked[i]=0;/**/}
}
cc::~cc(){
  free(belongs);
  free(UpdateIndex[0]);
  free(UpdateIndex[1]);
  //free(marked);
}

void cc::assign(uint32_t source, uint32_t target, Graph<Node>& graphOut, Graph<Node>& graphIn){//cout<<"ck2\n";
	//cout<<size<<endl;
	//cout<<source<<" "<<target<<endl;
	if(source>=size || target>=size) expand(max(graphOut.last,graphIn.last)+1);
	//cout<<"ck3\n";
	//if(target>size) expand(target);
	//cout<<"ck4\n";
	cout << "yolo " << belongs[source] <<"\t" << belongs[target] << "\t" << updateIndexCount << "\t" << updateIndexSize << endl;
	if(belongs[source]==-1){//cout<<"ck5\n";
		if(belongs[target]==-1){//cout<<"ck6\n";
			count++;cout<<"c7\n";
			belongs[source]=count;//cout<<"ck8\n";
			belongs[target]=count;//cout<<"ck8\n";
		}
		else{
			//count++;cout<<"c8\n";
			belongs[source]=belongs[target];//cout<<"ck9\n";
		}
	}
	else{
		if(belongs[target]==-1){//cout<<"ck10\n";
			belongs[target]=belongs[source];//cout<<"ck11\n";
		}
		else{
			cout << "yolo " << updateIndexCount << "\t" << updateIndexSize << endl;
			if(updateIndexCount>=updateIndexSize){
				cout<<"ck12##############\n";
				print();
				init(size);//cout<<"ck13\n";
				run(graphOut,graphIn);
				updateIndexCount=0;
			}
			else{
				count++;cout<<"c9\n";
				//cout<<updateIndexCount<<endl;
				if(belongs[source]!=belongs[target]){
					UpdateIndex[0][updateIndexCount]=belongs[source];
					UpdateIndex[1][updateIndexCount]=belongs[target];
					updateIndexCount++;cout<<"ck14\n"<<"============"<< updateIndexCount<<endl;
				}
			}
		}
	}
}
void cc::expand(uint32_t newC){
  uint32_t i;
  uint32_t newSize;
  newSize = size*2;
  cout << "checking -------------" << newSize<< endl;
  while(newSize<=newC) { newSize *= 2; }
  cout << "checking -------------@" << newSize << endl;
  belongs=(uint32_t*) realloc(belongs, newSize*sizeof(uint32_t));
  if(belongs==NULL) cerr << "cc Expand : Malloc" << endl;
  memset(belongs+size, -1, sizeof(uint32_t) * (newSize-size));
	cout << "CC expanded " << newSize << endl;
	/*marked=(uint32_t*) realloc(marked, newSize*sizeof(bool));
  if(marked==NULL) cerr << "cc Expand 2 : Malloc" << endl;
  memset(marked+size, -1, sizeof(bool) * (newSize-size));/**/

  size=newSize;
  cout << "CC expanded " << size << endl;
}

void cc::print(){
	uint32_t i;
	cout << "Belongs cc index /" << size << endl;
	for(i=0; i<size; i++) {
		if(belongs[i]!=-1) cout << i << "->("<< belongs[i]<<")\n";
	}
	cout << "Belongs update index" << endl;
	for(i=0; i<updateIndexSize; i++) {
		cout << i << "->("<< UpdateIndex[0][i]<<" , " << UpdateIndex[1][i] << ")\n";
	}
	cout<<endl;
}
void cc::run(Graph<Node>& graphOut,Graph<Node>& graphIn){
	uint32_t i,head;
	Queue<uint32_t> bfs_queue;
	bfs_queue.init();
	//cout << "checkpoint1 ---- " << head << endl;
	for (head=0; head<size; head++){
//cout << " \t\t checking head " << head << endl;
		if((graphOut.validNode(head) || graphIn.validNode(head)) && belongs[head]==-1){
			
//cout << "checkpoint2 ---- " << head << endl;
			
			count++;
			belongs[head]= count;
			
			bfs_queue.push(head);
			bfs_dual(graphIn,graphOut,bfs_queue);
			
		}
	}
	
}
void cc::bfs_dual(Graph<Node>& graphIn, Graph<Node>& graphOut, Queue<uint32_t>& myQueue){
	uint32_t max, i, head, *neigb, s, j;
	bool* visited=(bool *)malloc(size*sizeof(bool));
	for(j=0;j<size;j++)visited[j]=false;
	do{
		head=myQueue.pop();
		if(visited[head]==true)continue;
		visited[head]=true;
		belongs[head]=count;
		s=graphIn.getNodeSize(head);
		neigb=graphIn.getNodeNeighbor(head);		
		for(j=0;j<s;j++){
			myQueue.push(neigb[j]);
		}
		s=graphOut.getNodeSize(head);
		neigb=graphOut.getNodeNeighbor(head);		
		for(j=0;j<s;j++){
			myQueue.push(neigb[j]);
		}
	}while(!myQueue.isEmpty());
}
