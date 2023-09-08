#include <chrono>
#include <sys/time.h>

#include "Calendar.hpp"
#include "InitializeException.hpp"
#include "System.hpp"
#include "TimeZone.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

int _Calendar::kCommonDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int _Calendar::kLeapDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int _Calendar::kGregorianBase = 1900;
uint64_t _Calendar::kSecondMillsecond = 1000;
uint64_t _Calendar::kMinuteMillsecond = 60 * kSecondMillsecond;
uint64_t _Calendar::kHourMillsecond = 60 * kMinuteMillsecond;
uint64_t _Calendar::kDayMillsecond = 24 * kHourMillsecond;

_Calendar::_Calendar(sp<_Calendar> c) : _Calendar(c->toTimeMillis()) {
}

_Calendar::_Calendar() {
    mTimeMillis = st(System)::CurrentTimeMillis();
    init();
}

_Calendar::_Calendar(long long mseconds):mTimeMillis(mseconds) {
    init();
}

_Calendar::_Calendar(int year, int month, int dayOfMonth, int hour = 0,
                     int minute = 0, int second = 0, int millisecond = 0) {
    if (!isValid(year,month,dayOfMonth,hour,minute,second,millisecond)) {
        Trigger(InitializeException, "invalid param")
    }

    mMonth = month;
    mYear = year;
    mDayOfMonth = dayOfMonth;
    mDayOfWeek = caculateDayOfWeek(mYear,mMonth,mDayOfMonth);
    mHour = hour;
    mMinute = minute;
    mSecond = second;
    mMilliSecond = millisecond;
}

void _Calendar::setTime(long int timeval) {
    mTimeMillis = timeval;
    init();
}

int _Calendar::caculateDayOfWeek(int y, int m, int d) {
    m += 1;
    d += 1;

    if (m == 1 || m == 2) {
        m += 12;
        y--;
    }

    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
}

bool _Calendar::isValid(int year, int month, int day, int hour, int minute,
                        int second, int millisecond) {
    const int *days = isLeapYear(year)?kLeapDays:kCommonDays;

    return (year >= 0 && year <= 9999) && (month >= 0 && month <= 11) &&
           (day >= 1 && day <= days[month]) && (hour >= 0 && hour <= 23) &&
           (minute >= 0 && minute <= 59) && (second >= 0 && second <= 60) &&
           (millisecond >= 0 && millisecond <= 999);
}

void _Calendar::init() {
    time_t timeT = (mTimeMillis + st(TimeZone)::GetZone() * kHourMillsecond) / 1000;

    struct tm now;
    gmtime_r(&timeT, &now);

    mYear = now.tm_year + kGregorianBase;
    mMonth = now.tm_mon;
    mDayOfWeek = now.tm_wday;
    mDayOfMonth = now.tm_mday;
    mDayOfYear = now.tm_yday;
    mHour = now.tm_hour;
    mMinute = now.tm_min;
    mSecond = now.tm_sec;
    mMilliSecond = mTimeMillis % 1000;
}

bool _Calendar::equals(Object obj) {
    auto c = dynamic_cast<_Calendar *>(obj.get_pointer());
    return c != nullptr && (mYear == c->mYear && mMonth == c->mMonth &&
            mDayOfMonth == c->mDayOfMonth && mHour == c->mHour &&
            mMinute == c->mMinute && mMilliSecond == c->mMilliSecond);
}

int *_Calendar::getDays(int year) {
    return isLeapYear(year)?kLeapDays:kCommonDays;
}

int _Calendar::onUpdateByYear(int year) {
    // update dayOfMonth
    if (!isLeapYear(year) && mMonth == February && mDayOfMonth == 29) {
        mDayOfMonth = 28;
    }

    // update dayOfWeek
    mDayOfWeek = caculateDayOfWeek(year, mMonth, mDayOfMonth);

    // update dayOfYear
    mDayOfYear = caculateDayOfYear(year, mMonth, mDayOfMonth);
    
    mYear = year;
    return 0;
}

int _Calendar::onUpdateByMonth(int month) {
    // update dayOfMonth
    if (month < 0 || month > December) {
        LOG(ERROR)<<"Calendar,onUpdateByMonth invalid params,mon is "<<month;
        return -1;
    }

    // update dayOfMonth
    if (const int *days = getDays(mYear);mDayOfMonth > days[month]) {
        mDayOfMonth = days[month];
    }

    // update dayOfWeek
    mDayOfWeek = caculateDayOfWeek(mYear, month, mDayOfMonth);

    // update dayOfYear
    mDayOfYear = caculateDayOfYear(mYear, month, mDayOfMonth);

    mMonth = month;
    return 0;
}

int _Calendar::onUpdateByDayOfWeek(int day) {
    if (day < 0 || day > Saturday) {
        LOG(ERROR)<<"Calendar,onUpdateByDayOfWeek invalid params,day is "<<day;
        return -1;
    }

    int days = day - mDayOfWeek;
    if(days != 0) {
        mDayOfWeek = day;
        add(Field::DayOfYear, days);
    }
    return 0;
}

int _Calendar::onUpdateByDayOfMonth(int day) {
    if (day < 0) {
        LOG(ERROR)<<"Calendar,onUpdateByDayOfMonth invalid params,day is "<<day;
        return -1;
    }

    // update dayOfMonth
    const int *days = getDays(mYear);
    mDayOfMonth = (day <= days[mMonth])?day:days[mMonth];

    // update dayOfWeek
    mDayOfWeek = caculateDayOfWeek(mYear, mMonth, mDayOfMonth);

    // update dayOfYear
    mDayOfYear = caculateDayOfYear(mYear, mMonth, mDayOfMonth);

    return 0;
}

int _Calendar::onUpdateByDayOfYear(int day) {
    if (day < 0) {
        LOG(ERROR)<<"Calendar,onUpdateByDayOfYear invalid params,day is "<<day;
        return -1;
    }

    mDayOfYear = day;
    // update dayOfMonth
    const int *days = getDays(mYear);
    int mon = January;
    for (; mon <= December; mon++) {
        if (day + 1 > days[mon]) {
            day -= days[mon];
            continue;
        }
        break;
    }

    mDayOfMonth = day + 1;

    // update month
    mMonth = mon;

    // update dayOfWeek
    mDayOfWeek = caculateDayOfWeek(mYear,mMonth,mDayOfMonth);
    return 0;
}

int _Calendar::caculateDayOfYear(int year, int month, int dayOfMonth) {
    if (month == January) {
        return dayOfMonth - 1;
    }

    int allDays = 0;
    const int *days = getDays(year);

    for (int mon = January; mon <= month - 1; mon++) {
        allDays += days[mon];
    }

    allDays += (dayOfMonth - 1);
    return allDays;
}

int _Calendar::add(_Calendar::Field field, uint64_t v) {
    switch (field) {
        case Field::Year: {
            mYear += v;
            return onUpdateByYear(mYear);
        }

        case Field::Month: {
            long int currentMonth = (mMonth + v);
            mYear += currentMonth / 12;
            mMonth = currentMonth % 12;
            if (mMonth < 0) {
                mYear--;
                mMonth += 12;
            }
            return onUpdateByMonth(mMonth);
        }

        case Field::DayOfYear:
        case Field::DayOfMonth:
        case Field::DayOfWeek: {
            onUpdateMillseconds(v * kDayMillsecond);
            break;
        }

        case Field::Hour: {
            onUpdateMillseconds(v * kHourMillsecond);
            break;
        }

        case Field::Minute: {
            onUpdateMillseconds(v * kMinuteMillsecond);
            break;
        }

        case Field::Second: {
            onUpdateMillseconds(v * kSecondMillsecond);
            break;
        }

        case Field::MilliSecond: {
            onUpdateMillseconds(v);
            break;
        }

        default:
            return -1;
    }

    return 0;
}

void _Calendar::onUpdateMillseconds(uint64_t interval) {
    this->mTimeMillis = toTimeMillis() + interval;
    init();
}

int _Calendar::set(_Calendar::Field field, int value) {
    switch (field) {
        case Field::Year: {
            return onUpdateByYear(value);
        }

        case Field::Month: {
            return onUpdateByMonth(value);
        }

        case Field::DayOfWeek: {
            return onUpdateByDayOfWeek(value);
        }

        case Field::DayOfMonth: {
            return onUpdateByDayOfMonth(value);
        }

        case Field::DayOfYear: {
            return onUpdateByDayOfYear(value);
        }

        case Field::Hour: {
            if (value >= 0 && value <= 23) {
                mHour = value;
                return 0;
            }
        } break;

        case Field::Minute: {
            if (value >= 0 && value <= 59) {
                mMinute = value;
                return 0;
            }
        } break;

        case Field::Second: {
            if (value >= 0 && value <= 59) {
                mSecond = value;
                return 0;
            }
        } break;

        case Field::MilliSecond: {
            if (value >= 0 && value <= 999) {
                mMilliSecond = value;
                return 0;
            }
        } break;
    }

    return -1;
}

int _Calendar::get(_Calendar::Field field) const {
    switch (field) {
        case Field::Year:
            return mYear;

        case Field::Month:
            return mMonth;

        case Field::DayOfWeek:
            return mDayOfWeek;

        case Field::DayOfMonth:
            return mDayOfMonth;

        case Field::DayOfYear:
            return mDayOfYear;

        case Field::Hour:
            return mHour;

        case Field::Minute:
            return mMinute;

        case Field::Second:
            return mSecond;

        case Field::MilliSecond:
            return mMilliSecond;
    }

    return -1;
}

int _Calendar::getMaximum(_Calendar::Field field) {
    switch(field) {
        case Field::DayOfWeek:
        return 7;

        case Field::DayOfYear:
        return isLeapYear(mYear)?366:365;

        case Field::DayOfMonth:
        return getMonthDays(mMonth);

        default:
        LOG(ERROR)<<"Calendar unsupport maximum filed ";
    }
    return -1;
}

int _Calendar::getMinimum(_Calendar::Field field) {
    switch(field) {
        case Field::DayOfWeek:
        return Month::January;

        case Field::DayOfYear:
        return 0;

        case Field::DayOfMonth:
        return 1;

        default:
        LOG(ERROR)<<"Calendar unsupport minimum filed ";
    }
    return -1;
}

long int _Calendar::toTimeMillis() const {

    std::tm time;
    time.tm_isdst = 0;

    time.tm_year = mYear - _Calendar::kGregorianBase;
    time.tm_mon = mMonth;
    time.tm_wday = mDayOfWeek;
    time.tm_mday = mDayOfMonth;
    time.tm_yday = mDayOfYear;
    time.tm_hour = mHour;
    time.tm_min = mMinute;
    time.tm_sec = mSecond;

    return std::mktime(&time) * 1000 + mMilliSecond;
}

bool _Calendar::isLeapYear(int year) {
    return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}

int _Calendar::getMonthDays(int month) {
    const int *days = getDays(mYear);
    return days[month];
}

DateTime _Calendar::getDateTime() {
    return createDateTime(mYear, mMonth, mDayOfMonth, mHour,mMinute,
                                   mSecond, mMilliSecond, 0, mDayOfWeek, mDayOfYear);
}

DateTime _Calendar::getGmtDateTime() {
    Calendar c = createCalendar(mYear, mMonth, mDayOfMonth, mHour, mMinute, 
                                mSecond, mMilliSecond);
    c->add(Field::Hour, -st(TimeZone)::GetZone());
    return c->getDateTime();
}

} // namespace obotcha