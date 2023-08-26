#include <algorithm>
#include <regex>
#include <sys/time.h>

#include "Calendar.hpp"
#include "DateTime.hpp"
#include "InitializeException.hpp"

namespace obotcha {
#define SKIP_JUNK()                                                            \
    while (it != end && !std::isdigit(*it)) {                                  \
        ++it;                                                                  \
    }

#define SKIP_DIGITS()                                                          \
    while (it != end && std::isdigit(*it))                                     \
    ++it

#define PARSE_NUMBER(var)                                                      \
    while (it != end && std::isdigit(*it))                                     \
    var = var * 10 + ((*it++) - '0')

#define PARSE_NUMBER_N(var, n)                                                 \
    {                                                                          \
        int i = 0;                                                             \
        while (i++ < n && it != end && std::isdigit(*it)) {                    \
            var = var * 10 + ((*it++) - '0');                                  \
        }                                                                      \
    }

#define PARSE_YEAR(var, n, len)                                                \
    {                                                                          \
        len = 0;                                                               \
        int i = 0;                                                             \
        while (i++ < n && it != end && !std::isspace(*it) &&                   \
               std::isdigit(*it)) {                                            \
            len++;                                                             \
            var = var * 10 + ((*it++) - '0');                                  \
        }                                                                      \
    }

#define PARSE_FRACTIONAL_N(var, n)                                             \
    {                                                                          \
        int i = 0;                                                             \
        while (i < n && it != end && std::isdigit(*it)) {                      \
            var = var * 10 + ((*it++) - '0');                                  \
            i++;                                                               \
        }                                                                      \
        while (i++ < n)                                                        \
            var *= 10;                                                         \
    }

const std::string _DateTime::ISO8601_FORMAT("%Y-%m-%dT%H:%M:%S%z");
const std::string _DateTime::ISO8601_FRAC_FORMAT("%Y-%m-%dT%H:%M:%s%z");
const std::string _DateTime::ISO8601_REGEX(
    "([\\+-]?\\d{4}(?!\\d{2}\\b))"
    "((-?)"
    "((0[1-9]|1[0-2])(\\3([12]\\d|0[1-9]|3[01]))?|W([0-4]\\d|5[0-2])(-?[1-7])?|"
    "(00[1-9]|0[1-9]\\d|[12]\\d{2}|3([0-5]\\d|6[1-6])))"
    "([T\\s]"
    "((([01]\\d|2[0-3])((:?)[0-5]\\d)?|24\\:?00)([\\.,]\\d+(?!:))?)?"
    "(\\17[0-5]\\d([\\.,]\\d+)?)?([A-I]|[K-Z]|([\\+-])([01]\\d|2[0-3]):?([0-5]"
    "\\d)?)?)?)?");

const std::string _DateTime::RFC822_FORMAT("%w, %e %b %y %H:%M:%S %Z");
const std::string _DateTime::RFC822_REGEX("(((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
                            "\\d\\d? +"
                            "((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|("
                            "Sep)|(Oct)|(Nov)|(Dec)) +"
                            "\\d\\d(\\d\\d)? +"
                            "\\d\\d:\\d\\d(:\\d\\d)? +"
                            "(([+\\-]?\\d\\d\\d\\d)|(UT)|(GMT)|(EST)|(EDT)|("
                            "CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|\\w)");

const std::string _DateTime::RFC1123_FORMAT("%w, %e %b %Y %H:%M:%S %Z");
const std::string _DateTime::RFC1123_REGEX(_DateTime::RFC822_REGEX);

const std::string _DateTime::HTTP_FORMAT("%w, %d %b %Y %H:%M:%S %Z");
const std::string _DateTime::HTTP_REGEX(
    "(((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
    "\\d\\d? +"
    "((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) "
    "+"
    "\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
    "((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
    "(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|("
    "PST)|(PDT)|\\w)");

const std::string _DateTime::RFC850_FORMAT("%W, %e-%b-%y %H:%M:%S %Z");
const std::string _DateTime::RFC850_REGEX(
    "(((Monday)|(Tuesday)|(Wednesday)|(Thursday)|(Friday)|(Saturday)|(Sunday)|"
    "(Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)), *)?"
    "\\d\\d?-((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)"
    "|(Dec))-"
    "\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
    "((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
    "(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|("
    "PST)|(PDT)|\\w)");

const std::string _DateTime::RFC1036_FORMAT("%W, %e %b %y %H:%M:%S %Z");
const std::string _DateTime::RFC1036_REGEX(
    "(((Monday)|(Tuesday)|(Wednesday)|(Thursday)|(Friday)|(Saturday)|(Sunday)),"
    " *)?"
    "\\d\\d? +"
    "((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|(Sep)|(Oct)|(Nov)|(Dec)) "
    "+"
    "\\d\\d(\\d\\d)? +\\d\\d:\\d\\d(:\\d\\d)? "
    "((UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|(PST)|(PDT)|)?+"
    "(([+\\-]?\\d\\d\\d\\d)?|(UT)|(GMT)|(EST)|(EDT)|(CST)|(CDT)|(MST)|(MDT)|("
    "PST)|(PDT)|\\w)");

const std::string _DateTime::ASCTIME_FORMAT("%w %b %f %H:%M:%S %Y");
const std::string _DateTime::ASCTIME_REGEX("((Mon)|(Tue)|(Wed)|(Thu)|(Fri)|(Sat)|(Sun)) +"
                             "((Jan)|(Feb)|(Mar)|(Apr)|(May)|(Jun)|(Jul)|(Aug)|"
                             "(Sep)|(Oct)|(Nov)|(Dec)) +"
                             "\\d\\d? +\\d\\d:\\d\\d:\\d\\d +(\\d\\d\\d\\d)");

const std::string _DateTime::SORTABLE_FORMAT("%Y-%m-%d %H:%M:%S");
const std::string _DateTime::SORTABLE_REGEX(
    "(\\d\\d\\d\\d-\\d\\d-\\d\\d \\d\\d:\\d\\d:\\d\\d)");

const std::string _DateTime::FORMAT_LIST[] = {
    _DateTime::ISO8601_FORMAT, 
    _DateTime::ISO8601_FRAC_FORMAT,
    _DateTime::RFC822_FORMAT,  
    _DateTime::RFC1123_FORMAT,
    _DateTime::HTTP_FORMAT,    
    _DateTime::RFC850_FORMAT,
    _DateTime::RFC1036_FORMAT, 
    _DateTime::ASCTIME_FORMAT,
    _DateTime::SORTABLE_FORMAT};

const std::string _DateTime::WEEKDAY_NAMES[] = {
    "Sunday",   "Monday", "Tuesday", "Wednesday",
    "Thursday", "Friday", "Saturday"};

const std::string _DateTime::MONTH_NAMES[] = {
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December"};

const std::string _DateTime::REGEX_LIST[] = {
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

_DateTime::_DateTime(int year, int month, int day, int hour, int minute,
                     int second, int millisecond, int microsecond,
                     int dayOfWeek, int dayOfYear, int tzd)
                     :mYear(year),mMonth(month),mDay(day),
                      mHour(hour),mMinute(minute),mSecond(second),mMillisecond(millisecond),mMicrosecond(microsecond),
                      mDayOfWeek(dayOfWeek),mDayOfMonth(day),mDayOfYear(dayOfYear),mTzd(tzd) {
}

_DateTime::_DateTime(String content) {
    Format format = isValid(content->trim());
    Panic(format == Format::Err,InitializeException, "invalid date string")
    parse(format, content);
}

_DateTime::_DateTime(Format format, String content) {
    if (std::string f = REGEX_LIST[format];!std::regex_match(content->getStdString(), 
                                                           std::regex(f))) {
        Trigger(InitializeException, "illegal format")
    }
    parse(format, content);
}

_DateTime::_DateTime(String fmt, String content) {
    if (fmt == nullptr || content == nullptr || fmt->size() < 1 ||
        content->size() == 0) {
        Trigger(InitializeException, "illegal format")
    }
    parse(fmt->getStdString(), content->getStdString());
}

int _DateTime::year() const { 
    return mYear; 
}

int _DateTime::month() const { 
    return mMonth; 
}

int _DateTime::dayOfMonth() const { 
    return mDayOfMonth; 
}

int _DateTime::dayOfWeek() const { 
    return mDayOfWeek; 
}

int _DateTime::dayOfYear() const { 
    return mDayOfYear; 
}

int _DateTime::hour() const { 
    return mHour; 
}

int _DateTime::hourAMPM() const {
    if (mHour < 1) {
        return 12;
    } else if (mHour > 12) {
        return mHour - 12;
    } else {
        return mHour;
    }
}

bool _DateTime::isAM() const { 
    return mHour < 12; 
}

bool _DateTime::isPM() const { 
    return mHour >= 12; 
}

int _DateTime::minute() const { 
    return mMinute; 
}

int _DateTime::second() const { 
    return mSecond; 
}

int _DateTime::millisecond() const { 
    return mMillisecond; 
}

int _DateTime::microsecond() const { 
    return mMicrosecond; 
}

int _DateTime::tzd() const { return mTzd; }

long int _DateTime::toTimeMillis() {
    auto c = createCalendar(mYear,mMonth,mDayOfMonth,mHour,mMinute,mSecond,mMillisecond);
    return c->toTimeMillis();
}

_DateTime::Format _DateTime::isValid(String content) const {
    for (int i = 0; i < Format::Max; i++) {
        std::string f = REGEX_LIST[i];
        if (std::regex_match(content->getStdString(), std::regex(f))) {
            return static_cast<_DateTime::Format>(i);
        }
    }
    return Format::Err;
}

// date time string parse function
int _DateTime::parse(std::string fmt, std::string str) {
    std::string::const_iterator it = str.begin();
    std::string::const_iterator end = str.end();
    std::string::const_iterator itf = fmt.begin();
    std::string::const_iterator endf = fmt.end();

    while (itf != endf && it != end) {
        if (*itf == '%') {
            if (++itf != endf) {
                switch (*itf) {
                case 'w':
                case 'W': {
                    auto start = it;
                    while (it != end && std::isspace(*it)) {
                        ++it;
                    }

                    while (it != end && std::isalpha(*it)) {
                        ++it;
                    }
                    mDayOfWeek = parseDayOfWeek(start,it);
                    break;
                }
                case 'b':
                case 'B':
                    mMonth = parseMonth(it, end);
                    break;
                case 'd':
                case 'e':
                case 'f':
                    SKIP_JUNK()
                    PARSE_NUMBER_N(mDay, 2)
                    mDayOfMonth = mDay;
                    break;
                case 'm':
                case 'n':
                case 'o':
                    SKIP_JUNK()
                    PARSE_NUMBER_N(mMonth, 2)
                    mMonth--;
                    break;
                case 'y':
                case 'Y': {
                    SKIP_JUNK()
                    int len = 0;
                    PARSE_YEAR(mYear, 4, len);
                    if (len == 2) {
                        if (mYear >= 69) {
                            mYear += 1900;
                        } else {
                            mYear += 2000;
                        }
                    }
                } break;
                case 'r':
                    SKIP_JUNK()
                    PARSE_NUMBER(mYear);
                    if (mYear < 1000) {
                        if (mYear >= 69)
                            mYear += 1900;
                        else
                            mYear += 2000;
                    }
                    break;
                case 'H':
                case 'h':
                    SKIP_JUNK()
                    PARSE_NUMBER_N(mHour, 2)
                    break;
                case 'a':
                case 'A':
                    mHour = parseAMPM(it, end, mHour);
                    break;
                case 'M':
                    SKIP_JUNK()
                    PARSE_NUMBER_N(mMinute, 2)
                    break;
                case 'S':
                case 's': // ISO89601 Frac is same as ISO8601's analysis..TODO
                    SKIP_JUNK()
                    PARSE_NUMBER_N(mSecond, 2)
                    if (it != end && (*it == '.' || *it == ',')) {
                        ++it;
                        PARSE_FRACTIONAL_N(mMillisecond, 3)
                        PARSE_FRACTIONAL_N(mMicrosecond, 3)
                        SKIP_DIGITS();
                    }
                    break;
                case 'i':
                    SKIP_JUNK()
                    PARSE_NUMBER_N(mMillisecond, 3)
                    break;
                case 'c':
                    SKIP_JUNK()
                    PARSE_NUMBER_N(mMillisecond, 1)
                    mMillisecond *= 100;
                    break;
                case 'F':
                    SKIP_JUNK()
                    PARSE_FRACTIONAL_N(mMillisecond, 3)
                    PARSE_FRACTIONAL_N(mMicrosecond, 3)
                    SKIP_DIGITS();
                    break;
                case 'z':
                case 'Z':
                    mTzd = parseTZD(it, end);
                    break;
                }
                ++itf;
            }
        } else
            ++itf;
    }

    return 0;
}

int _DateTime::parse(Format format, String content) {
    std::string str = content->getStdString();
    std::string fmt = st(DateTime)::FORMAT_LIST[format];
    return parse(fmt, str);
}

int _DateTime::parseMonth(std::string::const_iterator &it,
                          const std::string::const_iterator &end) const {
    std::string month;
    while (it != end && (std::isspace(*it) || std::ispunct(*it)))
        ++it;
    bool isFirst = true;
    while (it != end && std::isalpha(*it)) {
        char ch = (*it++);
        if (isFirst) {
            month += static_cast<char>(std::toupper(ch));
            isFirst = false;
        } else
            month += static_cast<char>(std::tolower(ch));
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

int _DateTime::parseDayOfWeek(std::string::const_iterator & it,
                const std::string::const_iterator &end) const {
    std::string dayOfWeek;
    
    while (it != end && (std::isspace(*it) || std::ispunct(*it))){
        ++it;
    }
    
    while (it != end && std::isalpha(*it)) {
        char ch = (*it++);
        dayOfWeek += static_cast<char>(std::toupper(ch));
    }
    
    if(dayOfWeek == "MON") {
        return st(Calendar)::Monday;
    } else if(dayOfWeek == "TUE") {
        return st(Calendar)::Tuesday;
    } else if(dayOfWeek == "WED") {
        return st(Calendar)::Wednesday;
    } else if(dayOfWeek == "THU") {
        return st(Calendar)::Thursday;
    } else if(dayOfWeek == "FRI") {
        return st(Calendar)::Friday;
    } else if(dayOfWeek == "SAT") {
        return st(Calendar)::Saturday;
    } else if(dayOfWeek == "SUN") {
        return st(Calendar)::Sunday;
    }

    return -1;
}

int _DateTime::parseAMPM(std::string::const_iterator &it,
                         const std::string::const_iterator &end, int hour) const {
    std::string ampm;
    while (it != end && (std::isspace(*it) || std::ispunct(*it)))
        ++it;
    while (it != end && std::isalpha(*it)) {
        char ch = (*it++);
        ampm += static_cast<char>(std::toupper(ch));
    }

    if (ampm == "AM") {
        return (hour == 12)?0:hour;
    } else if (ampm == "PM") {
        return (hour<12)?(hour+12):hour;
    }

    return -1;
}

int _DateTime::parseTZD(std::string::const_iterator &it,
                        const std::string::const_iterator &end) const {
    struct Zone {
        const char *designator;
        int timeZoneDifferential;
    };

    static Zone zones[] = {{"Z", 0},
                           {"UT", 0},
                           {"GMT", 0},
                           {"BST", 1 * 3600},
                           {"IST", 1 * 3600},
                           {"WET", 0},
                           {"WEST", 1 * 3600},
                           {"CET", 1 * 3600},
                           {"CEST", 2 * 3600},
                           {"EET", 2 * 3600},
                           {"EEST", 3 * 3600},
                           {"MSK", 3 * 3600},
                           {"MSD", 4 * 3600},
                           {"NST", -3 * 3600 - 1800},
                           {"NDT", -2 * 3600 - 1800},
                           {"AST", -4 * 3600},
                           {"ADT", -3 * 3600},
                           {"EST", -5 * 3600},
                           {"EDT", -4 * 3600},
                           {"CST", -6 * 3600},
                           {"CDT", -5 * 3600},
                           {"MST", -7 * 3600},
                           {"MDT", -6 * 3600},
                           {"PST", -8 * 3600},
                           {"PDT", -7 * 3600},
                           {"AKST", -9 * 3600},
                           {"AKDT", -8 * 3600},
                           {"HST", -10 * 3600},
                           {"AEST", 10 * 3600},
                           {"AEDT", 11 * 3600},
                           {"ACST", 9 * 3600 + 1800},
                           {"ACDT", 10 * 3600 + 1800},
                           {"AWST", 8 * 3600},
                           {"AWDT", 9 * 3600}};

    int tzd = 0;
    while (it != end && std::isspace(*it))
        ++it;
    if (it != end) {
        if (std::isalpha(*it)) {
            std::string designator;
            designator += *it++;
            if (it != end && std::isalpha(*it))
                designator += *it++;
            if (it != end && std::isalpha(*it))
                designator += *it++;
            if (it != end && std::isalpha(*it))
                designator += *it++;
            //for (unsigned i = 0; i < sizeof(zones) / sizeof(Zone); ++i) {
            for(auto &myzone:zones) {
                if (designator == myzone.designator) {
                    tzd = myzone.timeZoneDifferential;
                    break;
                }
            }
        }
        if (it != end && (*it == '+' || *it == '-')) {
            int sign = *it == '+' ? 1 : -1;
            ++it;
            int hours = 0;
            PARSE_NUMBER_N(hours, 2)
            if (it != end && *it == ':')
                ++it;
            int minutes = 0;
            PARSE_NUMBER_N(minutes, 2)
            tzd += sign * (hours * 3600 + minutes * 60);
        }
    }
    return tzd;
}

String _DateTime::toString() { 
    return format(Format::HTTP); 
}

String _DateTime::toString(Format fmt) { 
    return format(fmt); 
}

String _DateTime::toString(String fmt) { 
    return format(0, fmt); 
}

String _DateTime::toStringWithTimeZone(int timezone) {
    return format(Format::HTTP, nullptr, timezone);
}

String _DateTime::toStringWithTimeZone(int type, int timezone) {
    return format(type, nullptr, timezone);
}

String _DateTime::toStringWithTimeZone(String fmt, int timezone) {
    return format(0, fmt, timezone);
}

// local format function
String _DateTime::format(int type, String format, int timeZoneDifferential) {
    std::string fmt = (format == nullptr)?st(DateTime)::FORMAT_LIST[type]:format->getStdString();
    std::string::const_iterator it = fmt.begin();
    std::string::const_iterator end = fmt.end();
    std::string str;
    while (it != end) {
        if (*it == '%') {
            if (++it != end) {
                switch (*it) {
                case 'w': {
                    if (mDayOfWeek == -1) {
                        mDayOfWeek = st(Calendar)::caculateDayOfWeek(
                            mYear, mMonth, mDay);
                    }
                    str.append(st(DateTime)::WEEKDAY_NAMES[mDayOfWeek], 0, 3);
                    break;
                }

                case 'W': {
                    if (mDayOfWeek == -1) {
                        mDayOfWeek = st(Calendar)::caculateDayOfWeek(
                            mYear, mMonth, mDay);
                    }
                    str.append(st(DateTime)::WEEKDAY_NAMES[mDayOfWeek]);
                    break;
                }

                case 'b': {
                    str.append(st(DateTime)::MONTH_NAMES[mMonth], 0, 3);
                    break;
                }

                case 'B': {
                    str.append(st(DateTime)::MONTH_NAMES[mMonth]);
                    break;
                }

                case 'd': {
                    char buff[4] = {0};
                    formatNumWidth2(mDayOfMonth, buff, 4);
                    str.append(buff);
                    break;
                }

                case 'e': {
                    char buff[4] = {0};
                    formatNum(mDayOfMonth, buff, 4);
                    str.append(buff);
                    break;
                }

                case 'f': {
                    char buff[4] = {0};
                    formatNumWidth2(mDayOfMonth, buff, 4, false);
                    str.append(buff);
                    break;
                }

                case 'm': {
                    char buff[4] = {0};
                    formatNumWidth2(mMonth + 1, buff, 4);
                    str.append(buff);
                    break;
                }

                case 'n': {
                    char buff[4] = {0};
                    formatNum(mMonth + 1, buff, 4);
                    str.append(buff);
                    break;
                }

                case 'o': {
                    char buff[4] = {0};
                    formatNumWidth2(mMonth + 1, buff, 4, false);
                    str.append(buff);
                    break;
                }

                case 'y': {
                    char buff[4] = {0};
                    formatNumWidth2(mYear % 100, buff, 4);
                    str.append(buff);
                    break;
                }

                case 'Y': {
                    char buff[8] = {0};
                    formatNumWidth4(mYear, buff, 8);
                    str.append(buff);
                    break;
                }

                case 'H': {
                    char buff[4] = {0};
                    formatNumWidth2(mHour, buff, 4);
                    str.append(buff);
                    break;
                }

                case 'h': {
                    char buff[4] = {0};
                    formatNumWidth2(hourAMPM(), buff, 4);
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
                    char buff[4] = {0};
                    formatNumWidth2(mMinute, buff, 4);
                    str.append(buff);
                    break;
                }

                case 'S': {
                    char buff[4] = {0};
                    formatNumWidth2(mSecond, buff, 4);
                    str.append(buff);
                    break;
                }

                case 's': {
                    char buff[4] = {0};
                    formatNumWidth2(mSecond, buff, 4);
                    str.append(buff);

                    str += '.';
                    char buff2[8] = {0};
                    formatNumWidth6(mMillisecond * 1000 + mMicrosecond, buff2,
                                    8);
                    str.append(buff2);
                    break;
                }

                case 'i': {
                    char buff[8] = {0};
                    formatNumWidth3(mMillisecond, buff, 8);
                    str.append(buff);
                    break;
                }

                case 'c': {
                    char buff[32] = {0};
                    formatNum(mMillisecond / 100, buff, 32);
                    str.append(buff);
                    break;
                }

                case 'F': {
                    char buff[8] = {0};
                    formatNumWidth6(mMillisecond, buff, 8);
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

                default:
                    str += *it;
                }
                ++it;
            }
        } else
            str += *it++;
    }

    return createString(str);
}

void _DateTime::tzdISO(std::string &str, int timeZoneDifferential) {
    if (timeZoneDifferential != 0xFFFF) {
        if (timeZoneDifferential >= 0) {
            str += '+';
            char buff[4] = {0};
            formatNumWidth2(timeZoneDifferential / 3600, buff, 4);
            str.append(buff);
            str += ':';

            char buff2[4] = {0};
            formatNumWidth2((timeZoneDifferential % 3600) / 60, buff2, 4);
            str.append(buff2);
        } else {
            str += '-';
            char buff[4] = {0};
            formatNumWidth2(-timeZoneDifferential / 3600, buff, 4);
            str.append(buff);
            str += ':';
            char buff2[4] = {0};
            formatNumWidth2((-timeZoneDifferential % 3600) / 60, buff2, 4);
            str.append(buff2);
        }
    } else {
        str += 'Z';
    }
}

void _DateTime::tzdRFC(std::string &str, int timeZoneDifferential) {
    if (timeZoneDifferential != 0xFFFF) {
        if (timeZoneDifferential >= 0) {
            str += '+';
            char buff[4] = {0};
            formatNumWidth2(timeZoneDifferential / 3600, buff, 4);
            str.append(buff);

            char buff2[4] = {0};
            formatNumWidth2((timeZoneDifferential % 3600) / 60, buff2, 4);
            str.append(buff2);
        } else {
            str += '-';
            char buff[4] = {0};
            formatNumWidth2(-timeZoneDifferential / 3600, buff, 4);
            str.append(buff);

            char buff2[4] = {0};
            formatNumWidth2((-timeZoneDifferential % 3600) / 60, buff2, 4);
            str.append(buff2);
        }
    } else {
        str += "GMT";
    }
}

void _DateTime::formatNum(int value, char *buff, int length) const {
    snprintf(buff, length, "%d", value);
}

void _DateTime::formatNumWidth2(int value, char *buff, int length,
                                bool fillzero) const {
    snprintf(buff, length, fillzero?"%02d":"%2d", value);
}

void _DateTime::formatNumWidth3(int value, char *buff, int length,
                                bool fillzero) const {
    snprintf(buff, length, fillzero?"%03d":"%3d", value);
}

void _DateTime::formatNumWidth6(long value, char *buff, int length,
                                bool fillzero) const {
    snprintf(buff, length, fillzero?"%06ld":"%6ld", value);
}

void _DateTime::formatNumWidth4(int value, char *buff, int length,
                                bool fillzero) const {
    snprintf(buff, length, fillzero?"%04d":"%4d", value);
}

} // namespace obotcha
