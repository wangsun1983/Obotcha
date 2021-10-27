#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "String.hpp"

using namespace obotcha;

DECLARE_CLASS(HashMapOperatorData) {
public:
  int i;
  int j;
};

void testHashMapOperator() {
  while(1) {
    HashMap<String,HashMapOperatorData> map = createHashMap<String,HashMapOperatorData>();
    HashMapOperatorData data = createHashMapOperatorData();
    data->i = 100;
    data->j = 101;
    map->put(createString("bbb"),data);

    HashMapOperatorData data2 = map[createString("bbb")];

    if(data2 == nullptr) {
      printf("---[HashMap Operator Test case1] [FAILED]--- \n");
      break;
    }

    if(data2->i != 100 || data2->j != 101) {
      printf("---[HashMap Operator Test case2] [FAILED]--- \n");
      break;
    }

    printf("---[HashMap Operator Test case3] [OK]--- \n");
    break;
  }



}
