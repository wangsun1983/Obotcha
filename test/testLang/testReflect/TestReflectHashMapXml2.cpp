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
#include "XmlWriter.hpp"
#include "XmlDocument.hpp"

using namespace obotcha;

DECLARE_CLASS(HashMapXmlValue2) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(HashMapXmlValue2,data1,data2)
};

DECLARE_CLASS(XmlReflectData2) {
public:
  HashMap<String,HashMap<String,HashMapXmlValue2>> map;
  DECLARE_REFLECT_FIELD(XmlReflectData2,map)
};

void testReflectHashMapXml2() {
  //test1
  while(1) {
    XmlReflectData2 data2 = createXmlReflectData2();
    data2->map = createHashMap<String,HashMap<String,HashMapXmlValue2>>();

    HashMap<String,HashMapXmlValue2> maps = createHashMap<String,HashMapXmlValue2>();
    HashMapXmlValue2 value1 = createHashMapXmlValue2();
    value1->data1 = 1;
    value1->data2 = 2;

    HashMapXmlValue2 value2 = createHashMapXmlValue2();
    value2->data1 = 3;
    value2->data2 = 4;

    HashMapXmlValue2 value3 = createHashMapXmlValue2();
    value3->data1 = 5;
    value3->data2 = 6;

    maps->put(createString("tag1"),value1);
    maps->put(createString("tag2"),value2);
    maps->put(createString("tag3"),value3);

    HashMap<String,HashMapXmlValue2> maps2 = createHashMap<String,HashMapXmlValue2>();
    maps2->put(createString("tag2"),value2);
    maps2->put(createString("tag3"),value3);

    data2->map->put(createString("content1"),maps);
    data2->map->put(createString("content2"),maps2);

    XmlDocument doc = createXmlDocument();
    doc->importFrom(data2);
    XmlWriter writer = createXmlWriter(doc);
    writer->write("output_xml_5.xml");

    XmlDocument doc1 = createXmlDocument("output_xml_5.xml");
    XmlReflectData2 data3 = createXmlReflectData2();
    doc1->reflectTo(data3);
    if(data3->map == nullptr || data3->map->size() != 2) {
      printf("ReflectHashMapXml2 test2-------[FAIL] \n");
      break;
    }

    HashMap<String,HashMapXmlValue2> map3_1 = data3->map->get(createString("content1"));
    if(map3_1 == nullptr || map3_1->size() != 3) {
      printf("ReflectHashMapXml2 test3-------[FAIL],map3_1 size is %d \n",map3_1->size());
      break;
    }

    HashMapXmlValue2 value3_1 = map3_1->get(createString("tag1"));
    if(value3_1 == nullptr || value3_1->data1 != 1 || value3_1->data2 != 2) {
      printf("ReflectHashMapXml2 test3_1-------[FAIL] \n");
      break;
    }

    HashMapXmlValue2 value3_2 = map3_1->get(createString("tag2"));
    if(value3_2 == nullptr || value3_2->data1 != 3 || value3_2->data2 != 4) {
      printf("ReflectHashMapXml2 test4-------[FAIL] \n");
      break;
    }

    HashMapXmlValue2 value3_3 = map3_1->get(createString("tag3"));
    if(value3_3 == nullptr || value3_3->data1 != 5 || value3_3->data2 != 6) {
      printf("ReflectHashMapXml2 test5-------[FAIL] \n");
      break;
    }

    HashMap<String,HashMapXmlValue2> map3_2 = data3->map->get(createString("content2"));
    if(map3_2 == nullptr || map3_2->size() != 2) {
      printf("ReflectHashMapXml2 test6-------[FAIL] \n");
      break;
    }

    HashMapXmlValue2 value4_1 = map3_2->get(createString("tag2"));
    if(value4_1 == nullptr || value4_1->data1 != 3 || value4_1->data2 != 4) {
      printf("ReflectHashMapXml2 test7-------[FAIL],data1 is %d,data2 is %d \n",value4_1->data1,value4_1->data2);
      break;
    }

    HashMapXmlValue2 value4_2 = map3_2->get(createString("tag3"));
    if(value4_2 == nullptr || value4_2->data1 != 5 || value4_2->data2 != 6) {
      printf("ReflectHashMapXml2 test8-------[FAIL] \n");
      break;
    }

    printf("ReflectHashMapXml2 test100-------[OK] \n");
    break;
  }
}
