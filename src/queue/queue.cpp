#include <iostream>
#include <stdlib.h>
#include <process.h>

#include "queue.h"
/*
using namespace std;

template <class T>
bool Queue<T>::isEmpty()
{
  if( (front==0 && rear==-1) || front==rear )
    return true;
  else
    return false;
}

template <class T>
bool Queue<T>::isFull()
{
  if(rear==size-1)
    return true;
  else
    return false;
}

template <class T>
void Queue<T>::atFront()
{
  if(isEmpty())
     cout << "Sorry the queue is empty!\n";
  else
     cout << "Front element of the queue is : " << queue[front] << "\n";
}

template <class T>
void Queue<T>::atRear()
{
  if(isEmpty())
     cout << "Sorry the queue is empty!\n";
  else
     cout << "Rear element of the queue is : " << queue[rear] << "\n";
}

template <class T>
void Queue<T>::insert()
{
  T ele;
  if(isFull())
    cout << "Sorry the queue is full!\n";
  else
  {
    cin >> ele;
    queue[++rear]=ele;
  }
}

template <class T>
void Queue<T>::deletion()
{
  if(isEmpty())
     cout<<"\nSorry the queue is empty!";
  else
     cout<<"\nDeleted element of the queue is : " << queue[front++];
}

template <class T>
void Queue<T>::display()
{
     if(isEmpty())
     cout<<"\nSorry the queue is empty!";
     else
     {
         cout<<"\nQueue elements are : ";
         for(int i=front;i<=rear;i++)
         {
                 cout<<"\t"<<queue[i];
         }
     }
}

int test()
{
    int ch;
    Queue<int> q(10);
    do
    {
             cout<<"\n 1.Insertion \n 2.Deletion \n 3.Display Front Element \n 4.Display Rear Element \n 5.Display Queue \n 6.Exit \n";
             cout<<"Enter your Choice:";
             cin>>ch;
             switch(ch)
             {
                       case 1:
                            q.insert();
                            break;
                       case 2:
                            q.deletion();
                            break;
                       case 3:
                            q.atfront();
                            break;
                       case 4:
                            q.atrear();
                            break;
                       case 5:
                            q.display();
                            break;
                       case 6:
                            exit(0);
                            break;
                       default: cout<<"\nWrong Choice Entered!";

             }
    }while(ch<=6);
    system("pause");
    return 0;
}
*/
