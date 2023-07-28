#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "DateTime.hpp"
#include "HashMap.hpp"
#include "HttpDate.hpp"
#include "String.hpp"

namespace obotcha {

_HttpDate::_HttpDate(DateTime t):mDate(t) {
}

_HttpDate::_HttpDate(String date) { 
    mDate = createDateTime(date); 
}

String _HttpDate::toString() {
    return mDate->toString(st(DateTime)::FormatHTTP);
}

DateTime _HttpDate::toDateTime() {
    return mDate;
}

} // namespace obotcha
