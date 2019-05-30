#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ConfReader.hpp"
#include "ConfValue.hpp"
#include "Log.hpp"

using namespace obotcha;

int main() {
    printf("---[ConfReader Test Start]--- \n");
    ConfReader reader = createConfReader("simple.conf");
    //int parse();
    while(1) {
        int result = reader->parse();
        if(result < 0) {
          printf("---[ConfReader Test {parse()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[ConfReader Test {parse()} case2] [Success]--- \n");
        break;
    }

    //getAll();
#if 0
    while(1) {
      HashMap<String,String> map = reader->getAll();
      if(map->size()!= 3) {
        printf("---[ConfReader Test {getAll()} case1] [FAILED]--- \n");
        break;
      }

      String v1 = map->get("Desktop-Picture");
      if(!v1->contains("/usr/images/earth.jpg")) {
        printf("---[ConfReader Test {getAll()} case2] [FAILED]--- \n");
        break;
      }

      String v2 = map->get("Position");
      if(!v2->contains("Centered")) {
        printf("---[ConfReader Test {getAll()} case3] [FAILED]--- \n");
        break;
      }

      String v3 = map->get("Background Color");
      if(!v3->contains("Black")) {
        printf("---[ConfReader Test {getAll()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[ConfReader Test {getAll()} case5] [Success]--- \n");
      break;
    }
#endif
    //getConf(String);
    while(1) {
      String v1 = reader->get("Desktop-Picture");
      if(!v1->contains("/usr/images/earth.jpg")) {
        printf("---[ConfReader Test {getConf(String)} case2] [FAILED]--- \n");
        break;
      }

      String v2 = reader->get("Position");
      if(!v2->contains("Centered")) {
        printf("---[ConfReader Test {getConf(String)} case3] [FAILED]--- \n");
        break;
      }

      String v3 = reader->get("Background Color");
      if(!v3->contains("Black")) {
        printf("---[ConfReader Test {getConf(String)} case4] [FAILED]--- \n");
        break;
      }

      printf("---[ConfReader Test {getConf(String)} case5] [Success]--- \n");
      break;
    }

}
