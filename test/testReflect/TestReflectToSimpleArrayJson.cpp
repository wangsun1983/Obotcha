#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <type_traits>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Reflect.hpp"
#include "String.hpp"
#include "Math.hpp"
#include "Field.hpp"
#include "JsonWriter.hpp"
#include "JsonReader.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(IntArray) {
public:
  ArrayList<Integer> lists;
  DECLARE_REFLECT_FIELD(IntArray,lists)
};

int testReflectToSimpleArrayJson() {
  //test1
  while(1) {
    IntArray data = createIntArray();
    data->lists = createArrayList<Integer>();
    data->lists->add(createInteger(1));
    data->lists->add(createInteger(2));
    JsonValue jvalue = createJsonValue();
    jvalue->importFrom(data);
    JsonWriter jwriter = createJsonWriter("output3.json");
    jwriter->write(jvalue);

    printf("Reflect ArrayList To File test11-------[OK] \n");
    break;
  }
}
