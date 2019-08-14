#ifndef __DATE_TIME_PARSER_HPP__
#define __DATE_TIME_PARSER_HPP__

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


DECLARE_SIMPLE_CLASS(DateTimeParser) {
public:
    static DateTime parse(int type,String);
    static DateTime parse(String);

private:
    static int parseMonth(std::string::const_iterator& it, const std::string::const_iterator& end);
    static int parseAMPM(std::string::const_iterator& it, const std::string::const_iterator& end, int hour);
    static int parseTZD(std::string::const_iterator& it, const std::string::const_iterator& end);
};

}
#endif
