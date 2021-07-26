#include <stdio.h>
#include <unistd.h>

#include "IniValue.hpp"
#include "IniReader.hpp"
#include "Log.hpp"

using namespace obotcha;

extern int basetest();
extern int searchvaluetest();

int main() {
  basetest();
  searchvaluetest();
}
