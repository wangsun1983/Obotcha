#include <vector>
#include <algorithm>
#include <sys/time.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "DateTime.hpp"

using namespace std;

namespace obotcha {

const std::string _DateTime::ISO8601_FORMAT("%Y-%m-%dT%H:%M:%S%z");
const std::string _DateTime::ISO8601_FRAC_FORMAT("%Y-%m-%dT%H:%M:%s%z");
const std::string _DateTime::ISO8601_REGEX("([\\+-]?\\d{4}(?!\\d{2}\\b))"
	"((-?)"
	"((0[1-9]|1[0-2])(\\3([12]\\d|0[1-9]|3[01]))?|W([0-4]\\d|5[0-2])(-?[1-7])?|"
	"(00[1-9]|0[1-9]\\d|[12]\\d{2}|3([0-5]\\d|6[1-6])))"
	"([T\\s]"
	"((([01]\\d|2[0-3])((:?)[0-5]\\d)?|24\\:?00)([\\.,]\\d+(?!:))?)?"
	"(\\17[0-5]\\d([\\.,]\\d+)?)?([A-I]|[K-Z]|([\\+-])([01]\\d|2[0-3]):?([0-5]\\d)?)?)?)?");

const std::string _DateTime::RFC822_FORMAT("%w, %e %b %y %H:%M:%S %Z");
const std::string _DateTime::RFC822_REGEX("(((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
	"\\d\\d? +"
	"((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) +"
	"\\d\\d(\\d\\d)? +"
	"\\d\\d:\\d\\d(:\\d\\d)? +"
	"(([+\\-]?\\d\\d\\d\\d)|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTime::RFC1123_FORMAT("%w, %e %b %Y %H:%M:%S %Z");
const std::string _DateTime::RFC1123_REGEX(_DateTime::RFC822_REGEX);

const std::string _DateTime::HTTP_FORMAT("%w, %d %b %Y %H:%M:%S %Z");
const std::string _DateTime::HTTP_REGEX("(((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
	"\\d\\d? +"
	"((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) +"
	"\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
	"((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
	"(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTime::RFC850_FORMAT("%W, %e-%b-%y %H:%M:%S %Z");
const std::string _DateTime::RFC850_REGEX(
	"(((Monday)|(Tuesday)|(Wednesday)|(Thursday)|(Friday)|(Saturday)|(Sunday)|"
	"(Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
	"\\d\\d?-((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec))-"
	"\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
	"((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
	"(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTime::RFC1036_FORMAT("%W, %e %b %y %H:%M:%S %Z");
const std::string _DateTime::RFC1036_REGEX(
	"(((Monday)|(Tuesday)|(Wednesday)|(Thursday)|(Friday)|(Saturday)|(Sunday)), *)?"
	"\\d\\d? +"
	"((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) +"
	"\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
	"((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
	"(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTime::ASCTIME_FORMAT("%w %b %f %H:%M:%S %Y");
const std::string _DateTime::ASCTIME_REGEX("((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)) +"
	"((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) +"
	"\\d\\d? +\\d\\d:\\d\\d:\\d\\d +(\\d\\d\\d\\d)");

const std::string _DateTime::SORTABLE_FORMAT("%Y-%m-%d %H:%M:%S");
const std::string _DateTime::SORTABLE_REGEX("(\\d\\d\\d\\d-\\d\\d-\\d\\d \\d\\d:\\d\\d:\\d\\d)");


const std::string _DateTime::FORMAT_LIST[] =
{
	_DateTime::ISO8601_FORMAT,
	_DateTime::ISO8601_FRAC_FORMAT,
	_DateTime::RFC822_FORMAT,
	_DateTime::RFC1123_FORMAT,
	_DateTime::HTTP_FORMAT,
	_DateTime::RFC850_FORMAT,
	_DateTime::RFC1036_FORMAT,
	_DateTime::ASCTIME_FORMAT,
	_DateTime::SORTABLE_FORMAT
};


const std::string _DateTime::WEEKDAY_NAMES[] =
{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};


const std::string _DateTime::MONTH_NAMES[] =
{
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};


const std::string _DateTime::REGEX_LIST[] =
{
	_DateTime::ISO8601_REGEX,
	_DateTime::ISO8601_REGEX, //->_DateTime::ISO8601_FRAC_FORMAT,
	_DateTime::RFC822_REGEX,
	_DateTime::RFC1123_REGEX,
	_DateTime::HTTP_REGEX,
	_DateTime::RFC850_REGEX,
	_DateTime::RFC1036_REGEX,
	_DateTime::ASCTIME_REGEX,
	_DateTime::SORTABLE_REGEX

};


_DateTime::_DateTime() {
    //TODO
}
	
_DateTime::_DateTime(const tm& tmStruct) {
    //TODO
}
		
_DateTime::_DateTime(int year, 
              int month, 
              int day, 
              int hour, 
              int minute, 
              int second, 
              int millisecond,
			  int dayOfWeek,
			  int dayOfMonth,
			  int dayOfYear,
			  long time) {
    _year = year;
	_month = month;
	_day = day;
	_hour = hour;
	_minute = minute;
	_second = second;
	_millisecond = millisecond;
	_dayOfMonth = dayOfMonth;
	_dayOfWeek = dayOfWeek;
	_dayOfYear = dayOfYear;
	_time = time;
}

int _DateTime::year() const{
    return _year;
}
		
int _DateTime::month() const {
    return _month;
}
	
int _DateTime::dayOfMonth() const {
    return _dayOfMonth;
}
		
int _DateTime::dayOfWeek() const {
	return _dayOfWeek;
}
	
int _DateTime::dayOfYear() const {
	return _dayOfYear;
}
	
int _DateTime::hour() const {
	return _hour;
}
		
int _DateTime::hourAMPM() const {
    if (_hour < 1) {
		return 12;
	} else if (_hour > 12) {
        return _hour - 12;
	} else {
		return _hour;
	}
}
	
bool _DateTime::isAM() const {
    return _hour < 12;
}

bool _DateTime::isPM() const {
    return _hour >= 12;
}
		
int _DateTime::minute() const {
    return _minute;
}
		
int _DateTime::second() const {
    return _second;
}
		
int _DateTime::millisecond() const {
    return _millisecond;
}

}
