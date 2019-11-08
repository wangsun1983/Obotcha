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
#include "DateTimeParser.hpp"
#include "DateTimeFormatter.hpp"
#include "Calendar.hpp"

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


DateTime _DateTimeParser::parse(String content) {
    int type = st(DateTimeFormatter)::isValid(content);
	return parse(type,content);
}

DateTime _DateTimeParser::parse(int type,String content) {
    std::string fmt = st(DateTime)::FORMAT_LIST[type];

    if (st(DateTimeFormatter)::isValid(createString(fmt),content) != -1) {
        return nullptr;
    }

	int year   = 0;
	int month  = 0;
	int day    = 0;
	int hour   = 0;
	int minute = 0;
	int second = 0;
	int millis = 0;
	int micros = 0;
	//int tzd    = 0;
    
    std::string str = content->getStdString();

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
					month = parseMonth(it, end);
					break;
				case 'd':
				case 'e':
				case 'f':
					SKIP_JUNK();
					PARSE_NUMBER_N(day, 2);
					break;
				case 'm':
				case 'n':
				case 'o':
					SKIP_JUNK();
					PARSE_NUMBER_N(month, 2);
					break;					
				case 'y':
					SKIP_JUNK();
					PARSE_NUMBER_N(year, 2);
					if (year >= 69)
						year += 1900;
					else
						year += 2000;
					break;
				case 'Y':
					SKIP_JUNK();
					PARSE_NUMBER_N(year, 4);
					break;
				case 'r':
					SKIP_JUNK();
					PARSE_NUMBER(year);
					if (year < 1000)
					{
						if (year >= 69)
							year += 1900;
						else
							year += 2000;
					}
					break;
				case 'H':
				case 'h':
					SKIP_JUNK();
					PARSE_NUMBER_N(hour, 2);
					break;
				case 'a':
				case 'A':
					hour = parseAMPM(it, end, hour);
					break;
				case 'M':
					SKIP_JUNK();
					PARSE_NUMBER_N(minute, 2);
					break;
				case 'S':
					SKIP_JUNK();
					PARSE_NUMBER_N(second, 2);
					break;
				case 's':
					SKIP_JUNK();
					PARSE_NUMBER_N(second, 2);
					if (it != end && (*it == '.' || *it == ','))
					{
						++it;
						PARSE_FRACTIONAL_N(millis, 3);
						PARSE_FRACTIONAL_N(micros, 3);
						SKIP_DIGITS();
					}
					break;
				case 'i':
					SKIP_JUNK();
					PARSE_NUMBER_N(millis, 3);
					break;
				case 'c':
					SKIP_JUNK();
					PARSE_NUMBER_N(millis, 1);
					millis *= 100;
					break;
				case 'F':
					SKIP_JUNK();
					PARSE_FRACTIONAL_N(millis, 3);
					PARSE_FRACTIONAL_N(micros, 3);
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
	if (month == 0) month = 1;
	if (day == 0) day = 1;
	if (st(Calendar)::isValid(year, month, day, hour, minute, second, millis)) {
        Calendar c = createCalendar(year, month, day, hour, minute, second, millis);
        return c->getDateTime();
    }
		//dateTime.assign(year, month, day, hour, minute, second, millis, micros);
	else
		return nullptr;

	//timeZoneDifferential = tzd;
}

int _DateTimeParser::parseMonth(std::string::const_iterator& it, const std::string::const_iterator& end)
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

int _DateTimeParser::parseAMPM(std::string::const_iterator& it, const std::string::const_iterator& end, int hour)
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

int _DateTimeParser::parseTZD(std::string::const_iterator& it, const std::string::const_iterator& end) {
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


}
