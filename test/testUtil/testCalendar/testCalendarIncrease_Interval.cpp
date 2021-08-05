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

int testCalendarIncreaseYear_Interval() {
    int size = yearList->size();
    TimeData d1 = yearList->get(0);

    Calendar testData = createCalendar(d1->time);

    for(int i = 1;i < size;i++) {
        Calendar c1 = createCalendar(testData);
        c1->add(st(Calendar)::Year,i);
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
               printf("---[Calendar Test {testCalendarIncreaseYear_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarIncreaseYear_Interval()} case2] [Success]--- \n");
    return 0;
}

int testCalendarIncreaseDay_Interval() {
    int size = dateList->size();
    TimeData d1 = dateList->get(0);
    Calendar testData = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        Calendar c1 = createCalendar(testData);
        c1->add(st(Calendar)::DayOfYear,i);
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
               printf("---[Calendar Test {testCalendarIncreaseDay_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarIncreaseDay_Interval()} case2] [Success]--- \n");
    return 0;
}

int testCalendarIncreaseMonth_Interval() {
    int size = monthList->size();
    TimeData d1 = monthList->get(0);
    Calendar testData = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        Calendar c1 = createCalendar(testData);
        c1->add(st(Calendar)::Month,i);
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
               printf("---[Calendar Test {testCalendarIncreaseMonth_Interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarIncreaseMonth_Interval()} case2] [Success]--- \n");
    return 0;
}


//increaseHour
int testCalendarIncreaseHour_Interval() {
    int size = hourList->size();
    TimeData d1 = hourList->get(0);
    Calendar testData = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        Calendar c1 = createCalendar(testData);
        c1->add(st(Calendar)::Hour,i);
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
               printf("---[Calendar Test {increaseHour()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {increaseHour()} case2] [Success]--- \n");
    return 0;
}

//increaseMinute
int testCalendarIncreaseMinute_Interval() {
    int size = minuteList->size();
    TimeData d1 = minuteList->get(0);
    Calendar testData = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        Calendar c1 = createCalendar(testData);
        c1->add(st(Calendar)::Minute,i);
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
               printf("---[Calendar Test {increaseMinute_interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {increaseMinute_interval()} case2] [Success]--- \n");
    return 0;
}

//secondList
int testCalendarIncreaseSecond_Interval() {
    int size = secondList->size();
    TimeData d1 = secondList->get(0);
    Calendar testData = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        Calendar c1 = createCalendar(testData);
        c1->add(st(Calendar)::Second,i);
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
               printf("---[Calendar Test {increaseSecond_interval()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {increaseSecond_interval()} case2] [Success]--- \n");
    return 0;
}
