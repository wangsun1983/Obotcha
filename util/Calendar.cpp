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
    timeMillis = st(System)::CurrentTimeMillis();
    init();
}

_Calendar::_Calendar(long long mseconds):timeMillis(mseconds) {
    init();
}

_Calendar::_Calendar(int _year, int _month, int _dayOfMonth, int _hour = 0,
                     int _minute = 0, int _second = 0, int msecond = 0) {
    if (!isValid(_year, _month, _dayOfMonth, _hour, _minute, _second,
                 msecond)) {
        Trigger(InitializeException, "invalid param")
    }

    month = _month;
    year = _year;

    const int *_days = getDays(year);
    dayOfMonth = _days[month];
    dayOfMonth = _dayOfMonth;
    dayOfWeek = caculateDayOfWeek(year, month, dayOfMonth);

    hour = _hour;
    minute = _minute;
    second = _second;
    msec = msecond;
}

void _Calendar::setTime(long int timeval) {
    timeMillis = timeval;
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
    const int *_days = isLeapYear(year)?kLeapDays:kCommonDays;

    return (year >= 0 && year <= 9999) && (month >= 0 && month <= 11) &&
           (day >= 1 && day <= _days[month]) && (hour >= 0 && hour <= 23) &&
           (minute >= 0 && minute <= 59) && (second >= 0 && second <= 60) &&
           (millisecond >= 0 && millisecond <= 999);
}

void _Calendar::init() {
    time_t timeT =
        (timeMillis + st(TimeZone)::getZone() * kHourMillsecond) / 1000;

    struct tm now;
    gmtime_r(&timeT, &now);

    year = now.tm_year + kGregorianBase;
    month = now.tm_mon;
    dayOfWeek = now.tm_wday;
    dayOfMonth = now.tm_mday;
    dayOfYear = now.tm_yday;
    hour = now.tm_hour;
    minute = now.tm_min;
    second = now.tm_sec;
    msec = timeMillis % 1000;
}

bool _Calendar::equals(Object obj) {
    auto c = dynamic_cast<_Calendar *>(obj.get_pointer());
    return c != nullptr && (year == c->year && month == c->month &&
            dayOfMonth == c->dayOfMonth && hour == c->hour &&
            minute == c->minute && msec == c->msec);
}

int *_Calendar::getDays(int yearVal) {
    return isLeapYear(yearVal)?kLeapDays:kCommonDays;
}

int _Calendar::onUpdateByYear(int yearVal) {
    // update dayOfMonth
    if (!isLeapYear(yearVal) && month == February && dayOfMonth == 29) {
        dayOfMonth = 28;
    }

    // update dayOfWeek
    dayOfWeek = caculateDayOfWeek(yearVal, month, dayOfMonth);

    // update dayOfYear
    dayOfYear = caculateDayOfYear(yearVal, month, dayOfMonth);

    return 0;
}

int _Calendar::onUpdateByMonth(int mon) {
    // update dayOfMonth
    if (month < 0 || month > December) {
        LOG(ERROR)<<"Calendar,onUpdateByMonth invalid params,mon is "<<mon;
        return -1;
    }

    // update dayOfMonth
    if (const int *_days = getDays(year);dayOfMonth > _days[mon]) {
        dayOfMonth = _days[mon];
    }

    // update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year, month, dayOfMonth);

    // update dayOfYear
    dayOfYear = caculateDayOfYear(year, month, dayOfMonth);

    return 0;
}

int _Calendar::onUpdateByDayOfWeek(int day) {
    if (day <= 0 || day > Saturday) {
        LOG(ERROR)<<"Calendar,onUpdateByDayOfWeek invalid params,day is "<<day;
        return -1;
    }

    int days = day - dayOfWeek;
    dayOfWeek = day;
    add(DayOfYear, days);
    return 0;
}

int _Calendar::onUpdateByDayOfMonth(int day) {
    if (day < 0) {
        LOG(ERROR)<<"Calendar,onUpdateByDayOfMonth invalid params,day is "<<day;
        return -1;
    }

    // update dayOfMonth
    const int *_days = getDays(year);
    dayOfMonth = (day <= _days[month])?day:_days[month];

    // update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year, month, dayOfMonth);

    // update dayOfYear
    dayOfYear = caculateDayOfYear(year, month, dayOfMonth);

    return 0;
}

int _Calendar::onUpdateByDayOfYear(int day) {
    if (day < 0) {
        LOG(ERROR)<<"Calendar,onUpdateByDayOfYear invalid params,day is "<<day;
        return -1;
    }

    // update dayOfMonth
    const int *_days = getDays(year);
    int mon = January;
    for (; mon <= December; mon++) {
        if (day > _days[mon]) {
            day -= _days[mon];
        } else {
            break;
        }
    }
    dayOfMonth = day;

    // update month
    month = mon;

    // update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year, month, dayOfMonth);

    return 0;
}

int _Calendar::caculateDayOfYear(int _year, int _month, int _dayOfMonth) {
    if (_month == January) {
        return _dayOfMonth - 1;
    }

    const int *_days = getDays(_year);

    int allDays = 0;
    for (int mon = January; mon <= _month - 1; mon++) {
        allDays += _days[mon];
    }

    allDays += (_dayOfMonth - 1);

    return allDays;
}

int _Calendar::add(_Calendar::TimeType type, uint64_t v) {
    switch (type) {
        case Year: {
            year += v;
            return onUpdateByYear(year);
        }

        case Month: {
            long int currentMonth = (month + v);
            year += currentMonth / 12;
            month = currentMonth % 12;
            if (month < 0) {
                year--;
                month += 12;
            }
            return onUpdateByMonth(month);
        }

        case DayOfYear:
        case DayOfMonth:
        case DayOfWeek: {
            onUpdateMillseconds(v * kDayMillsecond);
            break;
        }

        case Hour: {
            onUpdateMillseconds(v * kHourMillsecond);
            break;
        }

        case Minute: {
            onUpdateMillseconds(v * kMinuteMillsecond);
            break;
        }

        case Second: {
            onUpdateMillseconds(v * kSecondMillsecond);
            break;
        }

        case MSecond: {
            onUpdateMillseconds(v);
            break;
        }

        default:
            return -1;
    }

    return 0;
}

void _Calendar::onUpdateMillseconds(uint64_t interval) {
    this->timeMillis = toTimeMillis() + interval;
    init();
}

int _Calendar::set(_Calendar::TimeType type, int value) {
    switch (type) {
        case Year: {
            return onUpdateByYear(value);
        }

        case Month: {
            return onUpdateByMonth(value);
        }

        case DayOfWeek: {
            return onUpdateByDayOfWeek(value);
        }

        case DayOfMonth: {
            return onUpdateByDayOfMonth(value);
        }

        case DayOfYear: {
            return onUpdateByDayOfYear(value);
        }

        case Hour: {
            if (value >= 0 && value <= 23) {
                hour = value;
                return 0;
            }
        } break;

        case Minute: {
            if (value >= 0 && value <= 59) {
                minute = value;
                return 0;
            }
        } break;

        case Second: {
            if (value >= 0 && value <= 59) {
                second = value;
                return 0;
            }
        } break;

        case MSecond: {
            if (value >= 0 && value <= 999) {
                msec = value;
                return 0;
            }
        } break;
    }

    return -1;
}

int _Calendar::get(_Calendar::TimeType type) const {
    switch (type) {
        case Year:
            return year;

        case Month:
            return month;

        case DayOfWeek:
            return dayOfWeek;

        case DayOfMonth:
            return dayOfMonth;

        case DayOfYear:
            return dayOfYear;

        case Hour:
            return hour;

        case Minute:
            return minute;

        case Second:
            return second;

        case MSecond:
            return msec;
    }

    return -1;
}

long int _Calendar::toTimeMillis() const {

    std::tm time;
    time.tm_isdst = 0;

    time.tm_year = year - _Calendar::kGregorianBase;
    time.tm_mon = month;
    time.tm_wday = dayOfWeek;
    time.tm_mday = dayOfMonth;
    time.tm_yday = dayOfYear;
    time.tm_hour = hour;
    time.tm_min = minute;
    time.tm_sec = second;

    return std::mktime(&time) * 1000 + msec;
}

bool _Calendar::isLeapYear(int _year) {
    if (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0)) {
        return true;
    }
    return false;
}

int _Calendar::getMonthDays(int _month) {
    const int *_days = getDays(year);
    return _days[_month];
}

DateTime _Calendar::getDateTime() {
    return createDateTime(year, month, dayOfMonth, hour, minute,
                                   second, msec, 0, dayOfWeek, dayOfYear);
}

DateTime _Calendar::getGmtDateTime() {
    Calendar c = createCalendar(year, month, dayOfMonth, hour, minute, second, msec);
    c->add(Hour, -st(TimeZone)::getZone());
    return c->getDateTime();
}

} // namespace obotcha