#ifndef __DATE_TIME_HPP__
#define __DATE_TIME_HPP__

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

using namespace std;

namespace obotcha {

enum DateTimeFormat {
    DateTimeFormatISO8601,
	DateTimeFormatISO8601Frac,
	DateTimeFormatRFC822,
	DateTimeFormatRFC1123,
	DateTimeFormatHTTP,
	DateTimeFormatRFC850,
	DateTimeFormatRFC1036,
	DateTimeFormatASCTIME,
	DateTimeFormatSORTABLE,
	DateTimeFormatMax
};

DECLARE_SIMPLE_CLASS(DateTime) {
public:
    _DateTime();
	
	_DateTime(const tm& tmStruct);

    _DateTime(int year, 
              int month, 
              int day, 
              int hour = 0, 
              int minute = 0, 
              int second = 0, 
              int millisecond = 0,
			  int dayOfWeek = 0,
			  int dayOfMonth = 0,
			  int dayOfYear = 0,
			  long time = 0);

    int year() const;
		/// Returns the year.
		
	int month() const;
		/// Returns the month (1 to 12).
	
	int dayOfMonth() const;
		/// Returns the day within the month (1 to 31).
		
	int dayOfWeek() const;
		/// Returns the weekday (0 to 6, where
		/// 0 = Sunday, 1 = Monday, ..., 6 = Saturday).
	
	int dayOfYear() const;
		/// Returns the number of the day in the year.
		/// January 1 is 1, February 1 is 32, etc.
	
	int hour() const;
		/// Returns the hour (0 to 23).
		
	int hourAMPM() const;
		/// Returns the hour (0 to 12).
	
	bool isAM() const;
		/// Returns true if hour < 12;

	bool isPM() const;
		/// Returns true if hour >= 12.
		
	int minute() const;
		/// Returns the minute (0 to 59).
		
	int second() const;
		/// Returns the second (0 to 59).
		
	int millisecond() const;
		/// Returns the millisecond (0 to 999)

    static const std::string ISO8601_FORMAT;
    static const std::string ISO8601_FRAC_FORMAT;
    static const std::string ISO8601_REGEX;

    static const std::string RFC822_FORMAT;
    static const std::string RFC822_REGEX;

    static const std::string RFC1123_FORMAT;
    static const std::string RFC1123_REGEX;

    static const std::string HTTP_FORMAT;
    static const std::string HTTP_REGEX;

    static const std::string RFC850_FORMAT;
    static const std::string RFC850_REGEX;

    static const std::string RFC1036_FORMAT;
    static const std::string RFC1036_REGEX;

    static const std::string ASCTIME_FORMAT;
    static const std::string ASCTIME_REGEX;

    static const std::string SORTABLE_FORMAT;
    static const std::string SORTABLE_REGEX;

	static const std::string FORMAT_LIST[];
	static const std::string WEEKDAY_NAMES[];
	static const std::string MONTH_NAMES[];
	static const std::string REGEX_LIST[];		
	
private:

    int _year;
	int _month;
	int _day;
	int _hour;
	int _minute;
	int _second;
	int _millisecond;
	int _microsecond;
    int _dayOfWeek; //[0,6]
    int _dayOfMonth; //[1,31]
    int _dayOfYear; //[0,365]
    long _time;
};

}
#endif