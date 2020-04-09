#include <vector>
#include <algorithm>
#include <sys/time.h>
#include <regex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "String.hpp"
#include "DateTime.hpp"
#include "InitializeException.hpp"

using namespace std;

namespace obotcha {
#define SKIP_JUNK() \
	while (it != end && !std::isdigit(*it)) ++it


#define SKIP_DIGITS() \
	while (it != end && std::isdigit(*it)) ++it


#define PARSE_NUMBER(var) \
	while (it != end && std::isdigit(*it)) var = var*10 + ((*it++) - '0')


#define PARSE_NUMBER_N(var, n) \
	{ int i = 0; while (i++ < n && it != end && std::isdigit(*it)) var = var*10 + ((*it++) - '0'); }


#define PARSE_FRACTIONAL_N(var, n) \
	{ int i = 0; while (i < n && it != end && std::isdigit(*it)) { var = var*10 + ((*it++) - '0'); i++; } while (i++ < n) var *= 10; }


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

_DateTime::_DateTime(String content) {
	_year = 0;
	_month = 0;
	_day = 0;
	_hour = 0;
	_minute = 0;
	_second = 0;
	_millisecond = 0;
	_dayOfMonth = 0;
	_dayOfWeek = 0;
	_dayOfYear = 0;

    int type = isValid(content);
	if(type == -1) {
		throw InitializeException("invalid date string");
	}
    parse(type,content);
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

int _DateTime::isValid(String content) {
	for(int i = 0; i < DateTimeFormatMax;i++) {
		std::string f = REGEX_LIST[i];
		if(std::regex_match(content->getStdString(),std::regex(f))) {
			return i;
		}
	}
	return -1;
}

//date time string parse function
int _DateTime::parse(int type,String content) {
    std::string str = content->getStdString();
    std::string fmt = st(DateTime)::FORMAT_LIST[type];

	std::string::const_iterator it   = str.begin();
	std::string::const_iterator end  = str.end();
	std::string::const_iterator itf  = fmt.begin();
	std::string::const_iterator endf = fmt.end();

	while (itf != endf && it != end)
	{
		if (*itf == '%')
		{
			if (++itf != endf)
			{
				switch (*itf)
				{
				case 'w':
				case 'W':
					while (it != end && std::isspace(*it)) ++it;
					while (it != end && std::isalpha(*it)) ++it;
					break;
				case 'b':
				case 'B':
					_month = parseMonth(it, end);
					break;
				case 'd':
				case 'e':
				case 'f':
					SKIP_JUNK();
					PARSE_NUMBER_N(_day, 2);
					break;
				case 'm':
				case 'n':
				case 'o':
					SKIP_JUNK();
					PARSE_NUMBER_N(_month, 2);
					break;					
				case 'y':
					SKIP_JUNK();
					PARSE_NUMBER_N(_year, 2);
					if (_year >= 69)
						_year += 1900;
					else
						_year += 2000;
					break;
				case 'Y':
					SKIP_JUNK();
					PARSE_NUMBER_N(_year, 4);
					break;
				case 'r':
					SKIP_JUNK();
					PARSE_NUMBER(_year);
					if (_year < 1000)
					{
						if (_year >= 69)
							_year += 1900;
						else
							_year += 2000;
					}
					break;
				case 'H':
				case 'h':
					SKIP_JUNK();
					PARSE_NUMBER_N(_hour, 2);
					break;
				case 'a':
				case 'A':
					_hour = parseAMPM(it, end, _hour);
					break;
				case 'M':
					SKIP_JUNK();
					PARSE_NUMBER_N(_minute, 2);
					break;
				case 'S':
					SKIP_JUNK();
					PARSE_NUMBER_N(_second, 2);
					break;
				case 's':
					SKIP_JUNK();
					PARSE_NUMBER_N(_second, 2);
					if (it != end && (*it == '.' || *it == ','))
					{
						++it;
						PARSE_FRACTIONAL_N(_millisecond, 3);
						PARSE_FRACTIONAL_N(_microsecond, 3);
						SKIP_DIGITS();
					}
					break;
				case 'i':
					SKIP_JUNK();
					PARSE_NUMBER_N(_millisecond, 3);
					break;
				case 'c':
					SKIP_JUNK();
					PARSE_NUMBER_N(_millisecond, 1);
					_millisecond *= 100;
					break;
				case 'F':
					SKIP_JUNK();
					PARSE_FRACTIONAL_N(_millisecond, 3);
					PARSE_FRACTIONAL_N(_microsecond, 3);
					SKIP_DIGITS();
					break;
				case 'z':
				case 'Z':
					//tzd = parseTZD(it, end);
					break;
				}
				++itf;
			}
		}
		else ++itf;
	}
	if (_month == 0) _month = 1;
	if (_day == 0) _day = 1;
}

int _DateTime::parseMonth(std::string::const_iterator& it, const std::string::const_iterator& end)
{
	std::string month;
	while (it != end && (std::isspace(*it) || std::ispunct(*it))) ++it;
	bool isFirst = true;
	while (it != end && std::isalpha(*it)) {
		char ch = (*it++);
		if (isFirst) { 
			month += static_cast<char>(std::toupper(ch));
			isFirst = false; 
		}
		else month += static_cast<char>(std::tolower(ch));
	}

	if (month.length() < 3) {
        return -1;
    }

	for (int i = 0; i < 12; ++i) {
		if (st(DateTime)::MONTH_NAMES[i].find(month) == 0) {
            return i;
        }
	}

	return -1;
}

int _DateTime::parseAMPM(std::string::const_iterator& it, const std::string::const_iterator& end, int hour)
{
	std::string ampm;
	while (it != end && (std::isspace(*it) || std::ispunct(*it))) ++it;
	while (it != end && std::isalpha(*it)) {
		char ch = (*it++);
		ampm += static_cast<char>(std::toupper(ch));
	}

	if (ampm == "AM") {
		if (hour == 12)
			return 0;
		else
			return hour;
	} else if (ampm == "PM") {
		if (hour < 12)
			return hour + 12;
		else
			return hour;
	}
	
    return -1;
}

int _DateTime::parseTZD(std::string::const_iterator& it, const std::string::const_iterator& end) {
	struct Zone
	{
		const char* designator;
		int         timeZoneDifferential;
	};

	static Zone zones[] =
	{
		{"Z",           0},
		{"UT",          0},
		{"GMT",         0},
		{"BST",    1*3600},
		{"IST",    1*3600},
		{"WET",         0},
		{"WEST",   1*3600},
		{"CET",    1*3600},
		{"CEST",   2*3600},
		{"EET",    2*3600},
		{"EEST",   3*3600},
		{"MSK",    3*3600},
		{"MSD",    4*3600},
		{"NST",   -3*3600-1800},
		{"NDT",   -2*3600-1800},
		{"AST",   -4*3600},
		{"ADT",   -3*3600},
		{"EST",   -5*3600},
		{"EDT",   -4*3600},
		{"CST",   -6*3600},
		{"CDT",   -5*3600},
		{"MST",   -7*3600},
		{"MDT",   -6*3600},
		{"PST",   -8*3600},
		{"PDT",   -7*3600},
		{"AKST",  -9*3600},
		{"AKDT",  -8*3600},
		{"HST",  -10*3600},
		{"AEST",  10*3600},
		{"AEDT",  11*3600},
		{"ACST",   9*3600+1800},
		{"ACDT",  10*3600+1800},
		{"AWST",   8*3600},
		{"AWDT",   9*3600}
	};

	int tzd = 0;
	while (it != end && std::isspace(*it)) ++it;
	if (it != end)
	{
		if (std::isalpha(*it))
		{
			std::string designator;
			designator += *it++;
			if (it != end && std::isalpha(*it)) designator += *it++;
			if (it != end && std::isalpha(*it)) designator += *it++;
			if (it != end && std::isalpha(*it)) designator += *it++;
			for (unsigned i = 0; i < sizeof(zones)/sizeof(Zone); ++i)
			{
				if (designator == zones[i].designator)
				{
					tzd = zones[i].timeZoneDifferential;
					break;
				}
			}
		}
		if (it != end && (*it == '+' || *it == '-'))
		{
			int sign = *it == '+' ? 1 : -1;
			++it;
			int hours = 0;
			PARSE_NUMBER_N(hours, 2);
			if (it != end && *it == ':') ++it;
			int minutes = 0;
			PARSE_NUMBER_N(minutes, 2);
			tzd += sign*(hours*3600 + minutes*60);
		}
	}
	return tzd;
}

String _DateTime::toString() {
    return format(DateTimeFormatHTTP);
}

String _DateTime::toString(int type) {
    return format(type);
}

//local format function
String _DateTime::format(int type,int timeZoneDifferential) {
    std::string fmt = st(DateTime)::FORMAT_LIST[type];
	std::string::const_iterator it  = fmt.begin();
	std::string::const_iterator end = fmt.end();
	std::string str;
	while (it != end) {
		if (*it == '%') {
			if (++it != end)
			{
				switch (*it)
				{
				case 'w': {
				    str.append(st(DateTime)::WEEKDAY_NAMES[_dayOfWeek], 0, 3); 
					break;
				}

				case 'W': {
					str.append(st(DateTime)::WEEKDAY_NAMES[_dayOfWeek]); 
					break;
				}

				case 'b': {
					str.append(st(DateTime)::MONTH_NAMES[_month], 0, 3);
					break;
				}

				case 'B': {
					str.append(st(DateTime)::MONTH_NAMES[_month]); 
					break;
				}

				case 'd': {
					//NumberFormatter::append0(str, dateTime.day(), 2);
					char buff[4] = {0};
					formatNumWidth2(_dayOfMonth,buff,4);
					str.append(buff);
					break;
				}

				case 'e': {
					//NumberFormatter::append(str, dateTime.day()); 
					char buff[4] = {0};
					formatNum(_dayOfMonth,buff,4);
					str.append(buff);
					break;
				}

				case 'f': {
					//NumberFormatter::append(str, dateTime.day(), 2);
					//String number = st(NumberFormatter)::format(_dayOfMonth,2);
					char buff[4] = {0};
					formatNumWidth2(_dayOfMonth,buff,4);
					str.append(buff);
					break;
				}

				case 'm': {
					//NumberFormatter::append0(str, dateTime.month(), 2); 
					//String number = st(NumberFormatter)::format0(_month,2);
					char buff[4] = {0};
					formatNumWidth2(_month,buff,4);
					str.append(buff);
					break;
				}

				case 'n': {
					//NumberFormatter::append(str, dateTime.month()); 
					//String number = st(NumberFormatter)::format(_month + 1);
					char buff[4] = {0};
					formatNum(_month + 1,buff,4);
					str.append(buff);
					break;
				}

				case 'o': {
					//NumberFormatter::append(str, dateTime.month(), 2); 
					//String number = st(NumberFormatter)::format(_month + 1,2);
					char buff[4] = {0};
					formatNumWidth2(_month + 1,buff,4);
					str.append(buff);
					break;
				}

				case 'y': {
					//NumberFormatter::append0(str, dateTime.year() % 100, 2);
					//String number = st(NumberFormatter)::format0(_year%100,2);
					char buff[4] = {0};
					formatNumWidth2(_year%100,buff,4);
					str.append(buff);
					break;
				}

				case 'Y': {
					//NumberFormatter::append0(str, dateTime.year(), 4); 
					//String number = st(NumberFormatter)::format0(_year,4);
					char buff[8] = {0};
					formatNumWidth4(_year,buff,8);					
					str.append(buff);
					break;
				}

				case 'H': {
				    //NumberFormatter::append0(str, dateTime.hour(), 2);
					//String number = st(NumberFormatter)::format0(_hour,2);
					char buff[4] = {0};
					formatNumWidth2(_hour,buff,4);					
					str.append(buff);
					break;
				}

				case 'h': {
					//NumberFormatter::append0(str, dateTime.hourAMPM(), 2); 
					//String number = st(NumberFormatter)::format0(hourAMPM(),2);
					char buff[4] = {0};
					formatNumWidth2(hourAMPM(),buff,4);
					str.append(buff);
					break;
				}

				case 'a': {
					str.append(isAM() ? "am" : "pm"); 

					break;
				}

				case 'A': {
					str.append(isAM() ? "AM" : "PM"); 
					break;
				}

				case 'M': {
					//NumberFormatter::append0(str, dateTime.minute(), 2); 
					//String number = st(NumberFormatter)::format0(_minute,2);
					char buff[4] = {0};
					formatNumWidth2(_minute,buff,4);
					str.append(buff);
					break;
				}

				case 'S': {
					//NumberFormatter::append0(str, dateTime.second(), 2);
					//String number = st(NumberFormatter)::format0(_second,2);
					char buff[4] = {0};
					formatNumWidth2(_second,buff,4);
					str.append(buff);
					break;
				}

				case 's': {
					//NumberFormatter::append0(str, dateTime.second(), 2);
					//String number = st(NumberFormatter)::format0(_second,2);
					char buff[4] = {0};
					formatNumWidth2(_second,buff,4);
					str.append(buff);

				    str += '.';
				    //NumberFormatter::append0(str, dateTime.millisecond()*1000 + dateTime.microsecond(), 6);
				    //number = st(NumberFormatter)::format0(_millisecond,6);
					char buff2[8] = {0};
					formatNumWidth6(_millisecond,buff2,6);
					str.append(buff2);
					break;
				}

				case 'i': {
					//NumberFormatter::append0(str, dateTime.millisecond(), 3); 
					//String number = st(NumberFormatter)::format0(_millisecond,3);
					char buff[8] = {0};
					formatNumWidth3(_millisecond,buff,8);
					str.append(buff);
					break;
				}

				case 'c': {
					//NumberFormatter::append(str, dateTime.millisecond()/100); 
					//String number = st(NumberFormatter)::format(_millisecond/100);
					char buff[32] = {0};
					formatNum(_millisecond/100,buff,32);
					str.append(buff);
					break;
				}

				case 'F': {
					//NumberFormatter::append0(str, dateTime.millisecond()*1000 + dateTime.microsecond(), 6); 
					//String number = st(NumberFormatter)::format0(_millisecond,6);
					char buff[8] = {0};
					formatNumWidth6(_millisecond,buff,8);
					str.append(buff);
					break;
				}

				case 'z': {
					tzdISO(str, timeZoneDifferential); 
					break;
				}

				case 'Z': {
					tzdRFC(str, timeZoneDifferential); 
					break;
				}

				default:  str += *it;
				}
				++it;
			}
		}
		else str += *it++;
	}

	return createString(str);
}

void _DateTime::tzdISO(std::string& str, int timeZoneDifferential) {
    if (timeZoneDifferential != 0xFFFF) {
		if (timeZoneDifferential >= 0) {
			str += '+';
			char buff[4] = {0};
			//String number = st(NumberFormatter)::format0(timeZoneDifferential/3600, 2);
			formatNumWidth2(timeZoneDifferential/3600,buff,4);
			str.append(buff);
			str += ':';

			char buff2[4] = {0};
			//number = st(NumberFormatter)::format0((timeZoneDifferential%3600)/60, 2);
			formatNumWidth2((timeZoneDifferential%3600)/60,buff2,4);
			str.append(buff2);
		} else {
			str += '-';
			//String number = st(NumberFormatter)::format0(-timeZoneDifferential/3600, 2);
			char buff[4] = {0};
			formatNumWidth2(-timeZoneDifferential/3600,buff,4);
			str.append(buff);
			str += ':';
			char buff2[4] = {0};
			//number = st(NumberFormatter)::format0((-timeZoneDifferential%3600)/60, 2);
			formatNumWidth2((-timeZoneDifferential%3600)/60,buff2,4);
			str.append(buff2);
		}
	}
	else str += 'Z';
}

void _DateTime::tzdRFC(std::string& str, int timeZoneDifferential) {
    if (timeZoneDifferential != 0xFFFF) {
		if (timeZoneDifferential >= 0) {
			str += '+';
			char buff[4] = {0};
			//String number = st(NumberFormatter)::format0(timeZoneDifferential/3600, 2);
			formatNumWidth2(timeZoneDifferential/3600,buff,2);
			str.append(buff);
             
			char buff2[4] = {0};
			//number = st(NumberFormatter)::format0((timeZoneDifferential%3600)/60, 2);
			formatNumWidth2((timeZoneDifferential%3600)/60,buff2,2);
			str.append(buff2);
		} else {
			str += '-';
			char buff[4] = {0};
			//String number = st(NumberFormatter)::format0(-timeZoneDifferential/3600, 2);
			formatNumWidth2(-timeZoneDifferential/3600,buff,2);
			str.append(buff);

            char buff2[4] = {0};
			//number = st(NumberFormatter)::format0((-timeZoneDifferential%3600)/60, 2);
			formatNumWidth2((-timeZoneDifferential%3600)/60,buff2,2);
			str.append(buff2);
		}		
	}
	else str += "GMT";
}

void _DateTime::formatNum(int value,char *buff,int length) {
    snprintf(buff,length,"%d",value);
}
void _DateTime::formatNumWidth2(int value,char *buff,int length) {
	snprintf(buff,length,"%02d",value);
}

void _DateTime::formatNumWidth3(int value,char *buff,int length) {
	snprintf(buff,length,"%03d",value);
}

void _DateTime::formatNumWidth6(long value,char *buff,int length) {
    snprintf(buff,length,"%06d",value);
}

void _DateTime::formatNumWidth4(int value,char *buff,int length){
	snprintf(buff,length,"%04d",value);
}


}
