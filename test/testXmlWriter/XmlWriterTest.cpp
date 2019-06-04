#include <stdio.h>
#include <iostream>
#include <type_traits>

#include "String.hpp"
#include "XmlWriter.hpp"
#include "XmlDocument.hpp"
#include "XmlValue.hpp"
#include "XmlReader.hpp"
#include "File.hpp"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace obotcha;
using namespace rapidxml;
int main() {
    printf("---[XmlValue TestFromFile Start]--- \n");
    XmlDocument document = createXmlDocument();
    XmlValue root = document->newRootNode("my root");
    String abc1 = createString("aName");
    String abc2 = createString("bValue");
    XmlValue node1 = document->newNode("aName","bValue");//createXmlValue(document);
    //XmlAttribute attr1 = document->newAttribute("attr1","aaa");
    //node1->appendAttr(attr1);
    node1->appendAttr("attr1","aaa");
    node1->appendAttr("attr2","bbb");
    root->appendNode(node1);

    XmlWriter xmlWriter = createXmlWriter(document);

    //File file = createFile("my.xml");
    //file->createNewFile();
    xmlWriter->write("my.xml");

    while(1) {
      XmlReader reader = createXmlReader("my.xml");
      XmlDocument doc = reader->parse();
      XmlValue myroot = doc->getRootNode();

      XmlValue abcnode1 = myroot->getNode("aName");
      if(abcnode1 == nullptr||!abcnode1->getStringValue()->equals("bValue")) {
        printf("---[XmlWriter Test {write()} case1] [FAILED]--- \n");
        break;
      }

      String attr1 = abcnode1->getStringAttr("attr1");
      if(attr1 == nullptr || !attr1->equals("aaa")) {
        printf("---[XmlWriter Test {write()} case2] [FAILED]--- \n");
        break;
      }

      String attr2 = abcnode1->getStringAttr("attr2");
      if(attr2 == nullptr || !attr2->equals("bbb")) {
        printf("---[XmlWriter Test {write()} case3] [FAILED]--- \n");
        break;
      }

      printf("---[XmlWriter Test {write()} case4] [Success]--- \n");
      break;
    }
/*
    String str1 = document->toString();
    printf("strrrrr1 is %s \n",str1->toChars());

    String str2 = document->toString();
    printf("strrrrr2 is %s \n",str2->toChars());

    String str3 = document->toString();
    printf("strrrrr3 is %s \n",str3->toChars());
*/

/*
    std::string text;
    rapidxml::print(std::back_inserter(text), document->xmlDoc, 0);
    printf("============================== \n");
    printf("toString1 is %s \n",text.data());

    std::string text2;
    rapidxml::print(std::back_inserter(text2), document->xmlDoc, 0);
    printf("============================== \n");
    printf("toString2 is %s \n",text2.data());

    std::string text3;
    rapidxml::print(std::back_inserter(text3), document->xmlDoc, 0);
    printf("============================== \n");
    printf("toString3 is %s \n",text3.data());


    //XmlWriter writer = createXmlWriter(document);
    //writer->write("my.xml");

    //String str2 = document->toString();
    //printf("str2 is %s \n",str->toChars());
    while(1){}
    */


}
