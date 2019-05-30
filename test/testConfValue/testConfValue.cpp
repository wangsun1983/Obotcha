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
    int result = reader->parse();
    //ConfValue(String);
    while(1) {
      ConfIterator iterator = reader->get()->getIterator();
      HashMap<String,String> mHashMap = createHashMap<String,String>();
      while(iterator->hasValue()) {
          mHashMap->put(iterator->getTag(),iterator->getValue());
          iterator->next();
      }
      String v1 = reader->get("Desktop-Picture");
      if(!v1->contains("/usr/images/earth.jpg")) {
        printf("---[ConfValue Test {getValue()/next()} case2] [FAILED]--- \n");
        break;
      }

      String v2 = reader->get("Position");
      if(!v2->contains("Centered")) {
        printf("---[ConfValue Test {getValue()/next()} case3] [FAILED]--- \n");
        break;
      }

      String v3 = reader->get("Background Color");
      if(!v3->contains("Black")) {
        printf("---[ConfValue Test {getValue()/next()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[ConfValue Test {getValue()/next()} case5] [Success]--- \n");
      break;
    }

}
