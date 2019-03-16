#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"

#include "Log.hpp"

using namespace obotcha;

int main() {
    JsonReader reader = createJsonReader(createString("abc.json"));
    JsonValue value = reader->parse();
    String v1 = value->getString("c");
    LOGD("v1 is ",v1);

    JsonValueIterator iterator = value->getIterator();
    while(iterator->hasValue()) {
      LOGD("has value");
      String tag = iterator->getTag();
      if(iterator->isInt()) {
          Integer val = value->getInteger(tag);
          LOGD("tag is ",tag, " val is ",val);
      }

      iterator->next();

    }
}
