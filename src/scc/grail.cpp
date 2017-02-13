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
}
	
grail::~grail(){
}
			
int grail::buildGrail(Graph<Node>& graph, scc<Component>& SCC){
}
