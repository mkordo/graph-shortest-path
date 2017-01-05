#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <fstream>

class Writer
{
  private:
    std::ofstream file;
    std::string filename;

  public:

    Writer(std::string);
    ~Writer();

    void writeInt(int);
    void writeStr(std::string);
};

#endif
