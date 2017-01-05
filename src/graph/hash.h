#ifndef HASH_H
#define HASH_H

#include <cstdint>    /* For uint32_t */

class HashNode
{
  public:
    uint32_t inserted;
    uint32_t size;
    uint32_t *neighbor;

    HashNode(uint32_t size_ = 103);
    ~HashNode();

    bool insert(uint32_t neighbor_, uint32_t version_);
    void print();
    void init(uint32_t size_ = 103);
    uint32_t getSize();

  private:
    bool findCell(uint32_t);
    void expand();
    void recreate();
    uint32_t hash(uint32_t);
    uint32_t primeNext(uint32_t);
};

#endif
