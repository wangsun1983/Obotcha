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
#include "XmlDocument.hpp"
#include "XmlReader.hpp"
#include "XmlWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(HashmapDataInteger) {
public:
  HashMap<Integer,Integer> maps;
  DECLARE_REFLECT_FIELD(HashmapDataInteger,maps)
};

void testHashMapIntegerInteger() {
    while(1) {
      HashMap<Integer,Integer> maps = createHashMap<Integer,Integer>();
      maps->put(createInteger(1),createInteger(10));
      maps->put(createInteger(2),createInteger(20));
      maps->put(createInteger(3),createInteger(30));

      XmlDocument doc = createXmlDocument();
      doc->importFrom(maps);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/hashmap_integer_integer_test1.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/hashmap_integer_integer_test1.xml"));
      XmlDocument doc2 = reader->get();

      HashMap<Integer,Integer> maps2 = createHashMap<Integer,Integer>();
      doc2->reflectTo(maps2);
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap Integer Integer Test case1] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createInteger(1));
      if(v1 == nullptr || v1->toValue() != 10) {
        printf("---[JsonReflect HashMap Integer Integer Test case2] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createInteger(2));
      if(v2 == nullptr || v2->toValue() != 20) {
        printf("---[JsonReflect HashMap Integer Integer Test case3] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createInteger(3));
      if(v3 == nullptr || v3->toValue() != 30) {
        printf("---[JsonReflect HashMap Integer Integer Test case4] [FAILED]--- \n");
        break;
      }

      break;
    }

    while(1) {
      HashmapDataInteger data = createHashmapDataInteger();
      HashMap<Integer,Integer> maps = createHashMap<Integer,Integer>();
      maps->put(createInteger(1),createInteger(10));
      maps->put(createInteger(2),createInteger(20));
      maps->put(createInteger(3),createInteger(30));
      data->maps = maps;

      XmlDocument doc = createXmlDocument();
      doc->importFrom(data);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/hashmap_integer_integer_test2.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/hashmap_integer_integer_test2.xml"));
      XmlDocument doc2 = reader->get();

      HashmapDataInteger data2 = createHashmapDataInteger();
      doc2->reflectTo(data2);
      HashMap<Integer,Integer> maps2 = data2->maps;
      if(maps2->size() != 3) {
        printf("---[JsonReflect HashMap Integer Integer Test case5] [FAILED]--- \n");
        break;
      }

      auto v1 = maps2->get(createInteger(1));
      if(v1 == nullptr || v1->toValue() != 10) {
        printf("---[JsonReflect HashMap Integer Integer Test case6] [FAILED]--- \n");
        break;
      }

      auto v2 = maps2->get(createInteger(2));
      if(v2 == nullptr || v2->toValue() != 20) {
        printf("---[JsonReflect HashMap Integer Integer Test case7] [FAILED]--- \n");
        break;
      }

      auto v3 = maps2->get(createInteger(3));
      if(v3 == nullptr || v3->toValue() != 30) {
        printf("---[JsonReflect HashMap Integer Integer Test case8] [FAILED]--- \n");
        break;
      }

      break;
    }

    printf("---[JsonReflect HashMap Integer Integer Test case100] [OK]--- \n");
}
