#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "XmlReader.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"

using namespace obotcha;


//<RegressionTests name="rootn" intv="123" boolv="false" doublev="1.1" floatv="2.2">

int testXmlValueFromMemory() {
    printf("---[XmlValue TestFromMemory Start]--- \n");
    //XmlReader reader = createXmlReader("regressions.xml");
    //XmlDocument doc = reader->parse();
    //XmlValue root = doc->getRootNode();
    XmlDocument doc = createXmlDocument();
    XmlValue root = doc->newRootNode("RegressionTests");
    root->appendAttr("name","rootn");
    root->appendAttr("intv","123");
    root->appendAttr("boolv","false");
    root->appendAttr("doublev","1.1");
    root->appendAttr("floatv","2.2");

    XmlValue teststring = doc->newNode("teststring","test string");
    teststring->appendAttr("name","BeiJing54");
    root->appendNode(teststring);

    XmlValue testint = doc->newNode("testint","12");
    testint->appendAttr("name","BeiJing54");
    root->appendNode(testint);

    XmlValue testbool = doc->newNode("testbool","false");
    testbool->appendAttr("name","BeiJing54");
    root->appendNode(testbool);

    XmlValue testdouble = doc->newNode("testdouble","1.11");
    testdouble->appendAttr("name","BeiJing54");
    root->appendNode(testdouble);

    XmlValue testfloat = doc->newNode("testfloat","2.22");
    testfloat->appendAttr("name","BeiJing54");
    root->appendNode(testfloat);

    XmlValue testDefault = doc->newNode("defaults");
    testDefault->appendAttr("name","BeiJing54");

    //XmlValue test1 = doc->newNode("testname","noname");
    //testDefault->appendNode(test1);
    testDefault->appendNode("testname","noname");

    //XmlValue test2 = doc->newNode("execpath",".");
    //testDefault->appendNode(test2);
    testDefault->appendNode("execpath",".");

    XmlValue test3 = doc->newNode("testprog","xmllint");
    testDefault->appendNode(test3);

    XmlValue test4 = doc->newNode("srcdir","test");
    testDefault->appendNode(test4);

    XmlValue test5 = doc->newNode("resdir","result");
    testDefault->appendNode(test5);

    XmlValue test6 = doc->newNode("file","*.xml");
    testDefault->appendNode(test6);

    XmlValue test7 = doc->newNode("reserrext","err");
    testDefault->appendNode(test7);

    root->appendNode(testDefault);

    //String getName();
    while(1) {
      String name = root->getName();
      //printf("name is %s \n",name->toChars());
      if(name == nullptr || !name->equals("RegressionTests")) {
        printf("---[XmlValue TestFromMemory {getName()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getName()} case2] [OK]--- \n");
      break;
    }

    //String getStringAttr(String attr)
    while(1) {
        String attr1 = root->getStringAttr("name");
        if(attr1 == nullptr || !attr1->equals("rootn")) {
          printf("---[XmlValue TestFromMemory {getStringAttr()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[XmlValue TestFromMemory {getStringAttr()} case2] [OK]--- \n");
        break;
    }

    //Integer getIntegerAttr(String attr);
    while(1) {
        Integer attr1 = root->getIntegerAttr("intv");
        if(attr1 == nullptr || attr1->toValue() != 123) {
          printf("---[XmlValue TestFromMemory {getIntegerAttr()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[XmlValue TestFromMemory {getIntegerAttr()} case2] [OK]--- \n");
        break;
    }

    //Boolean getBooleanAttr(String attr);
    while(1) {
        Boolean attr1 = root->getBooleanAttr("boolv");
        if(attr1 == nullptr || attr1->toValue() != false) {
          printf("---[XmlValue TestFromMemory {getBooleanAttr()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[XmlValue TestFromMemory {getBooleanAttr()} case2] [OK]--- \n");
        break;
    }

    //Double getDoubleAttr(String attr);
    while(1) {
      Double attr1 = root->getDoubleAttr("doublev");
      if(attr1 == nullptr || attr1->toValue() != 1.1f) {
        printf("---[XmlValue TestFromMemory {getDoubleAttr()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getDoubleAttr()} case2] [OK]--- \n");
      break;
    }

    //Float getFloatAttr(String attr);
    while(1) {
      Float attr1 = root->getFloatAttr("floatv");
      if(attr1 == nullptr || attr1->toValue() != 2.2f) {
        printf("---[XmlValue TestFromMemory {getFloatAttr()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getFloatAttr()} case2] [OK]--- \n");
      break;
    }

    //String getStringValue(String);
    while(1) {
      String value = root->getStringValue("teststring");
      if(value == nullptr || !value->equals("test string")) {
        printf("---[XmlValue TestFromMemory {getStringValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getStringValue()} case2] [OK]--- \n");
      break;
    }

    //Integer getIntegerValue(String);
    while(1) {
      Integer value = root->getIntegerValue("testint");
      if(value == nullptr || value->toValue() != 12) {
        printf("---[XmlValue TestFromMemory {getIntegerValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getIntegerValue()} case2] [OK]--- \n");
      break;
    }

    //Boolean getBooleanValue(String);
    while(1) {
      Boolean value = root->getBooleanValue("testbool");
      if(value == nullptr || value->toValue() != false) {
        printf("---[XmlValue TestFromMemory {getBooleanValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getBooleanValue()} case2] [OK]--- \n");
      break;
    }

    //Double getDoubleValue(String);
    while(1) {
      Double value = root->getDoubleValue("testdouble");
      if(value == nullptr || value->toValue() != 1.11f) {
        printf("---[XmlValue TestFromMemory {getDoubleValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getDoubleValue()} case2] [OK]--- \n");
      break;
    }

    //Double getFloatValue(String);
    while(1) {
      Float value = root->getFloatValue("testfloat");
      if(value == nullptr || value->toValue() != 2.22f) {
        printf("---[XmlValue TestFromMemory {getFloatValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getFloatValue()} case2] [OK]--- \n");
      break;
    }

    //XmlValue getNode(String);
    while(1) {
      XmlValue v = root->getNode("defaults");
      if(v == nullptr) {
        printf("---[XmlValue TestFromMemory {getNode()} case1] [FAILED]--- \n");
        break;
      }

      String t1 = v->getStringValue("testname");
      if(t1 == nullptr || !t1->equals("noname")) {
        printf("---[XmlValue TestFromMemory {getNode()} case2] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("execpath");
      if(t1 == nullptr || !t1->equals(".")) {
        printf("---[XmlValue TestFromMemory {getNode()} case3] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("testprog");
      if(t1 == nullptr || !t1->equals("xmllint")) {
        printf("---[XmlValue TestFromMemory {getNode()} case4] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("srcdir");
      if(t1 == nullptr || !t1->equals("test")) {
        printf("---[XmlValue TestFromMemory {getNode()} case5] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("resdir");
      if(t1 == nullptr || !t1->equals("result")) {
        printf("---[XmlValue TestFromMemory {getNode()} case6] [FAILED]--- \n");
        break;
      }

      t1 = v->getStringValue("file");
      if(t1 == nullptr || !t1->equals("*.xml")) {
        printf("---[XmlValue TestFromMemory {getNode()} case7] [FAILED]--- \n");
        break;
      }

      String attr1 = v->getStringAttr("name");
      if(attr1 == nullptr || !attr1->equals("BeiJing54")) {
        printf("---[XmlValue TestFromMemory {getNode()} case8] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getNode()} case8] [OK]--- \n");
      break;
    }

    //String getName();
    while(1) {
      XmlValue v = root->getNode("defaults");
      String na = v->getName();
      if(na == nullptr || !na->equals("defaults")) {
        printf("---[XmlValue TestFromMemory {getName()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {getName()} case2] [OK]--- \n");
      break;
    }

    //void updateName(String name);
    while(1) {
      XmlValue v = root->getNode("defaults");
      if(v == nullptr) {
        printf("---[XmlValue TestFromMemory {updateName()} case0] [FAILED]--- \n");
        break;
      }

      v->updateName("testupdate1");

      XmlValue v2 = root->getNode("testupdate1");
      if(v2 == nullptr) {
        printf("---[XmlValue TestFromMemory {updateName()} case1] [FAILED]--- \n");
        break;
      }

      String t1 = v2->getStringValue("testname");
      if(t1 == nullptr || !t1->equals("noname")) {
        printf("---[XmlValue TestFromMemory {updateName()} case2] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("execpath");
      if(t1 == nullptr || !t1->equals(".")) {
        printf("---[XmlValue TestFromMemory {updateName()} case3] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("testprog");
      if(t1 == nullptr || !t1->equals("xmllint")) {
        printf("---[XmlValue TestFromMemory {updateName()} case4] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("srcdir");
      if(t1 == nullptr || !t1->equals("test")) {
        printf("---[XmlValue TestFromMemory {updateName()} case5] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("resdir");
      if(t1 == nullptr || !t1->equals("result")) {
        printf("---[XmlValue TestFromMemory {updateName()} case6] [FAILED]--- \n");
        break;
      }

      t1 = v2->getStringValue("file");
      if(t1 == nullptr || !t1->equals("*.xml")) {
        printf("---[XmlValue TestFromMemory {updateName()} case7] [FAILED]--- \n");
        break;
      }

      String attr1 = v2->getStringAttr("name");
      if(attr1 == nullptr || !attr1->equals("BeiJing54")) {
        printf("---[XmlValue TestFromMemory {updateName()} case8] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {updateName()} case9] [OK]--- \n");
      break;
    }

    //void updateValue(String value);
    while(1) {
      XmlValue v = root->getNode("teststring");
      v->updateValue("new test");

      String t1 = root->getStringValue("teststring");
      if(t1 == nullptr || !t1->equals("new test")) {
        printf("---[XmlValue TestFromMemory {updateValue()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {updateValue()} case2] [OK]--- \n");
      break;
    }

    //void appendNode(XmlValue v);
    while(1) {
      XmlValue node = doc->newNode("myt1","hello world");
      root->appendNode(node);

      XmlValue node2 = root->getNode("myt1");
      if(node2 == nullptr || !node2->getStringValue()->equals("hello world")) {
        printf("---[XmlValue TestFromMemory {appendNode()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {appendNode()} case2] [OK]--- \n");
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
        printf("---[XmlValue TestFromMemory {appendAttr()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {appendAttr()} case1] [OK]--- \n");
      break;
    }

    //void removeNode(XmlValue v);
    while(1) {
      XmlValue node = root->getNode("testdouble");
      root->removeNode(node);

      XmlValue node2 = root->getNode("testdouble");
      if(node2 != nullptr) {
        printf("---[XmlValue TestFromMemory {removeNode()} case1] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {removeNode()} case2] [OK]--- \n");
      break;
    }

    //void removeNode(String v);
    while(1) {
      XmlValue node0 = root->getNode("testfloat");
      if(node0 == nullptr) {
        printf("---[XmlValue TestFromMemory {removeNode()} case3] [FAILED]--- \n");
        break;
      }

      root->removeNode(createString("testfloat"));
      XmlValue node2 = root->getNode("testfloat");
      if(node2 != nullptr) {
        printf("---[XmlValue TestFromMemory {removeNode()} case4] [FAILED]--- \n");
        break;
      }

      printf("---[XmlValue TestFromMemory {removeNode()} case5] [OK]--- \n");
      break;
    }

    return 0;
}
