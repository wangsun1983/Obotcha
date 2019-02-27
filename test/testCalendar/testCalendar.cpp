#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "Calendar.hpp"

void testSet() {

    /*
    time 1548992007428
    year is 2019
    month is 1
    day is 1
    hour is 11
    minute is 35
    second is 40
    dayOfYear is 32
    dayOfWeek is 6
    dayOfMonth is 1
    */

    /*
    time is 1549078599269
    year is 2019
    month is 1
    day is 2
    hour is 11
    minute is 36
    second is 39
    dayOfYear is 33
    dayOfWeek is 7
    dayOfMonth is 2
    */

    /*
    time is 1549165036356
    year is 2019
    month is 1
    day is 3
    hour is 11
    minute is 37
    second is 16
    dayOfYear is 34
    dayOfWeek is 1
    dayOfMonth is 3
    */

    /*
    time is 1549251460144
    year is 2019
    month is 1
    day is 4
    hour is 11
    minute is 37
    second is 40
    dayOfYear is 35
    dayOfWeek is 2
    dayOfMonth is 4
    */

    /*
    time is 1549337875232
    year is 2019
    month is 1
    day is 5
    hour is 11
    minute is 37
    second is 55
    dayOfYear is 36
    dayOfWeek is 3
    dayOfMonth is 5
    */

    /*
    time is 1549424293124
    year is 2019
    month is 1
    day is 6
    hour is 11
    minute is 38
    second is 13
    dayOfYear is 37
    dayOfWeek is 4
    dayOfMonth is 6
    */




}

int main() {
    //Test Calendar now
    Calendar m = createCalendar();
    printf("year is %d \n",m->get(st(Calendar)::CalendarType::Year));
    printf("month is %d \n",m->get(st(Calendar)::CalendarType::Month));
    printf("month is %d \n",m->get(st(Calendar)::CalendarType::DayOfMonth));






}
