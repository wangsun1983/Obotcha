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
#include "DateTimeFormatter.hpp"
#include "NumberFormatter.hpp"
#include "TimeZone.hpp"

namespace obotcha {
    	
String _DateTimeFormatter::format(DateTime datetime,int type,int timeZoneDifferential) {
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
				    str.append(st(DateTime)::WEEKDAY_NAMES[datetime->dayOfWeek()], 0, 3); 
					break;
				}

				case 'W': {
					str.append(st(DateTime)::WEEKDAY_NAMES[datetime->dayOfWeek()]); 
					break;
				}

				case 'b': {
					str.append(st(DateTime)::MONTH_NAMES[datetime->month()], 0, 3);
					break;
				}

				case 'B': {
					str.append(st(DateTime)::MONTH_NAMES[datetime->month()]); 
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
					String number = st(NumberFormatter)::format(datetime->month() + 1);
					str.append(number->getStdString());
					break;
				}

				case 'o': {
					//NumberFormatter::append(str, dateTime.month(), 2); 
					String number = st(NumberFormatter)::format(datetime->month() + 1,2);
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

void _DateTimeFormatter::tzdISO(std::string& str, int timeZoneDifferential)
{
	if (timeZoneDifferential != 0xFFFF)
	{
		if (timeZoneDifferential >= 0)
		{
			str += '+';
			String number = st(NumberFormatter)::format0(timeZoneDifferential/3600, 2);
			str.append(number->getStdString());
			str += ':';
			number = st(NumberFormatter)::format0((timeZoneDifferential%3600)/60, 2);
			str.append(number->getStdString());
		}
		else
		{
			str += '-';
			String number = st(NumberFormatter)::format0(-timeZoneDifferential/3600, 2);
			str.append(number->getStdString());
			str += ':';
			number = st(NumberFormatter)::format0((-timeZoneDifferential%3600)/60, 2);
			str.append(number->getStdString());
		}
	}
	else str += 'Z';
}


void _DateTimeFormatter::tzdRFC(std::string& str, int timeZoneDifferential)
{
	if (timeZoneDifferential != 0xFFFF)
	{
		if (timeZoneDifferential >= 0)
		{
			str += '+';
			String number = st(NumberFormatter)::format0(timeZoneDifferential/3600, 2);
			str.append(number->getStdString());

			number = st(NumberFormatter)::format0((timeZoneDifferential%3600)/60, 2);
			str.append(number->getStdString());
		}
		else
		{
			str += '-';
			String number = st(NumberFormatter)::format0(-timeZoneDifferential/3600, 2);
			str.append(number->getStdString());

			number = st(NumberFormatter)::format0((-timeZoneDifferential%3600)/60, 2);
			str.append(number->getStdString());
		}		
	}
	else str += "GMT";
}

int _DateTimeFormatter::isValid(String content) {
	for(int i = 0; i < DateTimeFormatMax;i++) {
		std::string f = st(DateTime)::REGEX_LIST[i];
		if(std::regex_match(content->getStdString(),std::regex(f))) {
			return i;
		}
	}
	return -1;
}

int _DateTimeFormatter::isValid(String fmt,String content) {
	if(std::regex_match(content->getStdString(),std::regex(fmt->getStdString()))) {
		return 0;
	}

	return -1;
}


}
