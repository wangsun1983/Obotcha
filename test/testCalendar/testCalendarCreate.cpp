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

extern int convertDayOfWeekFromJava(int);

int testCaldnerCreate() {
    //simpleTest();
    //Calendar(long int timeMillis)
    while(1) {
        int size = dateList->size();
        //printf("data size is %d \n",size);
        for(int i = 0;i<size;i++) {
          TimeData d1 = dateList->get(i);
          Calendar c1 = createCalendar(d1->time);
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
               printf("---[Calendar Test {Calendar(long int timeMillis)} case1] [FAILED]--- \n");
               break;
          }
        }

        size = hourList->size();
        for(int i = 0;i<size;i++) {
          TimeData d1 = hourList->get(i);
          Calendar c1 = createCalendar(d1->time);
          if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek) ||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {

               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear - 1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {Calendar(long int timeMillis)} case2] [FAILED]--- \n");
               break;
          }
        }

        size = minuteList->size();
        for(int i = 0;i<size;i++) {
          TimeData d1 = minuteList->get(i);
          Calendar c1 = createCalendar(d1->time);
          if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek) ||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {

               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear-1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {Calendar(long int timeMillis)} case3] [FAILED]--- \n");
               break;
          }
        }

        size = secondList->size();
        for(int i = 0;i<size;i++) {
          TimeData d1 = secondList->get(i);
          Calendar c1 = createCalendar(d1->time);
          if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek) ||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {

               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear - 1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),d1->dayOfWeek);
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {Calendar(long int timeMillis)} case4] [FAILED]--- \n");
               break;
          }
        }

        size = yearList->size();
        for(int i = 0;i<size;i++) {
          TimeData d1 = yearList->get(i);
          Calendar c1 = createCalendar(d1->time);
          if(c1->get(CalendarType::Year) != d1->year ||
             c1->get(CalendarType::Month) != d1->month ||
             c1->get(CalendarType::DayOfYear) != (d1->dayOfYear - 1) ||
             c1->get(CalendarType::DayOfWeek) != convertDayOfWeekFromJava(d1->dayOfWeek) ||
             c1->get(CalendarType::DayOfMonth) != d1->dayOfMonth ||
             c1->get(CalendarType::Hour) != d1->hour ||
             c1->get(CalendarType::Minute) != d1->minute ||
             c1->get(CalendarType::Second) != d1->second ||
             c1->get(CalendarType::MSecond) != d1->millisecond) {

               printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
               printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
               printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear - 1);
               printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
               printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
               printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
               printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
               printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
               printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
               printf("current time is %ld \n",d1->time);
               printf("---[Calendar Test {Calendar(long int timeMillis)} case5] [FAILED]--- \n");
               break;
          }
        }

        printf("---[Calendar Test {Calendar(long int timeMillis)} case6] [Success]--- \n");
        break;
    }

    //Calendar(int _year,int _month,int _dayOfMonth,int _hour = 0,int _minute = 0,int _second = 0)
    while(1) {
        int size = dateList->size();
        //printf("data size is %d \n",size);
        for(int i = 0;i<size;i++) {
          TimeData d1 = dateList->get(i);
          Calendar c1 = createCalendar(d1->year,d1->month,d1->dayOfMonth,d1->hour,d1->minute,d1->second,d1->millisecond);
          if(c1->toTimeMillis() != d1->time) {
              printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
              printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
              printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear - 1);
              printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
              printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
              printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
              printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
              printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
              printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
              printf("testdata time is %ld,calendar time is %ld \n",d1->time,c1->toTimeMillis());
              printf("---[Calendar Test {Calendar(int,int,int,int,int,int)} case1] [FAILED]--- \n");
              break;
          }
        }

        size = hourList->size();
        for(int i = 0;i<size;i++) {
            TimeData d1 = hourList->get(i);
            Calendar c1 = createCalendar(d1->year,d1->month,d1->dayOfMonth,d1->hour,d1->minute,d1->second,d1->millisecond);
            if(c1->toTimeMillis() != d1->time) {
                printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
                printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
                printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear - 1);
                printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
                printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
                printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
                printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
                printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
                printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
                printf("testdata time is %ld,calendar time is %ld \n",d1->time,c1->toTimeMillis());
                printf("---[Calendar Test {Calendar(int,int,int,int,int,int)} case2] [FAILED]--- \n");
                break;
          }
        }

        size = minuteList->size();
        for(int i = 0;i<size;i++) {
            TimeData d1 = minuteList->get(i);
            Calendar c1 = createCalendar(d1->year,d1->month,d1->dayOfMonth,d1->hour,d1->minute,d1->second,d1->millisecond);
            if(c1->toTimeMillis() != d1->time) {
                printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
                printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
                printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear - 1);
                printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
                printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
                printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
                printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
                printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
                printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
                printf("testdata time is %ld,calendar time is %ld \n",d1->time,c1->toTimeMillis());
                printf("---[Calendar Test {Calendar(int,int,int,int,int,int)} case3] [FAILED]--- \n");
                break;
          }
        }

        size = secondList->size();
        for(int i = 0;i<size;i++) {
            TimeData d1 = secondList->get(i);
            Calendar c1 = createCalendar(d1->year,d1->month,d1->dayOfMonth,d1->hour,d1->minute,d1->second,d1->millisecond);
            if(c1->toTimeMillis() != d1->time) {
                printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
                printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
                printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear - 1);
                printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
                printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
                printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
                printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
                printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
                printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
                printf("testdata time is %ld,calendar time is %ld \n",d1->time,c1->toTimeMillis());
                printf("---[Calendar Test {Calendar(int,int,int,int,int,int)} case4] [FAILED]--- \n");
                break;
          }
        }

        size = yearList->size();
        for(int i = 0;i<size;i++) {
            TimeData d1 = yearList->get(i);
            Calendar c1 = createCalendar(d1->year,d1->month,d1->dayOfMonth,d1->hour,d1->minute,d1->second,d1->millisecond);
            if(c1->toTimeMillis() != d1->time) {
                printf("Calndear year is %d,data year is %d \n",c1->get(CalendarType::Year),d1->year);
                printf("Calndear month is %d,data month is %d \n",c1->get(CalendarType::Month),d1->month);
                printf("Calndear dayOfYear is %d,data dayOfYear is %d \n",c1->get(CalendarType::DayOfYear),d1->dayOfYear - 1);
                printf("Calndear dayOfWeek is %d,data dayOfWeek is %d \n",c1->get(CalendarType::DayOfWeek),convertDayOfWeekFromJava(d1->dayOfWeek));
                printf("Calndear dayOfMonth is %d,data dayOfMonth is %d \n",c1->get(CalendarType::DayOfMonth),d1->dayOfMonth);
                printf("Calndear hour is %d,data hour is %d \n",c1->get(CalendarType::Hour),d1->hour);
                printf("Calndear minute is %d,data minute is %d \n",c1->get(CalendarType::Minute),d1->minute);
                printf("Calndear second is %d,data second is %d \n",c1->get(CalendarType::Second),d1->second);
                printf("Calndear millisecond is %d,data millisecond is %d \n",c1->get(CalendarType::MSecond),d1->millisecond);
                printf("testdata time is %ld,calendar time is %ld \n",d1->time,c1->toTimeMillis());
                printf("---[Calendar Test {Calendar(int,int,int,int,int,int)} case5] [FAILED]--- \n");
                break;
          }
        }

        printf("---[Calendar Test {Calendar(int,int,int,int,int,int)} case6] [Success]--- \n");
        break;
    }


    return 0;




}
