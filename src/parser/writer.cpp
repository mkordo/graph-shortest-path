#include <iostream>
#include <sstream>

#include "writer.h"

using namespace std;

Writer::Writer(string filename_)
{
  filename = filename_;
  file.open(filename);
  if(file.is_open() == false) cerr << "File: " << filename << " did not open...\n";
}

Writer::~Writer()
{
  file.close();
}

void Writer::writeInt(int result)
{
  file << result << "\n";
}

void Writer::writeStr(string str)
{
  file << str << "\n";
}