#ifndef __CALENDAR_HPP__
#define __CALENDAR_HPP__

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

    bool sameDate(Calendar c);

    bool set(int type,int value);

    int get(int type);

    long int toTimeMillis();

    void setTime(long int msec);

    DateTime getDateTime();

    DateTime getGmtDateTime();

    static bool isLeapYear(int year);

    static int caculateDayOfWeek(int y, int m, int d);

    static bool isValid(int year, int month, int day, int hour, int minute, int second, int millisecond);
    
    static const int January;
    static const int February;
    static const int March;
    static const int April;
    static const int May;
    static const int June;
    static const int July;
    static const int August;
    static const int September;
    static const int October;
    static const int November;
    static const int December;

    static const int Sunday;
    static const int Monday;
    static const int Tuesday;
    static const int Wednesday;
    static const int Thursday;
    static const int Friday;
    static const int Saturday;

    static const int Year;
    static const int Month;
    static const int DayOfWeek;
    static const int DayOfMonth;
    static const int DayOfYear;
    static const int Hour;
    static const int Minute;
    static const int Second;
    static const int MSecond;

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