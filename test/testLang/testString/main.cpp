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

int main() {

  basetest();

  ignorecasetest();

  trimtest();

  appendtest();

  splittest();

  equaltest();

  formattest();

  StringConstructTest();
}
