#include <sys/time.h>
#include <chrono>

#include "Calendar.hpp"
#include "TimeZone.hpp"
#include "System.hpp"
#include "InitializeException.hpp"

namespace obotcha {

int _Calendar::commonDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int _Calendar::leapDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int _Calendar::GregorianBase = 1900;

_Calendar::_Calendar() {
    timeMillis = st(System)::currentTimeMillis();
    init();
}

_Calendar::_Calendar(long long mseconds) {
    timeMillis = mseconds;
    init();
}

_Calendar::_Calendar(int _year,int _month,int _dayOfMonth,int _hour = 0,int _minute = 0,int _second = 0,int msecond = 0) {
    if(!isValid(_year,_month,_dayOfMonth,_hour,_minute,_second,msecond)) {
        throwInitializeException("invalid param");
    }

    month = _month;

    int *_days = getDays(year);
    dayOfMonth = _days[month];
    dayOfMonth = _dayOfMonth;
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    hour = _hour;
    minute = _minute;
    second = _second;
    msec = msecond;
}

void _Calendar::setTime(long int msec) {
    timeMillis = msec;
    init();
}

int _Calendar::caculateDayOfWeek(int y, int m, int d) {
    m += 1;
    d += 1;

    if(m == 1 || m == 2) {  
        m += 12;  
        y--;  
    }

    int week = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
	return week;
}

bool _Calendar::isValid(int year, int month, int day, int hour, int minute, int second, int millisecond) {
    int *_days = nullptr;
    bool isLeap = isLeapYear(year);
    if(isLeap) {
        _days = leapDays;
    } else {
        _days = commonDays;
    }

    return
		(year >= 0 && year <= 9999) &&
		(month >= 1 && month <= 12) &&
		(day >= 1 && day <= _days[month]) &&
		(hour >= 0 && hour <= 23) &&
		(minute >= 0 && minute <= 59) &&
		(second >= 0 && second <= 60) &&
		(millisecond >= 0 && millisecond <= 999);
}

void _Calendar::init() {

    //auto mTime = std::chrono::milliseconds(timeMillis);
    //auto tp = std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds>(mTime);
    //auto tt = std::chrono::system_clock::to_time_t(tp);
    //std::tm* now = std::gmtime(&tt);
    time_t timeT = timeMillis/1000l;
    
    struct tm now;
    gmtime_r(&timeT, &now);

    year = now.tm_year + GregorianBase;
    month = now.tm_mon;
    dayOfWeek = now.tm_wday;
    dayOfMonth = now.tm_mday;
    dayOfYear = now.tm_yday;
    hour = now.tm_hour + st(TimeZone)::getZone();
    minute = now.tm_min;
    second = now.tm_sec;
    msec = timeMillis%1000;

    if(hour >= 24) {
        hour = hour - 24;
        increaseDay(1);
    }
}

bool _Calendar::sameDate(Calendar c) {
    return (year == c->year 
           && month == c->month 
           && dayOfMonth == c->dayOfMonth);
}

int *_Calendar::getDays(int year) {
    bool isLeap = isLeapYear(year);
    if(isLeap) {
        return leapDays;
    }

    return commonDays;
}

void _Calendar::increaseHour(int _hour) {
    if(_hour < 0) {
        return decreaseHour(-_hour);
    }
    int _day = (hour + _hour)/24;
    hour = (hour+_hour)%24;

    if(_day != 0) {
        increaseDay(_day);
    }

}

void _Calendar::decreaseHour(int _hour) {
    if(_hour < 0) {
        return increaseHour(-_hour);
    }

    hour -= _hour;
    if(hour < 0) {
        int _day = (-hour)/24 + 1;
        decreaseDay(_day);
        hour = 24*_day + hour;
    }
}

void _Calendar::increaseMinute(int _minute) {
    if(_minute < 0) {
        return decreaseMinute(-_minute);
    }

    int _hour = (minute+_minute)/60;
    minute = (minute+_minute)%60;

    if(_hour != 0) {
        increaseHour(_hour);
    }
}

void _Calendar::decreaseMinute(int _minute) {
    if(_minute < 0) {
        return increaseMinute(-_minute);
    }

    minute -= _minute;

    if(minute < 0) {
        int _hour = (-minute)/60 + 1;
        decreaseHour(_hour);
        minute = 60*_hour + minute;
    }
}

void _Calendar::increaseSecond(int _second) {
    if(_second < 0) {
        return decreaseSecond(-_second);
    }

    int minuteTmp = (second+_second)/60;
    second = (second+_second)%60;

    if(minuteTmp != 0) {
        increaseMinute(minuteTmp);
    }
}

void _Calendar::decreaseSecond(int _second) {
    if(_second < 0) {
        return increaseSecond(-_second);
    }

    second -= _second;

    if(second < 0) {
        int _minute = (-second)/60 + 1;
        decreaseMinute(_minute);
        second = 60*_minute + second;
    }
}

bool _Calendar::onUpdateByYear(int value) {
    year = value;

    //update dayOfMonth
    bool isLeap = isLeapYear(year);
    if(!isLeap && month == February && dayOfMonth == 29) {
        dayOfMonth = 28;
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);

    return true;
}

bool _Calendar::onUpdateByMonth(int mon) {
    //update dayOfMonth
    if(month < 0 || month > December) {
        return false;
    }
    
    int *_days = getDays(year);

    //update dayOfMonth
    if(dayOfMonth > _days[mon]) {
        dayOfMonth = _days[mon];
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);

    return true;
}

bool _Calendar::onUpdateByDayOfWeek(int day) {
    if(day <= 0 || day > Saturday) {
        return false;
    }

    int days = day - dayOfWeek;

    dayOfWeek = day;
    if(days > 0) {
        increaseDay(days);
    } else if(days < 0){
        decreaseDay(days);
    }

    return true;
}

bool _Calendar::onUpdateByDayOfMonth(int day) {
    if(day < 0) {
        return false;
    }

    //update dayOfMonth
    int *_days = getDays(year);
    if(day <= _days[month]) {
        dayOfMonth = day;
    } else {
        dayOfMonth = _days[month];
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);

    return true;
}

bool _Calendar::onUpdateByDayOfYear(int day) {
    if(day < 0) {
        return false;
    }

    //update dayOfMonth
    int *_days = getDays(year);
    int mon = January;
    for(;mon <= December;mon++) {
        if(day > _days[mon]) {
            day -= _days[mon];
        } else {
            break;
        }
    }
    dayOfMonth = day;

    //update month
    month = mon;

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    return true;
}


int _Calendar::caculateDayOfYear(int _year,int _month,int _dayOfMonth) {
    if(_month == January) {
        return _dayOfMonth - 1;
    }
    
    int *_days = getDays(_year);

    int allDays = 0;
    for(int mon = January;mon <= _month - 1;mon++) {
        allDays += _days[mon];
    }

    allDays += (_dayOfMonth - 1);

    return allDays;
}

bool _Calendar::set(int type,int value) {
    bool ret = false;
    switch(type) {
        case Year: {
            ret = onUpdateByYear(value);
            break;
        }

        case Month:{
            ret = onUpdateByMonth(value);
            break;
        }

        case DayOfWeek:{
            ret = onUpdateByDayOfWeek(value);
            break;
        }

        case DayOfMonth:{
            ret = onUpdateByDayOfMonth(value);
            break;
        }
        break;

        case DayOfYear:{
            ret = onUpdateByDayOfYear(value);
            break;
        }
        break;

        case Hour:{
            if(value >= 0 && value <= 23) {
                hour = value;
                ret = true;
            }
            break;
        }

        case Minute:{
            if(value >= 0 && value <= 59) {
                minute = value;
                ret = true;
            }
            break;
        }

        case Second: {
            if(value >= 0 && value <= 59) {
                second = value;
                ret = true;
            }
            break;
        }
        
        case MSecond:{
            if(value >= 0 && value <= 999) {
                msec = value;
                ret = true;
            }
            break;
        }
    }

    return ret;
}

int _Calendar::get(int type) {
    switch(type) {
        case Year:
            return year;
        break;

        case Month:
            return month;
        break;

        case DayOfWeek:
            return dayOfWeek;
        break;

        case DayOfMonth:
            return dayOfMonth;
        break;

        case DayOfYear:
            return dayOfYear;
        break;

        case Hour:
            return hour;
        break;

        case Minute:
            return minute;
        break;

        case Second:
            return second;
        break;

        case MSecond:
            return msec;
        break;
    }

    return -1;
}

long int _Calendar::toTimeMillis() {

    std::tm time;

    time.tm_year = year - _Calendar::GregorianBase;
    time.tm_mon = month;
    time.tm_wday = dayOfWeek;
    time.tm_mday = dayOfMonth;
    time.tm_yday = dayOfYear;
    time.tm_hour = hour;
    time.tm_min = minute;
    time.tm_sec = second;
    
    return std::mktime(&time) *1000 + msec;

}

bool _Calendar::isLeapYear(int _year) {
    if (((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0)) {
        return true;
    }
    return false;
}
    
void _Calendar::increaseYear(int _year) {
    year += _year;
    
    //update dayOfMonth
    int *_days = getDays(year);

    //update dayOfMonth
    if(dayOfMonth > _days[month]) {
        dayOfMonth = _days[month];
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);
}


void _Calendar::decreaseYear(int _year) {
    if(_year > year) {
        return ;
    }

    year -= _year;

    //update dayOfMonth
    int *_days = getDays(year);

    //update dayOfMonth
    if(dayOfMonth > _days[month]) {
        dayOfMonth = _days[month];
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);
}
    


void _Calendar::increaseMonth(int mon) {
    
    year += (month + mon)/12;
    month = (month + mon)%12;

    //update dayOfMonth
    int *_days = getDays(year);

    //update dayOfMonth
    if(dayOfMonth > _days[month]) {
        dayOfMonth = _days[month];
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);
}

void _Calendar::decreaseMonth(int mon) {
    month -= mon;
    if(month < 0) {
        year -= (-month)/12;

        if(-month%12 != 0) {
            year--;
            month = 12 + month;
        } else {
            month = 0;
        }
    }

    //update dayOfMonth
    int *_days = getDays(year);

    //update dayOfMonth
    if(dayOfMonth > _days[month]) {
        dayOfMonth = _days[month];
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);
}

void _Calendar::increaseDay(int day) {

    dayOfMonth += day;
    int daysInMonth = getMonthDays(month);
    while (dayOfMonth > daysInMonth) {
        dayOfMonth -= daysInMonth;
        month += 1;
        if (month > December) {
            year += 1;
            month = 0;
        }
    }
    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);
    
    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);
}

void _Calendar::decreaseDay(int day) {
    dayOfMonth -= day;
    while (dayOfMonth <= 0){
        month--;
        if (month < 0) {
            year--;
            month = December;
        }
        dayOfMonth += getMonthDays(month);
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);
}

int _Calendar::getMonthDays(int _month) {
    //if (isLeapYear(year) && (February == month)){
    //    return 29;
    //}
    int *_days = getDays(year);

    return _days[_month];
}

DateTime _Calendar::getDateTime() {
    DateTime date = createDateTime(year,
                                   month,
                                   dayOfMonth,
                                   hour,
                                   minute,
                                   second,
                                   msec,
                                   0,
                                   dayOfWeek,
                                   dayOfYear);

    return date;                                   
}

DateTime _Calendar::getGmtDateTime() {
    Calendar c = createCalendar(year,
                                   month,
                                   dayOfMonth,
                                   hour,
                                   minute,
                                   second,
                                   msec);
    int hour = st(TimeZone)::getZone();                                   
    c->decreaseHour(hour);
    return c->getDateTime();               
}

}