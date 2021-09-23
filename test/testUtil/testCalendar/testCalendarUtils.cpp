#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "Calendar.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"
#include "ArrayList.hpp"

using namespace obotcha;

int convertDayOfWeekFromJava(int day) {
  switch(day) {
    case 1:
        return st(Calendar)::Sunday;
    case 2:
        return st(Calendar)::Monday;
    case 3:
        return st(Calendar)::Tuesday;
    case 4:
        return st(Calendar)::Wednesday;
    case 5:
        return st(Calendar)::Thursday;
    case 6:
        return st(Calendar)::Friday;
    case 7:
        return st(Calendar)::Saturday;
  }
  return 0;
}
