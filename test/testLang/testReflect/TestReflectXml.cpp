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

DECLARE_SIMPLE_CLASS(HashMapXmlValue) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(HashMapXmlValue,data1,data2)
};

DECLARE_SIMPLE_CLASS(XmlReflectData) {
public:
  HashMap<String,HashMapXmlValue> map;
  DECLARE_REFLECT_FIELD(XmlReflectData,map)
};

int testReflectToXml() {
  //test1
  while(1) {
    XmlReflectData data = createXmlReflectData();
    data->map = createHashMap<String,HashMapXmlValue>();
    HashMapXmlValue value = createHashMapXmlValue();
    value->data1 = 111;
    value->data2 = 222;

    data->map->put(createString("hello"),value);

    XmlDocument doc = createXmlDocument();
    doc->importFrom(data);
    XmlWriter writer = createXmlWriter(doc);
    writer->write("output_xml_1.xml");

    break;
  }
}
