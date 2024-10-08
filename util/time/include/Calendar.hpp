#ifndef __OBOTCHA_CALENDAR_HPP__
#define __OBOTCHA_CALENDAR_HPP__

#include "DateTime.hpp"
#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Calendar) {
  public:
    enum class Field {
        Year = 0,
        Month,
        DayOfWeek,
        DayOfMonth,
        DayOfYear,
        Hour,
        Minute,
        Second,
        MilliSecond,
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

    int add(_Calendar::Field field, long long v);

    bool equals(Object) override;

    int set(_Calendar::Field field, int value);

    int get(_Calendar::Field field) const;

    int getMaximum(_Calendar::Field);
    
    int getMinimum(_Calendar::Field) const;

    long int toTimeMillis() const;

    void setTime(long int msec);

    DateTime getDateTime();

    DateTime getGmtDateTime();

    static bool IsLeapYear(int year);

    static int CaculateDayOfWeek(int y, int m, int d);

    static bool IsValid(int year, int month, int day, int hour, int minute,
                        int second, int millisecond);

private:
    int mYear;

    int mMonth;         // months since January - [0, 11]

    int mDayOfWeek;     // days since Sunday - [0, 6]

    int mDayOfMonth;    // day of the month - [1, 31]

    int mDayOfYear;     // days since January 1 - [0, 365]

    int mHour;

    int mMinute;

    int mSecond;

    int mMilliSecond;

    void init(long long timeMillis);

    int getMonthDays(int month);

    int onUpdateByYear(int v);

    int onUpdateByMonth(int v);

    int onUpdateByDayOfWeek(int v);

    int onUpdateByDayOfMonth(int v);

    int onUpdateByDayOfYear(int v);

    void onUpdateMillseconds(long long interval);

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