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

DECLARE_SIMPLE_CLASS(DateTimeFormatter) {
public:
    static String format(DateTime,int type,int timeZoneDifferential = 0xFFFF);
    static int isValid(String content);
    static int isValid(String fmt,String content);

private:
    static void tzdISO(std::string& str, int timeZoneDifferential);
    static void tzdRFC(std::string& str, int timeZoneDifferential);
};

}
#endif
