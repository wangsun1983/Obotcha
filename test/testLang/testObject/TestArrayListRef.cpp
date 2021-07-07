#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyArrayDataRef) {
public:
    int value;
};

ArrayList<MyArrayDataRef> refList = createArrayList<MyArrayDataRef>();

void dataUpdate(const MyArrayDataRef &data) {
	printf("data count1 is %d \n",data->getStrongCount());
	refList->add(data);
	printf("data count2 is %d \n",data->getStrongCount());
}


int testObjectArrayListRef() {
#if 0
  while(1) {
    MyArrayDataRef ref = createMyArrayDataRef();
  	printf("main,ref count1 is %d \n",ref->getStrongCount());
  	//dataUpdate(createMyArrayDataRef());
    dataUpdate(ref);
  	printf("main,ref count2 is %d \n",ref->getStrongCount());

   {
    MyArrayDataRef ref3 = refList->get(0);
    printf("main,ref count4 is %d \n",ref->getStrongCount());
   }

   printf("main,ref count5 is %d \n",ref->getStrongCount());
   break;
 }
#endif

 while(1) {
   ArrayList<int> intList = createArrayList<int>();
   intList->add(123);

   int v = intList->get(0);
   printf("main,v is %d \n",v);
   break;
 }
  //printf("main,ref value3 is %d \n",ref3->value);
}
