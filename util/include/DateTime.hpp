#ifndef __OBOTCHA_DATE_TIME_HPP__
#define __OBOTCHA_DATE_TIME_HPP__

#include <algorithm>
#include <sys/time.h>
#include <vector>

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(DateTime) {
  public:
    enum Format {
        ISO8601 = 0,
        ISO8601Frac,
        RFC822,
        RFC1123,
        HTTP,
        RFC850,
        RFC1036,
        ASCTIME,
        SORTABLE,
        Max,
        Err = -1,
    };

    _DateTime() = default;

    _DateTime(int year, int month, int day, int hour = 0, int minute = 0,
              int second = 0, int millisecond = 0, int microsecond = 0,
              int dayOfWeek = -1, int dayOfYear = -1, int timezone = 0);

    explicit _DateTime(String);

    _DateTime(Format, String);

    _DateTime(String, String);

    int year() const;
    /// Returns the year.

    int month() const;
    /// Returns the month (0 to 11).

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

    int microsecond() const;

    int tzd() const;

    long int toTimeMillis();
    
    String toString() override;

    String toString(Format);

    String toString(String format);

    String toStringWithTimeZone(int timezone);

    String toStringWithTimeZone(int type, int timezone);

    String toStringWithTimeZone(String format, int timezone);

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
    int mYear = 0;
    int mMonth = 0;
    int mDay = 0;
    int mHour = 0;
    int mMinute = 0;
    int mSecond = 0;
    int mMillisecond = 0;
    int mMicrosecond = 0;
    int mDayOfWeek = 0;  //[0,6]
    int mDayOfMonth = 0; //[1,31]
    int mDayOfYear = 0;  //[0,365]
    //long mTime;
    int mTzd = 0;
    // local parse function
    int parse(Format type, String content);
    int parse(std::string format, std::string content);

    int parseDayOfWeek(std::string::const_iterator & start,
                   const std::string::const_iterator &end) const;

    int parseMonth(std::string::const_iterator & it,
                   const std::string::const_iterator &end) const;
    int parseAMPM(std::string::const_iterator & it,
                  const std::string::const_iterator &end, int hour) const;
    int parseTZD(std::string::const_iterator & it,
                 const std::string::const_iterator &end) const;

    // local format function
    String format(int type, String fmt = nullptr,
                  int timeZoneDifferential = 0xFFFF);
    void tzdISO(std::string & str, int timeZoneDifferential);
    void tzdRFC(std::string & str, int timeZoneDifferential);

    void formatNum(int value, char *buff, int length) const;
    void formatNumWidth2(int value, char *buff, int length,
                         bool fillzero = true) const;
    void formatNumWidth3(int value, char *buff, int length,
                         bool fillzero = true) const;
    void formatNumWidth4(int value, char *buff, int length,
                         bool fillzero = true) const;
    void formatNumWidth6(long value, char *buff, int length,
                         bool fillzero = true) const;

    Format isValid(String content) const;
};

} // namespace obotcha
#endif
