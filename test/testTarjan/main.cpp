#include <iostream>
#include <string>
#include <cstdint>  /* For uint32_t */
#include <ctime>

#include "../../src/graph/graph.h"
#include "../../src/parser/parser.h"
#include "../../src/parser/writer.h"
#include "../../src/queue/queue.h"
#include "../../src/stack/stack.h"
#include "../../src/scc/grail.h"
#include "../../src/search/search.h"
#include "../../src/statistics/statistics.h"

using namespace std;

int cmd(int, char**, string&, string&);
void createGraph(Graph<Node>&, Graph<Node>&, Graph<HashNode>&, string);
//void runQueries(Graph<Node>&, Graph<Node>&, Graph<HashNode>&, string);
void runQueries(Graph<Node>&, Graph<Node>&, Graph<HashNode>&, string,scc<Component>&);

Statistics stats(true);
//Statistics stats(false);

int main(int argc, char** argv)
{
  string filename, filenameQA;

  /////////////////////////
  stats.Start();

  cmd(argc, argv, filename, filenameQA);

  Graph<Node> graphOut;
  Graph<Node> graphIn;
  Graph<HashNode> graphDupl;

  createGraph(graphOut, graphIn, graphDupl, filename);
  graphOut.print();
  //graphIn.print();
  //stats.CreatedGraphs();
  //--------------------------------------------------------------------
  uint32_t i,j,s,*neigb,head;
  
  scc<Component> SCC;
  SCC.init(max(graphOut.last,graphIn.last)+1);
  //SCC.printBelong();return 0;
	meTARZANyouJANE T(max(graphOut.last,graphIn.last)+1);
	T.tarjan(graphOut,SCC);
	//T.saveSpace();
	SCC.print();
	SCC.printBelong();
	//for(i=0;i<max(graphOut.last,graphIn.last)+1;i++){
	//		cout<<i<<"("<<T.findNodeSCC(i)<<")";
	//}
	cout<<"BANANA\n";
	Graph<Node> hyper;
	Graph<HashNode> hyperDupl;
  HyperGraph(hyper, hyperDupl, graphOut, SCC);
  cout<<"hypergraph size: ("<<hyper.last+1<<")\n";
  hyper.print();
  
  grail G(hyper.last);
  G.build(hyper);
  
  //grail G(graphOut.last);
  //G.build(graphOut);
  
  //--------------------------------------------------------------------
  //runQueries(graphOut, graphIn, graphDupl, filenameQA,T.SCC);
  stats.ExecutedQueries();

  stats.finalSizes(graphOut.size, graphIn.size, graphDupl.size);
  stats.finalUsedSizes(graphOut.last, graphIn.last, graphDupl.last);
 // stats.Print();
  return 0;
}

void createGraph(Graph<Node> &graphOut, Graph<Node> &graphIn, Graph<HashNode> &graphDupl, string filename)
{
  uint32_t me, neighbor;
  Parser reader(filename);

  while( reader.getRow(me, neighbor) != STOP )
  {
    //reader.printRow(me, neighbor);
    /*
    graphOut.insert(me, neighbor);
    graphIn.insert(neighbor, me);
    //*/
    ///*
    if( graphDupl.insert(me, neighbor) == true ) {
      graphOut.insert(me, neighbor);
      graphIn.insert(neighbor, me);
    }
    else stats.duplicates++;
    //*/
  }
  //cout << "\n" << reader.getCount() << "\n";
}

//void runQueries(Graph<Node> &graphOut, Graph<Node> &graphIn, Graph<HashNode> &graphDupl, string filename)
void runQueries(Graph<Node> &graphOut, Graph<Node> &graphIn, Graph<HashNode> &graphDupl, string filename,scc<Component>& SCC)
{
  int type;
  uint32_t me, neighbor;
  Parser reader(filename);
  Writer output("results.txt");

  Search search;
  int result;
  while( ( type = reader.getQuery(me, neighbor) ) != STOP ) {
    //reader.printQuery(type, me, neighbor);
    if(type == QUESTION) {
      //stats.Query();
      //result = search.ShortestPath(graphOut, graphIn, me, neighbor);
      result = search.ShortestPath(graphOut, graphIn, me, neighbor,SCC);
      cout<<endl<<"("<<me<<"-"<<neighbor<<"):"<<result<<endl;
      output.writeInt(result);
      //break;
    }
    else if(type == INSERTION) {
      /*
      graphOut.insert(me, neighbor);
      graphIn.insert(neighbor, me);
      //*/
      ///*
      if( graphDupl.insert(me, neighbor) == true ) {
        graphOut.insert(me, neighbor);
        graphIn.insert(neighbor, me);
      }
      else stats.duplicatesQA++;
      //*/

    }
  }
  //cout << "\n" << reader.getCount() << "\n";
}
















int cmd(int argc, char** argv, string &filename, string &filenameQA)
{
  int i, k;
  string argument;

  argc--;
  argv++;

  if(argc%2!=0 || argc>4) {
    cerr << "Invalid arguments\n";
    return -1;
  }

  for (i=0; i<argc; i+=2)
  {
    argument.assign(argv[i]);
    if (argument.compare("-f") == 0) {
        filename.assign( argv[i+1] );
    }
    else if (argument.compare("-q") == 0) {
        filenameQA.assign( argv[i+1] );
    }
  }

  //cout << filename << "\n";
  //cout << filenameQA << "\n";

  return 0;
}
