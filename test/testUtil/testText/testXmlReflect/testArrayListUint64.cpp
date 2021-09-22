#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Uint64.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "XmlDocument.hpp"
#include "XmlReader.hpp"
#include "XmlWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(Uint64List) {
public:
    ArrayList<Uint64>lists;
    DECLARE_REFLECT_FIELD(Uint64List,lists)
};

DECLARE_CLASS(Uint64List2) {
public:
    ArrayList<Uint64>list1;
    ArrayList<Uint64>list2;
    DECLARE_REFLECT_FIELD(Uint64List2,list1,list2)
};

void testArrayListUint64() {
    while(1) {
      ArrayList<Uint64> list = createArrayList<Uint64>();
      list->add(createUint64(1));
      list->add(createUint64(2));
      list->add(createUint64(3));
      list->add(createUint64(4));
      list->add(createUint64(5));

      XmlDocument doc = createXmlDocument();
      doc->importFrom(list);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/list_Uint32_test2.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/list_Uint32_test2.xml"));
      XmlDocument doc2 = reader->get();

      ArrayList<Uint64> list2 = createArrayList<Uint64>();
      doc2->reflectTo(list2);

      if(list2->size() != 5) {
        printf("---[JsonReflect ArrayList Uint64 Test case1] [FAILED]--- \n");
        break;
      }

      if(list2->get(0)->toValue() != 1
        ||list2->get(1)->toValue() != 2
        ||list2->get(2)->toValue() != 3
        ||list2->get(3)->toValue() != 4
        ||list2->get(4)->toValue() != 5) {
          printf("---[JsonReflect ArrayList Uint64 Test case2] [FAILED]--- \n");
          break;
      }
      break;
    }

    while(1) {
      Uint64List2 list = createUint64List2();
      list->list1 = createArrayList<Uint64>();
      list->list2 = createArrayList<Uint64>();

      list->list1->add(createUint64(1));
      list->list1->add(createUint64(2));
      list->list1->add(createUint64(3));
      list->list1->add(createUint64(4));
      list->list1->add(createUint64(5));

      list->list2->add(createUint64(6));
      list->list2->add(createUint64(7));
      list->list2->add(createUint64(8));
      list->list2->add(createUint64(9));
      list->list2->add(createUint64(10));

      XmlDocument doc = createXmlDocument();
      doc->importFrom(list);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/list_Uint32_test2.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/list_Uint32_test2.xml"));
      XmlDocument doc2 = reader->get();

      Uint64List2 list2 = createUint64List2();
      doc2->reflectTo(list2);

      if(list2->list1->get(0)->toValue() != 1
        ||list2->list1->get(1)->toValue() != 2
        ||list2->list1->get(2)->toValue() != 3
        ||list2->list1->get(3)->toValue() != 4
        ||list2->list1->get(4)->toValue() != 5) {
          printf("---[JsonReflect ArrayList Uint64 Test case3] [FAILED]--- \n");
          break;
      }

      if(list2->list2->get(0)->toValue() != 6
        ||list2->list2->get(1)->toValue() != 7
        ||list2->list2->get(2)->toValue() != 8
        ||list2->list2->get(3)->toValue() != 9
        ||list2->list2->get(4)->toValue() != 10) {
          printf("---[JsonReflect ArrayList Uint64 Test case4] [FAILED]--- \n");
          break;
      }
      break;
    }

    printf("---[JsonReflect ArrayList Uint64 Test case100] [OK]--- \n");
}
