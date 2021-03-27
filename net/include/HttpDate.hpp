#ifndef __OBOTCHA_HTTP_DATE_HPP__
#define __OBOTCHA_HTTP_DATE_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpDate.hpp"
#include "DateTime.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpDate) {

public:
    _HttpDate(DateTime);
    _HttpDate(String);
    
    String toString();

private:
    DateTime mDate;
};

}

#endif
