#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "XmlDocument.hpp"
#include "XmlReader.hpp"
#include "XmlWriter.hpp"

using namespace obotcha;

DECLARE_CLASS(LongList) {
public:
    ArrayList<Long>lists;
    DECLARE_REFLECT_FIELD(LongList,lists)
};

DECLARE_CLASS(LongList2) {
public:
    ArrayList<Long>list1;
    ArrayList<Long>list2;
    DECLARE_REFLECT_FIELD(LongList2,list1,list2)
};

void testArrayListLong() {
    while(1) {
      ArrayList<Long> list = createArrayList<Long>();
      list->add(createLong(1));
      list->add(createLong(2));
      list->add(createLong(3));
      list->add(createLong(4));
      list->add(createLong(5));

      XmlDocument doc = createXmlDocument();
      doc->importFrom(list);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/list_Long_test1.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/list_Long_test1.xml"));
      XmlDocument doc2 = reader->get();

      ArrayList<Long> list2 = createArrayList<Long>();
      doc2->reflectTo(list2);

      if(list2->size() != 5) {
        printf("---[JsonReflect ArrayList Long Test case1] [FAILED]--- \n");
        break;
      }

      if(list2->get(0)->toValue() != 1
        ||list2->get(1)->toValue() != 2
        ||list2->get(2)->toValue() != 3
        ||list2->get(3)->toValue() != 4
        ||list2->get(4)->toValue() != 5) {
          printf("---[JsonReflect ArrayList Long Test case2] [FAILED]--- \n");
          break;
      }
      break;
    }

    while(1) {
      LongList2 list = createLongList2();
      list->list1 = createArrayList<Long>();
      list->list2 = createArrayList<Long>();

      list->list1->add(createLong(1));
      list->list1->add(createLong(2));
      list->list1->add(createLong(3));
      list->list1->add(createLong(4));
      list->list1->add(createLong(5));

      list->list2->add(createLong(6));
      list->list2->add(createLong(7));
      list->list2->add(createLong(8));
      list->list2->add(createLong(9));
      list->list2->add(createLong(10));

      XmlDocument doc = createXmlDocument();
      doc->importFrom(list);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/list_Long_test2.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/list_Long_test2.xml"));
      XmlDocument doc2 = reader->get();

      LongList2 list2 = createLongList2();
      doc2->reflectTo(list2);

      if(list2->list1->get(0)->toValue() != 1
        ||list2->list1->get(1)->toValue() != 2
        ||list2->list1->get(2)->toValue() != 3
        ||list2->list1->get(3)->toValue() != 4
        ||list2->list1->get(4)->toValue() != 5) {
          printf("---[JsonReflect ArrayList Long Test case3] [FAILED]--- \n");
          break;
      }

      if(list2->list2->get(0)->toValue() != 6
        ||list2->list2->get(1)->toValue() != 7
        ||list2->list2->get(2)->toValue() != 8
        ||list2->list2->get(3)->toValue() != 9
        ||list2->list2->get(4)->toValue() != 10) {
          printf("---[JsonReflect ArrayList Long Test case4] [FAILED]--- \n");
          break;
      }
      break;
    }

    printf("---[JsonReflect ArrayList Long Test case100] [OK]--- \n");
}
