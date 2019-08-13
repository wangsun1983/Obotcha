#ifndef __DATE_TIME_FORMAT_HPP__
#define __DATE_TIME_FORMAT_HPP__

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

enum DateTimeFormat {
    DateTimeFormatISO8601,
	DateTimeFormatISO8601Frac,
	DateTimeFormatRFC822,
	DateTimeFormatRFC1123,
	DateTimeFormatHTTP,
	DateTimeFormatRFC850,
	DateTimeFormatRFC1036,
	DateTimeFormatASCTIME,
	DateTimeFormatSORTABLE
};

DECLARE_SIMPLE_CLASS(DateTimeFormatter) {
public:
    static String format(DateTime,int type);
    
private:

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
};

}
#endif
