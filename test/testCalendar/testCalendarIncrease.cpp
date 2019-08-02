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

int testCalendarIncreaseYear() {
    int size = yearList->size();
    TimeData d1 = yearList->get(0);

    Calendar c1 = createCalendar(d1->time);

    //printf("testCalendarIncreaseYear d1->year is %d \n",d1->year);
    //printf("testCalendarIncreaseYear c1 is %d \n",c1->get(CalendarType::Year));

    for(int i = 1;i < size;i++) {
        c1->increaseYear(1);
        d1 = yearList->get(i);
        if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarIncreaseYear()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarIncreaseYear()} case2] [Success]--- \n");
    return 0;
}

int testCalendarIncreaseDay() {
    int size = dateList->size();
    TimeData d1 = dateList->get(0);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        c1->increaseDay(1);
        d1 = dateList->get(i);
        if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarIncreaseDay()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarIncreaseDay()} case2] [Success]--- \n");
    return 0;
}

int testCalendarIncreaseMonth() {
    int size = monthList->size();
    TimeData d1 = monthList->get(0);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        c1->increaseMonth(1);
        d1 = monthList->get(i);
        if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {testCalendarIncreaseMonth()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {testCalendarIncreaseMonth()} case2] [Success]--- \n");
    return 0;
}


//increaseHour
int testCalendarIncreaseHour() {
    int size = hourList->size();
    TimeData d1 = hourList->get(0);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        c1->increaseHour(1);
        d1 = hourList->get(i);
        if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {increaseHour()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {increaseHour()} case2] [Success]--- \n");
    return 0;
}

//increaseMinute
int testCalendarIncreaseMinute() {
    int size = minuteList->size();
    TimeData d1 = minuteList->get(0);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        c1->increaseMinute(1);
        d1 = minuteList->get(i);
        if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {increaseMinute()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {increaseMinute()} case2] [Success]--- \n");
    return 0;
}

//secondList
int testCalendarIncreaseSecond() {
    int size = secondList->size();
    TimeData d1 = secondList->get(0);
    Calendar c1 = createCalendar(d1->time);
    for(int i = 1;i < size;i++) {
        c1->increaseSecond(1);
        d1 = secondList->get(i);
        if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek)||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {
               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear -1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {increaseSecond()} case1] [FAILED]--- \n");
               return -1;
        }
    }

    printf("---[Calendar Test {increaseSecond()} case2] [Success]--- \n");
    return 0;
}
