#include <stdio.h>
#include <unistd.h>

#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

using namespace obotcha;

#include <thread>
#include <atomic>
#include <iostream>
#include <list>

using namespace std;

Atomic<int> iCount(0);
//int iCount = 0;
#if 0
void threadfun1()
{
    for(int i =0; i< 1000; i++)
    {
      //printf("1111d\r\n");
      iCount++;
    }    
}
void threadfun2()
{
    for(int i =0; i< 1000; i++)
    {
      //printf("2222d\r\n");
      iCount--;
    }    
}

int main()
{
    std::list<thread> lstThread;
    for (int i=0; i< 100; i++)
    {
        lstThread.push_back(thread(threadfun1));
    }
    for (int i=0; i< 100; i++)
    {
        lstThread.push_back(thread(threadfun2));
    }
    
    for (auto& th: lstThread)
    {
        th.join();
    }

    //printf("finally iCount:%d\r\n",  iCount);
    //int x = iCount.load(memory_order_relaxed);
    printf("finally iCount:%d\r\n",  iCount.get());
}
#endif


int main() {
/*    
    Atomic<int> v;
    v = 100;
    printf("v is %d \n",v.get());
    v++;
    printf("101, v is %d \n",v->get());

    v = 1;
    v +=2;
    printf("3, v is %d \n",v->get());

    v = 1;
    v -= 1;
    printf("0, v is %d \n",v->get());

    v = 100;
    v = v -2;
    printf("98,v is %d \n",v->get());

    Atomic<int> v1 = 100;
    if(v1 != 100) {
        printf("it is error1 \n");
    } else {
        printf("it is ok1 \n");
    }

    if(v1 == 100) {
        printf("it is ok2 \n");
    } else {
        printf("it is error2");
    }

    Atomic<int> v3 = 100;
    Atomic<int> v4 = 123;

    v3 = v4;
    printf("v3 is %d \n",v3->get());
*/
    std::atomic<int> value(100);
    int exp = 3;
    if(value.compare_exchange_strong(exp,2)) {
        printf("this is %d \n",value.load(std::memory_order_relaxed));
    } 

    printf("2 this is %d \n",value.load(std::memory_order_relaxed));
}
