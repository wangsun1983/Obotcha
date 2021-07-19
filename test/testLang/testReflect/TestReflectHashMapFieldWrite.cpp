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

DECLARE_SIMPLE_CLASS(HashMapValue) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(HashMapValue,data1,data2)
};

DECLARE_SIMPLE_CLASS(Container) {
public:
  HashMap<String,HashMapValue> map;
  DECLARE_REFLECT_FIELD(Container,map)
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

    //
    JsonReader reader = createJsonReader(createFile("output_hashmap_1.json"));
    JsonValue readValue = reader->get();

    Container rdata3 = createContainer();
    readValue->reflectTo(rdata3);

    printf("read value size is %d \n",rdata3->map->size());

}
