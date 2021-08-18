#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <type_traits>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Reflect.hpp"
#include "String.hpp"
#include "Math.hpp"
#include "Field.hpp"
#include "HashMap.hpp"
#include "OStdInstanceOf.hpp"
#include "JsonValue.hpp"
#include "JsonWriter.hpp"
#include "JsonReader.hpp"

using namespace obotcha;

DECLARE_CLASS(HashMapValue) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(HashMapValue,data1,data2)
};

DECLARE_CLASS(Container) {
public:
  HashMap<String,HashMapValue> map;
  DECLARE_REFLECT_FIELD(Container,map)
};

DECLARE_CLASS(ContainerLists) {
public:
  ArrayList<HashMap<String,HashMapValue>> lists;
  DECLARE_REFLECT_FIELD(ContainerLists,lists)
};

int testReflectHashMapFieldWrite() {
#if 0
    //case1
    Container data1 = createContainer();
    Field f = data1->getField("map");
    f->createObject();

    if(data1->map == nullptr) {
      printf("create map failed \n");
    } else {
      printf("create map success \n");
    }

    KeyValuePair<Object,Object> data = f->createMapItemObject();
    if(data == nullptr) {
      printf("create object failed \n");
    } else {
      printf("create object success \n");
    }

    Object key = data->getKey();
    if(IsInstance(String,key)) {
      printf("key is a string \n");
      String str = Cast<String>(key);
      str->update("hello");
    } else {
      printf("key is not a string \n");
    }

    Object value = data->getValue();
    Field data1Field = value->getField("data1");
    data1Field->setValue(100);

    Field data2Field = value->getField("data2");
    data1Field->setValue(200);

    f->addMapItemObject(key,value);
    //TODO


    HashMapValue v = data1->map->get(createString("hello"));
    if(v == nullptr) {
      printf("v is null \n");
    }

    printf("v.data1 is %d,v.data2 is %d \n",v->data1,v->data2);
#endif
    //json update
    while(1) {
        Container c = createContainer();
        c->map = createHashMap<String,HashMapValue>();

        HashMapValue v1 = createHashMapValue();
        v1->data1 = 123;
        v1->data2 = 456;

        HashMapValue v2 = createHashMapValue();
        v2->data1 = 789;
        v2->data2 = 999;

        c->map->put(createString("tag1"),v1);
        c->map->put(createString("tag2"),v2);

        JsonValue jvalue = createJsonValue();
        jvalue->importFrom(c);

        JsonWriter jwriter = createJsonWriter("output_hashmap_1.json");
        jwriter->write(jvalue);

        JsonReader reader = createJsonReader(createFile("output_hashmap_1.json"));
        JsonValue readValue = reader->get();

        Container rdata3 = createContainer();
        readValue->reflectTo(rdata3);

        HashMapValue val1 = rdata3->map->get("tag1");
        if(val1 == nullptr) {
          printf("Reflect HashMap Write test1-------[FAIL] \n");
          break;
        }

        if(val1->data1 != 123 || val1->data2 != 456) {
          printf("Reflect HashMap Write test2-------[FAIL] \n");
          break;
        }

        HashMapValue val2 = rdata3->map->get("tag2");
        if(val2 == nullptr) {
          printf("Reflect HashMap Write test3-------[FAIL] \n");
          break;
        }

        if(val2->data1 != 789 || val2->data2 != 999) {
          printf("Reflect HashMap Write test4-------[FAIL] \n");
          break;
        }

        printf("Reflect HashMap Write test5-------[OK] \n");
        break;
    }

    //case2
    while(1) {
      ContainerLists ll = createContainerLists();
      ll->lists = createArrayList<HashMap<String,HashMapValue>>();
      HashMap<String,HashMapValue> map1 = createHashMap<String,HashMapValue>();
      HashMapValue vv1 = createHashMapValue();
      vv1->data1 = 1;
      vv1->data2 = 2;

      HashMapValue vv2 = createHashMapValue();
      vv2->data1 = 3;
      vv2->data2 = 4;

      map1->put(createString("T1"),vv1);
      map1->put(createString("T2"),vv2);
      ll->lists->add(map1);
      
      HashMap<String,HashMapValue> map2 = createHashMap<String,HashMapValue>();
      HashMapValue uu1 = createHashMapValue();
      uu1->data1 = 11;
      uu1->data2 = 12;

      HashMapValue uu2 = createHashMapValue();
      uu2->data1 = 13;
      uu2->data2 = 14;

      map2->put(createString("T1"),uu1);
      map2->put(createString("T2"),uu2);

      ll->lists->add(map2);
      JsonValue jvalue = createJsonValue();
      jvalue->importFrom(ll);

      JsonWriter jwriter = createJsonWriter("output_hashmap_2.json");
      jwriter->write(jvalue);

      JsonReader reader = createJsonReader(createFile("output_hashmap_2.json"));
      JsonValue readValue = reader->get();
      ContainerLists ll2 = createContainerLists();
      readValue->reflectTo(ll2);

      if(ll2 == nullptr) {
        printf("Reflect HashMap Write test6-------[FAIL] \n");
        break;
      }

      if(ll2->lists == nullptr) {
        printf("Reflect HashMap Write test7-------[FAIL] \n");
        break;
      }

      if(ll2->lists->size() != 2) {
        printf("Reflect HashMap Write test8-------[FAIL],ll2->lists->size() is %d \n",ll2->lists->size());
        break;
      }

      HashMap<String,HashMapValue> chkmap1 = ll2->lists->get(0);
      HashMapValue qq1 = chkmap1->get(createString("T1"));
      if(qq1 == nullptr || qq1->data1 != 1 ||qq1->data2 != 2) {
        printf("Reflect HashMap Write test9-------[FAIL] qq1->data1 is %d,qq1->data2 is %d\n",qq1->data1,qq1->data2);
        break;
      }

      HashMapValue qq2 = chkmap1->get(createString("T2"));
      if(qq2 == nullptr || qq2->data1 != 3 ||qq2->data2 != 4) {
        printf("Reflect HashMap Write test10-------[FAIL] \n");
        break;
      }

      HashMap<String,HashMapValue> chkmap2 = ll2->lists->get(1);
      HashMapValue tt1 = chkmap2->get(createString("T1"));
      if(tt1 == nullptr || tt1->data1 != 11 ||tt1->data2 != 12) {
        printf("Reflect HashMap Write test11-------[FAIL] \n");
        break;
      }

      HashMapValue tt2 = chkmap2->get(createString("T2"));
      if(tt2 == nullptr || tt2->data1 != 13 ||tt2->data2 != 14) {
        printf("Reflect HashMap Write test12-------[FAIL] \n");
        break;
      }

      printf("Reflect HashMap Write test13-------[OK] \n");
      break;
    }

}
