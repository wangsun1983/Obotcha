#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "XmlReader.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"

using namespace obotcha;


void testsopenvreader() {
    XmlReader reader = createXmlReader(createFile("sopenv.xml"));
    XmlValue value = reader->get()->getRootNode();
    XmlValue value_1 = value->getNode(createString("soapenv:Body"));
    XmlValue value_1_1 = value_1->getNode(createString("ResponseMessage"));
    XmlValue value_1_1_1 = value_1_1->getNode(createString("Header"));
    XmlValue value_2 = value_1_1_1->getNode(createString("Verb"));
    if(!value_2->getStringValue()->equals("Show")) {
      printf("---[XmlReader Sopenv Test parse()} case1] [FAILED]--- \n");
    }

    XmlValue value_3 = value_1_1_1->getNode(createString("Noun"));
    if(!value_3->getStringValue()->equals("OMSFHYCZCJSJ")) {
      printf("---[XmlReader Sopenv Test parse()} case2] [FAILED]--- \n");
    }

    XmlValue value_4 = value_1_1_1->getNode(createString("User"));
    XmlValue value_4_1 = value_4->getNode(createString("UserID"));
    if(!value_4_1->getStringValue()->equals("DDD")) {
      printf("---[XmlReader Sopenv Test parse()} case3] [FAILED]--- \n");
    }
    XmlValue value_4_2 = value_4->getNode(createString("Organization"));
    if(!value_4_2->getStringValue()->equals("BRUCE")) {
      printf("---[XmlReader Sopenv Test parse()} case4] [FAILED]--- \n");
    }

    XmlValue value_5 = value_1_1_1->getNode(createString("Property"));
    XmlValue value_5_1 = value_5->getNode(createString("Name"));
    if(!value_5_1->getStringValue()->equals("count")) {
      printf("value is %s \n",value_4_1->getStringValue()->toChars());
      printf("---[XmlReader Sopenv Test parse()} case5] [FAILED]--- \n");
    }
    XmlValue value_5_2 = value_5->getNode(createString("Value"));
    if(!value_5_2->getStringValue()->equals("50")) {
      printf("---[XmlReader Sopenv Test parse()} case6] [FAILED]--- \n");
    }

    XmlValue value_6 = value_1_1->getNode(createString("Reply"));
    XmlValue value_6_1 = value_6->getNode(createString("ReplyCode"));
    if(!value_6_1->getStringValue()->equals("OK")) {
      printf("---[XmlReader Sopenv Test parse()} case7] [FAILED]--- \n");
    }

    XmlValue value_7 = value_1_1->getNode(createString("Payload"));
    XmlValue value_7_1 = value_7->getNode(createString("rdf:RDF"));
    XmlValue value_7_2 = value_7_1->getNode(createString("cim:OMSFHYCZCJSJ"));
    XmlValue value_7_2_1 = value_7_2->getNode(createString("cim:aaa"));
    if(!value_7_2_1->getStringValue()->equals("ZHOGNG")) {
      printf("---[XmlReader Sopenv Test parse()} case8] [FAILED]--- \n");
    }

    XmlValue value_7_2_2 = value_7_2->getNode(createString("cim:bbb"));
    if(!value_7_2_2->getStringValue()->equals("广州")) {
      printf("---[XmlReader Sopenv Test parse()} case9] [FAILED]--- \n");
    }

    XmlValue value_7_2_2_c = value_7_2->getNode(createString("cim:bbb"));
    if(!value_7_2_2_c->getStringValue()->equals("广州")) {
      printf("---[XmlReader Sopenv Test parse()} case9] [FAILED]--- \n");
    }

    XmlValue value_7_2_3 = value_7_2->getNode(createString("cim:ccc"));
    if(!value_7_2_3->getStringValue()->equals("2018年第23周 (06.04~06.10)")) {
      printf("---[XmlReader Sopenv Test parse()} case10] [FAILED]--- \n");
    }

    XmlValue value_7_2_4 = value_7_2->getNode(createString("cim:ddd"));
    if(!value_7_2_4->getStringValue()->equals("16500")) {
      printf("---[XmlReader Sopenv Test parse()} case11] [FAILED]--- \n");
    }

    XmlValue value_7_2_5 = value_7_2->getNode(createString("cim:eee"));
    if(!value_7_2_5->getStringValue()->equals("8800")) {
      printf("---[XmlReader Sopenv Test parse()} case12] [FAILED]--- \n");
    }

    XmlValue value_7_2_6 = value_7_2->getNode(createString("cim:fff"));
    if(!value_7_2_6->getStringValue()->equals("2200000")) {
      printf("---[XmlReader Sopenv Test parse()} case13] [FAILED]--- \n");
    }

    XmlValue value_7_2_7 = value_7_2->getNode(createString("cim:ggg"));
    if(!value_7_2_7->getStringValue()->equals("0")) {
      printf("---[XmlReader Sopenv Test parse()} case14] [FAILED]--- \n");
    }

    XmlValue value_7_2_8 = value_7_2->getNode(createString("cim:hhh"));
    if(!value_7_2_8->getStringValue()->equals("0")) {
      printf("---[XmlReader Sopenv Test parse()} case15] [FAILED]--- \n");
    }

    printf("---[XmlReader Sopenv Test parse()} case100] [OK]--- \n");
}
