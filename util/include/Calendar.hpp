#ifndef __OBOTCHA_CALENDAR_HPP__
#define __OBOTCHA_CALENDAR_HPP__

#include "DateTime.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(Calendar) {
  public:
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

    _Calendar();

    explicit _Calendar(sp<_Calendar>);

    _Calendar(int _year, int _month, int _dayOfMonth, int _hour, int _minute,
              int _seconds, int mseconds);

    explicit _Calendar(long long timeMillis);

    int add(_Calendar::TimeType type, uint64_t v);

    bool equals(Calendar);

    int set(_Calendar::TimeType type, int value);

    int get(_Calendar::TimeType type);

    long int toTimeMillis();

    void setTime(long int msec);

    DateTime getDateTime();

    DateTime getGmtDateTime();

    static bool isLeapYear(int year);

    static int caculateDayOfWeek(int y, int m, int d);

    static bool isValid(int year, int month, int day, int hour, int minute,
                        int second, int millisecond);

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

    int onUpdateByYear(int v);

    int onUpdateByMonth(int v);

    int onUpdateByDayOfWeek(int v);

    int onUpdateByDayOfMonth(int v);

    int onUpdateByDayOfYear(int v);

    void onUpdateMillseconds(uint64_t interval);

    int caculateDayOfYear(int _year, int _month, int _dayOfMonth);

    int *getDays(int year);

    static int kCommonDays[];

    static int kLeapDays[];

    static int kGregorianBase;

    static uint64_t kSecondMillsecond;
    static uint64_t kMinuteMillsecond;
    static uint64_t kHourMillsecond;
    static uint64_t kDayMillsecond;
};

} // namespace obotcha
#endif