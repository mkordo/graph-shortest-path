#include <iostream>
#include <string>
#include <cstdint>  /* For uint32_t */
#include <ctime>
#include "tarjan.h"

using namespace std;

meTARZANyouJANE::meTARZANyouJANE(uint32_t s){
	uint32_t i;
	sizePanos = s;
	cout << "size of tarzan " << s << endl;
	marked=(bool*)malloc(s*sizeof(bool));
	if(marked==NULL) cerr << "meTARZANyouJANE Constructor : Malloc1" << endl;
	for(i=0;i<s;i++){
		marked[i]=false;
	}
	onStack=(bool*)malloc(s*sizeof(bool));
	if(onStack==NULL) cerr << "meTARZANyouJANE Constructor : Malloc2" << endl;
	defined=(bool*)malloc(s*sizeof(bool));
	if(defined==NULL) cerr << "meTARZANyouJANE Constructor : Malloc3" << endl;
	index=(uint32_t*)malloc(s*sizeof(uint32_t));
	if(index==NULL) cerr << "meTARZANyouJANE Constructor : Malloc4" << endl;
	lowlink=(uint32_t*)malloc(s*sizeof(uint32_t));
	if(lowlink==NULL) cerr << "meTARZANyouJANE Constructor : Malloc5" << endl;
	for(i=0;i<s;i++){ onStack[i]=false;defined[i]=false;}
	
	SCC_stack.init();
	Parent_stack.init();
	Children_stack.init();
}

meTARZANyouJANE::~meTARZANyouJANE(){
	//cout << "Destroy meTARZANyouJANE\n";
	free(marked);
	free(onStack);
	free(defined);
	free(index);
	free(lowlink);
	//cout << "Destroy meTARZANyouJANE\n";
};


int meTARZANyouJANE::tarjan(Graph<Node>& graph, scc<Component> & SCC){
	uint32_t i;

	//-------------------------------------------------- throw me away i spend too much computaional resources
	uint32_t index_=0;
	for(i=0;i<=graph.last;i++){
		if(graph.validNode(i) && !marked[i] ) {
			strongConnect(graph,i,index_, SCC);
		}
	}
	return 0;
}

//int rsc(Graph<Node> &graph, uint32_t head,bool *onStack, bool *defined, uint32_t *index, uint32_t *lowlink, bool *marked, Stack<uint32_t>& SCC_stack,Stack<uint32_t>& Parent_stack,Stack<uint32_t>& Children_stack, uint32_t &index_, scc<Component> SCC){
int meTARZANyouJANE::strongConnect(Graph<Node> &graph, uint32_t head ,uint32_t &index_,scc<Component> &SCC){
	uint32_t *neigb, s,temp=index_,i=0,x;
	index[head]=index_;
	lowlink[head]=index_;
	defined[head]=true;
	marked[head]=true;
	index_++;
	onStack[head]=true;
	SCC_stack.push(head);
	
	s=graph.getNodeSize(head);
	neigb=graph.getNodeNeighbor(head);
	if(neigb==NULL) {
		SCC.count++;
		SCC.insert(head);
		return 0;
		}
	while(1){ // Consider successors of v
		x = neigb[i];
		if(x>=sizePanos){ cout << "size of tarzan breached " << x << "\t" << sizePanos << endl; exit(-1);}
		if(defined[x]==false){ 	// Successor w has not yet been visited; recurse on it
			
			index[x]=index_;
			lowlink[x]=index_;
			defined[x]=true;
			marked[x]=true;
			index_++;
			if(graph.getNodeNeighbor(x)!=NULL){
				Parent_stack.push(head);
				Children_stack.push(i);
				i=0;head=x;
				
				onStack[head]=true;
				SCC_stack.push(head);
				s=graph.getNodeSize(head);
				neigb=graph.getNodeNeighbor(head);
				continue;
			}
			else{
				SCC.count++;
				//cout << "checkpoint 2" << endl;
				SCC.insert(x);
				
			}
		
		}
		else if (onStack[x]==true){
			//cout << "checkpoint 1" << endl;
			lowlink[head]=min(lowlink[head],index[x]);
		}
		
		i++;
			
		if(i>=s){
			if(index[head]==lowlink[head]){
				SCC.count++;
				do{ 
					x=SCC_stack.pop();
					onStack[x]=false;
					SCC.insert(x);
				}while(x!=head);
			}			
			if(Children_stack.isEmpty() || Parent_stack.isEmpty()) break;
			i=Children_stack.pop();x=Parent_stack.pop();
			if(x>=sizePanos){ cout << "size of tarzan breached " << x << "\t" << sizePanos << endl; exit(-1);}
			lowlink[x]=min(lowlink[head],lowlink[x]);
			head=x;
			s=graph.getNodeSize(head);
			neigb=graph.getNodeNeighbor(head);				
		}
		
	}
		
	return 0;
}


uint32_t min(uint32_t a,uint32_t b){
		if(a>=b) return b;
		else return a;
}

uint32_t max(uint32_t a,uint32_t b){
		if(a>=b) return a;
		else return b;
}

