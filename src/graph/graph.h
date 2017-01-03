#ifndef GRAPH_H
#define GRAPH_H

template <class T>
class Graph
{
  public:
    uint32_t version;
    uint32_t size;
    uint32_t last;
    T* *buffer;

    Graph(uint32_t size_ = 100);
    ~Graph();

    bool insert(uint32_t, uint32_t);
    void print();

  private:
    void expand(uint32_t);
};

#endif
