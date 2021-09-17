#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Integer.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"

using namespace obotcha;


DECLARE_CLASS(ListItem1) {
public:
    int data1;
    long data2;
    DECLARE_REFLECT_FIELD(ListItem1,data1,data2)
};

void testHashMapList() {
    while(1) {
      HashMap<Integer,ArrayList<ListItem1>> map = createHashMap<Integer,ArrayList<ListItem1>>();

      ArrayList<ListItem1> list1 = createArrayList<ListItem1>();
      ListItem1 item1 = createListItem1();
      item1->data1 = 1;
      item1->data2 = 2;

      ListItem1 item2 = createListItem1();
      item2->data1 = 3;
      item2->data2 = 4;

      ListItem1 item3 = createListItem1();
      item3->data1 = 5;
      item3->data2 = 6;

      list1->add(item1);
      list1->add(item2);
      list1->add(item3);

      ArrayList<ListItem1> list2 = createArrayList<ListItem1>();
      ListItem1 item2_1 = createListItem1();
      item2_1->data1 = 11;
      item2_1->data2 = 21;

      ListItem1 item2_2 = createListItem1();
      item2_2->data1 = 31;
      item2_2->data2 = 41;

      ListItem1 item2_3 = createListItem1();
      item2_3->data1 = 51;
      item2_3->data2 = 61;

      list2->add(item2_1);
      list2->add(item2_2);
      list2->add(item2_3);

      map->put(createInteger(0),list1);
      map->put(createInteger(1),list2);

      JsonWriter writer = createJsonWriter("./tmp/hashmap_list_test1.json");
      JsonValue value = createJsonValue();
      value->importFrom(map);
      writer->write(value);

      JsonReader reader = createJsonReader(createFile("./tmp/hashmap_list_test1.json"));
      JsonValue value2 = reader->get();

      HashMap<Integer,ArrayList<ListItem1>> map2 = createHashMap<Integer,ArrayList<ListItem1>>();
      value2->reflectTo(map2);

      if(map2->size() != 2) {
        printf("---[JsonReflect HashMap List Test case1] [FAILED]--- \n");
        break;
      }

      auto l1 = map2->get(createInteger(0));
      if(l1->size() != 3) {
        printf("---[JsonReflect HashMap List Test case2] [FAILED],size is %d--- \n",l1->size());
        printf("data1 is %d,data2 is %d",l1->get(0)->data1,l1->get(1)->data1);
        break;
      }

      if(l1->get(0)->data1 != 1 ||l1->get(0)->data2 != 2) {
        printf("---[JsonReflect HashMap List Test case3] [FAILED]--- \n");
        break;
      }

      if(l1->get(1)->data1 != 3 ||l1->get(1)->data2 != 4) {
        printf("---[JsonReflect HashMap List Test case4] [FAILED]--- \n");
        break;
      }

      if(l1->get(2)->data1 != 5 ||l1->get(2)->data2 != 6) {
        printf("---[JsonReflect HashMap List Test case5] [FAILED]--- \n");
        break;
      }

      auto l2 = map2->get(createInteger(1));
      if(l2->size() != 3) {
        printf("---[JsonReflect HashMap List Test case6] [FAILED]--- \n");
        break;
      }

      if(l2->get(0)->data1 != 11 ||l2->get(0)->data2 != 21) {
        printf("---[JsonReflect HashMap List Test case7] [FAILED]--- \n");
        break;
      }

      if(l2->get(1)->data1 != 31 ||l2->get(1)->data2 != 41) {
        printf("---[JsonReflect HashMap List Test case8] [FAILED]--- \n");
        break;
      }

      if(l2->get(2)->data1 != 51 ||l2->get(2)->data2 != 61) {
        printf("---[JsonReflect HashMap List Test case9] [FAILED]--- \n");
        break;
      }
      break;
    }

    printf("---[JsonReflect HashMap List Test case100] [OK]--- \n");
}
