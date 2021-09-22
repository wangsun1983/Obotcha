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

DECLARE_CLASS(HashMapXmlValue) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(HashMapXmlValue,data1,data2)
};

DECLARE_CLASS(XmlReflectData) {
public:
  HashMap<String,HashMapXmlValue> map;
  DECLARE_REFLECT_FIELD(XmlReflectData,map)
};

void testReflectToXml() {
  //test1
  while(1) {
    XmlReflectData data = createXmlReflectData();
    data->map = createHashMap<String,HashMapXmlValue>();
    HashMapXmlValue value = createHashMapXmlValue();
    value->data1 = 111;
    value->data2 = 222;

    HashMapXmlValue value2 = createHashMapXmlValue();
    value2->data1 = 333;
    value2->data2 = 444;

    data->map->put(createString("hello"),value);
    data->map->put(createString("hello1"),value2);

    XmlDocument doc = createXmlDocument();
    doc->importFrom(data);
    XmlWriter writer = createXmlWriter(doc);
    writer->write("output_xml_1.xml");

    XmlDocument doc1 = createXmlDocument("output_xml_1.xml");
    XmlReflectData data3 = createXmlReflectData();
    doc1->reflectTo(data3);
    if(data3->map == nullptr) {
      printf("map is nullptr \n");
    } else {
      printf("xml size is %d \n",data3->map->size());
    }

    HashMapXmlValue v1 = data3->map->get("hello");
    printf("v1 data1 is %d \n",v1->data1);
    printf("v1 data2 is %d \n",v1->data2);

    HashMapXmlValue v2 = data3->map->get("hello1");
    printf("v2 data1 is %d \n",v2->data1);
    printf("v2 data2 is %d \n",v2->data2);
    break;
  }
}
