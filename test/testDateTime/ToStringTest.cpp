#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "StrongPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "DateTime.hpp"
#include "Calendar.hpp"

using namespace obotcha;

int tostringtest() {
  Calendar c = createCalendar();
  DateTime date = c->getGmtDateTime();
  printf("date is %s \n",date->toString()->toChars());
}
