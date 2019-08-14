#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpDate.hpp"
#include "DateTimeFormatter.hpp"
#include "DateTime.hpp"

namespace obotcha {

_HttpDate::_HttpDate(DateTime t) {
    mDate = t;
}
    
String _HttpDate::genHtml() {
    return st(DateTimeFormatter)::format(mDate,DateTimeFormatHTTP);
}

}
