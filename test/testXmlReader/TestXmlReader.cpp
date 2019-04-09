#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Double.hpp"
#include "XmlReader.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"

using namespace obotcha;

int main() {
    XmlReader reader = createXmlReader("test.xml");
    XmlDocument doc = reader->parse();
    String content = doc->toString();
    printf("content is %s \n",content->toChars());

    XmlValue root = doc->getRootNode();
    printf("name is %s \n",root->getName()->toChars());

    /*
    XmlValueIterator iterator = root->getValueIterator();
    while(iterator->hasValue()) {
      XmlValue node = iterator->getValue();
      printf("name is %s \n",node->getName()->toChars());
      XmlValueIterator iterator2 = node->getValueIterator();
      while(iterator2->hasValue()) {
        XmlValue v1 = iterator2->getValue();
        printf("__name is %s \n",v1->getName()->toChars());

        //get Attribute
        XmlAttrIterator attrIterator = v1->getAttrIterator();
        while(attrIterator->hasValue()) {
          XmlAttribute aa = attrIterator->getAttribute();
          printf("attr _name is %s , value is %s \n",aa->getName()->toChars(),aa->getValue()->toChars());
          attrIterator->next();
        }

        iterator2->next();
      }
      iterator->next();
    }*/
}
