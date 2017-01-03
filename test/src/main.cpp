#include <iostream>
#include <cstdint>  /* For uint32_t */

#include "../../src/queue/queue.h"

using namespace std;

void testQueue();

int main(int argc, char** argv)
{
  testQueue();

  cout << "Ended test, exiting...\n";
  return 0;
}

void testQueue()
{
  int i;
  Queue<uint32_t> *test;

  test = new Queue<uint32_t>;
  delete test;

  test = new Queue<uint32_t>(10);

  for(i=0; i<10; i++) cout << "Poping: " << test->pop() << "\n";

  for(i=0; i<21; i++) test->push(i);

  for(i=0; i<10; i++) cout << "Poping: " << test->pop() << "\n";

  for(i=0; i<20; i++) cout << "Poping: " << test->pop() << "\n";

  test->print();

  delete test;
}