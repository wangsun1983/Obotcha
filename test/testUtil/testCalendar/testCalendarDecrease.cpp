#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "Calendar.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"
#include "ArrayList.hpp"
#include "testCalendar.hpp"

using namespace obotcha;

extern ArrayList<TimeData> dateList;
extern ArrayList<TimeData> hourList;
extern ArrayList<TimeData> minuteList;
extern ArrayList<TimeData> secondList;
extern ArrayList<TimeData> yearList;
extern ArrayList<TimeData> monthList;

extern int convertDayOfWeekFromJava(int);

int testCalendarDecreaseYear() {
    int size = yearList->size();
    TimeData d1 = yearList->get(size - 1);

    Calendar c1 = createCalendar(d1->time);

    for(int i = size-2;i > 0;i--) {
        c1->decreaseYear(1);
        d1 = yearList->get(i);
        if(c1->get(st(Calendar)::Year) != d1->year ||
             c1->get(st(Calendar)::Month) != d1->month ||
             c1->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             c1->get(st(Calendar)::Hour) != d1->hour ||
             c1->get(st(Calendar)::Minute) != d1->minute ||
             c1->get(st(Calendar)::Second) != d1->second ||
             c1->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseYear()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseYear()} case2] [Success]--- \n");
    return 0;
}

int testCalendarDecreaseDay() {
    int size = dateList->size();
    TimeData d1 = dateList->get(size - 1);

    Calendar c1 = createCalendar(d1->time);

    for(int i = size-2;i > 0;i--) {
        c1->decreaseDay(1);
        d1 = dateList->get(i);
        if(c1->get(st(Calendar)::Year) != d1->year ||
             c1->get(st(Calendar)::Month) != d1->month ||
             c1->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             c1->get(st(Calendar)::Hour) != d1->hour ||
             c1->get(st(Calendar)::Minute) != d1->minute ||
             c1->get(st(Calendar)::Second) != d1->second ||
             c1->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseDay()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseDay()} case2] [Success]--- \n");
    return 0;
}

int testCalendarDecreaseMonth() {
    int size = monthList->size();
    TimeData d1 = monthList->get(size - 1);
    Calendar c1 = createCalendar(d1->time);
    for(int i = size-2;i > 0;i--) {
        c1->decreaseMonth(1);
        d1 = monthList->get(i);
        if(c1->get(st(Calendar)::Year) != d1->year ||
             c1->get(st(Calendar)::Month) != d1->month ||
             c1->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             c1->get(st(Calendar)::Hour) != d1->hour ||
             c1->get(st(Calendar)::Minute) != d1->minute ||
             c1->get(st(Calendar)::Second) != d1->second ||
             c1->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseMonth()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseMonth()} case2] [Success]--- \n");
    return 0;
}


//increaseHour
int testCalendarDecreaseHour() {
    int size = hourList->size();
    TimeData d1 = hourList->get(size - 1);
    Calendar c1 = createCalendar(d1->time);
    for(int i = size - 2;i > 0;i--) {
        c1->decreaseHour(1);
        d1 = hourList->get(i);
        if(c1->get(st(Calendar)::Year) != d1->year ||
             c1->get(st(Calendar)::Month) != d1->month ||
             c1->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             c1->get(st(Calendar)::Hour) != d1->hour ||
             c1->get(st(Calendar)::Minute) != d1->minute ||
             c1->get(st(Calendar)::Second) != d1->second ||
             c1->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseHour()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseHour()} case2] [Success]--- \n");
    return 0;
}

//increaseMinute
int testCalendarDecreaseMinute() {
    int size = minuteList->size();
    TimeData d1 = minuteList->get(size - 1);
    Calendar c1 = createCalendar(d1->time);
    for(int i = size - 2;i > 0;i--) {
        c1->decreaseMinute(1);
        d1 = minuteList->get(i);
        if(c1->get(st(Calendar)::Year) != d1->year ||
             c1->get(st(Calendar)::Month) != d1->month ||
             c1->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             c1->get(st(Calendar)::Hour) != d1->hour ||
             c1->get(st(Calendar)::Minute) != d1->minute ||
             c1->get(st(Calendar)::Second) != d1->second ||
             c1->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseMinute()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseMinute()} case2] [Success]--- \n");
    return 0;
}

//secondList
int testCalendarDecreaseSecond() {
    int size = secondList->size();
    TimeData d1 = secondList->get(size - 1);
    Calendar c1 = createCalendar(d1->time);
    for(int i = size - 2;i > 0;i--) {
        c1->decreaseSecond(1);
        d1 = secondList->get(i);
        if(c1->get(st(Calendar)::Year) != d1->year ||
             c1->get(st(Calendar)::Month) != d1->month ||
             c1->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             c1->get(st(Calendar)::Hour) != d1->hour ||
             c1->get(st(Calendar)::Minute) != d1->minute ||
             c1->get(st(Calendar)::Second) != d1->second ||
             c1->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseSecond()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseSecond()} case2] [Success]--- \n");
    return 0;
}
