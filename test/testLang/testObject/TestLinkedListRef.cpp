#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "LinkedList.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyLinkedDataRef) {
public:
    int value;
};

static LinkedList<MyLinkedDataRef> refList = createLinkedList<MyLinkedDataRef>();

static void dataUpdate(const MyLinkedDataRef &data) {
	printf("data count1 is %d \n",data->getStrongCount());
	refList->enQueueLast(data);
	printf("data count2 is %d \n",data->getStrongCount());
}


int testObjectLinkedListRef() {

  while(1) {
    MyLinkedDataRef ref = createMyLinkedDataRef();
  	printf("main,ref count1 is %d \n",ref->getStrongCount());
  	//dataUpdate(createMyArrayDataRef());
    dataUpdate(ref);
  	printf("main,ref count2 is %d \n",ref->getStrongCount());

   {
    MyLinkedDataRef ref3 = refList->deQueueLast();
    printf("main,ref count4 is %d \n",ref->getStrongCount());
   }

   printf("main,ref count5 is %d \n",ref->getStrongCount());
   break;
 }
}
