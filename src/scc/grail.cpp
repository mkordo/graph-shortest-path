#include <iostream>
#include "grail.h"

using namespace std;

int HyperGraph(Graph<Node>& hyper, Graph<HashNode> &hyperDupl ,Graph<Node>& graph, scc<Component>& SCC){
	cout<<"\n\nHyperGraph\n\n";
	uint32_t i,j,k,temp,size,*neigb;
	
	for(i=0;i<SCC.count+1;i++){
			//cout<< i <<":\n";
			for(j=0;j<SCC.components[i].count;j++){
					//if(j!=0) cout <<",";
					temp=SCC.components[i].included[j];
					//cout<<" "<<temp;
					size=graph.getNodeSize(temp);
					//cout<<"("<<size<<")";
					neigb=graph.getNodeNeighbor(temp);
					//cout<<temp<<"E"<< SCC.belongs[temp]<<" |\t";
					for(k=0;k<size;k++){
						//cout<<"BANANA";
						//cout<<"-"<<SCC.belongs[neigb[k]]<<"-";
							if(SCC.belongs[neigb[k]]!=i){
								//cout<<"not in scc:"<<neigb[k]<<"E"<<SCC.belongs[neigb[k]]<<"\n";
								if( hyperDupl.insert(i, SCC.belongs[neigb[k]]) == true ) {
									hyper.insert(i, SCC.belongs[neigb[k]]);
								}
							}
							//else{cout<<"in scc:"<<neigb[k]<<"\n";}
					}
					//cout<<"|\n";
			}
			//cout<<"\n";
			
	}
	//cout<<"\n\n";
	//hyper.print();
	//cout<<"\n\n";
	return 0;
}


grail::grail(uint32_t size_){
	uint32_t i;
	size=size_;
	minRank=(uint32_t*)malloc(size*sizeof(uint32_t));
	if(minRank==NULL) cerr << "Grail Constructor : Malloc1" << endl;
	rank=(uint32_t*)malloc(size*sizeof(uint32_t));
	if(rank==NULL) cerr << "Grail Constructor : Malloc2" << endl;
	marked=(bool*)malloc(size*sizeof(bool));
	if(marked==NULL) cerr << "Grail Constructor : Malloc3" << endl;	
	minSoFar=(uint32_t*)malloc(size*sizeof(uint32_t));
	if(minSoFar==NULL) cerr << "Grail Constructor : Malloc4" << endl;	
	for(i=0;i<size;i++){
		minRank[i]=UINT32_MAX;
		rank[i]=UINT32_MAX;
		marked[i]=false;
		minSoFar[i]=0;
	}
	minSoFar[i]=0;
	
	iteration.init();
	child.init();
}
	
grail::~grail(){
	free(minRank);
	free(rank);
	free(marked);
	free(minSoFar);
}
			
int grail::build(Graph<Node>& hyper){
	cout<<endl<<"----------------------------------------------------GRAIL"<<endl;
	cout<<size<<endl;
	uint32_t i, index=0;
	for(i=0;i<=size;i++){
		if( !marked[i] ) {
			postOrder(hyper,i,index);
		}
	}
	
}

int grail::build(Graph<Node>& graph, Graph<Node>& graph2){
	cout<<endl<<"----------------------------------------------------GRAIL"<<endl;
	//cout<<"max i in matrix:"<<size<<endl;
	uint32_t i,index=0;
	for(i=0;i<=size;i++){
		cout<<"("<<i<<","<<marked[i]<<")"<<endl;
		if( /*( graph.validNode(i) || graph2.validNode(i) ) &&*/ !marked[i] ) {
			cout<<"post order from "<<i<<endl;
			postOrder(graph,graph2,i,index); //break;
		}
		
	}
	for(i=0;i<=size;i++){
		//if( ( graph.validNode(i) || graph2.validNode(i) ) ) {
			cout<<i<<"=("<<minRank[i]<<","<<rank[i]<<")"<<endl;
			
		//}
		
	}
	
}

int grail::postOrder(Graph<Node>& graph,uint32_t head,uint32_t &index){}

int grail::postOrder(Graph<Node>& graph, Graph<Node>& graph2,uint32_t head,uint32_t &index){
		//cout<<"post order from "<<head<<endl;
		uint32_t s, *neigb, i=0, x, j=0;
		s=graph.getNodeSize(head);
		neigb=graph.getNodeNeighbor(head);
		if(neigb==NULL) {
			cout<<"im broken! "<<index<<"\n";
			rank[head]=index;
			minRank[head]=index;cout<<head<<"--4-----------("<<rank[head]<<","<<minRank[head]<<")"<<endl;
			marked[head]=true;
			minSoFar[head]=min(minSoFar[head],index);
			index++;
			return 0;
		}
		//child.push(3);
		//cout<<"____________"<<child.top()<<"________";
		iteration.push(head);
		iteration.print();
		child.push(0);
	
		while(!iteration.isEmpty()){// && j<2){
			//cout<<"----------------------top:"<<iteration.top()<<endl;
			//for(j=0;j<s;j++){
				x=neigb[i];
				cout<<"x = ("<<x<<") \n";
				if(graph.validNode(x) && !marked[x]){ //if the node has neigbs put him in the stack
						//cout<<"ckp 13\n";
						iteration.push(x);iteration.print();
						child.push(i);child.print();
						i=0;head=x;
						s=graph.getNodeSize(head);
						neigb=graph.getNodeNeighbor(head);
						//break;
						continue;
				}
				else if /*/(graph2.validNode(x) &&*/ (!marked[x]){cout<<"noNeigb\n";//if a child has no neigb
						
						rank[x]=index;
						minRank[x]=index;
						minSoFar[head]=min(minSoFar[head],index);
						marked[x]=true; 		cout<<"marked:("<<x<<",visited)"<<endl;
						child.pop();
						child.push(i);
						index++; 						cout<<x<<"--1-----------("<<rank[x]<<","<<minRank[x]<<")"<<endl;
						
				} 
				/*else*/ if(marked[x]){/*cout<<"Im broken bye\n";break;}*/
						child.pop();
						i++;
						child.push(i);
						//continue;
				}
				//cout<<head<<" next child:("<<child.top()+1<<")\n";
				i=child.top();//cout<<"chk 1\n";
				//cout<<"Im "<<head<<" in my "<<i<<" with size "<<s<<endl;//break;
				i++;
				head=iteration.top();//cout<<"chk 2\n";
				s=graph.getNodeSize(head);//cout<<"chk 3\n";
				neigb=graph.getNodeNeighbor(head);//cout<<"chk 4\n";
				cout<<"Im "<<head<<" in my "<<i<<" with size "<<s<<endl;//break;
				if(i >= s ){
						cout<<"Im "<<head<<" in my "<<i<<" out of children im popping!\n";
						rank[head]=index;
						minRank[head]=minSoFar[head];
						//minRank[head]=13;
						cout<<head<<"--3-----------("<<rank[head]<<","<<minRank[head]<<")"<<endl;
						index++;
						marked[head]=true;
						//marked[iteration.top()];
						iteration.pop();iteration.print();
						child.pop();child.print();cout<<"chk 1\n";
						if(iteration.isEmpty()) return 0;
						head=iteration.top();cout<<"chk 2\n";
						neigb=graph.getNodeNeighbor(head);cout<<"chk 3\n";
						i=child.top()+1;
						child.pop();
						child.push(i);
						
				}cout<<"BANANA\n";
			//}
			//if()
			cout<<endl;
			if(iteration.isEmpty()) return 0;
			j++;//break;
			cout<<"i="<<i<<"-------------------------------------------------"<<endl;
		}
}
