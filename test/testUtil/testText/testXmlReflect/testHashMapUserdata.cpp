#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Uint8.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Uint8.hpp"
#include "XmlDocument.hpp"
#include "XmlReader.hpp"
#include "XmlWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(MapUserData) {
public:
  int data1;
  long data2;
  DECLARE_REFLECT_FIELD(MapUserData,data1,data2)
};

void testHashMapUserdata() {
    while(1) {
      HashMap<Integer,MapUserData> maps = createHashMap<Integer,MapUserData>();
      MapUserData d1 = createMapUserData();
      d1->data1 = 1;
      d1->data2 = 2;

      MapUserData d2 = createMapUserData();
      d2->data1 = 3;
      d2->data2 = 4;

      MapUserData d3 = createMapUserData();
      d3->data1 = 5;
      d3->data2 = 6;

      maps->put(createInteger(1),d1);
      maps->put(createInteger(2),d2);
      maps->put(createInteger(3),d3);

      XmlDocument doc = createXmlDocument();
      doc->importFrom(maps);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/hashmap_userdata_test1.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/hashmap_userdata_test1.xml"));
      XmlDocument doc2 = reader->get();

      HashMap<Integer,MapUserData> maps2 = createHashMap<Integer,MapUserData>();
      doc2->reflectTo(maps2);
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap UserData Test case1] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createInteger(1));
      if(v1 == nullptr || v1->data1 != 1 || v1->data2 != 2) {
        printf("---[JsonReflect HashMap UserData Test case2] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createInteger(2));
      if(v2 == nullptr || v2->data1 != 3 || v2->data2 != 4) {
        printf("---[JsonReflect HashMap UserData Test case3] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createInteger(3));
      if(v3 == nullptr || v3->data1 != 5 || v3->data2 != 6) {
        printf("---[JsonReflect HashMap UserData Test case4] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[JsonReflect HashMap UserData Test case100] [OK]--- \n");
}
