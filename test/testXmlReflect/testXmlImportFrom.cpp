#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Thread.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ExecutorService.hpp"
#include "Integer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "Integer.hpp"
#include "JsonReader.hpp"
#include "JsonWriter.hpp"
#include "MySqlClient.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"
#include "XmlWriter.hpp"
#include "XmlReader.hpp"


using namespace obotcha;

DECLARE_SIMPLE_CLASS(School) {
public:
  String name;
  DECLARE_REFLECT_FIELD(School,name);
};

DECLARE_SIMPLE_CLASS(Address) {
public:
  String url;
  int room;
  DECLARE_REFLECT_FIELD(Address,url,room)
};

DECLARE_SIMPLE_CLASS(Student) {
public:
  int age;
  String name;
  int id;
  Address addr;
  ArrayList<School> schools;
  DECLARE_REFLECT_FIELD(Student,age,name,id,addr,schools)
};

int testImportFrom() {
  XmlDocument doc = createXmlDocument();
  Student data1 = createStudent();
  data1->age = 10;
  data1->name = createString("hello");
  data1->id = 123;
  data1->addr = createAddress();
  data1->addr->url = createString("shanghai");
  data1->addr->room = 888;

  data1->schools = createArrayList<School>();
  School s1 = createSchool();
  s1->name = createString("school 1");
  School s2 = createSchool();
  s2->name = createString("school 2");
  School s3 = createSchool();
  s3->name = createString("school 3");
  data1->schools->add(s1);
  data1->schools->add(s2);
  data1->schools->add(s3);

  doc->importFrom(data1);

  XmlWriter writer = createXmlWriter(doc);
  writer->write("abc.xml"); 

  XmlReader reader = createXmlReader(createFile("abc.xml"));
  XmlDocument doc2 = reader->get();
  Student data2 = createStudent();
  doc2->reflectTo(data2);
  printf("data2 name is %s \n",data2->name->toChars());
  
  ListIterator<School> iterator = data2->schools->getIterator();
  while(iterator->hasValue()) {
    School sch = iterator->getValue();
    printf("school name is %s \n",sch->name->toChars());
    iterator->next();
  }
  
}