#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <cstdint>  /* For uint32_t */
#include <fstream>

enum { QUESTION, INSERTION, GUST, STOP };

class Parser
{
  private:
    std::ifstream file;
    std::string filename;
    uint32_t count;

  public:

    Parser(std::string);
    ~Parser();

    int getRow(uint32_t&, uint32_t&);
    int getQuery(uint32_t&, uint32_t&);
    uint32_t getCount();
    void printRow(uint32_t, uint32_t);
    void printQuery(int, uint32_t, uint32_t);
};

#endif
