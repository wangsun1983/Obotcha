#include "HttpDate.hpp"

namespace obotcha {

_HttpDate::_HttpDate(DateTime t):mDate(t) {
}

_HttpDate::_HttpDate(String date) { 
    mDate = createDateTime(date); 
}

String _HttpDate::toString() {
    return mDate->toString(st(DateTime)::Format::HTTP);
}

DateTime _HttpDate::toDateTime() {
    return mDate;
}

} // namespace obotcha
