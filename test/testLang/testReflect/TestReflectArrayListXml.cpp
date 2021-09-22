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

DECLARE_CLASS(XmlItemData1) {
public:
  int data1;
  int data2;
  DECLARE_REFLECT_FIELD(XmlItemData1,data1,data2)
};

DECLARE_CLASS(XmlReflectList) {
public:
  ArrayList<ArrayList<XmlItemData1>> lists;
  DECLARE_REFLECT_FIELD(XmlReflectList,lists)
};

void testReflectArrayListToXml() {
  //test1
  while(1) {
    XmlReflectList refLists = createXmlReflectList();
    refLists->lists = createArrayList<ArrayList<XmlItemData1>>();

    ArrayList<XmlItemData1> l1 = createArrayList<XmlItemData1>();
    XmlItemData1 d1 = createXmlItemData1();
    d1->data1 = 1;
    d1->data2 = 2;

    XmlItemData1 d2 = createXmlItemData1();
    d2->data1 = 3;
    d2->data2 = 4;

    XmlItemData1 d3 = createXmlItemData1();
    d3->data1 = 5;
    d3->data2 = 6;

    l1->add(d1);
    l1->add(d2);

    refLists->lists->add(l1);

    ArrayList<XmlItemData1> l2 = createArrayList<XmlItemData1>();
    l2->add(d1);
    l2->add(d2);
    l2->add(d3);
    refLists->lists->add(l2);

    XmlDocument doc = createXmlDocument();
    doc->importFrom(refLists);
    XmlWriter writer = createXmlWriter(doc);
    writer->write("output_xml_2.xml");


    XmlDocument doc1 = createXmlDocument("output_xml_2.xml");
    XmlReflectList data3 = createXmlReflectList();
    doc1->reflectTo(data3);

    if(data3->lists == nullptr || data3->lists->size() != 2) {
      printf("Reflect ArrayList Xml Reflect test1-------[FAIL] \n");
      break;
    }

    ArrayList<XmlItemData1> dl1 = data3->lists->get(0);
    if(dl1 == 0 || dl1->size() != 2) {
      printf("Reflect ArrayList Xml Reflect test2-------[FAIL] \n");
      break;
    }

    XmlItemData1 data1 = dl1->get(0);
    if(data1 == nullptr || data1->data1 != 1 || data1->data2 != 2) {
      printf("Reflect ArrayList Xml Reflect test3-------[FAIL] \n");
      break;
    }

    XmlItemData1 data2 = dl1->get(1);
    if(data2 == nullptr || data2->data1 != 3 || data2->data2 != 4) {
      printf("Reflect ArrayList Xml Reflect test4-------[FAIL],data2->data1 is %d \n",data2->data1);
      break;
    }

    ArrayList<XmlItemData1> dl2 = data3->lists->get(1);
    if(dl2 == nullptr || dl2->size() != 3) {
      printf("Reflect ArrayList Xml Reflect test5-------[FAIL],dl2->size is %d \n",dl2->size());
      break;
    }

    XmlItemData1 data2_1 = dl2->get(0);
    if(data2_1 == nullptr || data2_1->data1 != 1 || data2_1->data2 != 2) {
      printf("Reflect ArrayList Xml Reflect test6-------[FAIL] \n");
      break;
    }

    XmlItemData1 data2_2 = dl2->get(1);
    if(data2_2 == nullptr || data2_2->data1 != 3 || data2_2->data2 != 4) {
      printf("Reflect ArrayList Xml Reflect test7-------[FAIL] \n");
      break;
    }

    XmlItemData1 data2_3 = dl2->get(2);
    if(data2_3 == nullptr || data2_3->data1 != 5 || data2_3->data2 != 6) {
      printf("Reflect ArrayList Xml Reflect test8-------[FAIL] \n");
      break;
    }

    printf("Reflect ArrayList Xml Reflect test5-------[OK] \n");
    break;
  }
}
