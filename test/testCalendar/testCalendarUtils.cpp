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
        return Sunday;
    case 2:
        return Monday;
    case 3:
        return Tuesday;
    case 4:
        return Wednesday;
    case 5:
        return Thursday;
    case 6:
        return Friday;
    case 7:
         return Saturday;
  }
}