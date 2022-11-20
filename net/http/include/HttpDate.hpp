#ifndef __OBOTCHA_HTTP_DATE_HPP__
#define __OBOTCHA_HTTP_DATE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "DateTime.hpp"

namespace obotcha {

DECLARE_CLASS(HttpDate) {

public:
    _HttpDate(DateTime);
    _HttpDate(String);
    
    String toString();
    DateTime toDateTime();

private:
    DateTime mDate;
};

}

#endif
