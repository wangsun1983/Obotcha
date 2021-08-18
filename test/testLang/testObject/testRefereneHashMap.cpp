#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "HashMap<String,HashMapData>.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"

using namespace obotcha;

DECLARE_CLASS(HashMapData) {
public:
  int i;
};

DECLARE_CLASS(HashMapData2) IMPLEMENTS(HashMapData) {
public:
  int j;
};

int testReferenceHashMap() {
  //case 1
  while(1) {
    HashMapData ref = createHashMapData();
    HashMap<String,HashMapData> list = createHashMap<String,HashMapData>();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceHashMap<String,HashMapData>Count test1-------[FAIL] \n");
      break;
    }

    list->put(createString("tag"),ref);
    if(ref->getStrongCount() != 2) {
      printf("Object ReferenceHashMap<String,HashMapData>Count test2-------[FAIL] \n");
      break;
    }

    list->clear();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceHashMap<String,HashMapData>Count test3-------[FAIL] \n");
      break;
    }

    break;
  }

  //case 1
  while(1) {
    HashMapData2 ref = createHashMapData2();
    HashMap<String,HashMapData> list = createHashMap<String,HashMapData>();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceHashMap<String,HashMapData>Count test4-------[FAIL] \n");
      break;
    }

    list->put(createString("tag"),Cast<HashMapData>(ref));
    if(ref->getStrongCount() != 2) {
      printf("Object ReferenceHashMap<String,HashMapData>Count test5-------[FAIL] \n");
      break;
    }

    list->clear();
    if(ref->getStrongCount() != 1) {
      printf("Object ReferenceHashMap<String,HashMapData>Count test6-------[FAIL] \n");
      break;
    }

    break;
  }


  printf("Object ReferenceHashMap<String,HashMapData>Count test100-------[OK] \n");
  return 0;
}
