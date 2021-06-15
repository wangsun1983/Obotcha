#ifndef __OBOTCHA_CALENDAR_HPP__
#define __OBOTCHA_CALENDAR_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "DateTime.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Calendar) {
public:

    _Calendar();

    _Calendar(int _year,int _month,int _dayOfMonth,int _hour,int _minute,int _seconds,int mseconds);

    _Calendar(long long timeMillis);

    void increaseYear(int year);

    void decreaseYear(int year);

    void increaseDay(int day);

    void decreaseDay(int day);

    void increaseMonth(int mon);

    void decreaseMonth(int mon);

    void increaseHour(int hour);

    void decreaseHour(int hour);

    void increaseMinute(int minute);

    void decreaseMinute(int minute);

    void increaseSecond(int second);

    void decreaseSecond(int second);

    bool equals(Calendar);

    bool set(int type,int value);

    int get(int type);

    long int toTimeMillis();

    void setTime(long int msec);

    DateTime getDateTime();

    DateTime getGmtDateTime();

    static bool isLeapYear(int year);

    static int caculateDayOfWeek(int y, int m, int d);

    static bool isValid(int year, int month, int day, int hour, int minute, int second, int millisecond);
    
    enum Month {
        January = 0,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December,
    };
    
    enum WeekDay {
        Sunday = 0,
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
    };

    enum TimeType {
        Year = 0,
        Month,
        DayOfWeek,
        DayOfMonth,
        DayOfYear,
        Hour,
        Minute,
        Second,
        MSecond,
    };

private:
    long long timeMillis;

    int year;

    int month; //[0,11]

    int dayOfWeek; //[0,6]

    int dayOfMonth; //[1,31]

    int dayOfYear; //[0,365]

    int hour;

    int minute;

    int second;

    int msec;

    void init();

    int getMonthDays(int month);

    bool onUpdateByYear(int v);

    bool onUpdateByMonth(int v);

    bool onUpdateByDayOfWeek(int v);

    bool onUpdateByDayOfMonth(int v);

    bool onUpdateByDayOfYear(int v);

    int caculateDayOfYear(int _year,int _month,int _dayOfMonth);

    int *getDays(int year);

    static int commonDays[];

    static int leapDays[];

    static int GregorianBase;
};

}
#endif