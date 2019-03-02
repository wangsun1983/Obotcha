#include <stdio.h>
#include <unistd.h>

#include "Thread.hpp"
#include "HashMap.hpp"
#include "Integer.hpp"
#include "String.hpp"


DECLARE_SIMPLE_CLASS(TT1) {
  int i;
};

DECLARE_SIMPLE_CLASS(TT2) {
  int i;
};

int main() {

    printf("---[HashMap Test Start]--- \n");
    {
        HashMap<Integer,Integer> map = createHashMap<Integer,Integer>();
        Integer tag = createInteger(1);
        map->put(tag,createInteger(100));

        Integer tag2 = createInteger(1);
        Integer v = map->get(tag2);
        if(v == nullptr) {
          printf("not fine \n");
        } else {
          int value = map->get(tag2)->toValue();
          printf("value is %d \n",value);
        }
    }

    {
        HashMap<String,String> map = createHashMap<String,String>();
        String tag1 = "a1";
        String value1 = "v1";
        map->put(tag1,value1);

        String find1 = map->get(tag1);
        if(find1 == nullptr) {
          printf("null \n");
        } else {
          printf("find is %s \n",find1->toChars());
        }

        String tag2 = "a1";
        String find2 = map->get(tag2);
        if(find2 == nullptr) {
          printf("find2 is null \n");
        } else {
          printf("find2 is %s \n",find2->toChars());
        }
    }


}
