#ifndef __CALENDAR_HPP__
#define __CALENDAR_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

enum MonthEnum{
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
    December
};

enum WeekDayEnum{
    Monday = 0,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

enum CalendarType {
    Year = 0,
    Month,
    DayOfWeek,
    DayOfMonth,
    DayOfYear,
    Hour,
    Minute,
    Second,
    MSecond
};


DECLARE_SIMPLE_CLASS(Calendar) {
public:

    _Calendar();

    _Calendar(int _year,int _month,int _dayOfMonth,int _hour,int _minute,int _seconds);

    _Calendar(long int timeMillis);

    bool isLeapYear(int year);
    
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

    bool set(CalendarType type,int value);

    int get(CalendarType type);

    long int toTimeMillis();

    void setTime(long int msec);

    static int caculateDayOfWeek(int y, int m, int d);

private:
    long int timeMillis;

    int year;

    int month;

    int dayOfWeek;

    int dayOfMonth;

    int dayOfYear;

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