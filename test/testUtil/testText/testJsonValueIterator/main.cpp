#include <stdio.h>
#include <unistd.h>

#include "JsonWriter.hpp"
#include "JsonReader.hpp"
#include "JsonValue.hpp"

#include "Log.hpp"

using namespace obotcha;

extern void testJsonValueIterator();
extern void testJsonArrayIterator();

int main() {
  testJsonValueIterator();
  testJsonArrayIterator();
  return 0;
}
