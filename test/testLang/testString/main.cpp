#include <stdio.h>
#include <iostream>
#include <type_traits>

#include <string.h>
#include "String.hpp"
#include "ArrayList.hpp"
#include "NullPointerException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"
#include "TransformException.hpp"

using namespace obotcha;

extern int basetest();
extern int ignorecasetest();
extern int trimtest();
extern int appendtest();
extern int splittest();
extern int equaltest();
extern int formattest();
extern int StringConstructTest();
extern int TestStringUpdate();
extern int TestStringToChars();
extern int TestStringCharAt();
extern int TestStringSubString();
extern int TestStringTrim();
extern int TestStringTrimAll();
extern int TestStringSize();
extern int TestStringContains();
extern int TestStringIndexOf();
extern int TestStringEquals();

int main() {

  basetest();

  ignorecasetest();

  trimtest();

  appendtest();
  
  splittest();

  equaltest();

  formattest();
  
  StringConstructTest();

  TestStringUpdate();

  TestStringToChars();

  TestStringCharAt();
  
  TestStringSubString();

  TestStringTrim();

  TestStringTrimAll();

  TestStringSize();

  TestStringContains();

  TestStringIndexOf();

  TestStringEquals();
}
