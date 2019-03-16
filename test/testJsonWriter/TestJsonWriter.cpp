#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"

using namespace obotcha;

int main() {
    JsonWriter writer = createJsonWriter(createString("abc.json"));
    JsonValue value = createJsonValue();
    value->put("a",1);
    value->put("b",2);
    value->put("c","nihao");

    JsonArray array = createJsonArray("arr");
    array->append("abc1");
    array->append("abc2");
    array->append("abc3");

    value->put(array);

    writer->write(value);
    writer->close();
}
