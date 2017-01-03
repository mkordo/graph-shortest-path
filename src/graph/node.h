#ifndef NODE_H
#define NODE_H

#include <cstdint>    /* For uint32_t */

class Node
{
  public:
    uint32_t size;
    uint32_t current;
    uint32_t *version;
    uint32_t *neighbor;

    Node(uint32_t size_ = 100);
    ~Node();

    bool insert(uint32_t neighbor_, uint32_t version_);
    void print();

  private:
    void expand();
};

#endif
