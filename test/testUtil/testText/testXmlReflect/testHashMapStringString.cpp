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


DECLARE_CLASS(StringStringMap) {
public:
    HashMap<String,String>maps;
    DECLARE_REFLECT_FIELD(StringStringMap,maps)
};

DECLARE_CLASS(StringStringMap2) {
public:
    HashMap<String,String>maps1;
    HashMap<String,String>maps2;
    DECLARE_REFLECT_FIELD(StringStringMap2,maps1,maps2)
};

void testHashMapStringString() {
    while(1) {
      HashMap<String,String> map = createHashMap<String,String>();
      map->put("tag1","val1");
      map->put("tag2","val2");
      map->put("tag3","val3");
      map->put("tag4","val4");
      map->put("tag5","val5");

      XmlDocument doc = createXmlDocument();
      doc->importFrom(map);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/map_string_string_test1.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/map_string_string_test1.xml"));
      XmlDocument doc2 = reader->get();

      HashMap<String,String>map2 = createHashMap<String,String>();
      doc2->reflectTo(map2);

      if(map2->size() != 5) {
        printf("---[JsonReflect HashMap String String Test case1] [FAILED]--- \n");
        break;
      }

      if(!map2->get("tag1")->equals("val1")
        ||!map2->get("tag2")->equals("val2")
        ||!map2->get("tag3")->equals("val3")
        ||!map2->get("tag4")->equals("val4")
        ||!map2->get("tag5")->equals("val5")) {
          printf("---[JsonReflect HashMap String String Test case2] [FAILED]--- \n");
          break;
      }
      break;
    }

    while(1) {
      StringStringMap map = createStringStringMap();
      map->maps = createHashMap<String,String>();
      map->maps->put("tag1","val1");
      map->maps->put("tag2","val2");
      map->maps->put("tag3","val3");
      map->maps->put("tag4","val4");
      map->maps->put("tag5","val5");

      XmlDocument doc = createXmlDocument();
      doc->importFrom(map);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/map_string_string_test2.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/map_string_string_test2.xml"));
      XmlDocument doc2 = reader->get();

      StringStringMap checkValue = createStringStringMap();
      doc2->reflectTo(checkValue);

      auto map2 = checkValue->maps;
      if(map2->size() != 5) {
        printf("---[JsonReflect HashMap String String Test case3] [FAILED]--- \n");
        break;
      }

      if(!map2->get("tag1")->equals("val1")
        ||!map2->get("tag2")->equals("val2")
        ||!map2->get("tag3")->equals("val3")
        ||!map2->get("tag4")->equals("val4")
        ||!map2->get("tag5")->equals("val5")) {
          printf("---[JsonReflect HashMap String String Test case4] [FAILED]--- \n");
          break;
      }
      break;
    }

    while(1) {
      StringStringMap2 map = createStringStringMap2();
      map->maps1 = createHashMap<String,String>();
      map->maps1->put("tag1","val1");
      map->maps1->put("tag2","val2");
      map->maps1->put("tag3","val3");
      map->maps1->put("tag4","val4");
      map->maps1->put("tag5","val5");

      map->maps2 = createHashMap<String,String>();
      map->maps2->put("2_tag1","2_val1");
      map->maps2->put("2_tag2","2_val2");
      map->maps2->put("2_tag3","2_val3");
      map->maps2->put("2_tag4","2_val4");
      map->maps2->put("2_tag5","2_val5");

      XmlDocument doc = createXmlDocument();
      doc->importFrom(map);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/map_string_string_test4.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/map_string_string_test4.xml"));
      XmlDocument doc2 = reader->get();

      StringStringMap2 checkValue = createStringStringMap2();
      doc2->reflectTo(checkValue);

      auto map1 = checkValue->maps1;
      if(map1->size() != 5) {
        printf("---[JsonReflect HashMap String String Test case6] [FAILED]--- \n");
        break;
      }

      if(!map1->get("tag1")->equals("val1")
        ||!map1->get("tag2")->equals("val2")
        ||!map1->get("tag3")->equals("val3")
        ||!map1->get("tag4")->equals("val4")
        ||!map1->get("tag5")->equals("val5")) {
          printf("---[JsonReflect HashMap String String Test case7] [FAILED]--- \n");
          break;
      }

      auto map2 = checkValue->maps2;
      if(map2->size() != 5) {
        printf("---[JsonReflect HashMap String String Test case8] [FAILED]--- \n");
        break;
      }

      if(!map2->get("2_tag1")->equals("2_val1")
        ||!map2->get("2_tag2")->equals("2_val2")
        ||!map2->get("2_tag3")->equals("2_val3")
        ||!map2->get("2_tag4")->equals("2_val4")
        ||!map2->get("2_tag5")->equals("2_val5")) {
          printf("---[JsonReflect HashMap String String Test case9] [FAILED]--- \n");
          break;
      }
      break;
    }

    printf("---[JsonReflect HashMap String String Test case100] [OK]--- \n");
}
