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
#include "DateTimeFormatter.hpp"
#include "NumberFormatter.hpp"

namespace obotcha {
    
const std::string _DateTimeFormatter::ISO8601_FORMAT("%Y-%m-%dT%H:%M:%S%z");
const std::string _DateTimeFormatter::ISO8601_FRAC_FORMAT("%Y-%m-%dT%H:%M:%s%z");
const std::string _DateTimeFormatter::ISO8601_REGEX("([\\+-]?\\d{4}(?!\\d{2}\\b))"
	"((-?)"
	"((0[1-9]|1[0-2])(\\3([12]\\d|0[1-9]|3[01]))?|W([0-4]\\d|5[0-2])(-?[1-7])?|"
	"(00[1-9]|0[1-9]\\d|[12]\\d{2}|3([0-5]\\d|6[1-6])))"
	"([T\\s]"
	"((([01]\\d|2[0-3])((:?)[0-5]\\d)?|24\\:?00)([\\.,]\\d+(?!:))?)?"
	"(\\17[0-5]\\d([\\.,]\\d+)?)?([A-I]|[K-Z]|([\\+-])([01]\\d|2[0-3]):?([0-5]\\d)?)?)?)?");

const std::string _DateTimeFormatter::RFC822_FORMAT("%w, %e %b %y %H:%M:%S %Z");
const std::string _DateTimeFormatter::RFC822_REGEX("(((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
	"\\d\\d? +"
	"((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) +"
	"\\d\\d(\\d\\d)? +"
	"\\d\\d:\\d\\d(:\\d\\d)? +"
	"(([+\\-]?\\d\\d\\d\\d)|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTimeFormatter::RFC1123_FORMAT("%w, %e %b %Y %H:%M:%S %Z");
const std::string _DateTimeFormatter::RFC1123_REGEX(_DateTimeFormatter::RFC822_REGEX);

const std::string _DateTimeFormatter::HTTP_FORMAT("%w, %d %b %Y %H:%M:%S %Z");
const std::string _DateTimeFormatter::HTTP_REGEX("(((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
	"\\d\\d? +"
	"((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) +"
	"\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
	"((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
	"(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTimeFormatter::RFC850_FORMAT("%W, %e-%b-%y %H:%M:%S %Z");
const std::string _DateTimeFormatter::RFC850_REGEX(
	"(((Monday)|(Tuesday)|(Wednesday)|(Thursday)|(Friday)|(Saturday)|(Sunday)|"
	"(Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
	"\\d\\d?-((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec))-"
	"\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
	"((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
	"(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTimeFormatter::RFC1036_FORMAT("%W, %e %b %y %H:%M:%S %Z");
const std::string _DateTimeFormatter::RFC1036_REGEX(
	"(((Monday)|(Tuesday)|(Wednesday)|(Thursday)|(Friday)|(Saturday)|(Sunday)), *)?"
	"\\d\\d? +"
	"((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) +"
	"\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
	"((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
	"(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTimeFormatter::ASCTIME_FORMAT("%w %b %f %H:%M:%S %Y");
const std::string _DateTimeFormatter::ASCTIME_REGEX("((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)) +"
	"((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) +"
	"\\d\\d? +\\d\\d:\\d\\d:\\d\\d +(\\d\\d\\d\\d)");

const std::string _DateTimeFormatter::SORTABLE_FORMAT("%Y-%m-%d %H:%M:%S");
const std::string _DateTimeFormatter::SORTABLE_REGEX("(\\d\\d\\d\\d-\\d\\d-\\d\\d \\d\\d:\\d\\d:\\d\\d)");


const std::string _DateTimeFormatter::FORMAT_LIST[] =
{
	_DateTimeFormatter::ISO8601_FORMAT,
	_DateTimeFormatter::ISO8601_FRAC_FORMAT,
	_DateTimeFormatter::RFC822_FORMAT,
	_DateTimeFormatter::RFC1123_FORMAT,
	_DateTimeFormatter::HTTP_FORMAT,
	_DateTimeFormatter::RFC850_FORMAT,
	_DateTimeFormatter::RFC1036_FORMAT,
	_DateTimeFormatter::ASCTIME_FORMAT,
	_DateTimeFormatter::SORTABLE_FORMAT
};


const std::string _DateTimeFormatter::WEEKDAY_NAMES[] =
{
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};


const std::string _DateTimeFormatter::MONTH_NAMES[] =
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


const std::string _DateTimeFormatter::REGEX_LIST[] =
{
	_DateTimeFormatter::ISO8601_REGEX,
	_DateTimeFormatter::RFC822_REGEX,
	_DateTimeFormatter::RFC1123_REGEX,
	_DateTimeFormatter::HTTP_REGEX,
	_DateTimeFormatter::RFC850_REGEX,
	_DateTimeFormatter::RFC1036_REGEX,
	_DateTimeFormatter::ASCTIME_REGEX,
	_DateTimeFormatter::SORTABLE_REGEX
};


String _DateTimeFormatter::format(DateTime datetime,int type) {
	std::string fmt = FORMAT_LIST[type];
	std::string::const_iterator it  = fmt.begin();
	std::string::const_iterator end = fmt.end();
	std::string str;
	while (it != end)
	{
		if (*it == '%')
		{
			if (++it != end)
			{
				switch (*it)
				{
				case 'w': {
				    str.append(_DateTimeFormatter::WEEKDAY_NAMES[datetime->dayOfWeek()], 0, 3); 
					break;
				}

				case 'W': {
					str.append(_DateTimeFormatter::WEEKDAY_NAMES[datetime->dayOfWeek()]); 
					break;
				}

				case 'b': {
					str.append(_DateTimeFormatter::MONTH_NAMES[datetime->month() - 1], 0, 3);
					break;
				}

				case 'B': {
					str.append(_DateTimeFormatter::MONTH_NAMES[datetime->month() - 1]); 
					break;
				}

				case 'd': {
					//NumberFormatter::append0(str, dateTime.day(), 2); 
					String number = st(NumberFormatter)::format0(datetime->dayOfMonth(),2);
					str.append(number->getStdString());
					break;
				}

				case 'e': {
					//NumberFormatter::append(str, dateTime.day()); 
					String number = st(NumberFormatter)::format(datetime->dayOfMonth());
					str.append(number->getStdString());
					break;
				}

				case 'f': {
					//NumberFormatter::append(str, dateTime.day(), 2);
					String number = st(NumberFormatter)::format(datetime->dayOfMonth(),2);
					str.append(number->getStdString());
					break;
				}

				case 'm': {
					//NumberFormatter::append0(str, dateTime.month(), 2); 
					String number = st(NumberFormatter)::format0(datetime->month(),2);
					str.append(number->getStdString());
					break;
				}

				case 'n': {
					//NumberFormatter::append(str, dateTime.month()); 
					String number = st(NumberFormatter)::format(datetime->month());
					str.append(number->getStdString());
					break;
				}

				case 'o': {
					//NumberFormatter::append(str, dateTime.month(), 2); 
					String number = st(NumberFormatter)::format(datetime->month(),2);
					str.append(number->getStdString());
					break;
				}

				case 'y': {
					//NumberFormatter::append0(str, dateTime.year() % 100, 2);
					String number = st(NumberFormatter)::format0(datetime->year()%100,2);
					str.append(number->getStdString());
					break;
				}

				case 'Y': {
					//NumberFormatter::append0(str, dateTime.year(), 4); 
					String number = st(NumberFormatter)::format0(datetime->year(),4);
					str.append(number->getStdString());
					break;
				}

				case 'H': {
				    //NumberFormatter::append0(str, dateTime.hour(), 2);
					String number = st(NumberFormatter)::format0(datetime->hour(),2);
					str.append(number->getStdString());
					break;
				}

				case 'h': {
					//NumberFormatter::append0(str, dateTime.hourAMPM(), 2); 
					String number = st(NumberFormatter)::format0(datetime->hourAMPM(),2);
					str.append(number->getStdString());
					break;
				}

				case 'a': {
					str.append(datetime->isAM() ? "am" : "pm"); 

					break;
				}

				case 'A': {
					str.append(datetime->isAM() ? "AM" : "PM"); 
					break;
				}

				case 'M': {
					//NumberFormatter::append0(str, dateTime.minute(), 2); 
					String number = st(NumberFormatter)::format0(datetime->minute(),2);
					str.append(number->getStdString());
					break;
				}

				case 'S': {
					//NumberFormatter::append0(str, dateTime.second(), 2);
					String number = st(NumberFormatter)::format0(datetime->second(),2);
					str.append(number->getStdString());
					break;
				}

				case 's': {
					//NumberFormatter::append0(str, dateTime.second(), 2);
					String number = st(NumberFormatter)::format0(datetime->second(),2);
					str.append(number->getStdString());
				    str += '.';
				    //NumberFormatter::append0(str, dateTime.millisecond()*1000 + dateTime.microsecond(), 6);
				    number = st(NumberFormatter)::format0(datetime->millisecond(),6);
					str.append(number->getStdString());
					break;
				}

				case 'i': {
					//NumberFormatter::append0(str, dateTime.millisecond(), 3); 
					String number = st(NumberFormatter)::format0(datetime->millisecond(),3);
					str.append(number->getStdString());
					break;
				}

				case 'c': {
					//NumberFormatter::append(str, dateTime.millisecond()/100); 
					String number = st(NumberFormatter)::format(datetime->millisecond()/100);
					str.append(number->getStdString());
					break;
				}

				case 'F': {
					//NumberFormatter::append0(str, dateTime.millisecond()*1000 + dateTime.microsecond(), 6); 
					String number = st(NumberFormatter)::format0(datetime->millisecond(),6);
					str.append(number->getStdString());
					break;
				}

				case 'z': {
					//tzdISO(str, timeZoneDifferential); 
					break;
				}

				case 'Z': {
					//tzdRFC(str, timeZoneDifferential); 
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

}
