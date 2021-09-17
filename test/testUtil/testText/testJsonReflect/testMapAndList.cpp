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
#include "JsonReader.hpp"
#include "JsonWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(MapListTestData) {
public:
  int data1;
  long data2;
  DECLARE_REFLECT_FIELD(MapListTestData,data1,data2)
};

DECLARE_CLASS(MapListUserData) {
public:
  ArrayList<MapListTestData> lists;
  HashMap<String,MapListTestData> maps;
  DECLARE_REFLECT_FIELD(MapListUserData,lists,maps)
};

void testMapList() {
    while(1) {
      MapListUserData data = createMapListUserData();
      data->lists = createArrayList<MapListTestData>();
      MapListTestData t1 = createMapListTestData();
      t1->data1 = 1;
      t1->data2 = 2;

      MapListTestData t2 = createMapListTestData();
      t2->data1 = 3;
      t2->data2 = 4;

      MapListTestData t3 = createMapListTestData();
      t3->data1 = 5;
      t3->data2 = 6;
      data->lists->add(t1);
      data->lists->add(t2);
      data->lists->add(t3);

      auto maps = createHashMap<String,MapListTestData>();
      maps->put(createString("a"),t1);
      maps->put(createString("b"),t2);
      maps->put(createString("c"),t3);
      data->maps = maps;

      JsonWriter writer = createJsonWriter("./tmp/userdata_list_map_test2.json");
      JsonValue value = createJsonValue();
      value->importFrom(data);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/userdata_list_map_test2.json"));
      JsonValue value2 = reader->get();

      MapListUserData data2 = createMapListUserData();
      value2->reflectTo(data2);

      auto ll = data2->lists;
      if(ll == nullptr || ll->size() != 3) {
        printf("---[JsonReflect Map And List UserData Test case1] [FAILED]--- \n");
        break;
      }

      if(ll->get(0)->data1 != 1 || ll->get(0)->data2 != 2) {
        printf("---[JsonReflect Map And List UserData Test case2] [FAILED]--- \n");
        break;
      }

      if(ll->get(1)->data1 != 3 || ll->get(1)->data2 != 4) {
        printf("---[JsonReflect Map And List UserData Test case3] [FAILED]--- \n");
        break;
      }

      if(ll->get(2)->data1 != 5 || ll->get(2)->data2 != 6) {
        printf("---[JsonReflect Map And List UserData Test case4] [FAILED]--- \n");
        break;
      }

      auto mm = data2->maps;

      if(mm->size() != 3) {
        printf("---[JsonReflect Map And List UserData Test case5] [FAILED]--- \n");
        break;
      }

      if(mm->get("a") == nullptr ||mm->get("a")->data1 != 1 ||mm->get("a")->data2 != 2) {
        printf("---[JsonReflect Map And List UserData Test case6] [FAILED]--- \n");
        break;
      }

      if(mm->get("b") == nullptr ||mm->get("b")->data1 != 3 ||mm->get("b")->data2 != 4) {
        printf("---[JsonReflect Map And List UserData Test case7] [FAILED]--- \n");
        break;
      }

      if(mm->get("c") == nullptr ||mm->get("c")->data1 != 5 ||mm->get("c")->data2 != 6) {
        printf("---[JsonReflect Map And List UserData Test case8] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[JsonReflect HashMap UserData Test case100] [OK]--- \n");
}
