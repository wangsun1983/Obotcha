#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyTestRef) {
public:
    int value;
};

ArrayList<MyTestRef> list = createArrayList<MyTestRef>();

void dataUpdate(const MyTestRef &data) {
	printf("data count1 is %d \n",data->getStrongCount());
	list->add(data);
	printf("data count2 is %d \n",data->getStrongCount());
}


int testObjectRef() {
  MyTestRef ref = createMyTestRef();
	printf("main,ref count1 is %d \n",ref->getStrongCount());
	//dataUpdate(createMyTestRef());
  dataUpdate(ref);
	printf("main,ref count2 is %d \n",ref->getStrongCount());

 {
  MyTestRef ref3 = list->get(0);
  printf("main,ref count4 is %d \n",ref->getStrongCount());
 }

 printf("main,ref count5 is %d \n",ref->getStrongCount());
  //printf("main,ref value3 is %d \n",ref3->value);
}
