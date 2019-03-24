#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ConfReader.hpp"
#include "ConfValue.hpp"
#include "Log.hpp"

using namespace obotcha;

int main() {
    ConfReader reader = createConfReader("simple.conf");
    ConfValue value = reader->parse();

    if(value == nullptr) {
      printf("parse value is null \n");
      return 1;
    }

    ConfIterator iterator = value->getIterator();

    while(iterator->hasValue()) {
      LOGD("tag is ",iterator->getTag(),";value is ",iterator->getValue());
      iterator->next();
    }

    String bgvalue = value->getValue("Background Color");
    LOGD("bgvalue:",bgvalue);
}
