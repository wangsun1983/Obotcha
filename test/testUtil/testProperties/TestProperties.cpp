#include <stdio.h>
#include <unistd.h>

#include "Properties.hpp"

using namespace obotcha;

int main() {

    printf("---[Properties Test Start]--- \n");
    Properties props = createProperties();
    //void set(String key,String value);
    while(1) {
      String tag = "tag1";
      String v1 = props->get(tag);
      String val = "val1";
      props->set(tag,val);
      String v2 = props->get(tag);
      if(v1 != nullptr || v2 == nullptr) {
        printf("---[Properties Test {set(String key,String value)} case1] [FAILED]--- \n");
        break;
      }

      if(!v2->equals("val1")) {
        printf("---[Properties Test {set(String key,String value)} case2] [FAILED]--- \n");
        break;
      }

      props->set(tag,nullptr);
      String v3 = props->get(tag);
      if(v3 != nullptr) {
        printf("---[Properties Test {set(String key,String value)} case3] [FAILED]--- \n");
        break;
      }
      printf("---[Properties Test {set(String key,String value)} case4] [OK]--- \n");
      break;
    }

    //String get(String key);
    while(1) {
      props->set("tag1","val1");

      String v1 = props->get("aabb");
      if(v1 != nullptr) {
        printf("---[Properties Test {get(String key)} case1] [FAILED]--- \n");
        break;
      }

      String v2 = props->get("tag1");
      if(v2 == nullptr || !v2->equals("val1")) {
        printf("---[Properties Test {get(String key)} case2] [FAILED]--- \n");
        break;
      }

      printf("---[Properties Test {get(String key)} case3] [OK]--- \n");
      break;
    }

    //void remove(String key);
    while(1) {
      props->set("tag1","val1");
      String v1 = props->get("aabb");
      if(v1 != nullptr) {
        printf("---[Properties Test {get(String key)} case1] [FAILED]--- \n");
        break;
      }

      String v2 = props->get("tag1");
      if(v2 == nullptr || !v2->equals("val1")) {
        printf("---[Properties Test {get(String key)} case2] [FAILED]--- \n");
        break;
      }

      printf("---[Properties Test {get(String key)} case3] [OK]--- \n");
      break;
    }

    //void load(File file);
    while(1) {
      Properties props2 = createProperties();
      int ret = props2->load(createString("preload.txt"));
      String value1 = props2->get("value1");
      if(value1 == nullptr || !value1->equals("100")) {
          if(value1 != nullptr) {
            printf("value1 is %s \n",value1->toChars());
          }
          printf("---[Properties Test {load(File file)} case1] [FAILED]--- \n");
          break;
      }

      String value2 = props2->get("value2");
      if(value2 == nullptr || !value2->equals("200")) {
          printf("---[Properties Test {load(File file)} case2] [FAILED]--- \n");
          break;
      }

      printf("---[Properties Test {load(File file)} case3] [OK]--- \n");
      break;
    }

    //void save(File file);
    while(1) {
      Properties props3 = createProperties();
      props3->set("m1","m1value");
      props3->set("m2","m2value");
      props3->saveAs(createString("save.txt"));

      Properties props4 = createProperties();
      props4->load(createString("save.txt"));
      String value2 = props4->get("m1");
      if(value2 == nullptr || !value2->equals("m1value")) {
        printf("---[Properties Test {load(File file)} case1] [FAILED]--- \n");
        break;
      }

      printf("---[Properties Test {load(File file)} case2] [OK]--- \n");
      break;
    }

    printf("---[Properties Test {load(File file)} case2] [OK]--- \n");
}
