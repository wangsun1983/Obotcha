#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int testJsonArrayIterator() {
    while(1) {
      JsonReader reader = createJsonReader(createFile("stringarray.json"));
      JsonValue value = reader->get();
      auto iterator = value->getIterator();
      ArrayList<String> list = createArrayList<String>();
      list->add(S("abc1"));
      list->add(S("abc2"));
      list->add(S("abc3"));

      int index = 0;
      while(iterator->hasValue()) {
        auto str = iterator->getString();
        if(!str->equals(list->get(index))) {
          printf("---[JsonArrayIterator Test case1] [FAILED]--- \n");
          break;
        }

        iterator->next();
        index++;
      }

      if(index != 3){
        printf("---[JsonArrayIterator Test case2] [FAILED]--- \n");
        break;
      }
      break;
    }

    while(1) {
      JsonReader reader = createJsonReader(createFile("intarray.json"));
      JsonValue value = reader->get();
      auto iterator = value->getIterator();
      int array[] = {1, 100, 123};

      int index = 0;
      while(iterator->hasValue()) {
        auto str = iterator->getInteger();
        if(str->toValue() != array[index]) {
          printf("---[JsonArrayIterator Test case3] [FAILED]--- \n");
          break;
        }
        iterator->next();
        index++;
      }

      if(index != 3){
        printf("---[JsonArrayIterator Test case4] [FAILED]--- \n");
        break;
      }
      break;
    }

    printf("---[JsonArrayIterator Test case100] [OK]--- \n");
}
