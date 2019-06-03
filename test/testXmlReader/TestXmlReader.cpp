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
    printf("---[XmlReader Test Start]--- \n");
    XmlReader reader = createXmlReader("test.xml");
    XmlDocument doc = reader->parse();

    String content = doc->toString();
    //printf("content is %s \n",content->toChars());

    XmlValue root = doc->getRootNode();
    //printf("name is %s \n",root->getName()->toChars());
    String name = root->getName();
    while(1) {
        if(name == nullptr ||!name->equals("EllipsoidParams")) {
          printf("---[XmlReader Test {parse()} case1] [FAILED]--- \n");
          break;
        }

        printf("---[XmlReader Test {parse()} case1] [Success]--- \n");
        break;
    }

    return 0;
}
