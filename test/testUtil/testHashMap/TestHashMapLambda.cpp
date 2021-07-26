#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(Lambda1) {
public:
  int i;
};

void testHashMapLambda() {
  HashMap<int,Lambda1> map = createHashMap<int,Lambda1>();
  Lambda1 t1 = createLambda1();
  t1->i = 123;

  Lambda1 t2 = createLambda1();
  t2->i = 456;

  Lambda1 t3 = createLambda1();
  t3->i = 789;

  map->put(1,t1);
  map->put(2,t2);
  map->put(3,t3);

  map->foreach([](int key,Lambda1 value) {
    printf("key is %d,value is %d \n",key,value->i);
    return 1;
  });
}
