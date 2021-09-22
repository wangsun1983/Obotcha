#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "Float.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "XmlDocument.hpp"
#include "XmlReader.hpp"
#include "XmlWriter.hpp"
#include "Math.hpp"

using namespace obotcha;

DECLARE_CLASS(FloatList) {
public:
    ArrayList<Float>lists;
    DECLARE_REFLECT_FIELD(FloatList,lists)
};

DECLARE_CLASS(FloatList2) {
public:
    ArrayList<Float>list1;
    ArrayList<Float>list2;
    DECLARE_REFLECT_FIELD(FloatList2,list1,list2)
};

void testArrayListFloat() {
    while(1) {
      ArrayList<Float> list = createArrayList<Float>();
      list->add(createFloat(1.1));
      list->add(createFloat(2.2));
      list->add(createFloat(3.3));
      list->add(createFloat(4.4));
      list->add(createFloat(5.5));

      XmlDocument doc = createXmlDocument();
      doc->importFrom(list);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/list_Float_test1.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/list_Float_test1.xml"));
      XmlDocument doc2 = reader->get();

      ArrayList<Float> list2 = createArrayList<Float>();
      doc2->reflectTo(list2);

      if(list2->size() != 5) {
        printf("---[JsonReflect ArrayList Float Test case1] [FAILED]--- \n");
        break;
      }

      if(st(Math)::compareFloat(list2->get(0)->toValue(),1.1) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->get(1)->toValue(),2.2) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->get(2)->toValue(),3.3) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->get(3)->toValue(),4.4) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->get(4)->toValue(),5.5) != st(Math)::AlmostEqual) {
          printf("---[JsonReflect ArrayList Float Test case2] [FAILED]--- \n");
          break;
      }
      break;
    }

    while(1) {
      FloatList2 list = createFloatList2();
      list->list1 = createArrayList<Float>();
      list->list2 = createArrayList<Float>();

      list->list1->add(createFloat(1.1));
      list->list1->add(createFloat(2.2));
      list->list1->add(createFloat(3.3));
      list->list1->add(createFloat(4.4));
      list->list1->add(createFloat(5.5));

      list->list2->add(createFloat(6.6));
      list->list2->add(createFloat(7.7));
      list->list2->add(createFloat(8.8));
      list->list2->add(createFloat(9.9));
      list->list2->add(createFloat(10.1));

      XmlDocument doc = createXmlDocument();
      doc->importFrom(list);
      XmlWriter writer = createXmlWriter(doc);
      writer->write("./tmp/list_Float_test2.xml");
      XmlReader reader = createXmlReader(createFile("./tmp/list_Float_test2.xml"));
      XmlDocument doc2 = reader->get();

      FloatList2 list2 = createFloatList2();
      doc2->reflectTo(list2);

      if(st(Math)::compareFloat(list2->list1->get(0)->toValue(),1.1) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->list1->get(1)->toValue(),2.2) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->list1->get(2)->toValue(),3.3) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->list1->get(3)->toValue(),4.4) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->list1->get(4)->toValue(),5.5) != st(Math)::AlmostEqual) {
          printf("---[JsonReflect ArrayList Float Test case3] [FAILED]--- \n");
          break;
      }

      if(st(Math)::compareFloat(list2->list2->get(0)->toValue(),6.6) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->list2->get(1)->toValue(),7.7) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->list2->get(2)->toValue(),8.8) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->list2->get(3)->toValue(),9.9) != st(Math)::AlmostEqual
        ||st(Math)::compareFloat(list2->list2->get(4)->toValue(),10.1) != st(Math)::AlmostEqual) {
          printf("---[JsonReflect ArrayList Float Test case4] [FAILED]--- \n");
          break;
      }
      break;
    }

    printf("---[JsonReflect ArrayList Float Test case100] [OK]--- \n");
}
