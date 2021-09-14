#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

int dataFailTest() {
    printf("---[JsonReader Data Fail Test Start]--- \n");
    //String getString(String tag);
    while(1) {
      for(int index = 1;index <=33;index++) {
        String str = createString("./test/jsonchecker/fail")->append(createString(index),".json");
        JsonReader reader = createJsonReader(createFile(str));
        JsonValue value = reader->get();
        if(value != nullptr) {
          printf("---[JsonReader Data Fail Test case%d] [FAILED]--- \n",index);
          continue;
        }

        printf("---[JsonReader Data Fail Test case%d] [OK]--- \n",index);
      }

      break;
    }

    return 0;
}
