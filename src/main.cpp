#include <iostream>
#include <string>
#include <stdlib.h> /* srand, rand */
#include <cstdint>  /* For uint32_t */
#include <ctime>

#include "graph/graph.h"
#include "parser/parser.h"
#include "parser/writer.h"
#include "queue/queue.h"
#include "search/search.h"
#include "statistics/statistics.h"
#include "scheduler/scheduler.h"

using namespace std;

int cmd(int, char**, string&, string&);
void createGraph(Graph<Node>*, Graph<Node>*, Graph<HashNode>*, string);
void runQueries(Graph<Node>*, Graph<Node>*, Graph<HashNode>*, string);

Statistics stats(true);
//Statistics stats(false);

int main(int argc, char** argv)
{
  string filename, filenameQA;

  /////////////////////////
  stats.Start();

  cmd(argc, argv, filename, filenameQA);

  srand (time(NULL));

  Graph<Node> graphOut;
  Graph<Node> graphIn;
  Graph<HashNode> graphDupl;

  createGraph(&graphOut, &graphIn, &graphDupl, filename);
  //graphDupl.print();
  //graphOut.print();
  //graphIn.print();
  stats.CreatedGraphs();

  runQueries(&graphOut, &graphIn, &graphDupl, filenameQA);
  stats.ExecutedQueries();

  stats.totalNumOfVersions(graphOut.version);
  stats.finalSizes(graphOut.size, graphIn.size, graphDupl.size);
  stats.finalUsedSizes(graphOut.last, graphIn.last, graphDupl.last);
  stats.Print();
  return 0;
}

void createGraph(Graph<Node> *graphOut, Graph<Node> *graphIn, Graph<HashNode> *graphDupl, string filename)
{
  uint32_t me, neighbor;
  Parser reader(filename);

  while( reader.getRow(me, neighbor) != STOP )
  {
    if( graphDupl->insert(me, neighbor) == true ) {
      graphOut->insert(me, neighbor);
      graphIn->insert(neighbor, me);
    }
    else stats.duplicates++;
  }
  //cout << "\n" << reader.getCount() << "\n";
}


void runQueries(Graph<Node> *graphOut, Graph<Node> *graphIn, Graph<HashNode> *graphDupl, string filename)
{
  Scheduler taskManager(graphOut, graphIn, 2);
  Job newJob;
  Parser reader(filename);
  Writer output("results.txt");
  int oldType=-1;

  while( ( newJob.type = reader.getQuery(newJob.me, newJob.neighbor) ) != STOP ) {
    //reader.printQuery(type, me, neighbor);
    if(newJob.type == QUESTION) {
      stats.Query();
      newJob.version = graphOut->getVersion();
      taskManager.Assign(newJob);
    }
    else if(newJob.type == INSERTION) {
      stats.Insertion();
      if( graphDupl->insert(newJob.me, newJob.neighbor) == true ) {
        if(oldType == QUESTION) {
          graphOut->changeVersion();
          graphIn->changeVersion();
        }
        graphOut->insert(newJob.me, newJob.neighbor);
        graphIn->insert(newJob.neighbor, newJob.me);
      }
      else stats.duplicatesQA++;
    }
    else if(newJob.type == GUST) {
      stats.Gust();

      // Ensure that all workers are blocked
      taskManager.LockWorkers();
        taskManager.WakeAll();
      taskManager.UnlockWorkers();

      taskManager.Wait();

      taskManager.WriteResults(output);

      taskManager.Init();
    }
    oldType = newJob.type;
  }
  cout << "\nAll queries are finished!\n";
  
  // Ensure that all workers are blocked
  taskManager.LockWorkers();
      taskManager.StopAll();
      taskManager.WakeAll();
  taskManager.UnlockWorkers();
}


void runQueries2(Graph<Node> *graphOut, Graph<Node> *graphIn, Graph<HashNode> *graphDupl, string filename)
{
  int type;
  uint32_t me, neighbor;
  Parser reader(filename);
  Writer output("results.txt");

  Search search(graphOut, graphIn);
  int result;

  int version=0;

  while( ( type = reader.getQuery(me, neighbor) ) != STOP ) {
    //reader.printQuery(type, me, neighbor);
    if(type == QUESTION) {
      stats.Query();
      result = search.ShortestPath(me, neighbor, version);
      output.writeInt(result);
    }
    else if(type == INSERTION) {
      stats.Insertion();
      if( graphDupl->insert(me, neighbor) == true ) {
        graphOut->insert(me, neighbor);
        graphIn->insert(neighbor, me);
      }
      else stats.duplicatesQA++;
    }
  }
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
