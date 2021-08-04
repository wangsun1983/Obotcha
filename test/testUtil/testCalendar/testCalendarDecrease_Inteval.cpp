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

int testCalendarDecreaseYear_Interval() {
    int size = yearList->size();
    TimeData d1 = yearList->get(size - 1);

    Calendar c1 = createCalendar(d1->time);

    for(int i = 0;i < size;i++) {
        Calendar testCalendar = createCalendar(c1);

        testCalendar->decreaseYear(i);
        d1 = yearList->get(size - i -1);
        if(testCalendar->get(st(Calendar)::Year) != d1->year ||
             testCalendar->get(st(Calendar)::Month) != d1->month ||
             testCalendar->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             testCalendar->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             testCalendar->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             testCalendar->get(st(Calendar)::Hour) != d1->hour ||
             testCalendar->get(st(Calendar)::Minute) != d1->minute ||
             testCalendar->get(st(Calendar)::Second) != d1->second ||
             testCalendar->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",testCalendar->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",testCalendar->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",testCalendar->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",testCalendar->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",testCalendar->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",testCalendar->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",testCalendar->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",testCalendar->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",testCalendar->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseYear_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseYear_Interval()} case2] [Success]--- \n");
    return 0;
}

int testCalendarDecreaseDay_Interval() {
    int size = dateList->size();
    TimeData d1 = dateList->get(size - 1);

    Calendar c1 = createCalendar(d1->time);

    for(int i = 0;i < size;i++) {
        Calendar testCalendar = createCalendar(c1);
        testCalendar->decreaseDay(size - i -1);
        d1 = dateList->get(i);
        if(testCalendar->get(st(Calendar)::Year) != d1->year ||
             testCalendar->get(st(Calendar)::Month) != d1->month ||
             testCalendar->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             testCalendar->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             testCalendar->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             testCalendar->get(st(Calendar)::Hour) != d1->hour ||
             testCalendar->get(st(Calendar)::Minute) != d1->minute ||
             testCalendar->get(st(Calendar)::Second) != d1->second ||
             testCalendar->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",testCalendar->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",testCalendar->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",testCalendar->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",testCalendar->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",testCalendar->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",testCalendar->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",testCalendar->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",testCalendar->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",testCalendar->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseDay_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseDay_Interval()} case2] [Success]--- \n");
    return 0;
}

int testCalendarDecreaseMonth_Interval() {
    int size = monthList->size();
    TimeData d1 = monthList->get(size - 1);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 0;i < size;i++) {
        Calendar testCalendar = createCalendar(c1);
        testCalendar->decreaseMonth(i);
        d1 = monthList->get(size - i -1);
        if(testCalendar->get(st(Calendar)::Year) != d1->year ||
             testCalendar->get(st(Calendar)::Month) != d1->month ||
             testCalendar->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             testCalendar->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             testCalendar->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             testCalendar->get(st(Calendar)::Hour) != d1->hour ||
             testCalendar->get(st(Calendar)::Minute) != d1->minute ||
             testCalendar->get(st(Calendar)::Second) != d1->second ||
             testCalendar->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",testCalendar->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",testCalendar->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",testCalendar->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",testCalendar->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",testCalendar->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",testCalendar->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",testCalendar->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",testCalendar->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",testCalendar->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseMonth_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseMonth_Interval()} case2] [Success]--- \n");
    return 0;
}


//increaseHour
int testCalendarDecreaseHour_Interval() {
    int size = hourList->size();
    TimeData d1 = hourList->get(size - 1);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 0;i < size;i++) {
        Calendar testCalendar = createCalendar(c1);
        testCalendar->decreaseHour(i);
        d1 = hourList->get(size - i -1);
        if(testCalendar->get(st(Calendar)::Year) != d1->year ||
             testCalendar->get(st(Calendar)::Month) != d1->month ||
             testCalendar->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             testCalendar->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             testCalendar->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             testCalendar->get(st(Calendar)::Hour) != d1->hour ||
             testCalendar->get(st(Calendar)::Minute) != d1->minute ||
             testCalendar->get(st(Calendar)::Second) != d1->second ||
             testCalendar->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",testCalendar->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",testCalendar->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",testCalendar->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",testCalendar->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",testCalendar->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",testCalendar->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",testCalendar->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",testCalendar->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",testCalendar->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("decreaseHour is %d \n",i);
               printf("---[Calendar Test {testCalendarDecreaseHour_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseHour_Interval()} case2] [Success]--- \n");
    return 0;
}

//increaseMinute
int testCalendarDecreaseMinute_Interval() {
    int size = minuteList->size();
    TimeData d1 = minuteList->get(size - 1);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 0;i < size;i++) {
        Calendar testCalendar = createCalendar(c1);
        testCalendar->decreaseMinute(i);
        d1 = minuteList->get(size - i -1);
        if(testCalendar->get(st(Calendar)::Year) != d1->year ||
             testCalendar->get(st(Calendar)::Month) != d1->month ||
             testCalendar->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             testCalendar->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             testCalendar->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             testCalendar->get(st(Calendar)::Hour) != d1->hour ||
             testCalendar->get(st(Calendar)::Minute) != d1->minute ||
             testCalendar->get(st(Calendar)::Second) != d1->second ||
             testCalendar->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",testCalendar->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",testCalendar->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",testCalendar->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",testCalendar->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",testCalendar->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",testCalendar->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",testCalendar->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",testCalendar->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",testCalendar->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseMinute_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseMinute_Interval()} case2] [Success]--- \n");
    return 0;
}

//secondList
int testCalendarDecreaseSecond_Interval() {
    int size = secondList->size();
    TimeData d1 = secondList->get(size - 1);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 0;i < size;i++) {
        Calendar testCalendar = createCalendar(c1);
        testCalendar->decreaseSecond(i);
        d1 = secondList->get(size - i -1);
        if(testCalendar->get(st(Calendar)::Year) != d1->year ||
             testCalendar->get(st(Calendar)::Month) != d1->month ||
             testCalendar->get(st(Calendar)::DayOfYear) != (d1->dayOfYear - 1) ||
             testCalendar->get(st(Calendar)::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             testCalendar->get(st(Calendar)::DayOfMonth) != d1->dayOfMonth ||
             testCalendar->get(st(Calendar)::Hour) != d1->hour ||
             testCalendar->get(st(Calendar)::Minute) != d1->minute ||
             testCalendar->get(st(Calendar)::Second) != d1->second ||
             testCalendar->get(st(Calendar)::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",testCalendar->get(st(Calendar)::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",testCalendar->get(st(Calendar)::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",testCalendar->get(st(Calendar)::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",testCalendar->get(st(Calendar)::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",testCalendar->get(st(Calendar)::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",testCalendar->get(st(Calendar)::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",testCalendar->get(st(Calendar)::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",testCalendar->get(st(Calendar)::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",testCalendar->get(st(Calendar)::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarDecreaseSecond_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarDecreaseSecond_Interval()} case2] [Success]--- \n");
    return 0;
}
