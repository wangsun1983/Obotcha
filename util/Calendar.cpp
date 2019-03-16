#include <sys/time.h>
#include <chrono>

#include "Calendar.hpp"
#include "TimeZone.hpp"

namespace obotcha {

int _Calendar::commonDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int _Calendar::leapDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int _Calendar::GregorianBase = 1900;


_Calendar::_Calendar() {
    timeval tv;
    gettimeofday(&tv, NULL);
    timeMillis = tv.tv_sec*1000 + tv.tv_usec/1000;
    init();
}

_Calendar::_Calendar(long int mseconds) {
    timeMillis = mseconds;
    init();
}

_Calendar::_Calendar(int _year,int _month,int _dayOfMonth,int _hour = 0,int _minute = 0,int _second = 0) {
    year = _year;

    if(month > December) {
        month = December;
    }

    int *_days = getDays(year);
    dayOfMonth = _days[_month];

    if(_dayOfMonth < dayOfMonth) {
        dayOfMonth = _dayOfMonth;
    }

    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    onUpdateByYear(year);

    hour = _hour;
    minute = _minute;
    second = _second;
    msec = 0;
}

void _Calendar::setTime(long int msec) {
    timeMillis = msec;
    init();
}

int _Calendar::caculateDayOfWeek(int y, int m, int d) {  
    m += 1;
    if(m ==0 || m ==1) {  
        m += 12;  
        y--;  
    }

    return (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
}  

void _Calendar::init() {

    auto mTime = std::chrono::milliseconds(timeMillis);
    auto tp = std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm* now = std::gmtime(&tt);

    year = now->tm_year;
    month = now->tm_mon;
    printf("init month is %d\n",month);
    dayOfWeek = now->tm_wday;
    dayOfMonth = now->tm_mday;
    dayOfYear = now->tm_yday;
    hour = now->tm_hour + st(TimeZone)::getZone();
    minute = now->tm_min;
    second = now->tm_sec;
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

    hour += _hour%24;
    int _day = hour/24;

    if(_day != 0) {
        increaseDay(_day);
    }

}

void _Calendar::decreaseHour(int _hour) {
    if(_hour < 0) {
        return increaseHour(-_hour);
    }

    hour -= hour%24;
    int _day = hour/24;

    if(_day != 0) {
        decreaseDay(_day);
    }
}

void _Calendar::increaseMinute(int _minute) {
    if(_minute < 0) {
        return decreaseMinute(-_minute);
    }

    minute += _minute%60;

    int _hour = _minute/60;
    if(_hour != 0) {
        increaseHour(_hour);
    }
}

void _Calendar::decreaseMinute(int _minute) {
    if(_minute < 0) {
        return increaseMinute(-_minute);
    }

    minute += _minute%60;
    int _hour = _minute/60;

    if(_hour != 0) {
        decreaseHour(_hour);
    }
}

void _Calendar::increaseSecond(int _second) {
    if(_second < 0) {
        return decreaseSecond(-_second);
    }

    second += _second%60;
    int _minute = _minute/60;

    if(_minute != 0) {
        increaseMinute(_minute);
    }
}

void _Calendar::decreaseSecond(int _second) {
    if(_second < 0) {
        return increaseSecond(-_second);
    }

    second += _second%60;
    int _minute = _minute/60;

    if(_minute != 0) {
        decreaseMinute(_minute);
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
    if(day <= 0 && day > Sunday) {
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
        return _dayOfMonth;
    }
    
    int *_days = getDays(_year);

    int allDays = 0;
    for(int mon = January;mon <= _month - 1;mon++) {
        allDays += _days[mon];
    }

    allDays += DayOfMonth;

    return allDays;
}

bool _Calendar::set(CalendarType type,int value) {
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
}

int _Calendar::get(CalendarType type) {
    switch(type) {
        case Year:
            return GregorianBase + year;
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
}

long int _Calendar::toTimeMillis() {

    std::tm time;

    time.tm_year = year;
    time.tm_mon = month;
    time.tm_wday = dayOfWeek;
    time.tm_mday = dayOfMonth;
    time.tm_yday = dayOfYear;
    time.tm_hour = hour;
    time.tm_min = minute;
    time.tm_sec = second;
    
    return std::mktime(&time) *1000 + timeMillis%1000;

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
    
    year += mon/11;
    month += mon%11;

    //update dayOfMonth
    int *_days = getDays(year);

    //update dayOfMonth
    if(dayOfMonth > _days[mon]) {
        dayOfMonth = _days[mon];
    }

    //update dayOfWeek
    dayOfWeek = caculateDayOfWeek(year,month,dayOfMonth);

    //update dayOfYear
    dayOfYear = caculateDayOfYear(year,month,dayOfMonth);
}

void _Calendar::decreaseMonth(int mon) {
    year -= mon/11;
    month -= mon%11;

    //update dayOfMonth
    int *_days = getDays(year);

    //update dayOfMonth
    if(dayOfMonth > _days[mon]) {
        dayOfMonth = _days[mon];
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

}