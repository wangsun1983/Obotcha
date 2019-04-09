#include <stdio.h>
#include <iostream>
#include <type_traits>

#include "StringFormat.hpp"

using namespace obotcha;

int main() {

  printf("---[String Test Start]--- \n");
  StringFormat format = createStringFormat();
  String str = format->format("i say %s","hello");
  printf("str is %s \n",str->toChars());


}
