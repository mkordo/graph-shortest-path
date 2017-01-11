#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "job.h"
#include "scheduler.h"

using namespace std;

template <class T>
Scheduler<T>::Scheduler()
{

}

template <class T>
Scheduler<T>::~Scheduler()
{

}



/* Inform the compiler about which types we are going to use the template */
template class Scheduler<int>;