#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ConfReader.hpp"
#include "ConfValue.hpp"
#include "Log.hpp"

using namespace obotcha;

int main() {
    printf("---[ConfValue Test Start]--- \n");
    ConfReader reader = createConfReader("simple.conf");
    //ConfValue(String);
    while(1) {
      ConfIterator iterator = reader->get()->getIterator();
      HashMap<String,String> mHashMap = createHashMap<String,String>();
      while(iterator->hasValue()) {
          mHashMap->put(iterator->getTag(),iterator->getValue());
          iterator->next();
      }

      if(mHashMap->size() != 3) {
          printf("---[ConfValue Test {getValue()/next()} case1] [FAILED]--- \n");
          break;
      }

      String v1 = mHashMap->get("Desktop-Picture");
      if(!v1->equals("/usr/images/earth.jpg")) {
        printf("---[ConfValue Test {getValue()/next()} case2] [FAILED]--- \n");
        break;
      }

      String v2 = mHashMap->get("Position");
      if(!v2->equals("Centered")) {
        printf("---[ConfValue Test {getValue()/next()} case3] [FAILED]--- \n");
        break;
      }

      String v3 = mHashMap->get("Background Color");
      if(!v3->equals("Black")) {
        printf("---[ConfValue Test {getValue()/next()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[ConfValue Test {getValue()/next()} case5] [OK]--- \n");
      break;
    }

}
