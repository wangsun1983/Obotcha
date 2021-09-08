#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "ConfReader.hpp"
#include "Log.hpp"

using namespace obotcha;

void testConfIterator() {
    printf("---[ConfIterator Test Start]--- \n");
    ConfReader reader = createConfReader("simple.conf");
    //ConfIterator(String);
    while(1) {
      ConfIterator iterator = reader->getIterator();
      HashMap<String,String> mHashMap = createHashMap<String,String>();
      while(iterator->hasValue()) {
          mHashMap->put(iterator->getTag(),iterator->getValue());
          iterator->next();
      }

      if(mHashMap->size() != 4) {
          printf("---[ConfIterator Test {getValue()/next()} case1] [FAILED]---,mHashMap size is %d \n",mHashMap->size());
          break;
      }

      String v1 = mHashMap->get(createString("Desktop-Picture"));
      if(!v1->equals("/usr/images/earth.jpg")) {
        printf("---[ConfIterator Test {getValue()/next()} case2] [FAILED]--- \n");
        break;
      }

      String v2 = mHashMap->get(createString("Position"));
      if(!v2->equals("Centered")) {
        printf("---[ConfIterator Test {getValue()/next()} case3] [FAILED]--- \n");
        break;
      }

      String v3 = mHashMap->get(createString("Background Color"));
      if(!v3->equals("Black")) {
        printf("---[ConfIterator Test {getValue()/next()} case4] [FAILED]--- \n");
        break;
      }

      String v4 = mHashMap->get(createString("NULL"));
      if(v4->size() != 0) {
        printf("---[ConfIterator Test {getValue()/next()} case5] [FAILED]--- \n");
        break;
      }

      printf("---[ConfIterator Test {getValue()/next()} case100] [OK]--- \n");
      break;
    }

}
