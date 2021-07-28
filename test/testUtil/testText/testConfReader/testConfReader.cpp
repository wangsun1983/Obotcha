#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ConfReader.hpp"
#include "ConfValue.hpp"
#include "Log.hpp"

using namespace obotcha;

int basetest() {
    printf("---[ConfReader Test Start]--- \n");
    ConfReader reader = createConfReader("simple.conf");

    //getConf(String);
    while(1) {
      String v1 = reader->get("Desktop-Picture");
      if(!v1->equals("/usr/images/earth.jpg")) {
        printf("---[ConfReader Test {getConf(String)} case2] [FAILED]--- \n");
        break;
      }

      String v2 = reader->get("Position");
      if(!v2->equals("Centered")) {
        printf("---[ConfReader Test {getConf(String)} case3] [FAILED]--- \n");
        break;
      }

      String v3 = reader->get("Background Color");
      if(!v3->equals("Black")) {
        printf("---[ConfReader Test {getConf(String)} case4] [FAILED]--- \n");
        break;
      }

      String v4 = reader->get("NULL");
      if(v4 != nullptr) {
        printf("---[ConfReader Test {getConf(String)} case5] [FAILED]--- \n");
        break;
      }

      printf("---[ConfReader Test {getConf(String)} case6] [Success]--- \n");
      break;
    }

}
