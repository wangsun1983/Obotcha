#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "XmlReader.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"
#include "Math.hpp"

using namespace obotcha;

void testXmlValueFromFile() {
    printf("---[XmlValue TestFromFile Start]--- \n");
    XmlReader reader = createXmlReader(createFile("regressions.xml"));
    XmlDocument doc = reader->get();
    XmlValue root = doc->getRootNode();

    //String getName();
    while(1) {
      String name = root->getName();
      //printf("name is %s \n",name->toChars());
      if(name == nullptr || !name->equals("RegressionTests")) {
        printf("---[XmlValue TestFromFile {getName()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getName()} case2] [OK]--- \n");
      break;
    }

    //String getStringAttr(String attr)
    while(1) {
        String attr1 = root->getStringAttr("name");
        if(attr1 == nullptr || !attr1->equals("rootn")) {
          printf("---[XmlValue TestFromFile {getStringAttr()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[XmlValue TestFromFile {getStringAttr()} case2] [OK]--- \n");
        break;
    }

    //Integer getIntegerAttr(String attr);
    while(1) {
        Integer attr1 = root->getIntegerAttr("intv");
        if(attr1 == nullptr || attr1->toValue() != 123) {
          printf("---[XmlValue TestFromFile {getIntegerAttr()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[XmlValue TestFromFile {getIntegerAttr()} case2] [OK]--- \n");
        break;
    }

    //Boolean getBooleanAttr(String attr);
    while(1) {
        Boolean attr1 = root->getBooleanAttr("boolv");
        if(attr1 == nullptr || attr1->toValue() != false) {
          printf("---[XmlValue TestFromFile {getBooleanAttr()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[XmlValue TestFromFile {getBooleanAttr()} case2] [OK]--- \n");
        break;
    }

    //Double getDoubleAttr(String attr);
    while(1) {
      Double attr1 = root->getDoubleAttr("doublev");
      if(attr1 == nullptr || st(Math)::compareDouble(attr1->toValue(),1.1) != st(Math)::AlmostEqual) {
        printf("---[XmlValue TestFromFile {getDoubleAttr()} case1] [FAILED]---,value is %lf \n",attr1->toValue());
        break;
      }

      printf("---[XmlValue TestFromFile {getDoubleAttr()} case2] [OK]--- \n");
      break;
    }

    //Float getFloatAttr(String attr);
    while(1) {
      Float attr1 = root->getFloatAttr("floatv");
      if(attr1 == nullptr || st(Math)::compareFloat(attr1->toValue(),2.2)!= st(Math)::AlmostEqual) {
        printf("---[XmlValue TestFromFile {getFloatAttr()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getFloatAttr()} case2] [OK]--- \n");
      break;
    }

    //String getStringValue(String);
    while(1) {
      String value = root->getStringValue("teststring");
      if(value == nullptr || !value->equals("test string")) {
        printf("---[XmlValue TestFromFile {getStringValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getStringValue()} case2] [OK]--- \n");
      break;
    }

    //Integer getIntegerValue(String);
    while(1) {
      Integer value = root->getIntegerValue("testint");
      if(value == nullptr || value->toValue() != 12) {
        printf("---[XmlValue TestFromFile {getIntegerValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getIntegerValue()} case2] [OK]--- \n");
      break;
    }

    //Boolean getBooleanValue(String);
    while(1) {
      Boolean value = root->getBooleanValue("testbool");
      if(value == nullptr || value->toValue() != false) {
        printf("---[XmlValue TestFromFile {getBooleanValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getBooleanValue()} case2] [OK]--- \n");
      break;
    }

    //Double getDoubleValue(String);
    while(1) {
      Double value = root->getDoubleValue("testdouble");
      if(value == nullptr || st(Math)::compareDouble(value->toValue(),1.11)!= st(Math)::AlmostEqual) {
        printf("---[XmlValue TestFromFile {getDoubleValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getDoubleValue()} case2] [OK]--- \n");
      break;
    }

    //Double getFloatValue(String);
    while(1) {
      Float value = root->getFloatValue("testfloat");
      if(value == nullptr || st(Math)::compareFloat(value->toValue(),2.22)!= st(Math)::AlmostEqual) {
        printf("---[XmlValue TestFromFile {getFloatValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getFloatValue()} case2] [OK]--- \n");
      break;
    }

    //XmlValue getNode(String);
    while(1) {
      XmlValue v = root->getNode("defaults");
      if(v == nullptr) {
        printf("---[XmlValue TestFromFile {getNode()} case1] [FAILED]--- \n");
        break;
      }

      String t1 = v->getStringValue("testname");
      if(t1 == nullptr || !t1->equals("noname")) {
        printf("---[XmlValue TestFromFile {getNode()} case2] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("execpath");
      if(t1 == nullptr || !t1->equals(".")) {
        printf("---[XmlValue TestFromFile {getNode()} case3] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("testprog");
      if(t1 == nullptr || !t1->equals("xmllint")) {
        printf("---[XmlValue TestFromFile {getNode()} case4] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("srcdir");
      if(t1 == nullptr || !t1->equals("test")) {
        printf("---[XmlValue TestFromFile {getNode()} case5] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("resdir");
      if(t1 == nullptr || !t1->equals("result")) {
        printf("---[XmlValue TestFromFile {getNode()} case6] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("file");
      if(t1 == nullptr || !t1->equals("*.xml")) {
        printf("---[XmlValue TestFromFile {getNode()} case7] [FAILED]--- \n");
        break;
      }

      String attr1 = v->getStringAttr("name");
      if(attr1 == nullptr || !attr1->equals("BeiJing54")) {
        printf("---[XmlValue TestFromFile {getNode()} case8] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getNode()} case8] [OK]--- \n");
      break;
    }

    //String getName();
    while(1) {
      XmlValue v = root->getNode("defaults");
      String na = v->getName();
      if(na == nullptr || !na->equals("defaults")) {
        printf("---[XmlValue TestFromFile {getName()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {getName()} case2] [OK]--- \n");
      break;
    }

    //void updateName(String name);
    while(1) {
      XmlValue v = root->getNode("defaults");
      if(v == nullptr) {
        printf("---[XmlValue TestFromFile {updateName()} case0] [FAILED]--- \n");
        break;
      }

      v->updateName("testupdate1");

      XmlValue v2 = root->getNode("testupdate1");
      if(v2 == nullptr) {
        printf("---[XmlValue TestFromFile {updateName()} case1] [FAILED]--- \n");
        break;
      }

      String t1 = v2->getStringValue("testname");
      if(t1 == nullptr || !t1->equals("noname")) {
        printf("---[XmlValue TestFromFile {updateName()} case2] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("execpath");
      if(t1 == nullptr || !t1->equals(".")) {
        printf("---[XmlValue TestFromFile {updateName()} case3] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("testprog");
      if(t1 == nullptr || !t1->equals("xmllint")) {
        printf("---[XmlValue TestFromFile {updateName()} case4] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("srcdir");
      if(t1 == nullptr || !t1->equals("test")) {
        printf("---[XmlValue TestFromFile {updateName()} case5] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("resdir");
      if(t1 == nullptr || !t1->equals("result")) {
        printf("---[XmlValue TestFromFile {updateName()} case6] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("file");
      if(t1 == nullptr || !t1->equals("*.xml")) {
        printf("---[XmlValue TestFromFile {updateName()} case7] [FAILED]--- \n");
        break;
      }

      String attr1 = v2->getStringAttr("name");
      if(attr1 == nullptr || !attr1->equals("BeiJing54")) {
        printf("---[XmlValue TestFromFile {updateName()} case8] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {updateName()} case9] [OK]--- \n");
      break;
    }

    //void updateValue(String value);
    while(1) {
      XmlValue v = root->getNode("teststring");
      v->updateValue("new test");

      String t1 = root->getStringValue("teststring");
      if(t1 == nullptr || !t1->equals("new test")) {
        printf("---[XmlValue TestFromFile {updateValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {updateValue()} case2] [OK]--- \n");
      break;
    }

    //void appendNode(XmlValue v);
    while(1) {
      XmlValue node = doc->newNode("myt1","hello world");
      root->appendNode(node);

      XmlValue node2 = root->getNode("myt1");
      if(node2 == nullptr || !node2->getStringValue()->equals("hello world")) {
        printf("---[XmlValue TestFromFile {appendNode()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {appendNode()} case2] [OK]--- \n");
      break;
    }

    //void appendAttr(String name,String value);
    while(1) {
      XmlValue v = root->getNode("testdouble");
      v->appendAttr("testAttr1","testAttr1 hello");
      //printf("start getAttr!!! \n");
      String attr1 = v->getStringAttr("testAttr1");
      //if(attr1 == nullptr) {
      //  printf("attr1 is nullptr \n");
      //} else {
      //  printf("attr1 is %s,haha \n",attr1->toChars());
      //}

      if(attr1 == nullptr || !attr1->equals("testAttr1 hello")) {
        printf("---[XmlValue TestFromFile {appendAttr()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {appendAttr()} case1] [OK]--- \n");
      break;
    }

    //void removeNode(XmlValue v);
    while(1) {
      XmlValue node = root->getNode("testdouble");
      root->removeNode(node);

      XmlValue node2 = root->getNode("testdouble");
      if(node2 != nullptr) {
        printf("---[XmlValue TestFromFile {removeNode()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {removeNode()} case2] [OK]--- \n");
      break;
    }

    //void removeNode(String v);
    while(1) {
      XmlValue node0 = root->getNode("testfloat");
      if(node0 == nullptr) {
        printf("---[XmlValue TestFromFile {removeNode()} case3] [FAILED]--- \n");
        break;
      }

      root->removeNode(createString("testfloat"));
      XmlValue node2 = root->getNode("testfloat");
      if(node2 != nullptr) {
        printf("---[XmlValue TestFromFile {removeNode()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromFile {removeNode()} case5] [OK]--- \n");
      break;
    }
}
