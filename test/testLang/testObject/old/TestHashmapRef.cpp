#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyHashmapKey) {
public:
    int value;
};

DECLARE_SIMPLE_CLASS(MyHashmapValue) {
public:
    int value;
};

HashMap<MyHashmapKey,MyHashmapValue> map = createHashMap<MyHashmapKey,MyHashmapValue>();

static void dataUpdate(const MyHashmapKey &key,const MyHashmapValue &value) {
	printf("func1 key count is %d,value count is %d \n",key->getStrongCount(),value->getStrongCount());
  map->put(key,value);
  printf("func2 key count is %d,value count is %d \n",key->getStrongCount(),value->getStrongCount());
}


int testObjectHashmapRef() {
    MyHashmapKey key = createMyHashmapKey();
    MyHashmapValue value = createMyHashmapValue();
    printf("main1 key count is %d,value count is %d \n",key->getStrongCount(),value->getStrongCount());
    dataUpdate(key,value);
    printf("main2 key count is %d,value count is %d \n",key->getStrongCount(),value->getStrongCount());

    MyHashmapValue v = map->get(key);
    printf("main3 key count is %d,value count is %d \n",key->getStrongCount(),value->getStrongCount());
}
