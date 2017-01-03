#include <iostream>
#include <sstream>

#include "parser.h"

using namespace std;

Parser::Parser(string filename_)
{
  filename = filename_;
  file.open(filename);
  count=0;
}

Parser::~Parser()
{
  file.close();
}

int Parser::getRow(uint32_t &me, uint32_t &neighbor)
{
  string line;
  if (getline(file, line))
  {
      if(line[0]=='S') { return STOP; }
      istringstream iss(line);
      if (!(iss >> me >> neighbor)) { return STOP; } // error

      count++;
      return INSERTION;
  }
  return STOP;
}

int Parser::getQuery(uint32_t &me, uint32_t &neighbor)
{
  string line;
  string action;
  if (getline(file, line))
  {
      //cout << line << endl;
      if(line[0]=='F') { count++; return GUST; }
      istringstream iss(line);
      if (!(iss >> action >> me >> neighbor)) { return STOP; } // error
      count++;
      if(action[0]=='Q') return QUESTION;
      else if(action[0]=='A') return INSERTION;
      else { cerr << "Parser: Invalid action given\n"; }
  }
  return STOP;
}

void Parser::printRow(uint32_t me, uint32_t neighbor)
{
  cout << me << " " << neighbor << endl;
}

void Parser::printQuery(int type, uint32_t me, uint32_t neighbor)
{
  if(type==GUST) { cout << "F\n"; return; }
  else if(type == INSERTION) cout << "A ";
  else if(type == QUESTION) cout << "Q ";

  cout << me << " " << neighbor << endl;
}

uint32_t Parser::getCount()
{
  return count;
}
